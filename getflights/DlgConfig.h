#pragma once

#include "common/AdvComboBox.h"
#include "afxcmn.h"
#include <list>
#include "DataProcess.h"
#include "common/xgmvar.h"

using namespace std;

// CDlgConfig 对话框

class CDlgConfig : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgConfig)

public:
	CDlgConfig(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgConfig();

// 对话框数据
	enum { IDD = IDD_DLG_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CAdvComboBox m_comboFrom;
	CAdvComboBox m_comboTo;
	CDateTimeCtrl m_dtStart;
	CDateTimeCtrl m_dtEnd;
	CListCtrl m_listAirline;
	CListCtrl m_listAirlineDate;
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtrlLog;

	list<PTAirLineDateInfo> m_listAirDateData;
	bool		m_bStarted;

	CImageList	m_imageList;
	afx_msg void OnBnClickedBtnAirlineAdd();
	afx_msg void OnBnClickedBtnAirlineDel();
	afx_msg void OnBnClickedBtnAirlineAll();
	afx_msg void OnBnClickedBtnAirlineCancel();
	afx_msg void OnBnClickedBtnAirlineDateAdd();
	afx_msg void OnBnClickedBtnAirlineDateDel();
	afx_msg void OnBnClickedBtnAirlineDateDelall();

	// 删除列表中所有的航线信息
	void DeleteAllAirline(void);
	// 删除所有的航线日期信息
	void DeleteAllAirlineDates(void);
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedBtnStart();
	// 保存航线信息
	BOOL SaveAirlines(void);

	void AddLog(CString strLog);
	void AddProcessTime(void);
	afx_msg void OnBnClickedBtnClearLog();
	afx_msg void OnBnClickedBtnLoad();
	afx_msg void OnBnClickedBtnSave();
	LRESULT OnPrepareProxyIpProgress(WPARAM wParam, LPARAM lParam);

	void EnableCtrls(BOOL bEnable);
	void EnabeleQueryLessChangeFlightBtn(BOOL bEnable);

private:
	void	__SetListAirDateDataListCtl(list<PTAirLineDateInfo> &listAirDate);
	void	__GetCurListAirDateData(list<PTAirLineDateInfo> & listAirDateData);
	void	__EnableStartBtn(BOOL bEnable, int nCount=0);

	static CTime m_tProcessStartTime;
	static CTime m_tProcessEndTime;

public:
	afx_msg void OnBnClkQueryLessChangeFlightBtn();
};
