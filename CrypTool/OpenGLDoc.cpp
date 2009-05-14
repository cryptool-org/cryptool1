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

// OpenGLDoc.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "OpenGLDoc.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLDoc

IMPLEMENT_DYNCREATE(COpenGLDoc, CDocument)

COpenGLDoc::COpenGLDoc()
{
	volume = NULL;
	this->setResolution(128);
	this->setDensity(127);
	this->setShift(50);
	this->setVoxelSize(1);
	this->setWordLen(4);
	strcpy(sFile, "");

}

COpenGLDoc::COpenGLDoc(int arg_resolution, int arg_density, int arg_shift, int arg_wordlen)
{
	volume = NULL;
	this->setResolution(arg_resolution);
	this->setDensity(arg_density);
	this->setShift(arg_shift);
	this->setVoxelSize(1);
	this->setWordLen(arg_wordlen);
	strcpy(sFile, "");
}

BOOL COpenGLDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

COpenGLDoc::~COpenGLDoc()
{
	if (volume != NULL)
		delete volume;
}


BEGIN_MESSAGE_MAP(COpenGLDoc, CDocument)
	//{{AFX_MSG_MAP(COpenGLDoc)
		// HINWEIS - Der Klassen-Assistent fügt hier Zuordnungsmakros ein und entfernt diese.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose COpenGLDoc

#ifdef _DEBUG
void COpenGLDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COpenGLDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Serialisierung COpenGLDoc 

void COpenGLDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Code zum Speichern hier einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Code zum Laden hier einfügen

		char name[1024];
		strcpy(name, ar.m_strFileName);
		ifstream f;
		f.open(name);
		if (!f.is_open())
		{
			// FIXME Error
		}
		else
		{
			char sMagic[128];
			f.getline(sMagic, 128);
			f.getline(sFile, 1024);
			if ( strncmp(sMagic,"OPENGL", 6) )
			{
				// FIXME: ERROR
			}
			else
			{
				this->createVolumeData();
			}
		}
	}
}



void COpenGLDoc::setResolution(int arg)
{
	resolution = arg;
	nResolution[0] = resolution;
	nResolution[1] = resolution;
	nResolution[2] = resolution;
}

void COpenGLDoc::setShift(int arg)
{
	shift = arg;
}

void COpenGLDoc::setDensity(int arg)
{
	density = arg;
}

void COpenGLDoc::setVoxelSize(double arg)
{
	voxelsize = arg;
	dVoxelSize[0] = voxelsize;
	dVoxelSize[1] = voxelsize;
	dVoxelSize[2] = voxelsize;
}


void COpenGLDoc::setWordLen(int arg)
{
	wordlen = arg;
}


int COpenGLDoc::getResolution()
{
	return resolution;
}

int COpenGLDoc::getDensity()
{
	return density;
}

int COpenGLDoc::getShift()
{
	return shift;
}


double COpenGLDoc::getVoxelSize()
{
	return voxelsize;
}

int COpenGLDoc::getWordLen()
{
	return wordlen;
}


/////////////////////////////////////////////////////////////////////////////
// Befehle COpenGLDoc 

// analyze file (prepare volume data for renderer)
bool COpenGLDoc::createVolumeData()
{
	if (strcmp(sFile, "") == 0) {
		// no file set yet
		return false;
	}


	unsigned int numVals = resolution * resolution * resolution;

	if (volume != NULL)
		delete volume;
	volume = new StreamToVolume (resolution, resolution, resolution);

	int shiftpixels = (resolution * shift) / 100;
	if (shiftpixels < 0) shiftpixels = 0;
	if (shiftpixels > resolution) shiftpixels = resolution;

	volume->setWordLen(wordlen);
	volume->setDensity(density);
	volume->setShift(shiftpixels, shiftpixels, shiftpixels);
	volume->analyzeFile(sFile);

	return true;
}
