; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CClientSocket
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFCClient.h"

ClassCount=5
Class1=CMFCClientApp
Class2=CMFCClientDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CClientSocket
Resource3=IDD_MFCCLIENT_DIALOG

[CLS:CMFCClientApp]
Type=0
HeaderFile=MFCClient.h
ImplementationFile=MFCClient.cpp
Filter=N

[CLS:CMFCClientDlg]
Type=0
HeaderFile=MFCClientDlg.h
ImplementationFile=MFCClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MFCClientDlg.h
ImplementationFile=MFCClientDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MFCCLIENT_DIALOG]
Type=1
Class=CMFCClientDlg
ControlCount=1
Control1=IDC_SEND_FILE,button,1342242816

[CLS:CClientSocket]
Type=0
HeaderFile=ClientSocket.h
ImplementationFile=ClientSocket.cpp
BaseClass=CSocket
Filter=N

