; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CHelp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "aestool.h"

ClassCount=5
Class1=CAestoolApp
Class2=CAestoolDlg
Class3=CAboutDlg

ResourceCount=15
Resource1=AFX_IDD_NEWTYPEDLG
Resource2=IDR_MAINFRAME
Resource3=IDD_HELP (Deutsch (Deutschland))
Resource4=IDD_SPLASH (Englisch (GB))
Class4=CSplash
Resource5=IDD_SPLASH
Class5=CHelp
Resource6=IDD_AESTOOL_DIALOG (Englisch (GB))
Resource7=IDD_AESTOOL_DIALOG
Resource8=IDD_HELP
Resource9=IDD_AESTOOL_DIALOG (Deutsch (Deutschland))
Resource10=IDD_ABOUTBOX (Deutsch (Deutschland))
Resource11=IDD_SPLASH (Deutsch (Deutschland))
Resource12=AFX_IDD_NEWTYPEDLG (Englisch (GB))
Resource13=IDD_ABOUTBOX (Englisch (GB))
Resource14=IDD_HELP (Englisch (GB))
Resource15=IDD_ABOUTBOX

[CLS:CAestoolApp]
Type=0
HeaderFile=aestool.h
ImplementationFile=aestool.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CAestoolApp

[CLS:CAestoolDlg]
Type=0
HeaderFile=aestoolDlg.h
ImplementationFile=aestoolDlg.cpp
Filter=D
LastObject=IDC_STATIC_TITLE
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=aestoolDlg.h
ImplementationFile=aestoolDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_AESTOOL_DIALOG (Englisch (GB))]
Type=1
Class=CAestoolDlg
ControlCount=14
Control1=IDC_EDIT_KEY,edit,1350631552
Control2=IDC_EDIT_SRC,edit,1350631552
Control3=IDC_BUTTON_SRC,button,1342242816
Control4=IDC_RADIO_EXE,button,1342308361
Control5=IDC_RADIO_AES,button,1342177289
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_RADIO_PSHOW,button,1342308361
Control10=IDC_RADIO_PHIDE,button,1342177289
Control11=IDC_STATIC_TITLE,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287

[DLG:IDD_SPLASH]
Type=1
Class=CSplash
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

[CLS:CSplash]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CDialog
Filter=D
LastObject=CSplash

[DLG:IDD_SPLASH (Englisch (GB))]
Type=1
Class=CSplash
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_HELP]
Type=1
Class=CHelp
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352

[CLS:CHelp]
Type=0
HeaderFile=Help.h
ImplementationFile=Help.cpp
BaseClass=CDialog
Filter=D
LastObject=CHelp
VirtualFilter=dWC

[DLG:IDD_AESTOOL_DIALOG]
Type=1
Class=CAestoolDlg
ControlCount=14
Control1=IDC_EDIT_KEY,edit,1350631552
Control2=IDC_EDIT_SRC,edit,1350631552
Control3=IDC_BUTTON_SRC,button,1342242816
Control4=IDC_RADIO_EXE,button,1342308361
Control5=IDC_RADIO_AES,button,1342177289
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_RADIO_PSHOW,button,1342308361
Control10=IDC_RADIO_PHIDE,button,1342177289
Control11=IDC_STATIC_TITLE,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287

[DLG:IDD_HELP (Englisch (GB))]
Type=1
Class=?
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308354
Control22=IDC_STATIC,static,1342308354
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (Englisch (GB))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ABOUTBOX (Deutsch (Deutschland))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_AESTOOL_DIALOG (Deutsch (Deutschland))]
Type=1
Class=?
ControlCount=14
Control1=IDC_EDIT_KEY,edit,1350631552
Control2=IDC_EDIT_SRC,edit,1350631552
Control3=IDC_BUTTON_SRC,button,1342242816
Control4=IDC_RADIO_EXE,button,1342308361
Control5=IDC_RADIO_AES,button,1342177289
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_RADIO_PSHOW,button,1342308361
Control10=IDC_RADIO_PHIDE,button,1342177289
Control11=IDC_STATIC_TITLE,static,1342308352
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_STATIC,button,1342177287

[DLG:IDD_SPLASH (Deutsch (Deutschland))]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_HELP (Deutsch (Deutschland))]
Type=1
Class=?
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352

[DLG:AFX_IDD_NEWTYPEDLG (Englisch (GB))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177280
Control2=AFX_IDC_LISTBOX,listbox,1352728577
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=ID_HELP,button,1342242816

[DLG:AFX_IDD_NEWTYPEDLG]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177280
Control2=AFX_IDC_LISTBOX,listbox,1352728577
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=ID_HELP,button,1342242816

