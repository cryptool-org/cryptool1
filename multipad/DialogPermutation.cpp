// DialogPermutation.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "AscEdit.h"
#include "DialogPermutation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPermutation 


CDialogPermutation::CDialogPermutation(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPermutation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogPermutation)
	m_Perm1 = _T("");
	m_Perm2 = _T("");
	m_P1out = _T("");
	m_P2out = _T("");
	m_P1InSeq = 0;
	m_P1OutSeq = 1;
	m_P2InSeq = 0;
	m_P2OutSeq = 1;
	//}}AFX_DATA_INIT
}


void CDialogPermutation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogPermutation)
	DDX_Control(pDX, IDC_BUTTON1, m_Decrypt);
	DDX_Control(pDX, IDOK, m_Encrypt);
	DDX_Control(pDX, IDC_EDIT2, m_CPerm2);
	DDX_Control(pDX, IDC_EDIT1, m_CPerm1);
	DDX_Text(pDX, IDC_EDIT1, m_Perm1);
	DDV_MaxChars(pDX, m_Perm1, 32);
	DDX_Text(pDX, IDC_EDIT2, m_Perm2);
	DDV_MaxChars(pDX, m_Perm2, 32);
	DDX_Text(pDX, IDC_EDIT3, m_P1out);
	DDX_Text(pDX, IDC_EDIT4, m_P2out);
	DDX_Radio(pDX, IDC_RADIO1, m_P1InSeq);
	DDX_Radio(pDX, IDC_RADIO3, m_P1OutSeq);
	DDX_Radio(pDX, IDC_RADIO5, m_P2InSeq);
	DDX_Radio(pDX, IDC_RADIO7, m_P2OutSeq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogPermutation, CDialog)
	//{{AFX_MSG_MAP(CDialogPermutation)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDialogPermutation 

void CDialogPermutation::OnDecrypt() 
{
	UpdateData(TRUE);
	m_P1len = MakePerm(&m_Perm1, m_P1, m_P1inv);
	if(m_P1len <= 0) {
		m_CPerm1.SetFocus();
		return;
	}
	m_P2len = MakePerm(&m_Perm2, m_P2, m_P2inv);
	if(m_P2len < 0) {
		m_CPerm2.SetFocus();
		return;
	}
	m_Dec = 1;

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	CString Primes = CString("PARAMETER: ") + char(m_P1InSeq + '0') + ' ' + char(m_P1OutSeq + '0') +
	                                    ' ' + char(m_P2InSeq + '0') + ' ' + char(m_P2OutSeq + '0');
	CopyKey ( pc_str, Primes );

	OnOK();
}

void CDialogPermutation::OnEncrypt() 
{
	UpdateData(TRUE);
	m_P1len = MakePerm(&m_Perm1, m_P1, m_P1inv);
	if(m_P1len <= 0) {
		m_CPerm1.SetFocus();
		return;
	}
	m_P2len = MakePerm(&m_Perm2, m_P2, m_P2inv);
	if(m_P2len < 0) {
		m_CPerm2.SetFocus();
		return;
	}
	m_Dec = 0;

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	CString Primes = CString("PARAMETER: ") + char(m_P1InSeq + '0') + ' ' + char(m_P1OutSeq + '0') +
	                                    ' ' + char(m_P2InSeq + '0') + ' ' + char(m_P2OutSeq + '0');
	CopyKey ( pc_str, Primes );

	OnOK();
}



int CDialogPermutation::MakePerm( CString *Pin, int p[], int pinv[])
{
	int i, j, k, id[26], plen;

	if(Pin->GetLength() == 0) return 0;
	if(isdigit((*Pin)[0])) return MakePermInt( Pin, p, pinv);
	Pin->MakeUpper();
	for(i=0;i<Pin->GetLength();) {
		if(strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", Pin->GetAt(i)))
			i++;
		else
			Pin->Delete(i);
	}
	plen = min(Pin->GetLength(), 26);
	if(plen == 0) return 0;
	for(i=0;i<plen;i++) id[i]=i;
	for(i=0;i<plen;i++) {
		j = (Pin->GetAt(i)-'A') % (plen-i);
		p[i] = id[j];
		for(k=j; k<(plen-i); k++) id[k] = id[k+1];
	}
	for(i=0; i<plen; i++) pinv[p[i]]=i;

	return plen;
}

void CDialogPermutation::OnChangeEdit1() 
{
	int l;
	char buffer[1024];

	UpdateData(TRUE);
	m_CPerm1.EmptyUndoBuffer();
	l= m_Perm1.GetLength();
	if(l>1) {
		m_Decrypt.EnableWindow(TRUE);
		m_Encrypt.EnableWindow(TRUE);
		if(isalpha(m_Perm1[0])) {
			MakePerm(&m_Perm1, m_P1, m_P1inv);
			m_P1len = l;
			PrintPerm(buffer, m_P1, m_P1len);
			m_P1out = buffer;
		}
		else {
			makeASCII(m_Perm1);
			m_P1out = "";
			m_P1len = -1;
		}
	}
	else {
		m_Decrypt.EnableWindow(FALSE);
		m_Encrypt.EnableWindow(FALSE);
		m_P1out = "( 1 )";
	}
	UpdateData(FALSE);
}

void CDialogPermutation::OnChangeEdit2() 
{
	int l;
	char buffer[1024];

	UpdateData(TRUE);
	m_CPerm2.EmptyUndoBuffer();
	l= m_Perm2.GetLength();
	if(l>1) {
		if(isalpha(m_Perm2[0])) {
			MakePerm(&m_Perm2, m_P2, m_P2inv);
			m_P2len = l;
			PrintPerm(buffer, m_P2, m_P2len);
			m_P2out = buffer;
		}
		else {
			makeASCII(m_Perm2);
			m_P2out = "";
			m_P2len = -1;
		}
	}
	else {
		m_P2out = "( 1 )";
	}
	UpdateData(FALSE);
}

BOOL CDialogPermutation::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LoadString(AfxGetInstanceHandle(),IDS_PARAM_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	CString Primes;
	if ( PasteKey( pc_str, Primes ) )
	{
		UpdateData(true);
		int d = strlen("PARAMETER: ");
		m_P1InSeq  = (int)(Primes[d]   - '0');
		m_P1OutSeq = (int)(Primes[d+2] - '0');
		m_P2InSeq  = (int)(Primes[d+4] - '0');
		m_P2OutSeq = (int)(Primes[d+6] - '0');
		UpdateData(false);
	}
	else
	{
		UpdateData(true);
		int d = Primes.Find("PARAMETER: ", 0);
		m_P1InSeq  = 0;
		m_P1OutSeq = 1;
		m_P2InSeq  = 0;
		m_P2OutSeq = 1;
		UpdateData(false);
	}
	

	m_Decrypt.EnableWindow(FALSE);
	m_Encrypt.EnableWindow(FALSE);
	m_P1out = m_P2out = "( 1 )";
	UpdateData(FALSE);

	CString Title;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	Title = pc_str;
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

int CDialogPermutation::PrintPerm(char *dest, int *perm, int len)
{
	int i;
	char buffer[32];

	if(len < 2) {
		strcpy(dest,"( 1 )");
		return strlen(dest);
	}
	sprintf(dest,"( %d", perm[0]+1);
	for(i=1;i<len;i++) {
		sprintf(buffer,", %d", perm[i]+1);
		strcat(dest, buffer);
	}
	strcat(dest, " )");
	return strlen(dest);
}


//DEL void CDialogPermutation::OnCopyKey() 
//DEL {
//DEL 	HANDLE hndl;
//DEL 	char *globBuff;
//DEL 	int k;
//DEL 	CString buffer;
//DEL 
//DEL 	OpenClipboard();
//DEL 	hndl = ::GetClipboardData(CF_TEXT);
//DEL 	globBuff = (char *) GlobalLock(hndl);
//DEL 	buffer = globBuff;
//DEL 	GlobalUnlock(hndl);
//DEL 	CloseClipboard();
//DEL 	k = buffer.Find(';');
//DEL 	if(k==-1) {
//DEL 		m_Perm1 = makeASCII(buffer);
//DEL 		m_Perm2.Empty();
//DEL 	}
//DEL 	else {
//DEL 		m_Perm1 = makeASCII(buffer.Left(k));
//DEL 		m_Perm2 = makeASCII(buffer.Right(buffer.GetLength()-k-1));
//DEL 	}
//DEL 	UpdateData(FALSE);
//DEL 	OnChangeEdit1();
//DEL 	OnChangeEdit2();
//DEL }

void CDialogPermutation::OnPasteKey() 
{
	CString buffer;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
	if ( PasteKey(pc_str, buffer) )
	{
		UpdateData(TRUE);
		int k = buffer.Find(';');
		if(k==-1) {
			int k = buffer.Find("PARAMETER: ", 0);
			if ( k > 0 )
			{
				m_Perm1 = makeASCII(buffer.Left(k));
				k += strlen("PARAMETER: ");
				m_P1InSeq  = (int)(buffer[k]   - '0');
				m_P1OutSeq = (int)(buffer[k+2] - '0');
				m_P2InSeq  = (int)(buffer[k+4] - '0');
				m_P2OutSeq = (int)(buffer[k+6] - '0');
			}
			else
			{
				m_Perm1 = makeASCII(buffer);
			}
			m_Perm2.Empty();

		}
		else {
			m_Perm1 = makeASCII(buffer.Left(k));
			int d = buffer.Find("PARAMETER: ", 0);
			if ( d > 0 )
			{
				m_Perm2 = makeASCII(buffer.Mid(k+1,(d-k)-1));
				d += strlen("PARAMETER: ");
				m_P1InSeq  = (int)(buffer[d]   - '0');
				m_P1OutSeq = (int)(buffer[d+2] - '0');
				m_P2InSeq  = (int)(buffer[d+4] - '0');
				m_P2OutSeq = (int)(buffer[d+6] - '0');
			}
			else
			{
				m_Perm2 = makeASCII(buffer.Right(buffer.GetLength()-k-1));
			}
		}
		UpdateData(FALSE);
		OnChangeEdit1();
		OnChangeEdit2();
	}
}

CString CDialogPermutation::makeASCII(CString &line)
{
	int p, l;

	l = line.GetLength();
	if(l==0) return line;
	if(isalpha(line[0])) { // Alpha mode
		for(p = 0; p<l; p++) {
			if(!strchr("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", line[p])) {
				line.Delete(p);
				p--;
				l--;
			}
		}
	}
	else { // numerischer Modus
		for(p = 0; p<l; p++) {
			if(!strchr("0123456789,", line[p])) {
				line.Delete(p);
				p--;
				l--;
			}
		}
	}
	return line;
}

int CDialogPermutation::MakePermInt(CString *Pin, int p[], int pinv[])
{
	int i, j, k, plen, m, r, e;
	char buffer[1024];

	i = plen = m = 0;
	do {
		do {
			j = Pin->Find(',',i+1);
			if(j!=i-1) break;
			i++;
		} while(1);
		if(j==-1)
			e = Pin->GetLength() - i;
		else
			e = j-i;
		k = atoi(Pin->Mid(i,e))-1;
		i = j+1;
		if(k>=32) { // Fehler: zu großer Wert
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM ,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM_NUM_2_BIG,pc_str1,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str1,pc_str,MB_ICONWARNING|MB_OK);
			return -1;
		}
		m = max(m,k);
		for(r=0;r<plen;r++) {
			if(k == p[r]) { // Fehler doppelter Wert
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM ,pc_str,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM_DUPLICATE,pc_str1,STR_LAENGE_STRING_TABLE);
				sprintf(buffer, pc_str1, k+1);
				MessageBox(buffer,pc_str,MB_ICONWARNING|MB_OK);
				return -1;
			}
		}
		p[plen] = k;
		pinv[k] = plen;
		plen++;
	} while (j>=0);

	for(i=0;i<plen;i++) {
		for(j=0;j<plen;j++) {
			if(p[j] == i) break;
		}
		if(j>=plen) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM ,pc_str,STR_LAENGE_STRING_TABLE);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_PERM_MISSING,pc_str1,STR_LAENGE_STRING_TABLE);
			sprintf(buffer, pc_str1, i+1);
			MessageBox(buffer,pc_str,MB_ICONWARNING|MB_OK);
			return -1;
		}
	}

	return plen;
}
