; CLW-Datei enthält Informationen für den MFC-Klassen-Assistenten

[General Info]
Version=1
LastClass=CSplash
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "aestool.h"

ClassCount=4
Class1=CAestoolApp
Class2=CAestoolDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SPLASH
Resource4=IDD_AESTOOL_DIALOG (Englisch (GB))
Class4=CSplash
Resource5=IDD_AESTOOL_DIALOG
Resource6=IDD_SPLASH (Englisch (GB))

[CLS:CAestoolApp]
Type=0
HeaderFile=aestool.h
ImplementationFile=aestool.cpp
Filter=N

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

[DLG:IDD_AESTOOL_DIALOG]
Type=1
Class=CAestoolDlg
ControlCount=11
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC1,static,1342308352
Control7=IDC_STATIC2,static,1342308352
Control8=IDC_STATIC3,static,1342308352
Control9=IDC_EDIT2,edit,1350633600
Control10=IDC_EDIT3,edit,1350633600
Control11=IDC_STATIC4,static,1342308352

[DLG:IDD_AESTOOL_DIALOG (Englisch (GB))]
Type=1
Class=CAestoolDlg
ControlCount=11
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC1,static,1342308352
Control7=IDC_STATIC2,static,1342308352
Control8=IDC_STATIC3,static,1342308352
Control9=IDC_EDIT2,edit,1350633600
Control10=IDC_EDIT3,edit,1350633600
Control11=IDC_STATIC4,static,1342308352

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
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

