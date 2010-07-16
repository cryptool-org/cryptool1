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

// DlgSecretSharingSetup.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "IntegerArithmetic.h"
#include "DlgSecretSharingSetup.h"
#include "DlgSecretSharingIntro.h"
#include "DlgSecretSharingParameter.h"
#include "DlgSecretSharingReveal.h"
#include "DlgSecretSharingOptions.h"
#include "SecretSharingLog.h"
#include ".\dlgsecretsharingsetup.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgSecretSharingSetup-Dialogfeld

CDlgSecretSharingSetup::CDlgSecretSharingSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSecretSharingSetup::IDD, pParent)
	, m_show_intro(FALSE)
{
	//{{AFX_DATA_INIT(CDlgSecretSharingSetup)
	m_secret = _T("");
	m_threshold = _T("");
	m_polynom = _T("");
	m_participants = _T("");
	m_values = _T("");
	m_modulus = _T("");
	//}}AFX_DATA_INIT

	this->logFile = NULL;
	this->primeFlag = false;
	this->coeffFlag = false;
	this->coeff = NULL;
}

CDlgSecretSharingSetup::~CDlgSecretSharingSetup()
{
	delete this->logFile;
}

void CDlgSecretSharingSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSecretSharingSetup)
	DDX_Control(pDX, IDC_BUTTON_GENERATE, m_ctrl_ButtonPolynom);
	DDX_Text(pDX, IDC_EDIT_SECRET, m_secret);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_threshold);
	DDX_Text(pDX, IDC_EDIT_POLYNOM, m_polynom);
	DDX_Text(pDX, IDC_EDIT_PARTICIPANTS, m_participants);
	DDX_Control(pDX, IDC_BUTTON_UPDATE, m_ctrl_ButtonUpdate);
	DDX_Control(pDX, IDC_LIST_SHARES, m_list_shares);
	DDX_Control(pDX, IDC_EDIT_SECRET, m_ctrl_secret);
	DDX_Control(pDX, IDC_EDIT_THRESHOLD, m_ctrl_threshold);
	DDX_Control(pDX, IDC_EDIT_PARTICIPANTS, m_ctrl_participants);
	DDX_Control(pDX, IDOK, m_ctrl_ButtonOK);
	DDX_Text(pDX, IDC_EDIT_MOD, m_modulus);
	DDX_Control(pDX, IDC_BUTTON_OPT, m_ctrl_ButtonOptions);
	DDX_Control(pDX, IDC_BUTTON_CHANGE, m_ctrl_ButtonParameter);
	DDX_Check(pDX, IDC_CHECK_SHOWINTRO, m_show_intro);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSecretSharingSetup, CDialog)
	//{{AFX_MSG_MAP(CDlgSecretSharingSetup)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDOK, OnButtonOk)
	ON_EN_UPDATE(IDC_EDIT_THRESHOLD, OnUpdateEditThreshold)
	ON_EN_UPDATE(IDC_EDIT_SECRET, OnUpdateEditSecret)
	ON_EN_UPDATE(IDC_EDIT_PARTICIPANTS, OnUpdateEditParticipants)
	ON_BN_CLICKED(IDC_BUTTON_OPT, OnButtonOpt)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
	ON_BN_CLICKED(IDC_CHECK_SHOWINTRO, OnButtonClickedCheckShowintro)
	ON_BN_CLICKED(IDC_BUTTON_EXAMPLE, OnButtonExample)
	//}}AFX_MSG_MAP	
	ON_NOTIFY(NM_CLICK, IDC_LIST_SHARES, OnNMClickListShares)
END_MESSAGE_MAP()

BOOL CDlgSecretSharingSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	unsigned long intro = FALSE;
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "SecretSharing" ) == ERROR_SUCCESS )
	{
		CT_READ_REGISTRY_DEFAULT(intro, "ShowIntroShamir", intro);
		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	if(intro)
	{
		CDlgSecretSharingIntro dlg; //Einführung anzeigen
		dlg.DoModal();
	}

	partyLimit = "30";
	primeLimit = "10000";
	int colWidth = 150;  //Spaltenbreite in Pixel
    m_list_shares.SetExtendedStyle( LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT );
	m_list_shares.InsertColumn( 0,"", LVCFMT_LEFT,20,0);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_MEMBER, pc_str, STR_LAENGE_STRING_TABLE);
	m_list_shares.InsertColumn( 1, pc_str, LVCFMT_LEFT, colWidth, 1);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_VALUESS, pc_str, STR_LAENGE_STRING_TABLE);
	m_list_shares.InsertColumn( 2, pc_str, LVCFMT_LEFT, colWidth, 2);
	LoadString(AfxGetInstanceHandle(), IDS_STRING_SHARE, pc_str, STR_LAENGE_STRING_TABLE);
	m_list_shares.InsertColumn( 3, pc_str, LVCFMT_LEFT, colWidth, 3);
	return TRUE;  
}

//prüft die Eingabewerte und generiert daraus das Polynom
void CDlgSecretSharingSetup::OnButtonGenerate()		
{
	UpdateData(true);
	//leere Eingabefelder abfangen
	if(m_secret.IsEmpty() || m_participants.IsEmpty() || m_threshold.IsEmpty())
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRETSHARING_EMPTY, pc_str, 100);
		AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
		return;
	}
	t = atoi(LPCSTR(m_threshold));
	n = atoi(LPCSTR(m_participants));
	s = atoi(LPCSTR(m_secret));
	if(t > n) //falls Schwellenwert größer als die Teilnehmerzahl
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRETSHARING_THRESHOLD, pc_str, 200);
		AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
		m_threshold = "";
		m_ctrl_ButtonPolynom.EnableWindow(false);
		UpdateData(false);
		return;
	}
	maxParties = atoi(LPCSTR(partyLimit));
	if(n > maxParties) //falls Teilnehmerzahl über eingegebenem Limit
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRETSHARING_PARTICIPANTS, pc_str, 100);
		AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
		m_threshold = "";
		m_participants = "";
		m_ctrl_ButtonPolynom.EnableWindow(false);
		UpdateData(false);
		return;
	}
	//Bestimmung der Primzahl (Gruppe)
	maxPrime = atoi(LPCSTR(primeLimit));
	if (maxPrime < n || maxPrime < s)
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRETSHARING_SMALLPRIME, pc_str, 200);
		AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
		this->OnButtonOpt();
		UpdateData(false);
		return;
	}
	else
	{
		if (n > s)
		{
			P.SetLimits(n, maxPrime);
		}
		else P.SetLimits(s, maxPrime);
	}
	BOOL flag = FALSE;
	while (!flag)
	{
		P.RandP();
		flag = P.FermatTest(100);
	}
	CString primeT;
	P.GetPrime(primeT);
	g = atoi(LPCSTR(primeT));

	//Arrays mit öffentlichen Werten bzw. Koeffizienten füllen
	coeff = new long[t-1]; 
	parameter = new long[n];
	int i;
	for (i=0; i<t-1; i++)
	{
		coeff[i] = (rand() % g) + 1;
	}
	//kein öffentlicher Wert darf zweimal vorkommen
	for (i=0; i<n; i++)
	{
newRand: long tmp = (rand() % g) + 1;
		for (int j=0; j<i; j++)
		{
			if (tmp == parameter[j])
			{
				goto newRand;
			}
		}
		parameter[i] = tmp;
	}
	GeneratePoly(coeff); //der String m_polynom enthält jetzt das zufällige Polynom
	m_modulus = primeT; //Anzeige des Modulus
	m_ctrl_ButtonParameter.EnableWindow(true);
	m_ctrl_ButtonUpdate.EnableWindow(true);
	m_list_shares.DeleteAllItems();
	UpdateData(false);
}

//Berechnung der Shares der Teilnehmer
void CDlgSecretSharingSetup::OnButtonUpdate()
{
	UpdateData(true);
	shares = new Big[n];
	CString pubValue, result;
	m_list_shares.DeleteAllItems(); //evt. vorhandene Einträge werden gelöscht
	//für jeden Teilnehmer wird der öffentliche Wert und das Share angezeigt
	for (int row = 0; row < n; row++)
	{
		CString number;
		CString entry = "";
		entry.LoadString(IDS_STRING_MEMBER2);
		entry+=" ";
		number.Format("%d", row+1);
		entry += number;
		m_list_shares.InsertItem(row, "");
		shares[row] = CalculateShare(coeff, parameter[row]);
		BigToCString(shares[row], result, 10);
		pubValue.Format("%d", parameter[row]);
		m_list_shares.SetItemText(row, 1, entry);
		m_list_shares.SetItemText(row, 2, pubValue);
		m_list_shares.SetItemText(row, 3, result);
	}
	m_ctrl_ButtonOK.EnableWindow(true);
	m_ctrl_ButtonUpdate.EnableWindow(false);
	m_ctrl_secret.SetReadOnly(true);
	m_ctrl_participants.SetReadOnly(true);
	m_ctrl_threshold.SetReadOnly(true);
	UpdateData(false);
}

// Übernimmt die Werte der ausgewählten Parameter und berechnet das Geheimnis
void CDlgSecretSharingSetup::OnButtonOk()
{
	UpdateData(true);
	int numberSelected = 0;
	int j = m_list_shares.GetItemCount();
	int i;
	isSelected = new bool[j]; 
	for (i=0; i<j; i++)
	{
		isSelected[i]=false;
	}

	//welche Teilnehmer wurden ausgewählt?
	for (i=0; i<j; i++)
	{
		//if (m_list_shares.GetItemState(i, LVIS_SELECTED))
		if (m_list_shares.GetCheck(i))
		{
			numberSelected++;
			isSelected[i]=true;
		}
		else isSelected[i]=false;
	}
	if (numberSelected < t)
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_SECRETSHARING_LESS, pc_str, 100);
		AfxMessageBox(pc_str, MB_ICONINFORMATION|MB_OK);
		return;
	}
	else
	{
		RevealSecret(numberSelected);
	}
}


// Wird eine Zahl eingegeben, wird der Button "Polynom generieren" aktiviert
void CDlgSecretSharingSetup::OnUpdateEditThreshold()
{
	UpdateData(TRUE);
	int sels, sele;
	m_ctrl_threshold.GetSel(sels, sele);
	bool isNumber = CheckEdit(m_threshold, sels, sele);
	m_polynom = "";
	m_modulus = "";
	m_list_shares.DeleteAllItems();
	m_ctrl_threshold.SetSel(sels, sele);
	if (isNumber)
	{
		m_ctrl_ButtonPolynom.EnableWindow(true);
	}
	UpdateData(false);
}

void CDlgSecretSharingSetup::OnUpdateEditSecret()
{
	UpdateData(true);
	int sels, sele;
	m_ctrl_secret.GetSel(sels, sele);
	CheckEdit(m_secret, sels, sele);
	m_polynom = "";
	m_modulus = "";
	m_list_shares.DeleteAllItems();
	UpdateData(false);
	m_ctrl_secret.SetSel(sels, sele);
}

void CDlgSecretSharingSetup::OnUpdateEditParticipants()
{
	UpdateData(true);
	int sels, sele;
	m_ctrl_participants.GetSel(sels, sele);
	CheckEdit(m_participants, sels, sele);
	m_polynom = "";
	m_modulus = "";
	m_list_shares.DeleteAllItems();
	UpdateData(false);
	m_ctrl_participants.SetSel(sels, sele);
}


//generiert ein Polynom vom Grad t-1
void CDlgSecretSharingSetup::GeneratePoly(long *co)
{
	char expo[11], tmp[11];
	m_polynom = m_secret;
	for (int i=0; i<t-1; i++)
	{
		int n = _snprintf(tmp, sizeof(tmp), "%i", co[i]);
		ASSERT(n < sizeof(tmp));
		m_polynom += '+';
		m_polynom += tmp;
		m_polynom += 'x';
		if (i>0)
		{
			n = _snprintf(expo, sizeof(expo), "%i", i+1);
			ASSERT(n < sizeof(expo));
			m_polynom += '^';
			m_polynom += expo;
		}
	}
}

//berechnet das Share eines Teilnehmers
Big CDlgSecretSharingSetup::CalculateShare(long *co, long par)
{
	Big share = s;
	Big paraBig = par;
	for (int i=0; i<(t-1); i++)
	{
		Big expo;
		Big coBig = co[i];
		expo = pow(paraBig, i+1, g); 
		expo = modmult(coBig, expo, g);
		share += expo; 
	}
	share %= g;
	return share;
}

//sorgt für die syntaktisch richtige Eingabe und entfernt führende Nullen
bool CDlgSecretSharingSetup::CheckEdit(CString &m_edit, int & sels, int & sele)
{
	bool isNumber = false;
	while((0==m_edit.IsEmpty())&&('0'==m_edit.GetAt(0)))
	{
		m_edit = m_edit.Right(m_edit.GetLength()-1);
		sels=sele=0;								
	}
	int exp_counter = 0;
	for(int i=0; i < m_edit.GetLength(); i++)
	{
		char ch = m_edit.GetAt(i);
		if((ch>='0')&&(ch<='9'))
		{	
			isNumber = true;
		}
		else
		{
			m_edit = m_edit.Left(i) + m_edit.Right(m_edit.GetLength()-i-1);	
			if(i<=sele)
			{
				sele--;
				sels--;
			}
			i--;
		}
	}
	return isNumber;
}

//öffnet Dialog zur Anzeige des rekonstruierten Geheimnisses
void CDlgSecretSharingSetup::RevealSecret(int sel)
{
	int i;
	int numberSelected = sel; //Anzahl der ausgewählten Teilnehmer
	Big *prePub, *preVal; 
	numerator = new Big[numberSelected];
	denominator = new Big[numberSelected];
	prePub = new Big[numberSelected];
	preVal = new Big[numberSelected];
	int j = 0;
	for (i=0; i<n; i++)
	{
		if (isSelected[i] == true)
		{
			prePub[j] = parameter[i];
			preVal[j] = shares[i];
			j++;
		}
	}

	//für jeden der ausgewählten Teilnehmer wird ein Summand berechnet
	for (i=0; i<numberSelected; i++)
	{
		Big ini = 1;
		numerator[i] = ini;
		denominator[i] = ini;
		for (int j=0; j<numberSelected; j++)
		{
			if (j != i)
			{
				numerator[i] *= prePub[j];
				Big sub = prePub[j] - prePub[i];
				denominator[i] *= sub;
			}
		}
		if (denominator[i] < 0)
		{
			numerator[i] = -numerator[i];
			denominator[i] = abs(denominator[i]);
		}
		ReduceFrac(i);
		denominator[i] = inverse(denominator[i], g);
		numerator[i] = numerator[i] * denominator[i] * preVal[i];
		numerator[i] %= g;
		result += numerator[i];
	}
	result %= g;
	while (result < 0)
	{
		result += g;
	}
	UpdateData(false);

	this->logFile = new SecretSharingLog(this->partyLimit,
								this->primeLimit,
								this->m_secret,
								this->m_participants,
								this->m_threshold,
								this->m_polynom,
								this->m_modulus,
								this->parameter,
								this->shares,
								this->isSelected,
								this->numerator,
								this->denominator,
								this->result,
								this->primeFlag,
								this->coeffFlag);
	CDlgSecretSharingReveal dlgNew(this->n, this->g, this->isSelected, this->parameter, this->shares, this->logFile, result);
	dlgNew.DoModal();
	result = 0;
	m_ctrl_ButtonOptions.EnableWindow(true);
	m_ctrl_participants.SetReadOnly(false);
	m_ctrl_secret.SetReadOnly(false);
	m_ctrl_threshold.SetReadOnly(false);
}

void CDlgSecretSharingSetup::ReduceFrac(int pos)
{
	Big tmp;
	tmp = gcd(numerator[pos], denominator[pos]);
		if (tmp != 0)
		{
			numerator[pos] /= tmp;
			denominator[pos] /= tmp;
		}//kuerzen
}

//öffnet den Dialog zur Einstellung weiterer Parameter
void CDlgSecretSharingSetup::OnButtonOpt()
{
	CDlgSecretSharingOptions *dlgOpt;
	dlgOpt = new CDlgSecretSharingOptions();
	dlgOpt->m_prime = primeLimit;
	dlgOpt->m_limit = partyLimit;
	UpdateData(true);
	if (dlgOpt->DoModal() == IDOK)
	{
		this->primeLimit = dlgOpt->m_prime;
		this->partyLimit = dlgOpt->m_limit;
		UpdateData(false);
	}
	delete dlgOpt;
}

void CDlgSecretSharingSetup::OnButtonChange()
{
	bool newCoeffFlag = false;
	CDlgSecretSharingParameter *dlgPara;
	dlgPara = new CDlgSecretSharingParameter(this->m_secret, this->m_participants, this->m_threshold, this->m_modulus, this->coeff, this->maxPrime, this->maxParties, newCoeffFlag); 
	
	/*
	if(dlgPara->DoModal() == IDCANCEL)
	{
		// Speicher freigeben
		delete dlgPara;
		return;
	}
	*/
	
	if(dlgPara->DoModal() == IDOK)
	{
		if ((this->m_modulus.Compare(dlgPara->m_myPrime) != 0) && (dlgPara->m_myPrime != ""))
		{
			this->m_modulus = dlgPara->m_myPrime;
			this->primeFlag = true;
		}
		if (newCoeffFlag == true)
		{
			this->coeffFlag = true;
			CString strCoefficients = dlgPara->m_myCoeff;
			CString strOneCoeff;
			int pos = 0;
			int nCount = 0;

			// FIXME !!!
			pos = strCoefficients.Find(',', pos);
			strOneCoeff = strCoefficients.Mid(0, pos);
			// Tokenize not supported in MFC 6 // strOneCoeff = strCoefficients.Tokenize(",", pos);
			while (strOneCoeff != "")
			{
				long singleCoeff = atoi(LPCSTR(strOneCoeff));
				coeff[nCount] = singleCoeff;

				// FIXME !!!
				int posOld = pos+1;
				pos = strCoefficients.Find(',', posOld);
				strOneCoeff = strCoefficients.Mid(posOld, pos - posOld);
				// Tokenize not supported in MFC 6 // strOneCoeff = strCoefficients.Tokenize(",", pos);
				nCount++;
			}
		}
		GeneratePoly(coeff);
		m_list_shares.DeleteAllItems();
		m_ctrl_ButtonUpdate.EnableWindow(true);
		UpdateData(false);
	}
}


void CDlgSecretSharingSetup::OnButtonClickedCheckShowintro()
{
	UpdateData(true);

	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "SecretSharing" ) == ERROR_SUCCESS ) {
		CT_WRITE_REGISTRY(m_show_intro, "ShowIntroShamir");
		CT_CLOSE_REGISTRY();
	}
	else {
		// FIXME	
	}
}


void CDlgSecretSharingSetup::OnButtonExample()
{
	m_secret = "18";
	m_participants = "10";
	m_threshold = "4";
	m_ctrl_ButtonPolynom.EnableWindow(true);
	UpdateData(false);
}

void CDlgSecretSharingSetup::OnNMClickListShares(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE testItem = (LPNMITEMACTIVATE) pNMHDR;
	int item = testItem->iItem;
	int subitem = testItem->iSubItem;
	//ListControl.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED );
	
	if(subitem > 0)
	{
		if (m_list_shares.GetItemState(item, LVIS_SELECTED))
		{
			m_list_shares.SetItemState(item, LVIS_SELECTED, LVIS_SELECTED );
			if(m_list_shares.GetCheck(item))
			{
				m_list_shares.SetCheck(item,0);
			}
			else
                m_list_shares.SetCheck(item,1);

			m_list_shares.SetSelectionMark(item);
		}
		else
		{
			m_list_shares.SetCheck(item,0);
		}
	}
	*pResult = 0;
}
