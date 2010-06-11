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

//////////////////////////////////////////////////////////////////
// Autor: Jens Liebehenschel
//////////////////////////////////////////////////////////////////
// HillEingabe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKeyHill5x5.h"
#include "HillEncryption.h"
#include "ChrTools.h"
#include "KeyRepository.h"
#include "DlgHillOptions.h"
#include "CrypToolTools.h"
#include "assert.h"

/////////////////////////////////////////////////////////////////////////////
//
CDlgKeyHillBaseFunctions::CDlgKeyHillBaseFunctions(unsigned long keyRange) :
	HillMat(0),
	alphabetOffset(0),
	max_dim(keyRange),
	dim(1),
	matType(HILL_CHAR_MATRIX), 
	multType(VECTOR_MATRIX),
	cryptMode(0)
{
	HillNumMat  = new CHiEdit*[max_dim+1];
	HillAlphMat = new CEdit*  [max_dim];
	for ( unsigned long i=0; i<keyRange; i++ )
	{
		HillNumMat[i]  = new CHiEdit[max_dim];
		HillAlphMat[i] = new CEdit[max_dim];
	}
}

CDlgKeyHillBaseFunctions::~CDlgKeyHillBaseFunctions()
{
	for ( unsigned long i=0; i<max_dim; i++ )
	{
		delete []HillNumMat[i];
		delete []HillAlphMat[i];
	}
	delete []HillNumMat;
	delete []HillAlphMat;
}

int CDlgKeyHillBaseFunctions::ord( const char ch )
{
	for(int i=0;i<theApp.TextOptions.getAlphabet().GetLength();i++)
		if( theApp.TextOptions.getAlphabet()[i] == ch ) return i + alphabetOffset;

	return -1;
}

void CDlgKeyHillBaseFunctions::syncAlphNum( unsigned long i, unsigned long j )
{
	if( matType == HILL_CHAR_MATRIX )
	{
		CString cs;
		HillAlphMat[i][j].GetWindowText(cs);

		// QUICK FIX: if user supplied MORE THAN ON CHARACTER, for example by using 
		// the copy/paste mechanism, throw away all characters except the first one
		if(cs.GetLength() > 1) {
			cs.Delete(1, cs.GetLength() - 1);
		}

		if (cs.GetLength() == 1 )
		{
			if ( ord(cs[0]) >= 0 )
			{
				CString str;
				str.Format("%02d", ord(cs[0]) );
				HillNumMat[i][j].SetWindowText(str);
				// FIXME NextDlgCtrl();
			}
			else if ( theApp.TextOptions.getIgnoreCase() 
				      && MyIsLower(cs[0]) &&  ord(MyToUpper(cs[0])) >= 0 )
			{
				cs.SetAt(0,MyToUpper(cs[0]));
			}
			else
			{
				cs.Empty();
			}
			HillAlphMat[i][j].SetWindowText( cs );
		}
	}
}

void CDlgKeyHillBaseFunctions::formatNum( unsigned long i, unsigned long j )
{
	CString cs;
	HillNumMat[i][j].GetWindowText(cs);
	if(cs.GetLength() == 1)
	{
		int ord = _ttoi(cs);
		if( ord < (int)alphabetOffset || ord > theApp.TextOptions.getAlphabet().GetLength() + (int)alphabetOffset )
		{
			cs.Empty();
			HillNumMat[i][j].SetWindowText(cs);
		}
		else
		{
			cs.Insert(0,"0");
			HillNumMat[i][j].SetWindowText(cs);
		}
		// FIXME PrevDlgCtrl(); //because Tab and UpdateFeld makes both NextDlgCtrl
	}
}

void CDlgKeyHillBaseFunctions::syncNumAlph( unsigned long i, unsigned long j )
{
	if( matType == HILL_NUM_MATRIX )
	{
		CString cs;
		HillNumMat[i][j].GetWindowText(cs);

		if(cs.GetLength() == 2)
		{
			int ord = _ttoi(cs); 
			if( ord < (int)alphabetOffset || ord > theApp.TextOptions.getAlphabet().GetLength() + (int)alphabetOffset )
			{
				cs.Empty();
				HillNumMat[i][j].SetWindowText(cs);
			}
			else
			{
				HillAlphMat[i][j].SetWindowText( CString(theApp.TextOptions.getAlphabet()[ord - alphabetOffset]) ); 
				// FIXME NextDlgCtrl();
			}
		}
	}
}

int CDlgKeyHillBaseFunctions::validEntries()
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	unsigned long i, j;
	CString cs;
	for (i=0; i<dim; i++)
		for (j=0; j<dim; j++)
		{
			HillAlphMat[i][j].GetWindowText(cs);
			if ( (cs.GetLength() != 1) || 0 > ord(cs[0]) )
			{
				CString msg;
				msg.LoadStringA( IDS_HILL_BAD_KEY_NONVALID_CHAR );
				cs.LoadStringA ( IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED );
				// FIXME: MessageBox(msg, cs, MB_ICONWARNING|MB_OK);

				return FALSE;
			}
		}

	return TRUE;
}

int  CDlgKeyHillBaseFunctions::isInvertable()
{
	if ( !validEntries() )
		return 0;

	unsigned long modul = theApp.TextOptions.getAlphabet().GetLength();
	CSquareMatrixModN *mat, *mat_inv;

	mat		= new CSquareMatrixModN( dim, modul );
	mat_inv	= new CSquareMatrixModN( dim, modul );

	SetHillMatrix( mat );

	int invertable = mat->invert(mat_inv);
	if ( !invertable )
	{
		CString msg, cs;
		cs.FormatMessageA( "%dx%d", dim, dim );
		msg.FormatMessageA( IDS_HILL_BAD_KEY_INV, cs, modul);
		cs.LoadStringA( IDS_HILL_BAD_KEY );
		// FIXME MessageBox(msg, cs, MB_ICONWARNING|MB_OK);
	}

	delete mat;
	delete mat_inv;

	return invertable;
}

void CDlgKeyHillBaseFunctions::loadHillMatrix(CSquareMatrixModN& mat)
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM) && (mat.get_dim() == dim) );
	unsigned long modul = theApp.TextOptions.getAlphabet().GetLength();

	CString cs;
	unsigned long i, j;
	for (i=0; i<dim; i++)
		for (j=0; j<dim; j++)
		{
			HillAlphMat[i][j].GetWindowText(cs);
			ASSERT( 0 >= ord( cs[0] ) );
			mat(i,j) = ord(cs[0]);
		}
}

void CDlgKeyHillBaseFunctions::activateMatrix  ( CEdit **mat )
{
	unsigned long i, j;
	for ( i=0; i<dim; i++ )
		for ( j=0; j<dim; j++ )
			mat[i][j].EnableWindow( TRUE );
}

void CDlgKeyHillBaseFunctions::deactivateMatrix( CEdit **mat )
{
	unsigned long i, j;
	for ( i=0; i<max_dim; i++ )
		for ( j=0; j<max_dim; j++ )
			mat[i][j].EnableWindow( FALSE );
}

void CDlgKeyHillBaseFunctions::selectActMatrix ()
{
	deactivateMatrix( (CEdit**)HillNumMat );
	deactivateMatrix( HillAlphMat );
	if ( matType == HILL_CHAR_MATRIX ) // Alphabet
	{
		 activateMatrix( HillAlphMat );
		 HillAlphMat[0][0].SetFocus();
		 HillAlphMat[0][0].SetSel(0, -1);
	}
	else
	{
		 activateMatrix( HillAlphMat );
		 HillNumMat[0][0].SetFocus();
		 HillNumMat[0][0].SetSel(0, -1);
	}
}

void CDlgKeyHillBaseFunctions::selectHillDimension( unsigned long new_dim )
{
	assert( 1 <= new_dim && new_dim <= max_dim );
	dim = new_dim;
	selectActMatrix();
}

void CDlgKeyHillBaseFunctions::selectMatType( HillEditType new_type )
{
	matType = new_type;
	selectActMatrix();
}

void CDlgKeyHillBaseFunctions::selectMultType( HillMultType new_type )
{
	multType = new_type;
}

void CDlgKeyHillBaseFunctions::setMatFont()
{
	CFont cf;
	cf.CreatePointFont(80,"Courier");
	unsigned long i, j;
	for ( i=0; i<max_dim; i++)
	{
		for ( j=0; j<max_dim; j++)
		{
			HillAlphMat[i][j].SetFont(&cf);
			HillNumMat[i][j].SetFont(&cf);
		}
	}
}

void CDlgKeyHillBaseFunctions::pasteKey()
{
	CString cs;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);

	if ( PasteKey(pc_str,cs) )
	{
		int l = 0, laenge = cs.Find(HILLSTR_ALPHABETOFFSET);
		unsigned long i = 0, j, _dim = 0;

		while (l<laenge) if ( 0 <= ord( cs[l++] ) ) i++;
		if ( i <= max_dim*max_dim )
		{	
			i = j = l = 0;
 			while (l < laenge)
 			{
				if ( 0 <= ord(cs[l]) )
					HillAlphMat[i][j++].SetWindowTextA( CString(cs[l]) );
				else 
				{
					assert( i < _dim );			// FIXME
					assert( cs[l] == '\n' );	// FIXME 
					if ( _dim > 0 ) 
					{
						if ( _dim != j )
							assert( 0 );		// FIXME 
					}
					else
					{
						if ( j > max_dim )
							assert( 0 );		// FIXME 
						_dim = j;
					}
					i++;
					j = 0;
				}
				l++;
 			}
			dim = _dim;

			laenge += strlen(HILLSTR_ALPHABETOFFSET) +1;
			alphabetOffset = unsigned long(cs.GetAt(laenge) - '0');
			laenge = cs.Find(HILLSTR_MULTVARIANT);
			ASSERT(laenge > 0);
			laenge += strlen(HILLSTR_MULTVARIANT) +1;
			multType = (cs.GetAt(laenge) == '0') ? VECTOR_MATRIX : MATRIX_VECTOR;
		}
 		else
		{  
			// FIXME -- Message ... the stored Hill Key ...
		}
	}
}

void CDlgKeyHillBaseFunctions::copyKey()
{

}

void CDlgKeyHillBaseFunctions::SetHillMatrix( CSquareMatrixModN *mat )
{
	unsigned long i, j;
	for ( i=0; i<max_dim; i++ )
		for ( j=0; j<max_dim; j++ )
			if ( i<dim && j<dim )
			{  // FIXME 
				HillAlphMat[i][j].SetWindowTextA( CString( char('A' + (*mat)(i,j) - alphabetOffset)) );
				syncAlphNum(i,j);
			}
			else
			{
				HillAlphMat[i][j].SetWindowTextA( _T("") );
				HillNumMat[i][j].SetWindowTextA(_T(""));
			}
}

void CDlgKeyHillBaseFunctions::randomKey()
{
	CSquareMatrixModN mat( dim, theApp.TextOptions.getAlphabet().GetLength() );
	if (mat.zufaellige_invertierbare_matrix())
		SetHillMatrix( &mat );
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ON_WRONG_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		// FIXME: MessageBox(pc_str, NULL, MB_ICONERROR|MB_OK);
	}
}

void CDlgKeyHillBaseFunctions::readRegistry()
{
	unsigned long _matType = (unsigned long)HILL_CHAR_MATRIX;
	alphabetOffset = 0;
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		CT_READ_REGISTRY_DEFAULT(alphabetOffset, "OrdChrOffset", alphabetOffset);
		CT_READ_REGISTRY_DEFAULT(_matType,"EditKeyChrMatrix", _matType);
		matType = (HillEditType)_matType;
		CT_CLOSE_REGISTRY();
	}

}

void CDlgKeyHillBaseFunctions::writeRegistry()
{
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(alphabetOffset), "OrdChrOffset");
		CT_WRITE_REGISTRY(unsigned long(matType),		 "EditKeyChrMatrix");
		CT_CLOSE_REGISTRY();
	}
}

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHill5x5 

CDlgKeyHill5x5::CDlgKeyHill5x5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKeyHill5x5::IDD, pParent)
	, m_HillBase(0) // FIXME
	, m_pHillAlphInfo(_T(""))
	, m_Verbose(FALSE)
{
}

CDlgKeyHill5x5::~CDlgKeyHill5x5()
{
}

void CDlgKeyHill5x5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
// HillAlphMat
	DDX_Control(pDX, IDC_EDIT11, m_HillBase->HillAlphMat[0][0] );
	DDX_Control(pDX, IDC_EDIT12, m_HillBase->HillAlphMat[0][1] );
	DDX_Control(pDX, IDC_EDIT13, m_HillBase->HillAlphMat[0][2] );
	DDX_Control(pDX, IDC_EDIT14, m_HillBase->HillAlphMat[0][3] );
	DDX_Control(pDX, IDC_EDIT15, m_HillBase->HillAlphMat[0][4] );
	DDX_Control(pDX, IDC_EDIT21, m_HillBase->HillAlphMat[1][0] );
	DDX_Control(pDX, IDC_EDIT22, m_HillBase->HillAlphMat[1][1] );
	DDX_Control(pDX, IDC_EDIT23, m_HillBase->HillAlphMat[1][2] );
	DDX_Control(pDX, IDC_EDIT24, m_HillBase->HillAlphMat[1][3] );
	DDX_Control(pDX, IDC_EDIT25, m_HillBase->HillAlphMat[1][4] );
	DDX_Control(pDX, IDC_EDIT31, m_HillBase->HillAlphMat[2][0] );
	DDX_Control(pDX, IDC_EDIT32, m_HillBase->HillAlphMat[2][1] );
	DDX_Control(pDX, IDC_EDIT33, m_HillBase->HillAlphMat[2][2] );
	DDX_Control(pDX, IDC_EDIT34, m_HillBase->HillAlphMat[2][3] );
	DDX_Control(pDX, IDC_EDIT35, m_HillBase->HillAlphMat[2][4] );
	DDX_Control(pDX, IDC_EDIT41, m_HillBase->HillAlphMat[3][0] );
	DDX_Control(pDX, IDC_EDIT42, m_HillBase->HillAlphMat[3][1] );
	DDX_Control(pDX, IDC_EDIT43, m_HillBase->HillAlphMat[3][2] );
	DDX_Control(pDX, IDC_EDIT44, m_HillBase->HillAlphMat[3][3] );
	DDX_Control(pDX, IDC_EDIT45, m_HillBase->HillAlphMat[3][4] );
	DDX_Control(pDX, IDC_EDIT51, m_HillBase->HillAlphMat[4][0] );
	DDX_Control(pDX, IDC_EDIT52, m_HillBase->HillAlphMat[4][1] );
	DDX_Control(pDX, IDC_EDIT53, m_HillBase->HillAlphMat[4][2] );
	DDX_Control(pDX, IDC_EDIT54, m_HillBase->HillAlphMat[4][3] );
	DDX_Control(pDX, IDC_EDIT55, m_HillBase->HillAlphMat[4][4] );

// HillNumMat
	DDX_Control(pDX, IDC_EDIT36,  m_HillBase->HillNumMat[0][0] );
	DDX_Control(pDX, IDC_EDIT37,  m_HillBase->HillNumMat[0][1] );
	DDX_Control(pDX, IDC_EDIT38,  m_HillBase->HillNumMat[0][2] );
	DDX_Control(pDX, IDC_EDIT40,  m_HillBase->HillNumMat[0][3] );
	DDX_Control(pDX, IDC_EDIT46,  m_HillBase->HillNumMat[0][4] );
	DDX_Control(pDX, IDC_EDIT47,  m_HillBase->HillNumMat[1][0] );
	DDX_Control(pDX, IDC_EDIT48,  m_HillBase->HillNumMat[1][1] );
	DDX_Control(pDX, IDC_EDIT49,  m_HillBase->HillNumMat[1][2] );
	DDX_Control(pDX, IDC_EDIT50,  m_HillBase->HillNumMat[1][3] );
	DDX_Control(pDX, IDC_EDIT111, m_HillBase->HillNumMat[1][4] );
	DDX_Control(pDX, IDC_EDIT57,  m_HillBase->HillNumMat[2][0] );
	DDX_Control(pDX, IDC_EDIT58,  m_HillBase->HillNumMat[2][1] );
	DDX_Control(pDX, IDC_EDIT59,  m_HillBase->HillNumMat[2][2] );
	DDX_Control(pDX, IDC_EDIT56,  m_HillBase->HillNumMat[2][3] );
	DDX_Control(pDX, IDC_EDIT115, m_HillBase->HillNumMat[2][4] );
	DDX_Control(pDX, IDC_EDIT60,  m_HillBase->HillNumMat[3][0] );
	DDX_Control(pDX, IDC_EDIT61,  m_HillBase->HillNumMat[3][1] );
	DDX_Control(pDX, IDC_EDIT62,  m_HillBase->HillNumMat[3][2] );
	DDX_Control(pDX, IDC_EDIT116, m_HillBase->HillNumMat[3][3] );
	DDX_Control(pDX, IDC_EDIT117, m_HillBase->HillNumMat[3][4] );
	DDX_Control(pDX, IDC_EDIT63,  m_HillBase->HillNumMat[4][0] );
	DDX_Control(pDX, IDC_EDIT64,  m_HillBase->HillNumMat[4][1] );
	DDX_Control(pDX, IDC_EDIT69,  m_HillBase->HillNumMat[4][2] );
	DDX_Control(pDX, IDC_EDIT65,  m_HillBase->HillNumMat[4][3] );
	DDX_Control(pDX, IDC_EDIT66,  m_HillBase->HillNumMat[4][4] );

	DDX_Check(pDX, IDC_CHECK1, m_Verbose);
	DDX_Control(pDX, IDC_EDIT1, m_FeldUnsichtbar);
	DDX_Text(pDX, IDC_EDIT3, m_pHillAlphInfo);
	DDX_Text(pDX, IDC_EDIT2, m_alphabetOffset);
	DDV_MinMaxInt(pDX, m_alphabetOffset, 0, 1);
}


BEGIN_MESSAGE_MAP(CDlgKeyHill5x5, CDialog)
	//{{AFX_MSG_MAP(CDlgKeyHill5x5)

// HillAlphMat
	ON_EN_UPDATE(IDC_EDIT11, OnUpdateMat11)
	ON_EN_UPDATE(IDC_EDIT12, OnUpdateMat12)
	ON_EN_UPDATE(IDC_EDIT13, OnUpdateMat13)
	ON_EN_UPDATE(IDC_EDIT14, OnUpdateMat14)
	ON_EN_UPDATE(IDC_EDIT15, OnUpdateMat15)
	ON_EN_UPDATE(IDC_EDIT21, OnUpdateMat21)
	ON_EN_UPDATE(IDC_EDIT22, OnUpdateMat22)
	ON_EN_UPDATE(IDC_EDIT23, OnUpdateMat23)
	ON_EN_UPDATE(IDC_EDIT24, OnUpdateMat24)
	ON_EN_UPDATE(IDC_EDIT25, OnUpdateMat25)
	ON_EN_UPDATE(IDC_EDIT31, OnUpdateMat31)
	ON_EN_UPDATE(IDC_EDIT32, OnUpdateMat32)
	ON_EN_UPDATE(IDC_EDIT33, OnUpdateMat33)
	ON_EN_UPDATE(IDC_EDIT34, OnUpdateMat34)
	ON_EN_UPDATE(IDC_EDIT35, OnUpdateMat35)
	ON_EN_UPDATE(IDC_EDIT41, OnUpdateMat41)
	ON_EN_UPDATE(IDC_EDIT42, OnUpdateMat42)
	ON_EN_UPDATE(IDC_EDIT43, OnUpdateMat43)
	ON_EN_UPDATE(IDC_EDIT44, OnUpdateMat44)
	ON_EN_UPDATE(IDC_EDIT45, OnUpdateMat45)
	ON_EN_UPDATE(IDC_EDIT51, OnUpdateMat51)
	ON_EN_UPDATE(IDC_EDIT52, OnUpdateMat52)
	ON_EN_UPDATE(IDC_EDIT53, OnUpdateMat53)
	ON_EN_UPDATE(IDC_EDIT54, OnUpdateMat54)
	ON_EN_UPDATE(IDC_EDIT55, OnUpdateMat55)
// HillNumMat
	ON_EN_UPDATE(IDC_EDIT36, OnUpdateMat36)
	ON_EN_UPDATE(IDC_EDIT37, OnUpdateMat37)
	ON_EN_UPDATE(IDC_EDIT38, OnUpdateMat38)
	ON_EN_UPDATE(IDC_EDIT40, OnUpdateMat40)
	ON_EN_UPDATE(IDC_EDIT46, OnUpdateMat46)
	ON_EN_UPDATE(IDC_EDIT47, OnUpdateMat47)
	ON_EN_UPDATE(IDC_EDIT48, OnUpdateMat48)
	ON_EN_UPDATE(IDC_EDIT49, OnUpdateMat49)
	ON_EN_UPDATE(IDC_EDIT50, OnUpdateMat50)
	ON_EN_UPDATE(IDC_EDIT111, OnUpdateMat111)
	ON_EN_UPDATE(IDC_EDIT57, OnUpdateMat57)
	ON_EN_UPDATE(IDC_EDIT58, OnUpdateMat58)
	ON_EN_UPDATE(IDC_EDIT59, OnUpdateMat59)
	ON_EN_UPDATE(IDC_EDIT56, OnUpdateMat56)
	ON_EN_UPDATE(IDC_EDIT115, OnUpdateMat115)
	ON_EN_UPDATE(IDC_EDIT60, OnUpdateMat60)
	ON_EN_UPDATE(IDC_EDIT61, OnUpdateMat61)
	ON_EN_UPDATE(IDC_EDIT62, OnUpdateMat62)
	ON_EN_UPDATE(IDC_EDIT116, OnUpdateMat116)
	ON_EN_UPDATE(IDC_EDIT117, OnUpdateMat117)
	ON_EN_UPDATE(IDC_EDIT63, OnUpdateMat63)
	ON_EN_UPDATE(IDC_EDIT64, OnUpdateMat64)
	ON_EN_UPDATE(IDC_EDIT69, OnUpdateMat69)
	ON_EN_UPDATE(IDC_EDIT65, OnUpdateMat65)
	ON_EN_UPDATE(IDC_EDIT66, OnUpdateMat66)
	
	ON_EN_KILLFOCUS(IDC_EDIT36, OnExitMat36)
	ON_EN_KILLFOCUS(IDC_EDIT37, OnExitMat37)
	ON_EN_KILLFOCUS(IDC_EDIT38, OnExitMat38)
	ON_EN_KILLFOCUS(IDC_EDIT40, OnExitMat40)
	ON_EN_KILLFOCUS(IDC_EDIT46, OnExitMat46)
	ON_EN_KILLFOCUS(IDC_EDIT47, OnExitMat47)
	ON_EN_KILLFOCUS(IDC_EDIT48, OnExitMat48)
	ON_EN_KILLFOCUS(IDC_EDIT49, OnExitMat49)
	ON_EN_KILLFOCUS(IDC_EDIT50, OnExitMat50)
	ON_EN_KILLFOCUS(IDC_EDIT111, OnExitMat111)
	ON_EN_KILLFOCUS(IDC_EDIT57, OnExitMat57)
	ON_EN_KILLFOCUS(IDC_EDIT58, OnExitMat58)
	ON_EN_KILLFOCUS(IDC_EDIT59, OnExitMat59)
	ON_EN_KILLFOCUS(IDC_EDIT56, OnExitMat56)
	ON_EN_KILLFOCUS(IDC_EDIT115, OnExitMat115)
	ON_EN_KILLFOCUS(IDC_EDIT60, OnExitMat60)
	ON_EN_KILLFOCUS(IDC_EDIT61, OnExitMat61)
	ON_EN_KILLFOCUS(IDC_EDIT62, OnExitMat62)
	ON_EN_KILLFOCUS(IDC_EDIT116, OnExitMat116)
	ON_EN_KILLFOCUS(IDC_EDIT117, OnExitMat117)
	ON_EN_KILLFOCUS(IDC_EDIT63, OnExitMat63)
	ON_EN_KILLFOCUS(IDC_EDIT64, OnExitMat64)
	ON_EN_KILLFOCUS(IDC_EDIT69, OnExitMat69)
	ON_EN_KILLFOCUS(IDC_EDIT65, OnExitMat65)
	ON_EN_KILLFOCUS(IDC_EDIT66, OnExitMat66)

// Select Matrix Dimension
	ON_BN_CLICKED(IDC_RADIO1, OnDimension1)
	ON_BN_CLICKED(IDC_RADIO2, OnDimension2)
	ON_BN_CLICKED(IDC_RADIO3, OnDimension3)
	ON_BN_CLICKED(IDC_RADIO4, OnDimension4)
	ON_BN_CLICKED(IDC_RADIO5, OnDimension5)

	ON_BN_CLICKED(IDC_RADIO6, OnDisableAlphCode)
	ON_BN_CLICKED(IDC_RADIO7, OnEnableAlphCode)
	ON_BN_CLICKED(IDC_RADIO8, OnRowVectorMatrix)
	ON_BN_CLICKED(IDC_RADIO9, OnMatrixColumnVector)

	ON_BN_CLICKED(IDC_BUTTON3, OnZufaelligerSchluessel)
	ON_BN_CLICKED(IDC_BUTTON4, OnGroessereSchluessel)
	ON_BN_CLICKED(IDC_BUTTON5, OnDecrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnHillOptions)

	ON_BN_CLICKED(IDC_CHECK1, OnVerbose)

	ON_BN_CLICKED(IDC_BUTTON_TEXTOPTIONS, OnTextOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgKeyHill5x5 


// HillAlphMat
void CDlgKeyHill5x5::OnUpdateMat11() { m_HillBase->syncAlphNum(0,0); }
void CDlgKeyHill5x5::OnUpdateMat12() { m_HillBase->syncAlphNum(0,1); }
void CDlgKeyHill5x5::OnUpdateMat13() { m_HillBase->syncAlphNum(0,2); }
void CDlgKeyHill5x5::OnUpdateMat14() { m_HillBase->syncAlphNum(0,3); }
void CDlgKeyHill5x5::OnUpdateMat15() { m_HillBase->syncAlphNum(0,4); }
void CDlgKeyHill5x5::OnUpdateMat21() { m_HillBase->syncAlphNum(1,0); }
void CDlgKeyHill5x5::OnUpdateMat22() { m_HillBase->syncAlphNum(1,1); }
void CDlgKeyHill5x5::OnUpdateMat23() { m_HillBase->syncAlphNum(1,2); }
void CDlgKeyHill5x5::OnUpdateMat24() { m_HillBase->syncAlphNum(1,3); }
void CDlgKeyHill5x5::OnUpdateMat25() { m_HillBase->syncAlphNum(1,4); }
void CDlgKeyHill5x5::OnUpdateMat31() { m_HillBase->syncAlphNum(2,0); }
void CDlgKeyHill5x5::OnUpdateMat32() { m_HillBase->syncAlphNum(2,1); }
void CDlgKeyHill5x5::OnUpdateMat33() { m_HillBase->syncAlphNum(2,2); }
void CDlgKeyHill5x5::OnUpdateMat34() { m_HillBase->syncAlphNum(2,3); }
void CDlgKeyHill5x5::OnUpdateMat35() { m_HillBase->syncAlphNum(2,4); }
void CDlgKeyHill5x5::OnUpdateMat41() { m_HillBase->syncAlphNum(3,0); }
void CDlgKeyHill5x5::OnUpdateMat42() { m_HillBase->syncAlphNum(3,1); }
void CDlgKeyHill5x5::OnUpdateMat43() { m_HillBase->syncAlphNum(3,2); }
void CDlgKeyHill5x5::OnUpdateMat44() { m_HillBase->syncAlphNum(3,3); }
void CDlgKeyHill5x5::OnUpdateMat45() { m_HillBase->syncAlphNum(3,4); }
void CDlgKeyHill5x5::OnUpdateMat51() { m_HillBase->syncAlphNum(4,0); }
void CDlgKeyHill5x5::OnUpdateMat52() { m_HillBase->syncAlphNum(4,1); }
void CDlgKeyHill5x5::OnUpdateMat53() { m_HillBase->syncAlphNum(4,2); }
void CDlgKeyHill5x5::OnUpdateMat54() { m_HillBase->syncAlphNum(4,3); }
void CDlgKeyHill5x5::OnUpdateMat55() { m_HillBase->syncAlphNum(4,4); }

// HillNumMat
void CDlgKeyHill5x5::OnUpdateMat36()  { m_HillBase->syncNumAlph(0,0); }
void CDlgKeyHill5x5::OnUpdateMat37()  { m_HillBase->syncNumAlph(0,1); }
void CDlgKeyHill5x5::OnUpdateMat38()  { m_HillBase->syncNumAlph(0,2); }
void CDlgKeyHill5x5::OnUpdateMat40()  { m_HillBase->syncNumAlph(0,3); }
void CDlgKeyHill5x5::OnUpdateMat46()  { m_HillBase->syncNumAlph(0,4); }
void CDlgKeyHill5x5::OnUpdateMat47()  { m_HillBase->syncNumAlph(1,0); }
void CDlgKeyHill5x5::OnUpdateMat48()  { m_HillBase->syncNumAlph(1,1); }
void CDlgKeyHill5x5::OnUpdateMat49()  { m_HillBase->syncNumAlph(1,2); }
void CDlgKeyHill5x5::OnUpdateMat50()  { m_HillBase->syncNumAlph(1,3); }
void CDlgKeyHill5x5::OnUpdateMat111() { m_HillBase->syncNumAlph(1,4); }
void CDlgKeyHill5x5::OnUpdateMat57()  { m_HillBase->syncNumAlph(2,0); }
void CDlgKeyHill5x5::OnUpdateMat58()  { m_HillBase->syncNumAlph(2,1); }
void CDlgKeyHill5x5::OnUpdateMat59()  { m_HillBase->syncNumAlph(2,2); }
void CDlgKeyHill5x5::OnUpdateMat56()  { m_HillBase->syncNumAlph(2,3); }
void CDlgKeyHill5x5::OnUpdateMat115() { m_HillBase->syncNumAlph(2,4); }
void CDlgKeyHill5x5::OnUpdateMat60()  { m_HillBase->syncNumAlph(3,0); }
void CDlgKeyHill5x5::OnUpdateMat61()  { m_HillBase->syncNumAlph(3,1); }
void CDlgKeyHill5x5::OnUpdateMat62()  { m_HillBase->syncNumAlph(3,2); }
void CDlgKeyHill5x5::OnUpdateMat116() { m_HillBase->syncNumAlph(3,3); }
void CDlgKeyHill5x5::OnUpdateMat117() { m_HillBase->syncNumAlph(3,4); }
void CDlgKeyHill5x5::OnUpdateMat63()  { m_HillBase->syncNumAlph(4,0); }
void CDlgKeyHill5x5::OnUpdateMat64()  { m_HillBase->syncNumAlph(4,1); }
void CDlgKeyHill5x5::OnUpdateMat69()  { m_HillBase->syncNumAlph(4,2); }
void CDlgKeyHill5x5::OnUpdateMat65()  { m_HillBase->syncNumAlph(4,3); }
void CDlgKeyHill5x5::OnUpdateMat66()  { m_HillBase->syncNumAlph(4,4); }

void CDlgKeyHill5x5::OnExitMat36()  { m_HillBase->formatNum(0,0); }
void CDlgKeyHill5x5::OnExitMat37()  { m_HillBase->formatNum(0,1); }
void CDlgKeyHill5x5::OnExitMat38()  { m_HillBase->formatNum(0,2); }
void CDlgKeyHill5x5::OnExitMat40()  { m_HillBase->formatNum(0,3); }
void CDlgKeyHill5x5::OnExitMat46()  { m_HillBase->formatNum(0,4); }
void CDlgKeyHill5x5::OnExitMat47()  { m_HillBase->formatNum(1,0); }
void CDlgKeyHill5x5::OnExitMat48()  { m_HillBase->formatNum(1,1); }
void CDlgKeyHill5x5::OnExitMat49()  { m_HillBase->formatNum(1,2); }
void CDlgKeyHill5x5::OnExitMat50()  { m_HillBase->formatNum(1,3); }
void CDlgKeyHill5x5::OnExitMat111() { m_HillBase->formatNum(1,4); }
void CDlgKeyHill5x5::OnExitMat57()  { m_HillBase->formatNum(2,0); }
void CDlgKeyHill5x5::OnExitMat58()  { m_HillBase->formatNum(2,1); }
void CDlgKeyHill5x5::OnExitMat59()  { m_HillBase->formatNum(2,2); }
void CDlgKeyHill5x5::OnExitMat56()  { m_HillBase->formatNum(2,3); }
void CDlgKeyHill5x5::OnExitMat115() { m_HillBase->formatNum(2,4); }
void CDlgKeyHill5x5::OnExitMat60()  { m_HillBase->formatNum(3,0); }
void CDlgKeyHill5x5::OnExitMat61()  { m_HillBase->formatNum(3,1); }
void CDlgKeyHill5x5::OnExitMat62()  { m_HillBase->formatNum(3,2); }
void CDlgKeyHill5x5::OnExitMat116() { m_HillBase->formatNum(3,3); }
void CDlgKeyHill5x5::OnExitMat117() { m_HillBase->formatNum(3,4); }
void CDlgKeyHill5x5::OnExitMat63()  { m_HillBase->formatNum(4,0); }
void CDlgKeyHill5x5::OnExitMat64()  { m_HillBase->formatNum(4,1); }
void CDlgKeyHill5x5::OnExitMat69()  { m_HillBase->formatNum(4,2); }
void CDlgKeyHill5x5::OnExitMat65()  { m_HillBase->formatNum(4,3); }
void CDlgKeyHill5x5::OnExitMat66()  { m_HillBase->formatNum(4,4); }

// HILL parameter
void CDlgKeyHill5x5::SetDimension( unsigned long d)
{
	const unsigned long HillDimID[] = { 0, IDC_RADIO1, IDC_RADIO2, IDC_RADIO3, IDC_RADIO3, IDC_RADIO4, IDC_RADIO5 };
	m_HillBase->selectHillDimension( d ); radioSetHillDim(HillDimID[d]);
}
void CDlgKeyHill5x5::OnDimension1() { SetDimension(1); }
void CDlgKeyHill5x5::OnDimension2() { SetDimension(2); }
void CDlgKeyHill5x5::OnDimension3() { SetDimension(3); }
void CDlgKeyHill5x5::OnDimension4() { SetDimension(4); }
void CDlgKeyHill5x5::OnDimension5() { SetDimension(5); }

void CDlgKeyHill5x5::OnEnableAlphCode()     { m_HillBase->selectMatType ( HILL_CHAR_MATRIX ); }
void CDlgKeyHill5x5::OnDisableAlphCode()    { m_HillBase->selectMatType ( HILL_NUM_MATRIX ); }
void CDlgKeyHill5x5::OnRowVectorMatrix()    { m_HillBase->selectMultType( MATRIX_VECTOR ); radioSetMultType( IDC_RADIO8 ); }
void CDlgKeyHill5x5::OnMatrixColumnVector() { m_HillBase->selectMultType( VECTOR_MATRIX ); radioSetMultType( IDC_RADIO9 ); }

// helper functions
void CDlgKeyHill5x5::radioSetMultType( unsigned long ID ) {	CheckRadioButton(IDC_RADIO8,IDC_RADIO9, ID); }
void CDlgKeyHill5x5::radioSetHillDim ( unsigned long ID ) {	CheckRadioButton(IDC_RADIO1,IDC_RADIO5, ID); }
void CDlgKeyHill5x5::radioSetMatType ( unsigned long ID ) {	CheckRadioButton(IDC_RADIO6,IDC_RADIO7, ID); }
void CDlgKeyHill5x5::displayAlphabet() 
{ 
	CString sc;
	sc.FormatMessageA( IDS_HILL_CASE, theApp.TextOptions.getAlphabet().GetLength() );
	GetDlgItem(IDC_STATIC_HILL_ALPH)->SetWindowText(sc);
	m_pHillAlphInfo = theApp.TextOptions.getAlphabet();
	UpdateData( FALSE );
}

BOOL CDlgKeyHill5x5::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Verbose = bGlobVerbose;

	m_HillBase->readRegistry();
	m_HillBase->setMatFont();

	radioSetMultType( m_HillBase->multType );
	radioSetMatType ( m_HillBase->matType  );
	radioSetHillDim ( m_HillBase->dim      );
	displayAlphabet();
	SetDimension( m_HillBase->dim );

	CString cs;
	cs.LoadStringA(IDS_CRYPT_HILL);
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	m_Paste.EnableWindow( IsKeyEmpty(cs) );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgKeyHill5x5::DoCrypt( unsigned long mode )
{
	UpdateData(true);

	if ( !m_HillBase->isInvertable() )
	{
		// FIXME: Set FOCUS
		return;
	}
	m_HillBase->writeRegistry();
	m_HillBase->cryptMode = mode;
	CDialog::OnOK();
}

void CDlgKeyHill5x5::OnOK()		  { DoCrypt(0); }
void CDlgKeyHill5x5::OnDecrypt()  { DoCrypt(1); }
void CDlgKeyHill5x5::OnPasteKey() 
{	
	m_HillBase->pasteKey(); 
}

void CDlgKeyHill5x5::OnZufaelligerSchluessel() 
{
	m_HillBase->randomKey();
}


void CDlgKeyHill5x5::OnGroessereSchluessel() 
{
	m_HillBase->writeRegistry();
	m_HillBase->cryptMode = 3; // FIXME CHANGE DIMENSION
	m_HillBase->max_dim   = 10;

	CDialog::OnOK();	
}

void CDlgKeyHill5x5::OnHillOptions()
{
	DlgHillOptions hillOpt;
	if ( IDOK != hillOpt.DoModal() )
		return;

	m_HillBase->alphabetOffset = hillOpt.m_alphabetOffset;

}

void CDlgKeyHill5x5::OnVerbose()
{
	CButton* pCheck = (CButton*)GetDlgItem(IDC_CHECK1);
	m_Verbose = pCheck->GetCheck();
}

void CDlgKeyHill5x5::OnTextOptions()
{
	if(theApp.TextOptions.DoModal() != IDOK) 
		return;
	displayAlphabet();
}


BEGIN_MESSAGE_MAP(CHiEdit, CEdit)
	//{{AFX_MSG_MAP(CHiEdit)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHiEdit::OnLButtonUp(UINT nFlags, CPoint point )
{
	CEdit::OnLButtonUp(nFlags,point);
	SetSel(0, -1);
} 
