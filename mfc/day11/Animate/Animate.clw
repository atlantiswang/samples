; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAnimateDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Animate.h"

ClassCount=3
Class1=CAnimateApp
Class2=CAnimateDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_ANIMATE_DIALOG

[CLS:CAnimateApp]
Type=0
HeaderFile=Animate.h
ImplementationFile=Animate.cpp
Filter=N

[CLS:CAnimateDlg]
Type=0
HeaderFile=AnimateDlg.h
ImplementationFile=AnimateDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_OPEN_FILE

[CLS:CAboutDlg]
Type=0
HeaderFile=AnimateDlg.h
ImplementationFile=AnimateDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ANIMATE_DIALOG]
Type=1
Class=CAnimateDlg
ControlCount=11
Control1=IDC_STATIC,button,1342177287
Control2=IDC_FILE_PATH,edit,1350633600
Control3=IDC_STATIC,static,1342308352
Control4=IDC_OPEN_FILE,button,1342242816
Control5=IDC_VIDEO,SysAnimate32,1350631427
Control6=IDC_LIST_NAME,listbox,1352728833
Control7=IDC_STATIC,static,1342308352
Control8=IDC_REPLAY,button,1342242819
Control9=IDC_PLAY_COUNT,combobox,1344339970
Control10=IDC_PLAY,button,1342177289
Control11=IDC_STOP,button,1342177289

