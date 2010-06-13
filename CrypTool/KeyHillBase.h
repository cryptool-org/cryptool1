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

#pragma once

#include "afxwin.h"
#include "SquareMatrixModN.h"

#define DIM_DLG_HILL_5x5	5
#define DIM_DLG_HILL_10x10	10

#define DLG_HILL_5x5       0x10
#define DLG_HILL_10x10     0x20
#define HILL_RANGE         10

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill5x5 

class CHiEdit : public CEdit
{
protected:
	//{{AFX_MSG(CHiEdit)
	afx_msg void OnLButtonUp(UINT, CPoint);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
};

enum HillEditType { HILL_CHAR_MATRIX, HILL_NUM_MATRIX };
enum HillMultType { VECTOR_MATRIX, MATRIX_VECTOR };

class CKeyHillBase {
   CHiEdit           **HillNumMat;
	CEdit             **HillAlphMat;
	CSquareMatrixModN  *HillMat;
   CDialog            *currentDialog;

	// HILL parameter
	unsigned long   alphabetOffset;
	unsigned long   max_dim, dim, key_range;
	HillEditType    matType;
	HillMultType    multType; 
	unsigned long   cryptMode;

	friend class CDlgKeyHill5x5;
	friend class CDlgKeyHill10x10;

	// Select Matrix
	void setMatFont();
	void activateMatrix     ( CEdit **mat );
	void deactivateMatrix   ( CEdit **mat ); 
	void selectActMatrix    ( );
	void selectHillDimension( unsigned long new_dim );
	void selectMatType      ( HillEditType new_type );
	void selectMultType     ( HillMultType new_type );

	void syncNumAlph ( unsigned long i, unsigned long j );
	void syncAlphNum ( unsigned long i, unsigned long j );
	void formatNum   ( unsigned long i, unsigned long j );

	int  validEntries();
	int  isInvertable();

	void pasteKey();
	void copyKey();
	void readRegistry();
	void writeRegistry();
	void randomKey();
	void SetHillMatrix ( CSquareMatrixModN *mat );
	void loadHillMatrix( CSquareMatrixModN& mat );

public:
	int ord( const char ch );
	CKeyHillBase(unsigned long p_keyRange);
	~CKeyHillBase();
   int run( int currDlg = DLG_HILL_5x5 ); 
};

