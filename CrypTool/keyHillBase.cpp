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
#include "stdafx.h"
#include "assert.h"
#include "CrypToolApp.h"
#include "CrypToolTools.h"
#include "KeyRepository.h"
#include "SquareMatrixModN.h"
#include "KeyHillBase.h"
#include "DlgKeyHill5x5.h"
#include "DlgKeyHill10x10.h"

/////////////////////////////////////////////////////////////////////////////
//
CKeyHillBase::CKeyHillBase(unsigned long p_keyRange) :
	HillMat(0),
	alphabetOffset(0),
	max_dim(p_keyRange),
   key_range(p_keyRange),
	dim(1),
	matType(HILL_CHAR_MATRIX), 
	multType(VECTOR_MATRIX),
	cryptMode(0),
   currentDialog(0)
{
	HillNumMat  = new CHiEdit*[key_range];
	HillAlphMat = new CEdit*  [key_range];
	for ( unsigned long i=0; i<key_range; i++ )
	{
		HillNumMat[i]  = new CHiEdit[key_range];
		HillAlphMat[i] = new CEdit[key_range];
	}
}

CKeyHillBase::~CKeyHillBase()
{
	for ( unsigned long i=0; i<key_range; i++ )
	{
		delete []HillNumMat[i];
		delete []HillAlphMat[i];
	}
	delete []HillNumMat;
	delete []HillAlphMat;
}

int CKeyHillBase::run( int currDlg )
{
   CDlgKeyHill5x5    dlgKeyHill5x5;
   CDlgKeyHill10x10  dlgKeyHill10x10;

   dlgKeyHill5x5.init( this );
   // dlgKeyHill10x10.init( this ); 

   while ( currDlg > 1 )
   {
      if ( currDlg == DLG_HILL_5x5 ) 
      {
         max_dim = DIM_DLG_HILL_5x5;
         currentDialog = &dlgKeyHill5x5;
      }
      else
      {
         max_dim = DIM_DLG_HILL_10x10;
         currentDialog = &dlgKeyHill10x10;
      }
      if ( IDOK == currentDialog->DoModal() )
      {
         // FIXME 
         return IDOK;
      }
      // FIXME
      break;
   }

   return IDCANCEL;
}

int CKeyHillBase::ord( const char ch )
{
	for(int i=0;i<theApp.TextOptions.getAlphabet().GetLength();i++)
		if( theApp.TextOptions.getAlphabet()[i] == ch ) return i + alphabetOffset;

	return -1;
}

void CKeyHillBase::syncAlphNum( unsigned long i, unsigned long j )
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
				currentDialog->NextDlgCtrl();
			}
			else if ( theApp.TextOptions.getIgnoreCase() 
				      && MyIsLower(cs[0]) &&  ord(MyToUpper(cs[0])) >= 0 )
			{
				cs.SetAt(0,MyToUpper(cs[0]));
   			HillAlphMat[i][j].SetWindowText( cs );
			}
			else
			{
				cs.Empty();
			}
		}
	}
}

void CKeyHillBase::formatNum( unsigned long i, unsigned long j )
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
		currentDialog->PrevDlgCtrl(); //because Tab and UpdateFeld makes both NextDlgCtrl
	}
}

void CKeyHillBase::syncNumAlph( unsigned long i, unsigned long j )
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
				currentDialog->NextDlgCtrl();
			}
		}
	}
}

int CKeyHillBase::validEntries()
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
            currentDialog->MessageBoxA(msg, cs, MB_ICONWARNING|MB_OK);
				return FALSE;
			}
		}

	return TRUE;
}

int  CKeyHillBase::isInvertable()
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
		cs.Format( "%dx%d", dim, dim );
		msg.Format( IDS_HILL_BAD_KEY_INV, cs, modul);
		cs.LoadStringA( IDS_HILL_BAD_KEY );
		currentDialog->MessageBoxA(msg, cs, MB_ICONWARNING|MB_OK);
	}

	delete mat;
	delete mat_inv;

	return invertable;
}

void CKeyHillBase::loadHillMatrix(CSquareMatrixModN& mat)
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

void CKeyHillBase::activateMatrix  ( CEdit **mat )
{
	unsigned long i, j;
	for ( i=0; i<dim; i++ )
		for ( j=0; j<dim; j++ )
			mat[i][j].EnableWindow( TRUE );
}

void CKeyHillBase::deactivateMatrix( CEdit **mat )
{
	unsigned long i, j;
	for ( i=0; i<max_dim; i++ )
		for ( j=0; j<max_dim; j++ )
			mat[i][j].EnableWindow( FALSE );
}

void CKeyHillBase::selectActMatrix ()
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
		 activateMatrix( (CEdit**)HillNumMat );
		 HillNumMat[0][0].SetFocus();
		 HillNumMat[0][0].SetSel(0, -1);
	}
}

void CKeyHillBase::selectHillDimension( unsigned long new_dim )
{
	assert( 1 <= new_dim && new_dim <= max_dim );
	dim = new_dim;
	selectActMatrix();
}

void CKeyHillBase::selectMatType( HillEditType new_type )
{
	matType = new_type;
	selectActMatrix();
}

void CKeyHillBase::selectMultType( HillMultType new_type )
{
	multType = new_type;
}

void CKeyHillBase::setMatFont()
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

void CKeyHillBase::pasteKey()
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

void CKeyHillBase::copyKey()
{

}

void CKeyHillBase::SetHillMatrix( CSquareMatrixModN *mat )
{
	unsigned long i, j;
	CString cs;

	for ( i=0; i<max_dim; i++ )
		for ( j=0; j<max_dim; j++ )
			if ( i<dim && j<dim )
			{  // FIXME 
				HillAlphMat[i][j].SetWindowTextA( CString( char('A' + (*mat)(i,j) - alphabetOffset)) );
				cs.Format( "%02d", (*mat)(i,j) );
				HillNumMat[i][j].SetWindowTextA( cs );
			}
			else
			{
				HillAlphMat[i][j].SetWindowTextA( _T("") );
				HillNumMat[i][j].SetWindowTextA(_T(""));
			}
}

void CKeyHillBase::randomKey()
{
	CSquareMatrixModN mat( dim, theApp.TextOptions.getAlphabet().GetLength() );
	if (mat.zufaellige_invertierbare_matrix())
	{
		SetHillMatrix( &mat );
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ON_WRONG_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		currentDialog->MessageBoxA(pc_str, NULL, MB_ICONERROR|MB_OK);
	}
}

void CKeyHillBase::readRegistry()
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

void CKeyHillBase::writeRegistry()
{
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(unsigned long(alphabetOffset), "OrdChrOffset");
		CT_WRITE_REGISTRY(unsigned long(matType),		 "EditKeyChrMatrix");
		CT_CLOSE_REGISTRY();
	}
}
