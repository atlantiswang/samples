// DlgShowFlights.cpp : 实现文件
//

#include "stdafx.h"
#include "GetFlights.h"
#include "DlgShowFlights.h"
#include "afxdialogex.h"


// CDlgShowFlights 对话框

IMPLEMENT_DYNAMIC(CDlgShowFlights, CDialogEx)

CDlgShowFlights::CDlgShowFlights(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgShowFlights::IDD, pParent)
{

}

CDlgShowFlights::~CDlgShowFlights()
{
}

void CDlgShowFlights::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgShowFlights, CDialogEx)
END_MESSAGE_MAP()


// CDlgShowFlights 消息处理程序
