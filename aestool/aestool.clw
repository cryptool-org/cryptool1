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

ResourceCount=13
Resource1=IDD_SPLASH (Deutsch (Deutschland))
Resource2=IDR_MAINFRAME
Resource3=IDD_SPLASH (Englisch (GB))
Resource4=IDD_HELP (Englisch (GB))
Class4=CSplash
Resource5=IDD_AESTOOL_DIALOG (Englisch (GB))
Class5=CHelp
Resource6=IDD_ABOUTBOX (Deutsch (Deutschland))
Resource7=IDD_HELP
Resource8=IDD_AESTOOL_DIALOG
Resource9=IDD_SPLASH
Resource10=IDD_ABOUTBOX
Resource11=IDD_AESTOOL_DIALOG (Deutsch (Deutschland))
Resource12=IDD_HELP (Deutsch (Deutschland))
Resource13=IDD_ABOUTBOX (Englisch (GB))

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
ControlCount=16
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDIT3,edit,1350631552
Control5=IDC_BUTTON2,button,1342242816
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_RADIO3,button,1342308361
Control10=IDC_RADIO4,button,1342177289
Control11=IDC_RADIO1,button,1476526089
Control12=IDC_RADIO2,button,1476395017
Control13=IDC_STATIC4,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287

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
ControlCount=27
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
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352

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
ControlCount=16
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDIT3,edit,1350631552
Control5=IDC_BUTTON2,button,1342242816
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_RADIO3,button,1342308361
Control10=IDC_RADIO4,button,1342177289
Control11=IDC_RADIO1,button,1476526089
Control12=IDC_RADIO2,button,1476395017
Control13=IDC_STATIC4,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287

[DLG:IDD_HELP (Englisch (GB))]
Type=1
Class=?
ControlCount=27
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
Control23=IDC_STATIC,static,1342308354
Control24=IDC_STATIC,static,1342308354
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352

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
ControlCount=16
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_EDIT2,edit,1350631552
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_EDIT3,edit,1350631552
Control5=IDC_BUTTON2,button,1342242816
Control6=IDOK,button,1342242817
Control7=IDCANCEL,button,1342242816
Control8=IDC_BUTTON3,button,1342242816
Control9=IDC_RADIO3,button,1342308361
Control10=IDC_RADIO4,button,1342177289
Control11=IDC_RADIO1,button,1476526089
Control12=IDC_RADIO2,button,1476395017
Control13=IDC_STATIC4,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342177287
Control16=IDC_STATIC,button,1342177287

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
ControlCount=25
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
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352

