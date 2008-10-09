/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/



// DlgAdfgvxManual.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAdfgvxManual.h"
#include ".\dlgadfgvxmanual.h"
#include "DlgAdfgvxIntro.h"
#include "DlgAdfgvxStringBox.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "KeyRepository.h"

// CDlgAdfgvxManual-Dialogfeld



IMPLEMENT_DYNAMIC(CDlgAdfgvxManual, CDialog)
CDlgAdfgvxManual::CDlgAdfgvxManual(char* infile, CString oldTitle, CWnd* pParent)
	: CDialog(CDlgAdfgvxManual::IDD, pParent)
//CDlgAdfgvxManual::CDlgAdfgvxManual(CWnd* pParent /*=NULL*/)
//	: CDialog(CDlgAdfgvxManual::IDD, pParent)
	, password(_T(""))
	, plaintext(_T(""))
	, remaining(0)
	, remChars(_T(""))
	, numberedPassword(_T(""))
	, analysed(false)
	, iGotOne(false)
	, subKey(_T(""))
{

	//{{AFX_DATA_INIT(CDlgAdfgvxManual)
	minLength = 0;
	maxLength = 7;
	//}}AFX_DATA_INIT

	this->infile = infile;
	this->oldTitle = oldTitle;
	this->cipher = new adfgvx();

	for (int row=0;row<6;row++)
		for(int col=0;col<6;col++)
			this->matrix[row][col] = '*';
	
	
	
}

BOOL CDlgAdfgvxManual::OnInitDialog()
{	
	CDialog::OnInitDialog();
	VERIFY(c_insertKey.AutoLoad(IDC_INSERT_KEY, this));
	
	this->validCipherText=this->cipher->readCiphertext(this->infile);
	if ((validCipherText==4)|(validCipherText==5))
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_10,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		this->OnCancel();
	}
	else
	{
		unsigned long noIntro = FALSE;

		if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "ADFGVX" ) == ERROR_SUCCESS )
 		{
			CT_READ_REGISTRY_DEFAULT(noIntro, "ShowIntro", noIntro);
			CT_CLOSE_REGISTRY();
		}
		else
		{
			// FIXME
		}

		if(!noIntro)
		{
			DlgAdfgvxIntro intro = new DlgAdfgvxIntro();
			intro.DoModal();
		}
		
		UpdateData(false);
		//if clipboard has key from adfgvx-typ, enable paste button
		if (IsKeyEmpty("ADFGVX Chiffre"))
			c_insertKey.EnableWindow(true);
		else
			c_insertKey.EnableWindow(false);
		
		for (int i =0;i<50;i++)
			this->pwdList[i]="";
		
		UpdateData(false);

		buttonResub.EnableWindow(false);
		buttonResetMatrix.EnableWindow(false);
		buttonStdMatrix.EnableWindow(false);
		buttonStringBox.EnableWindow(false);
		buttonOutput.EnableWindow(false);
	}
	return TRUE;
}

CDlgAdfgvxManual::~CDlgAdfgvxManual()
{
}

void CDlgAdfgvxManual::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_M00, matrix[0][0]);
	DDV_MaxChars(pDX, matrix[0][0], 1);
	DDX_Text(pDX, IDC_M01, matrix[0][1]);
	DDV_MaxChars(pDX, matrix[0][1], 1);
	DDX_Text(pDX, IDC_M02, matrix[0][2]);
	DDV_MaxChars(pDX, matrix[0][2], 1);
	DDX_Text(pDX, IDC_M03, matrix[0][3]);
	DDV_MaxChars(pDX, matrix[0][3], 1);
	DDX_Text(pDX, IDC_M04, matrix[0][4]);
	DDV_MaxChars(pDX, matrix[0][4], 1);
	DDX_Text(pDX, IDC_M05, matrix[0][5]);
	DDV_MaxChars(pDX, matrix[0][5], 1);
	DDX_Text(pDX, IDC_M10, matrix[1][0]);
	DDV_MaxChars(pDX, matrix[1][0], 1);
	DDX_Text(pDX, IDC_M11, matrix[1][1]);
	DDV_MaxChars(pDX, matrix[1][1], 1);
	DDX_Text(pDX, IDC_M12, matrix[1][2]);
	DDV_MaxChars(pDX, matrix[1][2], 1);
	DDX_Text(pDX, IDC_M13, matrix[1][3]);
	DDV_MaxChars(pDX, matrix[1][3], 1);
	DDX_Text(pDX, IDC_M14, matrix[1][4]);
	DDV_MaxChars(pDX, matrix[1][4], 1);
	DDX_Text(pDX, IDC_M15, matrix[1][5]);
	DDV_MaxChars(pDX, matrix[1][5], 1);
	DDX_Text(pDX, IDC_M20, matrix[2][0]);
	DDV_MaxChars(pDX, matrix[2][0], 1);
	DDX_Text(pDX, IDC_M21, matrix[2][1]);
	DDV_MaxChars(pDX, matrix[2][1], 1);
	DDX_Text(pDX, IDC_M22, matrix[2][2]);
	DDV_MaxChars(pDX, matrix[2][2], 1);
	DDX_Text(pDX, IDC_M23, matrix[2][3]);
	DDV_MaxChars(pDX, matrix[2][3], 1);
	DDX_Text(pDX, IDC_M24, matrix[2][4]);
	DDV_MaxChars(pDX, matrix[2][4], 1);
	DDX_Text(pDX, IDC_M25, matrix[2][5]);
	DDV_MaxChars(pDX, matrix[2][5], 1);
	DDX_Text(pDX, IDC_M30, matrix[3][0]);
	DDV_MaxChars(pDX, matrix[3][0], 1);
	DDX_Text(pDX, IDC_M31, matrix[3][1]);
	DDV_MaxChars(pDX, matrix[3][1], 1);
	DDX_Text(pDX, IDC_M32, matrix[3][2]);
	DDV_MaxChars(pDX, matrix[3][2], 1);
	DDX_Text(pDX, IDC_M33, matrix[3][3]);
	DDV_MaxChars(pDX, matrix[3][3], 1);
	DDX_Text(pDX, IDC_M34, matrix[3][4]);
	DDV_MaxChars(pDX, matrix[3][4], 1);
	DDX_Text(pDX, IDC_M35, matrix[3][5]);
	DDV_MaxChars(pDX, matrix[3][5], 1);
	DDX_Text(pDX, IDC_M40, matrix[4][0]);
	DDV_MaxChars(pDX, matrix[4][0], 1);
	DDX_Text(pDX, IDC_M41, matrix[4][1]);
	DDV_MaxChars(pDX, matrix[4][1], 1);
	DDX_Text(pDX, IDC_M42, matrix[4][2]);
	DDV_MaxChars(pDX, matrix[4][2], 1);
	DDX_Text(pDX, IDC_M43, matrix[4][3]);
	DDV_MaxChars(pDX, matrix[4][3], 1);
	DDX_Text(pDX, IDC_M44, matrix[4][4]);
	DDV_MaxChars(pDX, matrix[4][4], 1);
	DDX_Text(pDX, IDC_M45, matrix[4][5]);
	DDV_MaxChars(pDX, matrix[4][5], 1);
	DDX_Text(pDX, IDC_M50, matrix[5][0]);
	DDV_MaxChars(pDX, matrix[5][0], 1);
	DDX_Text(pDX, IDC_M51, matrix[5][1]);
	DDV_MaxChars(pDX, matrix[5][1], 1);
	DDX_Text(pDX, IDC_M52, matrix[5][2]);
	DDV_MaxChars(pDX, matrix[5][2], 1);
	DDX_Text(pDX, IDC_M53, matrix[5][3]);
	DDV_MaxChars(pDX, matrix[5][3], 1);
	DDX_Text(pDX, IDC_M54, matrix[5][4]);
	DDV_MaxChars(pDX, matrix[5][4], 1);
	DDX_Text(pDX, IDC_M55, matrix[5][5]);
	DDV_MaxChars(pDX, matrix[5][5], 1);
	//{{AFX_DATA_MAP(CDlgAdfgvxManual)
	DDX_Text(pDX, IDC_TEXTFIELD_NUMBEREDPASSWORD, numberedPassword);
	DDX_CBIndex(pDX, IDC_MAXLENGTH, maxLength);
	DDX_Text(pDX, IDC_EDIT_POSSIBLE_PLAINTEXT, plaintext);
	DDX_Text(pDX, IDC_EDIT_REMAINING_SOL, remaining);
	DDX_Text(pDX, IDC_EDIT_REMCHARS, remChars);
	DDX_CBIndex(pDX, IDC_MINLENGTH, minLength);
	DDX_Control(pDX, IDC_PASSWORD_BOX, pwdListBox);
	DDX_Text (pDX, IDC_PASSWORD_BOX, password);
	DDX_Control(pDX, IDC_RESUBSTITUTE, buttonResub);
	DDX_Control(pDX, IDC_RESET_MATRIX, buttonResetMatrix);
	DDX_Control(pDX, IDOK, buttonOutput);
	DDX_Control(pDX, IDC_BUTTON_STRINGBOX, buttonStringBox);
	DDX_Control(pDX, IDC_MATRIX_STANDARD, buttonStdMatrix);
	//}}AFX_DATA_INIT
	//DDX_Control(pDX, IDC_CHECK_SHOW_INF, checkShowInfo);
}

BEGIN_MESSAGE_MAP(CDlgAdfgvxManual, CDialog)
	//{{AFX_MSG_MAP(CDlgAdfgvxManual)
	ON_BN_CLICKED(IDC_NEXT_PERMUTATION, OnBnClickedNextPermutation)
	ON_EN_CHANGE(IDC_M00, OnEnChangeM00)
	ON_EN_CHANGE(IDC_M01, OnEnChangeM01)
	ON_EN_CHANGE(IDC_M02, OnEnChangeM02)
	ON_EN_CHANGE(IDC_M03, OnEnChangeM03)
	ON_EN_CHANGE(IDC_M04, OnEnChangeM04)
	ON_EN_CHANGE(IDC_M05, OnEnChangeM05)
	ON_EN_CHANGE(IDC_M10, OnEnChangeM10)
	ON_EN_CHANGE(IDC_M11, OnEnChangeM11)
	ON_EN_CHANGE(IDC_M12, OnEnChangeM12)
	ON_EN_CHANGE(IDC_M13, OnEnChangeM13)
	ON_EN_CHANGE(IDC_M14, OnEnChangeM14)
	ON_EN_CHANGE(IDC_M15, OnEnChangeM15)
	ON_EN_CHANGE(IDC_M20, OnEnChangeM20)
	ON_EN_CHANGE(IDC_M21, OnEnChangeM21)
	ON_EN_CHANGE(IDC_M22, OnEnChangeM22)
	ON_EN_CHANGE(IDC_M23, OnEnChangeM23)
	ON_EN_CHANGE(IDC_M24, OnEnChangeM24)
	ON_EN_CHANGE(IDC_M25, OnEnChangeM25)
	ON_EN_CHANGE(IDC_M30, OnEnChangeM30)
	ON_EN_CHANGE(IDC_M31, OnEnChangeM31)
	ON_EN_CHANGE(IDC_M32, OnEnChangeM32)
	ON_EN_CHANGE(IDC_M33, OnEnChangeM33)
	ON_EN_CHANGE(IDC_M34, OnEnChangeM34)
	ON_EN_CHANGE(IDC_M35, OnEnChangeM35)
	ON_EN_CHANGE(IDC_M40, OnEnChangeM40)
	ON_EN_CHANGE(IDC_M41, OnEnChangeM41)
	ON_EN_CHANGE(IDC_M42, OnEnChangeM42)
	ON_EN_CHANGE(IDC_M43, OnEnChangeM43)
	ON_EN_CHANGE(IDC_M44, OnEnChangeM44)
	ON_EN_CHANGE(IDC_M45, OnEnChangeM45)
	ON_EN_CHANGE(IDC_M50, OnEnChangeM50)
	ON_EN_CHANGE(IDC_M51, OnEnChangeM51)
	ON_EN_CHANGE(IDC_M52, OnEnChangeM52)
	ON_EN_CHANGE(IDC_M53, OnEnChangeM53)
	ON_EN_CHANGE(IDC_M54, OnEnChangeM54)
	ON_EN_CHANGE(IDC_M55, OnEnChangeM55)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_MAXLENGTH, OnCbnSelchangeMaxlength)
	ON_CBN_SELCHANGE(IDC_MINLENGTH, OnCbnSelchangeMinlength)
	ON_BN_CLICKED(IDC_BUTTON_FORCE, OnBnClickedButtonForce)
	ON_BN_CLICKED(IDC_RESET_MATRIX, OnBnClickedResetMatrix)
	ON_BN_CLICKED(IDC_RESUBSTITUTE, OnBnClickedResubstitute)
	ON_CBN_EDITCHANGE(IDC_PASSWORD_BOX, OnCbnEditchangePasswordBox)
	ON_CBN_SELCHANGE(IDC_PASSWORD_BOX, OnCbnSelchangePasswordBox)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_MATRIX_STANDARD, OnBnClickedMatrixStandard)
	ON_BN_CLICKED(IDC_BUTTON_STRINGBOX, OnBnClickedButtonStringbox)
END_MESSAGE_MAP()


// CDlgAdfgvxManual-Meldungshandler


/* klicking this button forces the usage of the password filled into the password field
*	this overcomes the problem that a user-defined password would not be permitted
*	if the analysis-function considers it "not worthy"
*/
//force using the password, even if the adfgvx-goodenough considers it "not worthy";
//can be necessary with short ciphertexts
void CDlgAdfgvxManual::OnBnClickedButtonForce()
{
	UpdateData(true);

	//test if the password is included in the password list
	counter = -1;
	//check the pwdList whether the pwd is already contained
	for(int i=0;i<50;i++)
	{
		if(pwdList[i].Mid(36)==password)
			counter = i;
	}
	if(counter==-1)//password is new and must be tested
	{
		//validate the transposition-password
		int validPassword=cipher->CheckPassword(minLength, maxLength, password);
		//in contrast to the transposition-analysis, the password-field must not be empty!
		if (password.GetLength()<1)
			validPassword=6;

		//passwordLength<1
		if (validPassword==6)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_6,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}

		//invalid characters: remove, then recheck the password & start again
		if (validPassword==4)
		{
			CString oldPassword=password;
			password=cipher->CleansePassword(validPassword, password);
			minLength=password.GetLength()-1;
			maxLength=minLength;
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_4,pc_str,STR_LAENGE_STRING_TABLE);
			CString message=(CString)pc_str+(CString)(password);
			MessageBox(message);
			OnBnClickedButtonForce();
		}	



		//redundant characters: redundant characters are removed, minLength/maxLength is adjusted; recheck
		if (validPassword==7)
		{
			CString oldPassword=password;
			password=cipher->CleansePassword(validPassword, password);
			minLength=password.GetLength()-1;
			maxLength=minLength;
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_7,pc_str,STR_LAENGE_STRING_TABLE);
			CString message=(CString)pc_str+(CString)(password);
			MessageBox(message);
			OnBnClickedButtonForce();
		}

		//password ok
		if (validPassword==0)
		{
			
			cipher->ForcePassword(password);
			cipher->resubstitution();
			plaintext = cipher->plaintext.c_str();
			//fill the edit-control fields with the current substitution matrix
			for(int row=0;row<6;row++)
				for (int col=0;col<6;col++)
					this->matrix[row][col]=cipher->getMatrix(row,col);
			
			PwdEnqueue(password);
		}
	}

	else //password exists
	{
		//fill the substitution matrix
		int i=0;
		for(int row=0;row<6;row++)
			for (int col=0;col<6;col++)
			{
				this->matrix[row][col]=pwdList[pwdListBox.GetCurSel()][i];
				i++;
			}
	}
	analysed=true;
	buttonResub.EnableWindow(true);
	buttonResetMatrix.EnableWindow(true);
	buttonStdMatrix.EnableWindow(true);
	buttonStringBox.EnableWindow(true);

	Resubstitute();
	UpdateRemChars();
	UpdateData(false);
	CDialog::NextDlgCtrl();

}


//starts the search for the transposition password
void CDlgAdfgvxManual::OnBnClickedNextPermutation()
{
	UpdateData(true);
	analysed=false;
	buttonResub.EnableWindow(false);
	buttonResetMatrix.EnableWindow(false);
	buttonStdMatrix.EnableWindow(false);
	buttonStringBox.EnableWindow(false);
	buttonOutput.EnableWindow(false);

	//validate the transposition-password
	int validPassword=cipher->CheckPassword(minLength, maxLength, password);
	
	//passwordLength<1
	if (validPassword==6)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_6,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
	}

	//invalid characters: remove, then recheck the password & start again
	if (validPassword==4)
	{
		CString oldPassword=password;
		password=cipher->CleansePassword(validPassword, password);
		minLength=password.GetLength()-1;
		if (maxLength==(oldPassword.GetLength()-1))
			maxLength=minLength;
		UpdateData(false);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_4,pc_str,STR_LAENGE_STRING_TABLE);
		CString message=(CString)pc_str+(CString)(password);
		MessageBox(message);
		OnBnClickedNextPermutation();
	}	
	
	//redundant characters: redundant characters are removed, minLength/maxLength is adjusted; recheck
	if (validPassword==7)
	{
		CString oldPassword=password;
		password=cipher->CleansePassword(validPassword, password);
		minLength=password.GetLength()-1;
		if (maxLength==(oldPassword.GetLength()-1))
			maxLength=minLength;
		UpdateData(false);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_7,pc_str,STR_LAENGE_STRING_TABLE);
		CString message=(CString)pc_str+(CString)(password);
		MessageBox(message);
		OnBnClickedNextPermutation();
	}

	//password ok
	if (validPassword==0)
	{
		Permutate();
		//CWinThread* permThread = AfxBeginThread(StaticThread,(LPVOID)this,THREAD_PRIORITY_NORMAL,0,0/*CREATE_SUSPENDED*/);
		//while(MsgWaitForMultipleObjects(1, &permThread->m_hThread, FALSE, INFINITE, QS_ALLINPUT)==WAIT_TIMEOUT);
		//while(SetEvent(permThread->m_hThread)!=0);
		//WaitForSingleObject(permThread->m_hThread, INFINITE);
		//while(!threadIdle);
		//MessageBox(password);
		
	}
	
	//analysed=true;
	UpdateRemChars();
	if (password.GetLength()>0)
	{
		analysed=true;
		buttonResub.EnableWindow(true);
		buttonResetMatrix.EnableWindow(true);
		buttonStdMatrix.EnableWindow(true);
		buttonStringBox.EnableWindow(true);
		this->GetDlgItem(IDC_BUTTON_FORCE)->EnableWindow(true);
		Resubstitute();
	}
	else
		this->GetDlgItem(IDC_BUTTON_FORCE)->EnableWindow(false);
	UpdateData(false);

	CDialog::NextDlgCtrl();
	
}
void CDlgAdfgvxManual::Permutate()
{
		SHOW_HOUR_GLASS
		
		//store the old password in case we need it later (...no further passwords found)
		CString oldPassword=password;

		//funny thing: the dropdown-control counts the entries in the list, starting at zero
		//so the element "1" sets the variable to int 0.
		//this explains the following term (maxLength+1)	
		password = cipher->nextPassword((minLength+1), (maxLength+1), password);

		//no password within the boundaries 
		if (password.Compare("") ==0&&!iGotOne)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_9,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
			
			//display the order of the columns
			this->numberedPassword=cipher->LettersToNumbers(password);
		}
		
		//found a password (not the same as currently in the password box)
		if (password.Compare("") !=0&&password!=oldPassword)
		{
			cipher->resubstitution();
			plaintext = cipher->plaintext.c_str();
			//fill the edit-control fields with the current substitution matrix
			int i=0;
			for(int row=0;row<6;row++)
				for (int col=0;col<6;col++)
					this->matrix[row][col]=cipher->getMatrix(row,col);
			//display the order of the columns
			this->numberedPassword=cipher->LettersToNumbers(password);
			//add password to the list
			PwdEnqueue(password);
			iGotOne=true;
			//UpdateData(false);
		}
		
		//no further passwords within the boundaries
		//if (password.Compare("") ==0&&iGotOne)//&&password==oldPassword)
		else
			if(iGotOne)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_9B,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
			password=oldPassword;
			//display the order of the columns
			this->numberedPassword=cipher->LettersToNumbers(password);
		}

		UpdateData(false);
		HIDE_HOUR_GLASS
			
}

//function to check if the input is a valid character & if there are double characters in the matrix
CString CDlgAdfgvxManual::CheckInput(CString oldEntry, CString input)
{
	counter=0;
	if(input==' '|| input=='*' || input.GetLength()==0)
		return "*";
	if (('A'<=input.GetAt(0)&&input.GetAt(0)<='z')|('0'<=input.GetAt(0)&&input.GetAt(0)<='9'))
	{
		//checks, if the matrix contains the input more than once, 
		//the "unnecessary" brackets: 
		//i found the for-loop enter line "if(counter>1)" every time. don't know why...
		for (int col=0;col<6;col++)
		{
			for(int row=0;row<6;row++)
			{
				if(matrix[row][col]==input)	
					counter++;
			}
		}

		//if that is the case, the user can choose what to do		
		if(counter>1)
		{
			//option dialog: keep new & delete old or cancel entry?
			if('0'<=input.GetAt(0)&&input.GetAt(0)<='9')
				LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_CHAR_EXISTS_1B, pc_str, STR_LAENGE_STRING_TABLE);
			else
				LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_CHAR_EXISTS_1A, pc_str, STR_LAENGE_STRING_TABLE);
			CString message=(CString)pc_str+(CString)(input);
			LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_CHAR_EXISTS_2, pc_str, STR_LAENGE_STRING_TABLE);
			message+=pc_str;
			if (AfxMessageBox (message,MB_YESNO)==IDYES)
			{
				//brackets: see above
				for (int col=0;col<6;col++)
				{
					for(int row=0;row<6;row++)
					{
						if(matrix[row][col]==input)
							matrix[row][col]="*";
					}
				}
			}
			else
				return oldEntry;
		}
								

		return input;
	}
	//invalid character: error message is displayed
	else
	{
		
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_11,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		return "*";
	}
}

//this function updates the remaining chars to be inserted into the matrix & the possible solutions
void CDlgAdfgvxManual::UpdateRemChars()
{	
	double countStars=0;
	remChars="ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	for (int col=0;col<6;col++)
			for(int row=0;row<6;row++)
				if(matrix[row][col]!="*")
					remChars.Remove(matrix[row][col].GetAt(0));
				else
					countStars++;
	remaining=countStars;
	while(countStars>1)
		remaining=remaining*(--countStars);
	UpdateData(false);
}

//function to resubstitute the ciphertext according to the current substitution matrix
void CDlgAdfgvxManual::Resubstitute()
{
	//UpdateData(false);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
	}
	else
	{
		double countStars=0;
		//set the substitution-matrix
		for (int row=0;row<6;row++)
			for(int col=0;col<6;col++)
				cipher->setMatrix(row,col,matrix[row][col][0]);
			
		//resubstitute the ciphertext with the new matrix
		cipher->repermutation(password);
		cipher->resubstitution();
		plaintext = cipher->plaintext.c_str();
		if(plaintext.GetLength()>0)
			buttonOutput.EnableWindow(true);
		else
			buttonOutput.EnableWindow(false);
	}
	UpdateData(false);
}




void CDlgAdfgvxManual::OnBnClickedOk()
{

	if (GetFocus()==GetDlgItem(IDOK))
	{
	if(password.GetLength()==0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
	}
	else
	{
		SHOW_HOUR_GLASS
		char outfile[256];
		//saves the password and serialized matrix 
		CString pwdString;
		pwdString += password;
		pwdString += ", ";
		for (int row=0;row<6;row++)
			for(int col=0;col<6;col++)
				pwdString += matrix[row][col][0];
		//get filename of temporary file
		GetTmpName(outfile,"cry",".txt");
		//write the plaintext to outfile
		cipher->writePlaintext(outfile);
		//create a new document
		OpenNewDoc(outfile,pwdString,this->oldTitle,IDS_CRYPT_ADFGVX,true,1);
		HIDE_HOUR_GLASS
			this->EndDialog(1);
	}
	}

	if (GetFocus()==GetDlgItem(IDC_NEXT_PERMUTATION))
		CDlgAdfgvxManual::OnBnClickedNextPermutation();

	else
		CDialog::NextDlgCtrl(); 
}

void CDlgAdfgvxManual::OnCbnSelchangeMinlength()
{
	UpdateData(true);
	iGotOne=false;
	if(password.GetLength()>0)
		if(password.GetLength()!=(minLength+1))
		{		
			//set blank password
			password="";
			analysed=false;
			buttonResub.EnableWindow(false);
			buttonResetMatrix.EnableWindow(false);
			buttonStdMatrix.EnableWindow(false);
			buttonStringBox.EnableWindow(false);
			//clear the substitution matrix & reset the current solution
			for (int row=0;row<6;row++)
				for(int col=0;col<6;col++)
					this->matrix[row][col] = '*';
			
			//alternate action: set minLength to current password length
			//found too confusing => removed
			//minLength=password.GetLength()-1;
			UpdateData(false);
		}

	if(minLength>maxLength)
	{
		maxLength=minLength;
		UpdateData(false);
	}
	
}

void CDlgAdfgvxManual::OnCbnSelchangeMaxlength()
{
	UpdateData(true);
	iGotOne=false;
	//if the password length exceeds the maximum length, it is cleared
	if(password.GetLength()>(maxLength+1))
	{		
		password="";
		analysed=false;
		buttonResub.EnableWindow(false);
		buttonResetMatrix.EnableWindow(false);
		buttonStdMatrix.EnableWindow(false);
		buttonStringBox.EnableWindow(false);

		//clear the substitution matrix & reset the current solution
		for (int row=0;row<6;row++)
			for(int col=0;col<6;col++)
				this->matrix[row][col] = '*';
	
		//maxLength=password.GetLength()-1;
		UpdateData(false);
	}

	if(maxLength<minLength)
	{
		minLength=maxLength;
		UpdateData(false);
	}
	
}

void CDlgAdfgvxManual::OnCbnEditchangePasswordBox()
{
	UpdateData(TRUE);
	analysed=false;
	buttonResub.EnableWindow(false);
	buttonResetMatrix.EnableWindow(false);
	buttonStdMatrix.EnableWindow(false);
	buttonStringBox.EnableWindow(false);

	if (password.GetLength() >0)
	{
		this->GetDlgItem(IDC_BUTTON_FORCE)->EnableWindow(true);
		if(maxLength<password.GetLength())
			maxLength=(password.GetLength()-1);
		minLength=(password.GetLength()-1);

		/*counter = -1;
		//check the pwdList whether the pwd is already contained
		for(int i=0;i<50;i++)
		{
			if(pwdList[i].Mid(36)==password)
				counter = i;
		}*/

	}
	else		
		this->GetDlgItem(IDC_BUTTON_FORCE)->EnableWindow(false);
	
	
	//display the order of the columns
	this->numberedPassword=cipher->LettersToNumbers(password);
	
	//##################
	//KICKED OUT BECAUSE OF SUBKEY!!!
	//clear the substitution matrix & reset the current solution 
	/*for (int row=0;row<6;row++)
		for(int col=0;col<6;col++)
			this->matrix[row][col] = '*';
	plaintext="";*/
	//###################

	

	/*if(counter !=-1)//existing password
		//fill the substitution matrix
		for(int row=0;row<6;row++)
			for (int col=0;col<6;col++)
			{
				this->matrix[row][col]=pwdList[pwdListBox.GetCurSel()][counter];
				counter++;
			}
	UpdateRemChars();*/

	UpdateData(FALSE);
}

void CDlgAdfgvxManual::OnCbnSelchangePasswordBox()
{	
	//warum zum geier wird das passwort nicht automatisch vom inhalt der box überschrieben?
	//dataexchange läuft, aber nix passiert
	//beim zweiten aufruf wird das passwort des ersten aufrufs gesetzt, hängt also immer 1 hinterher.

	CDlgAdfgvxManual::OnCbnEditchangePasswordBox();
}

void CDlgAdfgvxManual::OnBnClickedResetMatrix()
{
	LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_MATRIX_RESET, pc_str, STR_LAENGE_STRING_TABLE);

	if (AfxMessageBox (pc_str,MB_YESNO)==IDYES)
	{
		for (int col=0;col<6;col++)
			for(int row=0;row<6;row++)
				this->matrix[row][col]='*';
		
		UpdateRemChars();
		Resubstitute();
	}
}

void CDlgAdfgvxManual::OnBnClickedMatrixStandard()
{
	LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_MATRIX_RESET, pc_str, STR_LAENGE_STRING_TABLE);

	if (AfxMessageBox (pc_str,MB_YESNO)==IDYES)
	{
		char zv[6][6]={'A','B','C','D','E','F',
					'G','H','I','J','K','L',
					'M','N','O','P','Q','R',
					'S','T','U','V','W','X',
					'Y','Z','0','1','2','3',
					'4','5','6','7','8','9'};

		for(int row=0;row<6;row++)
			for (int col=0;col<6;col++)
				this->matrix[row][col]=zv[row][col];
		
		UpdateRemChars();
		Resubstitute();
		PwdEnqueue(password);
	}
}

void CDlgAdfgvxManual::OnBnClickedButtonStringbox()
{
	DlgAdfgvxStringBox stringbox= new DlgAdfgvxStringBox();
	stringbox.DoModal();

	CString pwd=stringbox.GetInput();
	int result=0;
	if (pwd.GetLength()>0)
	{
		result=cipher->CheckStringBox(pwd);
				
		switch(result)
		{
			//wrong string length
			case 1: 
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_STRINGLENGTH,pc_str,STR_LAENGE_STRING_TABLE);
					MessageBox(pc_str);
					break;
				}
			//invalid characters contained
			case 2:	
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_STRINGINVALID,pc_str,STR_LAENGE_STRING_TABLE);
					MessageBox(pc_str);
					break;
				}
			//redundant characters
			case 3: 
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_STRINGREDUNDANT,pc_str,STR_LAENGE_STRING_TABLE);
					MessageBox(pc_str);
					break;
				}
			case 0: 
				{
					int counter=0;
					for(int row=0;row<6;row++)
						for (int col=0;col<6;col++)
							this->matrix[row][col]=pwd.GetAt(counter++);
					break;
				}
		}
		delete stringbox;
	}

	//synchronize data with textfields
	UpdateData(false);
	Resubstitute();
}

void CDlgAdfgvxManual::OnBnClickedResubstitute()
{
	Resubstitute();
	//enqueue password: update the subKey
	PwdEnqueue(password);
}

void CDlgAdfgvxManual::OnBnClickedInsertKey()
{
	CString key; 
	PasteKey("ADFGVX",key);
	//position of ',' first part represent passwort, 
	//second one the serialized matrix
	int split = key.Find(',');
	//set password variable for dialog
	password = key.Left(split);
	UpdateData(false);
	
	if(validCiphertext)
	{
		//permutate the ciphertext with the password
		OnCbnEditchangePasswordBox();
		OnBnClickedButtonForce();
	}
	//partly solved adfgvx-texts consisting of plaintext characters and adfgvx-bigrams
	else
	{
		analysed=true;
		buttonResub.EnableWindow(true);
		buttonResetMatrix.EnableWindow(true);
		buttonStdMatrix.EnableWindow(true);
		buttonStringBox.EnableWindow(true);
	}

	//set matrix variables for dialog
	for (int row=0;row<6;row++)
		for(int col=0;col<6;col++)
			this->matrix[row][col] = key[split+2+row*6+col];
	//synchronize data : set textfields to values of variables
	UpdateData(false);
	
	Resubstitute();
}


//function that adds newly found or user-defined passwords to a queue
void CDlgAdfgvxManual::PwdEnqueue(CString pwd)
{
	//pwdList-structure: 0-35 substitution, 36-x transposition

	//read the current substitution matrix and write it to CString subKey
	subKey="";
	for(int row=0;row<6;row++)
			for (int col=0;col<6;col++)
				subKey.Append(matrix[row][col]);

	//check the pwdList whether the pwd is already contained, if so, update the subKey
	bool newPwd=true;
	for(int i=0;i<50;i++)
		if(pwdList[i].Mid(36)==pwd)
		{
			pwdList[i]=subKey+pwd;
			newPwd=false;
		}

	//new pwd: reorganise the combobox
	if(newPwd)
	{
		pwdListBox.ResetContent();

		for(int i=49;i>0;i--)
		{	
			if(this->pwdList[i-1]!="")
			{
				this->pwdList[i]=pwdList[i-1];
				pwdListBox.InsertString(0,pwdList[i].Mid(36));
			}
		}
		this->pwdList[0]=subKey+pwd;

		pwdListBox.InsertString(0,pwdList[0].Mid(36));
		pwdListBox.SelectString(0,pwdList[0].Mid(36));
		
		UpdateData(false);
	}
	
}	


// thread starting function still to come
/*
static UINT StaticThread(LPVOID param)
{
	((CDlgAdfgvxManual*)param)->Permutate();
	return 0;
}
*/




//******************************************************************************
// the following 36 functions call CheckInput to check all edit-control-fields
void CDlgAdfgvxManual::OnEnChangeM00()
{	
	oldEntry=matrix[0][0];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[0][0]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[0][0]=CheckInput(oldEntry, matrix[0][0]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM01()
{	
	oldEntry=matrix[0][1];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[0][1]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[0][1]=CheckInput(oldEntry, matrix[0][1]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM02()
{	
	oldEntry=matrix[0][2];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[0][2]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[0][2]=CheckInput(oldEntry, matrix[0][2]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM03()
{	
	oldEntry=matrix[0][3];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[0][3]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[0][3]=CheckInput(oldEntry, matrix[0][3]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM04()
{	
	oldEntry=matrix[0][4];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[0][4]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[0][4]=CheckInput(oldEntry, matrix[0][4]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM05()
{	
	oldEntry=matrix[0][5];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[0][5]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[0][5]=CheckInput(oldEntry, matrix[0][5]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM10()
{	
	oldEntry=matrix[1][0];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[1][0]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[1][0]=CheckInput(oldEntry, matrix[1][0]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM11()
{	
	oldEntry=matrix[1][1];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[1][1]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[1][1]=CheckInput(oldEntry, matrix[1][1]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM12()
{	
	oldEntry=matrix[1][2];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[1][2]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[1][2]=CheckInput(oldEntry, matrix[1][2]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM13()
{	
	oldEntry=matrix[1][3];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[1][3]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[1][3]=CheckInput(oldEntry, matrix[1][3]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM14()
{	
	oldEntry=matrix[1][4];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[1][4]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[1][4]=CheckInput(oldEntry, matrix[1][4]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM15()
{	
	oldEntry=matrix[1][5];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[1][5]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[1][5]=CheckInput(oldEntry, matrix[1][5]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM20()
{	
	oldEntry=matrix[2][0];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[2][0]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[2][0]=CheckInput(oldEntry, matrix[2][0]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM21()
{	
	oldEntry=matrix[2][1];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[2][1]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[2][1]=CheckInput(oldEntry, matrix[2][1]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM22()
{	
	oldEntry=matrix[2][2];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[2][2]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[2][2]=CheckInput(oldEntry, matrix[2][2]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM23()
{	
	oldEntry=matrix[2][3];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[2][3]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[2][3]=CheckInput(oldEntry, matrix[2][3]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM24()
{	
	oldEntry=matrix[2][4];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[2][4]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[2][4]=CheckInput(oldEntry, matrix[2][4]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM25()
{	
	oldEntry=matrix[2][5];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[2][5]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[2][5]=CheckInput(oldEntry, matrix[2][5]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM30()
{	
	oldEntry=matrix[3][0];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[3][0]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[3][0]=CheckInput(oldEntry, matrix[3][0]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM31()
{	
	oldEntry=matrix[3][1];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[3][1]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[3][1]=CheckInput(oldEntry, matrix[3][1]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM32()
{	
	oldEntry=matrix[3][2];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[3][2]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[3][2]=CheckInput(oldEntry, matrix[3][2]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM33()
{	
	oldEntry=matrix[3][3];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[3][3]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[3][3]=CheckInput(oldEntry, matrix[3][3]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM34()
{	
	oldEntry=matrix[3][4];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[3][4]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[3][4]=CheckInput(oldEntry, matrix[3][4]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM35()
{	
	oldEntry=matrix[3][5];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[3][5]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[3][5]=CheckInput(oldEntry, matrix[3][5]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM40()
{	
	oldEntry=matrix[4][0];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[4][0]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[4][0]=CheckInput(oldEntry, matrix[4][0]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM41()
{	
	oldEntry=matrix[4][1];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[4][1]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[4][1]=CheckInput(oldEntry, matrix[4][1]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM42()
{	
	oldEntry=matrix[4][2];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[4][2]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[4][2]=CheckInput(oldEntry, matrix[4][2]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM43()
{	
	oldEntry=matrix[4][3];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[4][3]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[4][3]=CheckInput(oldEntry, matrix[4][3]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM44()
{	
	oldEntry=matrix[4][4];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[4][4]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[4][4]=CheckInput(oldEntry, matrix[4][4]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM45()
{	
	oldEntry=matrix[4][5];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[4][5]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[4][5]=CheckInput(oldEntry, matrix[4][5]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM50()
{	
	oldEntry=matrix[5][0];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[5][0]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[5][0]=CheckInput(oldEntry, matrix[5][0]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM51()
{	
	oldEntry=matrix[5][1];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[5][1]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[5][1]=CheckInput(oldEntry, matrix[5][1]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM52()
{	
	oldEntry=matrix[5][2];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[5][2]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[5][2]=CheckInput(oldEntry, matrix[5][2]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM53()
{	
	oldEntry=matrix[5][3];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[5][3]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[5][3]=CheckInput(oldEntry, matrix[5][3]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM54()
{	
	oldEntry=matrix[5][4];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[5][4]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[5][4]=CheckInput(oldEntry, matrix[5][4]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}

void CDlgAdfgvxManual::OnEnChangeM55()
{	
	oldEntry=matrix[5][5];
	UpdateData(TRUE);
	if(!analysed)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_8,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		matrix[5][5]=oldEntry;
		UpdateData(false);
	}
	else
	{
		matrix[5][5]=CheckInput(oldEntry, matrix[5][5]);
		//UpdateData(false);
		UpdateRemChars();
		//Resubstitute();
		CDialog::NextDlgCtrl();
	}
}


//***************************************************





