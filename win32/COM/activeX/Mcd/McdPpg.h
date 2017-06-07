#if !defined(AFX_MCDPPG_H__0A6F9433_1FC8_4322_A2E7_60D9B7D3366C__INCLUDED_)
#define AFX_MCDPPG_H__0A6F9433_1FC8_4322_A2E7_60D9B7D3366C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// McdPpg.h : Declaration of the CMcdPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMcdPropPage : See McdPpg.cpp.cpp for implementation.

class CMcdPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMcdPropPage)
	DECLARE_OLECREATE_EX(CMcdPropPage)

// Constructor
public:
	CMcdPropPage();

// Dialog Data
	//{{AFX_DATA(CMcdPropPage)
	enum { IDD = IDD_PROPPAGE_MCD };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMcdPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCDPPG_H__0A6F9433_1FC8_4322_A2E7_60D9B7D3366C__INCLUDED)
