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

// StreamToVolume.h: Schnittstelle für die Klasse StreamToVolume.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STREAMTOVOLUME_H__8BCC1637_0F0B_4996_90A4_4385E48FD921__INCLUDED_)
#define AFX_STREAMTOVOLUME_H__8BCC1637_0F0B_4996_90A4_4385E48FD921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

union FourByteValue {
	unsigned char OneByte;
	unsigned short TwoByte;
	unsigned int FourByte;
};

const unsigned int mode_AutoDensity = 1;


class StreamToVolume  
{
public:
	// constructor requires cube dimensions
	StreamToVolume(int dimx, int dimy, int dimz);
	virtual ~StreamToVolume();

	// specify analysis parameters
	int setDensity(int d);
	int setShift(int x, int y, int z);
	int setWordLen(int w);

	// clear volume
	void clear();
	
	// analysis interface, may be called more than once to populate the cube	
	// analyze the specified file
	int analyzeFile(char* filename);
	int analyzeFile(char* filename, unsigned int mode);

	// analyze the specified memory section
	int analyzeBuf(unsigned char* buffer, unsigned int size);

	// get a pointer to the initialized volume memory structure
	unsigned char* getVolume();

private:
	unsigned char* voxelBuffer;
	int dim[3];
	int shift[3];

	unsigned int sampleBytes;
	unsigned int density;

	// temporary voxel buffer
	unsigned int voxel[3];
	unsigned int voxelIndex;
};


#endif // !defined(AFX_STREAMTOVOLUME_H__8BCC1637_0F0B_4996_90A4_4385E48FD921__INCLUDED_)
