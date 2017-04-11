; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMFCTabDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFCTab.h"

ClassCount=5
Class1=CMFCTabApp
Class2=CMFCTabDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG1
Class4=CDlog1
Resource4=IDD_MFCTAB_DIALOG
Class5=CDlg2
Resource5=IDD_DIALOG2

[CLS:CMFCTabApp]
Type=0
HeaderFile=MFCTab.h
ImplementationFile=MFCTab.cpp
Filter=N

[CLS:CMFCTabDlg]
Type=0
HeaderFile=MFCTabDlg.h
ImplementationFile=MFCTabDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TAB

[CLS:CAboutDlg]
Type=0
HeaderFile=MFCTabDlg.h
ImplementationFile=MFCTabDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MFCTAB_DIALOG]
Type=1
Class=CMFCTabDlg
ControlCount=1
Control1=IDC_TAB,SysTabControl32,1342177280

[DLG:IDD_DIALOG1]
Type=1
Class=CDlog1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:CDlog1]
Type=0
HeaderFile=Dlog1.h
ImplementationFile=Dlog1.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_DIALOG2]
Type=1
Class=CDlg2
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552

[CLS:CDlg2]
Type=0
HeaderFile=Dlg2.h
ImplementationFile=Dlg2.cpp
BaseClass=CDialog
Filter=D

