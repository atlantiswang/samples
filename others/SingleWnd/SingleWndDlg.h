
// SingleWndDlg.h : 头文件
//

#pragma once

#define WM_USER_NOTIFY  WM_USER +1
// CSingleWndDlg 对话框
class CSingleWndDlg : public CDialog
{
// 构造
public:
	CSingleWndDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SINGLEWND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnNotifyMsg(WPARAM wparam,LPARAM lparam);
public:
	CDialog *m_pDlg;
	NOTIFYICONDATA m_NotifyIcon;
	afx_msg void OnPopupExit();
	afx_msg void OnPopupDlg1();
	afx_msg void OnPopupDlg2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	CDialog *m_pDlgShowing;
	bool HasShowingDlg(void);
	afx_msg void OnPopupNoModal();
};
