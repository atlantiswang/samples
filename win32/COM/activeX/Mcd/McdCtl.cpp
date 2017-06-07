// McdCtl.cpp : Implementation of the CMcdCtrl ActiveX Control class.

#include "stdafx.h"
#include "Mcd.h"
#include "McdCtl.h"
#include "McdPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMcdCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMcdCtrl, COleControl)
	//{{AFX_MSG_MAP(CMcdCtrl)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMcdCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMcdCtrl)
	DISP_PROPERTY_NOTIFY(CMcdCtrl, "Direction", m_direction, OnDirectionChanged, VT_BOOL)
	DISP_FUNCTION(CMcdCtrl, "SetNumbers", SetNumbers, VT_EMPTY, VTS_I4 VTS_I4)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMcdCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMcdCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMcdCtrl)
	EVENT_CUSTOM("MyMsg", FireMyMsg, VTS_NONE)
	EVENT_STOCK_CLICK()
	EVENT_STOCK_DBLCLICK()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMcdCtrl, 1)
	PROPPAGEID(CMcdPropPage::guid)
END_PROPPAGEIDS(CMcdCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMcdCtrl, "MCD.McdCtrl.1",
	0x5c3ee2fd, 0x5b12, 0x4de9, 0xa6, 0x29, 0x64, 0x34, 0xd1, 0xc, 0x4c, 0x1b)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMcdCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMcd =
		{ 0x5bbd7b01, 0x984f, 0x4771, { 0xae, 0x3b, 0x1e, 0x28, 0x5b, 0x18, 0x12, 0xb4 } };
const IID BASED_CODE IID_DMcdEvents =
		{ 0x8b094327, 0x2670, 0x4850, { 0xa4, 0x4f, 0x32, 0x6b, 0xb1, 0xb1, 0x9b, 0xda } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMcdOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMcdCtrl, IDS_MCD, _dwMcdOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl::CMcdCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMcdCtrl

BOOL CMcdCtrl::CMcdCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MCD,
			IDB_MCD,
			afxRegApartmentThreading,
			_dwMcdOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl::CMcdCtrl - Constructor

CMcdCtrl::CMcdCtrl()
{
	InitializeIIDs(&IID_DMcd, &IID_DMcdEvents);
	//设置控件的初始大小
	SetInitialSize(230,210);
	m_a=12;
	m_b=16;
	m_direction=FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl::~CMcdCtrl - Destructor

CMcdCtrl::~CMcdCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl::OnDraw - Drawing function

void CMcdCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	//设置控件的背景色
	CBrush brush(RGB(255,255,0));
	pdc->FillRect(&rcBounds,&brush);
	//设置圆的背景色
	CBrush brush2(RGB(0,0,0));
	CBrush *pOldBrush=pdc->SelectObject(&brush2);
	//设置圆心位置
	POINT p1={30,130};
	POINT p2={190,p1.y};
	POINT p3={(p1.x+p2.x)/2,
		m_direction?p1.y-60:p1.y+60};
	int r=15;
	//画圆
	pdc->Ellipse(p1.x-r,p1.y-r,p1.x+r,p1.y+r);
	pdc->Ellipse(p2.x-r,p2.y-r,p2.x+r,p2.y+r);
	pdc->Ellipse(p3.x-r,p3.y-r,p3.x+r,p3.y+r);
//	pdc->SelectObject(&pOldBrush);
	//画圆的连接线;
	pdc->MoveTo(p1);
	pdc->LineTo(p3);
	pdc->LineTo(p2);
	//设置文本的对齐方式，颜色和背景颜色
	pdc->SetTextAlign(TA_CENTER);
	pdc->SetTextColor(RGB(255,255,255));
	pdc->SetBkMode(TRANSPARENT);
	//输出数值
	CString strInfo;
	strInfo.Format("%d",m_a);
	pdc->TextOut(p1.x,p1.y-9,strInfo);
	strInfo.Format("%d",m_b);
	pdc->TextOut(p2.x,p2.y-9,strInfo);
	strInfo.Format("%d",Mcd(m_a,m_b));
	pdc->TextOut(p3.x,p3.y-9,strInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl::DoPropExchange - Persistence support

void CMcdCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl::OnResetState - Reset control to default state

void CMcdCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl::AboutBox - Display an "About" box to the user

void CMcdCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MCD);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMcdCtrl message handlers

int CMcdCtrl::Mcd(int a, int b)
{
	if(b==0)
	{
		return a;
	}
	return Mcd(b,a%b);
}

void CMcdCtrl::SetNumbers(long x, long y) 
{
	m_a=x;
	m_b=y;
	//控件重绘->OnDraw()->Mcd()
	InvalidateControl();
}

void CMcdCtrl::OnDirectionChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CMcdCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	FireMyMsg();
}
