/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

// StreamToVolume.cpp: Implementierung der Klasse StreamToVolume.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StreamToVolume.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////


StreamToVolume::StreamToVolume(int dimx, int dimy, int dimz)
{
	voxelBuffer = NULL;

	sampleBytes = 4;
	density = 127;
	voxelIndex = 0;
	
	if (! (dimx < 0 ||
			dimx > 255 ||
			dimy < 0 ||
			dimy > 255 ||
			dimz < 0 ||
			dimz > 255))
	{
		short jj;

		dim[0] = dimx;
		dim[1] = dimy;
		dim[2] = dimz;

		for (jj = 0; jj < 3; jj++) {
			shift[jj] = dim[jj] / 2;
			voxel[jj] = 0;
		}

		voxelBuffer = new unsigned char [dimx * dimy * dimz];

		this->clear();
	}

	// voxelBuffer is NULL on parameter error
}


int StreamToVolume::setDensity(int d)
{
	density = d;
	return true;
}

int StreamToVolume::setShift(int x, int y, int z)
{
	if ((abs(x) > dim[0] / 2) || (abs(y) > dim[1] / 2) || (abs(z) > dim[2] / 2)) return false;
	
	shift[0] = x;
	shift[1] = y;
	shift[2] = z;
	return true;
}

int StreamToVolume::setWordLen(int w)
{
	if ((w != 1) && (w != 2) && (w != 4)) return false;
	sampleBytes = w;
	return true;
}


// clear volume
void StreamToVolume::clear()
{
	if (voxelBuffer)
		memset(voxelBuffer, 0, dim[0] * dim[1] * dim[2]);
}


// analyze the specified file
int StreamToVolume::analyzeFile(char *filename)
{
	CFile file;
	int bufsize = 0;
	unsigned char* buffer;
	unsigned int read;
	int rc;

	if (!voxelBuffer) return false;

	bufsize = sampleBytes * 32768;
	buffer = new unsigned char [bufsize];
	if (! buffer) return false;

	if(!file.Open( filename, CFile::modeRead | CFile::typeBinary))
	{
		delete[] buffer;
		return false;
	}

	rc = true;
	while(rc && (read = file.Read(buffer, bufsize)))
	{
		rc = analyzeBuf(buffer, read);
	}
	file.Close();

	delete[] buffer;
	return rc;
}


// analyze the specified file
int StreamToVolume::analyzeFile(char *filename, unsigned int mode)
{
	if ((mode & mode_AutoDensity) != 0) {
		// get input file size
		__int64 filesize = 0;
		CFile rawfile;
		if(!rawfile.Open(filename,CFile::modeRead | CFile::typeBinary )) {
			return false;
		}
		filesize = (__int64)rawfile.GetLength();
		rawfile.Close();

		// compute display density
		double ratio = dim[0] * dim[1] * dim[2]/ (filesize / sampleBytes + 1.0);  // prevent division by zero
		// compute an integer between 0 and 3 inclusive from this ratio
		int exp = (int) ratio * 2;
		if (exp < 0) exp = 0;
		if (exp > 3) exp = 3;

		this->setDensity((1 << (exp + 5)) - 1);
	}
		
	return this->analyzeFile(filename);
}



// analyze the specified memory section
// buffer: pointer to data
// size: length in bytes, must be dividible by sampleBytes
int StreamToVolume::analyzeBuf(unsigned char* buffer, unsigned int size)
{
	unsigned int ii;
	short jj;
	__int64 tmp64;
	unsigned int scale[3];

	if (!voxelBuffer) return false;
	if (size % sampleBytes != 0) return false;

	// scale factor to apply in order to bring resulting coordinates into dimx/dimy/dimz range
	for (jj = 0; jj < 3; jj++) {
		// left shift operator only works with 
		// 32 bit, so leave out the last 8 bit and multiply by 256 afterwards
		// similar to: (1 << (sampleBytes * 8)); (which won't work on 32 bit processors)
		tmp64 = (__int64)((int)1 << ((sampleBytes - 1) * 8));  // don't optimize
		tmp64 *= 256;                            // this into one line!
		scale[jj] = (unsigned int) (tmp64 / dim[jj]);

		if (scale[jj] < 1)
			scale[jj] = 1;
	}

	ii = 1; // not 0
	while (ii * sampleBytes < size)
	{
		FourByteValue* val1 = (FourByteValue*) &buffer[sampleBytes * ii];
		FourByteValue* val2 = (FourByteValue*) &buffer[sampleBytes * (ii - 1)];

		switch (sampleBytes)
		{
			case 1:
				voxel[voxelIndex] = (unsigned char) ((unsigned char) val1->OneByte - 
													 (unsigned char) val2->OneByte +
													 (unsigned char) shift[voxelIndex] * scale[voxelIndex]
													);
				break;
			case 2:
				voxel[voxelIndex] = (unsigned short) ((unsigned short) val1->TwoByte - 
													  (unsigned short) val2->TwoByte +
 													  (unsigned short) shift[voxelIndex] * scale[voxelIndex]
													);
				break;
			case 4:
				voxel[voxelIndex] = (unsigned int) ((unsigned int) val1->FourByte - 
					                                (unsigned int) val2->FourByte +
												    (unsigned int) shift[voxelIndex] * scale[voxelIndex]
													);
				break;
		}

		voxelIndex = (voxelIndex + 1) % 3;

		if (voxelIndex == 0)
		{
			// voxel now contains a 3d coordinate. the coordinate must now be trimmed to fit into the 3d buffer.
			unsigned int addr = 0;
			unsigned int offset = 1;
			for (jj = 0; jj < 3; jj++) {
				voxel[jj] /= scale[jj];
				// plot point
				if (voxel[jj] >= (unsigned int) dim[jj])
					voxel[jj] = dim[jj] - 1;
				addr += voxel[jj] * offset;
				offset *= dim[jj];
			}
			
			if (voxelBuffer[addr] + density > voxelBuffer[addr])
				voxelBuffer[addr] += density;
		}
		ii++;
	}


	return true;	
}


unsigned char* StreamToVolume::getVolume()
{
	return voxelBuffer;
}


StreamToVolume::~StreamToVolume()
{
	if (voxelBuffer)
		delete[] voxelBuffer;
}
