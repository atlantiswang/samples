#pragma once


// CMyDialog 对话框

class CMyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyDialog)

public:
	CMyDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_UI };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
