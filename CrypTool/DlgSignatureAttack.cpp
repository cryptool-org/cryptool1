// DlgSignatureAttack.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "CrypToolApp.h"
#include "CrypToolTools.h"
#include "DlgSignatureAttack.h"
#include "DlgOptionsSignatureAttack.h"
#include "DlgStatisticsSignatureAttack.h"
#include "FileTools.h"
#include <fstream.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "SignatureAttack.h"
#include "SignatureAttackMFC.h"
#include "OptionsForSignatureAttack.h"
#include "ErrorcodesForSignatureAttack.h"
#include "DlgShowProgress.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureAttack 


CDlgSignatureAttack::CDlgSignatureAttack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSignatureAttack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSignatureAttack)
	m_file_harmless = _T("");
	m_file_dangerous = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSignatureAttack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSignatureAttack)
	DDX_Control(pDX, IDC_FILE_HARMLESS, m_control_file_harmless);
	DDX_Control(pDX, IDC_FILE_DANGEROUS, m_control_file_dangerous);
	DDX_Control(pDX, IDC_COMPUTE, m_control_compute);
	DDX_Text(pDX, IDC_FILE_HARMLESS, m_file_harmless);
	DDX_Text(pDX, IDC_FILE_DANGEROUS, m_file_dangerous);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSignatureAttack, CDialog)
	//{{AFX_MSG_MAP(CDlgSignatureAttack)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_BN_CLICKED(IDC_BROWSE_HARMLESS, OnBrowseOriginal)
	ON_BN_CLICKED(IDC_BROWSE_DANGEROUS, OnBrowseFake)
	ON_BN_CLICKED(IDC_COMPUTE, OnCompute)
	ON_EN_UPDATE(IDC_FILE_DANGEROUS, OnUpdateFileFake)
	ON_EN_UPDATE(IDC_FILE_HARMLESS, OnUpdateFileOriginal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDlgSignatureAttack 

void CDlgSignatureAttack::OnOptions() 
{
	CDlgOptionsSignatureAttack DlgOSA;
	DlgOSA.DoModal();
}

void CDlgSignatureAttack::OnBrowseOriginal() 
{
	UpdateData(TRUE);
	BrowseDocument(m_file_harmless);
	UpdateData(FALSE);
}

void CDlgSignatureAttack::OnBrowseFake() 
{
	UpdateData(TRUE);
	BrowseDocument(m_file_dangerous);
	UpdateData(FALSE);
}

void CDlgSignatureAttack::OnCompute() 
{
	int SigAttTestMode = theApp.GetProfileInt("Settings", "SignatureAttackTestMode", 0);

	if (SigAttTestMode)
	{
		SHOW_HOUR_GLASS

		bool DocFiles = false;
		char FilePath[256], *HarmlessText, *DangerousText;
		CString LogPath;
		CWinThread *CWThread;
		FILE *SigAttTest;
		ifstream ifstr_Harmless, ifstr_Dangerous;
		int HarmlessDocLength, DangerousDocLength;
		MSG FloydMessage;
		ofstream ofstr_Harmless, ofstr_Dangerous;
		struct stat stat_object;
		time_t StartTime;
		UINT MessageID;

		int SignificantBitLengthCounter, HashAlgorithmsCounter, AttemptsCounter, TotalAttemptsCounter = 0;

		LogPath = theApp.GetProfileString("SigAttTest", "LogPath", "C:\\");
		time(&StartTime);

		for (SignificantBitLengthCounter = theApp.GetProfileInt("SigAttTest", "SignificantBitLengthMIN", 0);
			SignificantBitLengthCounter <= theApp.GetProfileInt("SigAttTest", "SignificantBitLengthMAX", 0);
			SignificantBitLengthCounter += theApp.GetProfileInt("SigAttTest", "SignificantBitLengthJump", 1))
		{
			theApp.WriteProfileInt("Settings", "SignatureAttackSignificantBitLength", SignificantBitLengthCounter);

			for (HashAlgorithmsCounter = theApp.GetProfileInt("SigAttTest", "HashAlgorithmIDMIN", 0);
				HashAlgorithmsCounter <= theApp.GetProfileInt("SigAttTest", "HashAlgorithmIDMAX", 0);
				HashAlgorithmsCounter ++)
			{
				theApp.WriteProfileInt("Settings", "SignatureAttackHashAlgorithmID", HashAlgorithmsCounter);

				for (AttemptsCounter = 0;
					AttemptsCounter < theApp.GetProfileInt("SigAttTest", "Attempts", 0);
					AttemptsCounter ++)
				{
					if (TotalAttemptsCounter == theApp.GetProfileInt("SigAttTest", "AttemptsMAX", 0))
					{
						return;
					}
					TotalAttemptsCounter ++;

					m_file_harmless = theApp.GetProfileString("SigAttTest", "HarmlessDocument", NULL);
					m_file_dangerous = theApp.GetProfileString("SigAttTest", "DangerousDocument", NULL);

	#ifdef _SIG_ATT_PRE_RPE_MODIFY

					ifstr_Harmless.open(m_file_harmless, ios::in | ios::binary);
					stat((const char *) m_file_harmless, & stat_object);
					if (0 == stat_object.st_size)
					{
						GenerateMessageText(15);
						return;
					}
					HarmlessDocLength = stat_object.st_size;
					HarmlessText = new char[HarmlessDocLength];
					ifstr_Harmless.read(HarmlessText, HarmlessDocLength);
					ifstr_Harmless.close();
					ofstr_Harmless.open(m_file_harmless, ios::out | ios::binary);
					HarmlessText[HarmlessDocLength-1] = AttemptsCounter + 32;
					ofstr_Harmless.write(HarmlessText, HarmlessDocLength);
					ofstr_Harmless.close();


					ifstr_Dangerous.open(m_file_dangerous, ios::in | ios::binary);
					stat((const char *) m_file_dangerous, & stat_object);
					if (0 == stat_object.st_size)
					{
						GenerateMessageText(15);
						return;
					}
					DangerousDocLength = stat_object.st_size;
					DangerousText = new char[DangerousDocLength];
					ifstr_Dangerous.read(DangerousText, DangerousDocLength);
					ifstr_Dangerous.close();
					ofstr_Dangerous.open(m_file_dangerous, ios::out | ios::binary);
					DangerousText[DangerousDocLength-1] = AttemptsCounter + 32;
					ofstr_Dangerous.write(DangerousText, DangerousDocLength);
					ofstr_Dangerous.close();

	#endif

					OptionsForSignatureAttack OFSA(m_file_harmless, m_file_dangerous, SigAttTestMode);
					if (0 != OFSA.GetErrorcode())
					{
						return;
					}

					if (false == DocFiles)
					{
						DocFiles = true;

						ifstr_Harmless.open(m_file_harmless, ios::in | ios::binary);
						ifstr_Dangerous.open(m_file_dangerous, ios::in | ios::binary);
						_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_HARMLESS);
						ofstr_Harmless.open(FilePath, ios::out | ios::binary);
						_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_DANGEROUS);
						ofstr_Dangerous.open(FilePath, ios::out | ios::binary);
						if (!ifstr_Harmless || !ifstr_Dangerous || !ofstr_Harmless || !ofstr_Dangerous)
						{
							return;
						}

						stat((const char *) m_file_harmless, & stat_object);
						if (0 == stat_object.st_size)
						{
							GenerateMessageText(15);
							return;
						}
						HarmlessDocLength = stat_object.st_size;
						HarmlessText = new char[HarmlessDocLength];					

						stat((const char *) m_file_dangerous, & stat_object);
						if (0 == stat_object.st_size)
						{
							GenerateMessageText(15);
							return;
						}
						DangerousDocLength = stat_object.st_size;
						DangerousText = new char[DangerousDocLength];

						ifstr_Harmless.read(HarmlessText, HarmlessDocLength);
						ofstr_Harmless.write(HarmlessText, HarmlessDocLength);

						ifstr_Harmless.close();
						ofstr_Harmless.close();

						ifstr_Dangerous.read(DangerousText, DangerousDocLength);
						ofstr_Dangerous.write(DangerousText, DangerousDocLength);
						ifstr_Dangerous.close();
						ofstr_Dangerous.close();

						delete []HarmlessText;
						delete []DangerousText;
						
						_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_HEADER);
						SigAttTest = fopen(FilePath, "w+");
						if (NULL == SigAttTest)
						{
							return;
						}

						fprintf(SigAttTest,
							"ModificationMethod=%d\nHarmlessFile=%s%d%s\nHarmlessFileLength=%d\nDangerousFile=%s%d%s\nDangerousFileLength=%d",
							theApp.GetProfileInt("Settings", "SignatureAttackModificationMethod", 0),
							LogPath, StartTime, _SIG_ATT_HARMLESS, HarmlessDocLength,
							LogPath, StartTime,	_SIG_ATT_DANGEROUS, DangerousDocLength);

	#ifdef _SIG_ATT_SPEED_INCREMENT

						fprintf(SigAttTest, "\nModifyOriginalDocumentBeforeRun=1");

	#endif

	#ifndef _SIG_ATT_SPEED_INCREMENT

						fprintf(SigAttTest, "\nModifyOriginalDocumentBeforeRun=0");

	#endif

	#ifdef _SIG_ATT_MODIFYING_OPTIMIZER

						fprintf(SigAttTest, "\nSpeedOptimizer=1");

	#endif

	#ifndef _SIG_ATT_MODIFYING_OPTIMIZER

						fprintf(SigAttTest, "\nSpeedOptimizer=0");

	#endif

	#ifdef _SIG_ATT_ALWAYS_INIT_HASH

						fprintf(SigAttTest, "\nAlwaysInitHash=1");

	#endif

	#ifndef _SIG_ATT_ALWAYS_INIT_HASH

						fprintf(SigAttTest, "\nAlwaysInitHash=0");

	#endif

						fprintf(SigAttTest, "\nComments=%s", theApp.GetProfileString("SigAttTest", "Comments", ""));
						fclose(SigAttTest);

						_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_LOG);
						SigAttTest = fopen(FilePath, "w+");
						if (NULL == SigAttTest)
						{
							return;
						}
					}

					// Beginn - Versuchsreihe ohne Fortschrittsanzeige
					/*SignatureAttack *S_A = new SignatureAttack(&OFSA, SigAttTest, TotalAttemptsCounter);
					S_A->Do_Floyd();*/
					// Ende - Versuchsreihe ohne Fortschrittsanzeige

					// Beginn - Versuchsreihe mit Fortschrittsanzeige
					MessageID = RegisterWindowMessage("Floyd_Terminated");

					SignatureAttack *S_A = new SignatureAttackMFC(&OFSA, SigAttTest, TotalAttemptsCounter,
						this->m_hWnd, MessageID);
					CWThread = AfxBeginThread(SignatureAttackMFC::StaticThreadFunction, (void *)S_A);
					
					while (1)
					{
						if (PeekMessage(&FloydMessage, NULL, 0, 0, PM_NOREMOVE))
						{
							GetMessage(&FloydMessage, NULL, 0, 0);
							if (MessageID == FloydMessage.message)
							{
								break;	// nur wenn der Floyd-Algorithmus beendet wurde, Schleife verlassen - 
							}			// andere Messages werden ignoriert

							TranslateMessage(&FloydMessage); 
							DispatchMessage(&FloydMessage);
						}

						else WaitMessage();
					}
					// Ende - Versuchsreihe mit Fortschrittsanzeige

					if (_SIG_ATT_FLOYD_CANCELED == S_A->GetResults()->GetFloydResult())
					{
						delete S_A;				// Versuchsreihe vom Benutzer abgebrochen !
						fflush(SigAttTest);
						GenerateMessageText(_SIG_ATT_TEST_SERIES_STOPPED, MB_ICONINFORMATION);
						return;
					}

					delete S_A;
					fflush(SigAttTest);
				}
			}
		}
		fclose(SigAttTest);
		HIDE_HOUR_GLASS
	}

	else
	{
		CAppDocument *NewHarmlessDocument, *NewDangerousDocument;
		char *hashasci, hashhex [128], outfile[1024], doctitle[1024];
		CString crypT, msg;
		int Errorcode, ii, SignificantBitLength, strlen = 0;
		ofstream ModifiedHarmlessFile, ModifiedDangerousFile;

		crypT.Format(IDS_STRING_SIG_ATT_CRYPTOOL);

		OptionsForSignatureAttack OFSA(m_file_harmless, m_file_dangerous, SigAttTestMode);
		if (0 != OFSA.GetErrorcode())
		{
			GenerateMessageText(OFSA.GetErrorcode());
			return;
		}

		// Beginn - Angriff ohne Fortschrittsanzeige
		/*SignatureAttack *S_A = new SignatureAttack(&OFSA);
		SHOW_HOUR_GLASS
		S_A->Do_Floyd();
		HIDE_HOUR_GLASS*/
		// Ende - Angriff ohne Fortschrittsanzeige

		// Beginn - Angriff mit Fortschrittsanzeige
		CWinThread *CWThread;
		MSG FloydMessage;
		UINT MessageID;

		MessageID = RegisterWindowMessage("Floyd_Terminated");

		SignatureAttack *S_A = new SignatureAttackMFC(&OFSA, NULL, 0, this->m_hWnd, MessageID);
		CWThread = AfxBeginThread(SignatureAttackMFC::StaticThreadFunction, (void *)S_A);
		
		while (1)
		{
			if (PeekMessage(&FloydMessage, NULL, 0, 0, PM_NOREMOVE))
			{
				GetMessage(&FloydMessage, NULL, 0, 0);
				if (MessageID == FloydMessage.message)
				{
					break;	// nur wenn der Floyd-Algorithmus beendet wurde, Schleife verlassen - andere Messages werden
				}			// ignoriert

				TranslateMessage(&FloydMessage); 
				DispatchMessage(&FloydMessage);
			}

			else WaitMessage();
		}
		// Ende - Angriff mit Fortschrittsanzeige

		Errorcode = S_A->GetResults()->GetFloydResult();
		if (_SIG_ATT_DOCUMENTS_FOUND != Errorcode)
		{
			delete S_A;
			GenerateMessageText(Errorcode, MB_ICONINFORMATION);
			return;
		}

		GenerateMessageText(Errorcode, MB_ICONINFORMATION);
		SHOW_HOUR_GLASS

		GetTmpName(outfile,"cry",".tmp");
		ModifiedHarmlessFile.open(outfile, ios::out | ios::binary);
		if (!ModifiedHarmlessFile)
		{
			HIDE_HOUR_GLASS
			GenerateMessageText(IDS_STRING_FILE_NOT_OPEN);
			return;
		}
		ModifiedHarmlessFile.write(OFSA.GetHarmlessDocument()->GetDocumentData(),
			OFSA.GetHarmlessDocument()->GetDocumentLength());
		ModifiedHarmlessFile.close();
		NewHarmlessDocument = theApp.OpenDocumentFileNoMRU(outfile);

		// Dokumenttitel für Vorlage erstellen:
		msg.Format(IDS_STRING_SIG_ATT_DOCUMENT_TITLE_HARMLESS);

		hashasci = S_A->GetResults()->GetMatchingHashBytes();
		SignificantBitLength = OFSA.GetSignificantBitLength();
		for (ii = 0; ii < SignificantBitLength / 8; ii ++)
		{
			strlen += _snprintf(hashhex + strlen, 3, "%2.2X ", (unsigned char) hashasci[ii]);
		}

		if (0 != SignificantBitLength % 8)
		{
			strlen += _snprintf(hashhex + strlen, 4, "... ");
		}
				hashhex[strlen - 1] = '\0';

		_snprintf(doctitle, sizeof(doctitle) - 1, "%s%s, <%s>",
			msg, OFSA.GetHashOp()->GetHashAlgorithmName(), hashhex);
		NewHarmlessDocument->SetTitle(doctitle);

		GetTmpName(outfile,"cry",".tmp");
		ModifiedDangerousFile.open(outfile, ios::out | ios::binary);
		if (!ModifiedDangerousFile)
		{
			HIDE_HOUR_GLASS
			GenerateMessageText(IDS_STRING_FILE_NOT_OPEN);
			return;
		}
		ModifiedDangerousFile.write(OFSA.GetDangerousDocument()->GetDocumentData(),
			OFSA.GetDangerousDocument()->GetDocumentLength());
		ModifiedDangerousFile.close();
		NewDangerousDocument = theApp.OpenDocumentFileNoMRU(outfile);
		
		// Dokumenttitel für 2. Dokument erstellen:
		msg.Format(IDS_STRING_SIG_ATT_DOCUMENT_TITLE_DANGEROUS);
		_snprintf(doctitle, sizeof(doctitle) - 1, "%s%s, <%s>",
			msg, OFSA.GetHashOp()->GetHashAlgorithmName(), hashhex);
		NewDangerousDocument->SetTitle(doctitle);
		
		HIDE_HOUR_GLASS
		
		CDlgStatisticsSignatureAttack DlgSSA;
		DlgSSA.SetData(S_A->GetResults(),
			OFSA.GetHarmlessDocument()->GetModifiedBytes(), OFSA.GetDangerousDocument()->GetModifiedBytes());
		DlgSSA.DoModal();
		if (true == DlgSSA.GetPrintStatistics())
		{
			DlgSSA.PrintStatistics();
		}

		delete S_A;
	}
}

BOOL CDlgSignatureAttack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_file_harmless = theApp.GetProfileString("Settings", "SignatureAttackHarmlessFile", "");
	m_file_dangerous = theApp.GetProfileString("Settings", "SignatureAttackDangerousFile", "");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDlgSignatureAttack::OnUpdateFileFake() 
{
	UpdateData(TRUE);
	AreValidPaths();
	UpdateData(FALSE);
}

void CDlgSignatureAttack::OnUpdateFileOriginal() 
{
	UpdateData(TRUE);
	AreValidPaths();
	UpdateData(FALSE);
}

bool CDlgSignatureAttack::AreValidPaths()
{
	if (TRUE == m_file_harmless.IsEmpty() || TRUE == m_file_dangerous.IsEmpty())
	{
		m_control_compute.EnableWindow(FALSE);
		return false;
	}

	m_control_compute.EnableWindow(TRUE);
	return true;
}

void CDlgSignatureAttack::BrowseDocument(CString & DocType)
{
	CString filename;

	CFileDialog FDlg(TRUE, NULL, filename, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"All Files (*.*)|*.*|TXT Files (*.txt)|*.txt||", this);
	if (IDCANCEL == FDlg.DoModal())
	{
		return;
	}

	DocType = FDlg.GetPathName();
	
	if (m_file_harmless.IsEmpty())
	{
		m_control_compute.EnableWindow(FALSE);
		m_control_file_harmless.SetFocus();
	}
	else if (m_file_dangerous.IsEmpty())
	{
		m_control_compute.EnableWindow(FALSE);
		m_control_file_dangerous.SetFocus();
	}
	else
	{
		m_control_compute.EnableWindow(TRUE);
		m_control_compute.SetFocus();
	}
}

void CDlgSignatureAttack::GenerateMessageText(int Errorcode, UINT MessageBoxStyle)
{
	CString msg;
	
	switch (Errorcode)
	{
		case _SIG_ATT_BAD_HARMLESS_FILE:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_HARMLESS_FILE); break;
		case _SIG_ATT_BAD_DANGEROUS_FILE:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_DANGEROUS_FILE); break;
		case _SIG_ATT_BAD_HASH_ALGORITHM:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_HASH_ALGORITHM); break;
		case _SIG_ATT_DOCUMENTS_FOUND:			msg.LoadString(IDS_STRING_SIG_ATT_DOCUMENTS_FOUND); break;
		case _SIG_ATT_NO_DOCUMENTS_FOUND:		msg.LoadString(IDS_STRING_SIG_ATT_NO_DOCUMENTS_FOUND); break;
		case _SIG_ATT_BAD_MODIFIABILITY:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_MODIFIABILITY); break;
		case _SIG_ATT_FLOYD_CANCELED:			msg.LoadString(IDS_STRING_SIG_ATT_FLOYD_CANCELED); break;
		case _SIG_ATT_TEST_SERIES_STOPPED:		msg.LoadString(IDS_STRING_SIG_ATT_STA_TEST_SERIES_STOPPED); break;

		default:								msg.LoadString(IDS_STRING_SIG_ATT_UNKNOWN_ERROR);
	}
	
	MessageBox(msg, "CrypTool", MessageBoxStyle | MB_APPLMODAL);
}

void CDlgSignatureAttack::OnCancel() 
{
	theApp.WriteProfileString("Settings", "SignatureAttackHarmlessFile", m_file_harmless);
	theApp.WriteProfileString("Settings", "SignatureAttackDangerousFile", m_file_dangerous);
	CDialog::OnCancel();
}
