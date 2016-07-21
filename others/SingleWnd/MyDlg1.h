#pragma once


// CMyDlg1 对话框
#define DOMAL 1

class CMyDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CMyDlg1)

public:
	CMyDlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDlg1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	bool m_style;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
