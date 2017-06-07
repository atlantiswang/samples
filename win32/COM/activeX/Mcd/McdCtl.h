#if !defined(AFX_MCDCTL_H__239B71A3_203C_43DC_98A3_9A19DDA1C104__INCLUDED_)
#define AFX_MCDCTL_H__239B71A3_203C_43DC_98A3_9A19DDA1C104__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// McdCtl.h : Declaration of the CMcdCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl : See McdCtl.cpp for implementation.

class CMcdCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMcdCtrl)

// Constructor
public:
	CMcdCtrl();
	int m_a;
	int m_b;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMcdCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CMcdCtrl();

	DECLARE_OLECREATE_EX(CMcdCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMcdCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMcdCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMcdCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMcdCtrl)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMcdCtrl)
	BOOL m_direction;
	afx_msg void OnDirectionChanged();
	afx_msg void SetNumbers(long x, long y);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMcdCtrl)
	void FireMyMsg()
		{FireEvent(eventidMyMsg,EVENT_PARAM(VTS_NONE));}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CMcdCtrl)
	dispidDirection = 1L,
	dispidSetNumbers = 2L,
	eventidMyMsg = 1L,
	//}}AFX_DISP_ID
	};
private:
	int Mcd(int a,int b);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCDCTL_H__239B71A3_203C_43DC_98A3_9A19DDA1C104__INCLUDED)
