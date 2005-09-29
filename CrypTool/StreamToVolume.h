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
