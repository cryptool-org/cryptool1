; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CAestoolApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "aestool.h"

ClassCount=5
Class1=CAestoolApp
Class2=CAestoolDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_AESTOOL_DIALOG (Englisch (GB))
Resource2=IDR_MAINFRAME
Resource3=IDD_HELP (Englisch (GB))
Resource4=IDD_AESTOOL_DIALOG
Class4=CSplash
Resource5=IDD_SPLASH (Englisch (GB))
Class5=CHelp
Resource6=IDD_SPLASH
Resource7=IDD_ABOUTBOX
Resource8=IDD_HELP
Resource9=IDD_ABOUTBOX (Englisch (GB))

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
LastObject=CAestoolDlg
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
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_EDIT2,edit,1350633600
Control7=IDC_EDIT3,edit,1350633600
Control8=IDC_STATIC4,static,1342308352
Control9=IDC_RADIO1,button,1476526089
Control10=IDC_RADIO2,button,1476395017
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_BUTTON3,button,1342242816

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
ControlCount=22
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
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

[CLS:CHelp]
Type=0
HeaderFile=Help.h
ImplementationFile=Help.cpp
BaseClass=CDialog
Filter=D
LastObject=IDCANCEL

[DLG:IDD_AESTOOL_DIALOG]
Type=1
Class=CAestoolDlg
ControlCount=14
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_EDIT2,edit,1350633600
Control7=IDC_EDIT3,edit,1350633600
Control8=IDC_STATIC4,static,1342308352
Control9=IDC_RADIO1,button,1476526089
Control10=IDC_RADIO2,button,1476395017
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287
Control14=IDC_BUTTON3,button,1342242816

[DLG:IDD_HELP (Englisch (GB))]
Type=1
Class=?
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
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

[DLG:IDD_ABOUTBOX (Englisch (GB))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

