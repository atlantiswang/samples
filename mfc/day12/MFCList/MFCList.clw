; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMFCListDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFCList.h"

ClassCount=3
Class1=CMFCListApp
Class2=CMFCListDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_MFCLIST_DIALOG

[CLS:CMFCListApp]
Type=0
HeaderFile=MFCList.h
ImplementationFile=MFCList.cpp
Filter=N

[CLS:CMFCListDlg]
Type=0
HeaderFile=MFCListDlg.h
ImplementationFile=MFCListDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_LIST

[CLS:CAboutDlg]
Type=0
HeaderFile=MFCListDlg.h
ImplementationFile=MFCListDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MFCLIST_DIALOG]
Type=1
Class=CMFCListDlg
ControlCount=2
Control1=IDC_LIST,SysListView32,1350631425
Control2=IDC_STYLE,combobox,1344339971

