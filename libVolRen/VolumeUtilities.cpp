// VolumeUtilities.cpp: implementation of the VolumeUtilities class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VolumeUtilities.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void VolumeUtilities::convertUSHORTtoUCHAR_Linear(
	const unsigned short *pReadBuffer, 
	unsigned char *pWriteBuffer, 
	unsigned long nNumValues) 
{
	unsigned long i;

	unsigned short nDataMax = pReadBuffer[0];
	unsigned short nDataMin = pReadBuffer[0];

	for(i = 1; i < nNumValues; i++) {
		if (pReadBuffer[i] > nDataMax) nDataMax = pReadBuffer[i];
		if (pReadBuffer[i] < nDataMin) nDataMin = pReadBuffer[i];
	}

	double dDataMapping = 255.0 / double(nDataMax - nDataMin);
	
	for(i = 0; i < nNumValues; i++) {
		pWriteBuffer[i] = (unsigned char) ( double(pReadBuffer[i]-nDataMin) * dDataMapping);
	}

}


void VolumeUtilities::getMappingTableUSHORTtoUCHAR_Linear(
	const unsigned short *pReadBuffer, 
	unsigned char *pMapTable, 
	unsigned long nNumValues) 
{
	unsigned long i;

	unsigned short nDataMax = pReadBuffer[0];
	unsigned short nDataMin = pReadBuffer[0];

	for(i = 1; i < nNumValues; i++) {
		if (pReadBuffer[i] > nDataMax) nDataMax = pReadBuffer[i];
		if (pReadBuffer[i] < nDataMin) nDataMin = pReadBuffer[i];
	}

	double dDataMapping = 255.0 / double(nDataMax - nDataMin);
	
	memset(pMapTable, 0, nDataMin * sizeof(unsigned char));
	memset(pMapTable + nDataMax, 255, (65536-nDataMax) * sizeof(unsigned char));

	for(i = nDataMin; i < nDataMax; i++) {
		pMapTable[i] = (unsigned char) ( double(i-nDataMin) * dDataMapping);
	}
}

void VolumeUtilities::convertUSHORTtoUCHAR_HistLinear(
	const unsigned short *pReadBuffer, 
	unsigned char *pWriteBuffer, 
	unsigned long nNumValues) 
{

	unsigned int i;

	unsigned char pMapTable[65536];

	getMappingTableUSHORTtoUCHAR_HistLinear(pReadBuffer, pMapTable, nNumValues);

	for(i = 0; i < nNumValues; i++) {
		pWriteBuffer[i] = pMapTable[pReadBuffer[i]];
	}
}


void VolumeUtilities::getMappingTableUSHORTtoUCHAR_HistLinear(
	const unsigned short *pReadBuffer, 
	unsigned char *pMapTable, 
	unsigned long nNumValues) 
{

	unsigned long i;
	// calculate the histogram
	unsigned long pHistogram[65536];
	memset(pHistogram,0,65536*sizeof(unsigned long));
	for(i = 0; i < nNumValues; i++) {
		pHistogram[pReadBuffer[i]]++;
	}

	// calculate the mapping table for histogram linearization
	unsigned long nThreshold = nNumValues/256;

	unsigned char nUCHARvalue = 0;
	unsigned long nCount = 0;

	int nNumSamples = nNumValues;

	for(i = 0; i < 65536; i++) {

		pMapTable[i] = nUCHARvalue;

		nCount += pHistogram[i];
		if (nCount > nThreshold) {
			nUCHARvalue++;
			nNumSamples -= nCount;
			nThreshold = int( double(nNumSamples)/ (256.0-double(nUCHARvalue)) );
			nCount = 0;
		} 
	}

	return;

}
