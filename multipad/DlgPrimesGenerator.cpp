// DlgPrimesGenerator.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgPrimesGenerator.h"
#include "zzgen.h"
#include "Primes_and_random_numbers.h"
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgPrimesGenerator 


DlgPrimesGenerator::DlgPrimesGenerator(CWnd* pParent /*=NULL*/)
	: CDialog(DlgPrimesGenerator::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgPrimesGenerator)
	m_radio1 = 0;
	m_radio4 = 0;
	m_edit1 = _T("1");
	m_edit2 = _T("50000");
	m_edit3 = _T("1");
	m_edit4 = _T("50000");
	m_edit5 = _T("0");
	m_edit6 = _T("0");
	//}}AFX_DATA_INIT
}


void DlgPrimesGenerator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgPrimesGenerator)
	DDX_Control(pDX, IDC_EDIT2, m_control_edit2);
	DDX_Control(pDX, IDC_EDIT1, m_control_edit1);
	DDX_Control(pDX, IDC_BUTTON_GENERATE, m_control_button_generate);
	DDX_Control(pDX, IDC_BUTTON_ACCEPT, m_control_button_accept);
	DDX_Control(pDX, IDC_EDIT4, m_control_edit4);
	DDX_Control(pDX, IDC_EDIT3, m_control_edit3);
	DDX_Radio(pDX, IDC_RADIO1, m_radio1);
	DDX_Radio(pDX, IDC_RADIO4, m_radio4);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDV_MaxChars(pDX, m_edit1, 15);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDV_MaxChars(pDX, m_edit2, 15);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDV_MaxChars(pDX, m_edit3, 15);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDV_MaxChars(pDX, m_edit4, 15);
	DDX_Text(pDX, IDC_EDIT5, m_edit5);
	DDX_Text(pDX, IDC_EDIT6, m_edit6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgPrimesGenerator, CDialog)
	//{{AFX_MSG_MAP(DlgPrimesGenerator)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, OnButtonGenerate)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_EN_UPDATE(IDC_EDIT3, OnUpdateEdit3)
	ON_EN_UPDATE(IDC_EDIT4, OnUpdateEdit4)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT, OnButtonAccept)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten DlgPrimesGenerator 

void DlgPrimesGenerator::OnRadio4() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(true);
	m_control_edit4.EnableWindow(true);
	UpdateData(false);
}

void DlgPrimesGenerator::OnRadio5() 
{
	UpdateData(true);
	m_control_edit3.EnableWindow(false);
	m_control_edit4.EnableWindow(false);
	UpdateData(false);
}

BOOL DlgPrimesGenerator::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Zusätzliche Initialisierung hier einfügen
	
	m_control_button_accept.EnableWindow(false);
	//m_control_button_generate.EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void DlgPrimesGenerator::OnButtonGenerate() 

		// erzeugt zwei Zufalls-Primzahlen innerhalb der angegebenen Grenzen
{
	UpdateData(true);

	if(0==m_radio4)
	{
		if((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty())&&(0==m_edit3.IsEmpty())&&(0==m_edit4.IsEmpty()))
		{
			if((Get_Value(m_edit1)<=Get_Value(m_edit2))&&(Get_Value(m_edit3)<=Get_Value(m_edit4)))
			{
				if((Get_Value(m_edit1)*Get_Value(m_edit3))<(c_MaxPrime_low))
				{
					theApp.DoWaitCursor(0);
					long prime1=Get_Random_Value(m_edit1,m_edit2);
					if(0!=prime1)
					{
						itoa(prime1,m_edit5.GetBuffer(20),10);						
					}
					else
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING42004,pc_str,STR_LAENGE_STRING_TABLE);
						sprintf(line,pc_str);
						AfxMessageBox(line);
					}

					long prime2=Get_Random_Value(m_edit3,m_edit4);
					if(0!=prime2)
					{
						itoa(prime2,m_edit6.GetBuffer(20),10);
					}
					else
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING42005,pc_str,STR_LAENGE_STRING_TABLE);
						sprintf(line,pc_str);
						AfxMessageBox(line);
					}
					theApp.DoWaitCursor(-1);
				}
				else
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING42003,pc_str,STR_LAENGE_STRING_TABLE);
					sprintf(line,pc_str,c_MaxPrime_low);
					AfxMessageBox(line);
				}
			}
			else
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING42001,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
			}
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING42000,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);
		}
	}

	else
	{
		if((0==m_edit1.IsEmpty())&&(0==m_edit2.IsEmpty()))
		{
			if(Get_Value(m_edit1)<=Get_Value(m_edit2))
			{
				if((Get_Value(m_edit1)*Get_Value(m_edit1))<(c_MaxPrime_low))
				{
					theApp.DoWaitCursor(0);
					long prime1=Get_Random_Value(m_edit1,m_edit2);
					if(0!=prime1)
					{
						itoa(prime1,m_edit5.GetBuffer(20),10);						
					}
					else
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING42004,pc_str,STR_LAENGE_STRING_TABLE);
						sprintf(line,pc_str);
						AfxMessageBox(line);
					}

					long prime2=Get_Random_Value(m_edit1,m_edit2);
					if(0!=prime2)
					{
						itoa(prime2,m_edit6.GetBuffer(20),10);
					}
					else
					{
						LoadString(AfxGetInstanceHandle(),IDS_STRING42005,pc_str,STR_LAENGE_STRING_TABLE);
						sprintf(line,pc_str);
						AfxMessageBox(line);
					}
					theApp.DoWaitCursor(-1);
				}
				else
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING42002,pc_str,STR_LAENGE_STRING_TABLE);
					sprintf(line,pc_str,long(sqrt(c_MaxPrime_low)));
					AfxMessageBox(line);
				}
			}
			else
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING42001,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(line,pc_str);
				AfxMessageBox(line);
			}
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING42000,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(line,pc_str);
			AfxMessageBox(line);
		}
	}

	if(("0"!=m_edit5)&&("0"!=m_edit6))
	{
		m_control_button_accept.EnableWindow(true);
	}

	UpdateData(false);
}

void DlgPrimesGenerator::OnUpdateEdit1() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit1.GetSel(sels,sele);
	CheckEdit_Input(m_edit1,sels,sele);
	UpdateData(false);
	m_control_edit1.SetSel(sels,sele);
}

double DlgPrimesGenerator::Get_Value(CString m_edit)

		// liefert den double-Wert eines CString unter Berücksichtigung des '^'-Zeichens zurück
{
	int exp_pos=m_edit.Find('^');
	if((exp_pos<0)||('^'==m_edit[m_edit.GetLength()-1]))
	{
		return(double(atof(m_edit)));
	}
	return(pow(double(atof(m_edit.Left(exp_pos))),double(atof(m_edit.Right(m_edit.GetLength()-exp_pos-1)))));
}

void DlgPrimesGenerator::CheckEdit_Input(CString & m_edit, int & sels, int & sele)

		// sorgt dafür, daß keine syntaktisch falsche Eingabe in die Ober- und Untergrenze-Eingabefelder
		// möglich ist, führende Nullen werden entfernt, die Variablen sels und sele dienen der
		// Formatierung
{
	while((0==m_edit.IsEmpty())&&('0'==m_edit.GetAt(0)))
	{
		m_edit=m_edit.Right(m_edit.GetLength()-1);
		sels=sele=0;								
	}

	int exp_counter=0;
	for(int i=0;i<m_edit.GetLength();i++)
	{
		char ch=m_edit.GetAt(i);
		if((ch>='0')&&(ch<='9'))
		{
			
		}
		else if('^'==ch)
		{
			if(0==i)
			{
				m_edit=m_edit.Right(m_edit.GetLength()-1);
				sels=sele=0;
			}
			if(0==exp_counter)
			{
				exp_counter=1;
			}
			else
			{
				m_edit=m_edit.Left(i)+m_edit.Right(m_edit.GetLength()-i-1);
				if(i<=sele)
				{
					sele--;
					sels--;
				}
				i--;
			}
		}
		else
		{
			m_edit=m_edit.Left(i)+m_edit.Right(m_edit.GetLength()-i-1);		
			if(i<=sele)
			{
				sele--;
				sels--;
			}
			i--;
		}
	}

	if(Get_Value(m_edit)>LONG_MAX)
	{
		if(0==exp_counter)
		{
			while(Get_Value(m_edit)>LONG_MAX)
			{
				m_edit=m_edit.Left(m_edit.GetLength()-1);
			}
		}
		else
		{
			itoa(LONG_MAX,m_edit.GetBuffer(20),10);
			sels=sele=20;
		}
	}
}

void DlgPrimesGenerator::OnUpdateEdit2() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit2.GetSel(sels,sele);
	CheckEdit_Input(m_edit2,sels,sele);
	UpdateData(false);
	m_control_edit2.SetSel(sels,sele);
}

void DlgPrimesGenerator::OnUpdateEdit3() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit3.GetSel(sels,sele);
	CheckEdit_Input(m_edit3,sels,sele);
	UpdateData(false);
	m_control_edit3.SetSel(sels,sele);	
}

void DlgPrimesGenerator::OnUpdateEdit4() 
{
	UpdateData(true);
	int sels,sele;
	m_control_edit4.GetSel(sels,sele);
	CheckEdit_Input(m_edit4,sels,sele);
	UpdateData(false);
	m_control_edit4.SetSel(sels,sele);
}

long DlgPrimesGenerator::Get_Prime1()

		// diese und die nächste Funktion können aus anderen Klassen aufgerufen werden, um sich dorthin
		// zwei Primzahlen zu holen
{
	return(atol(m_edit5));
}

long DlgPrimesGenerator::Get_Prime2()
{
	return(atol(m_edit6));
}

void DlgPrimesGenerator::OnCancel() 

		// wenn der Button "Abbrechen" gewählt wird, werden die Primzahlen auf 0 gesetzt
{
	m_edit5=m_edit6="0";	
	CDialog::OnCancel();
}

void DlgPrimesGenerator::OnButtonAccept() 

		// wenn der Button "Übernehmen" gewählt wird, kann der Dialog nur verlassen werden,
		// wenn das Produkt der beiden Primzahlen kleiner als c_MaxPrime_high ist
{
	double product=(Get_Value(m_edit5)*Get_Value(m_edit6));
	if(product<c_MaxPrime_high)
	{
		CDialog::OnCancel();
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING42006,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,c_MaxPrime_high);
		AfxMessageBox(line);
	}
}

long DlgPrimesGenerator::Get_Random_Value(CString lower_limit, CString upper_limit)

		// ruft den Algorithmus zur Erzeugung einer Zufallszahl und danach den Test-Algorithmus auf, den
		// der Anwender benutzen möchte
{
	long lower=long(Get_Value(lower_limit)),upper=long(Get_Value(upper_limit));
	long range=upper-lower,rand_val;
	int loop_counter;
	for(int i=1;i<=500;i++)			
	{
		loop_counter=0;
		do 
		{
			if(50<loop_counter)
			{
				return(0);
			}
			loop_counter++;
			rand_val=Parn.Random_with_limits(lower,upper);
			if((2==rand_val)||(3==rand_val))
			{
				return(rand_val);
			}
		}		
		while((0==(rand_val%2))||(1==rand_val));
		
		if((0==m_radio1)&&(true==Parn.Prime_test_Miller_Rabin(rand_val,100)))
		{
			return(rand_val);
		}

		if((1==m_radio1)&&(true==Parn.Prime_test_Solovay_Strassen(rand_val,100)))
		{
			return(rand_val);
		}

		if((2==m_radio1)&&(true==Parn.Prime_test_Fermat(rand_val,100)))
		{
			return(rand_val);
		}
	}

	return(0);	
}
