#pragma once


// CDlgShowFlights 对话框

class CDlgShowFlights : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgShowFlights)

public:
	CDlgShowFlights(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgShowFlights();

// 对话框数据
	enum { IDD = IDD_DLG_SHOW_FLIGHTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
