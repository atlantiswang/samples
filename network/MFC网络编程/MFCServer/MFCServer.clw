; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMFCServerApp
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MFCServer.h"

ClassCount=4
Class1=CMFCServerApp
Class2=CMFCServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CServerSocket
Resource3=IDD_MFCSERVER_DIALOG

[CLS:CMFCServerApp]
Type=0
HeaderFile=MFCServer.h
ImplementationFile=MFCServer.cpp
Filter=N
LastObject=CMFCServerApp

[CLS:CMFCServerDlg]
Type=0
HeaderFile=MFCServerDlg.h
ImplementationFile=MFCServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MFCServerDlg.h
ImplementationFile=MFCServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MFCSERVER_DIALOG]
Type=1
Class=CMFCServerDlg
ControlCount=1
Control1=IDC_START,button,1342242816

[CLS:CServerSocket]
Type=0
HeaderFile=ServerSocket.h
ImplementationFile=ServerSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q

