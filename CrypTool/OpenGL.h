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

#if !defined(AFX_OPENGL_H__34EC9E69_B426_4DC4_8F61_7DEEC99D79D1__INCLUDED_)
#define AFX_OPENGL_H__34EC9E69_B426_4DC4_8F61_7DEEC99D79D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGL.h : header file
//

// #include "StreamToVolume.h"
#include "CrypToolVolRen.h"
// #include "VolumeUtilities.h"

/////////////////////////////////////////////////////////////////////////////
// COpenGL window

class COpenGL : public CWnd
{
// Construction
	CCrypToolVolRen *m_pVolumeRenderer;
public:
	COpenGL();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGL)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COpenGL();

	// Generated message map functions
protected:
	//{{AFX_MSG(COpenGL)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGL_H__34EC9E69_B426_4DC4_8F61_7DEEC99D79D1__INCLUDED_)
