#include "stdafx.h"
#include "resource.h"
class CMyDoc : public CDocument
{
	DECLARE_DYNCREATE(CMyDoc)
public:
	CString strDoc;
};
IMPLEMENT_DYNCREATE(CMyDoc,CDocument)
class CMyView : public CEditView
{
	DECLARE_DYNCREATE(CMyView)
public:
	virtual void OnUpdate(
		CView* pSender, LPARAM lHint, CObject* pHint  );
};
IMPLEMENT_DYNCREATE(CMyView,CEditView)
void CMyView::OnUpdate(
		CView* pSender, LPARAM lHint, CObject* pHint  )
{
	CMyDoc *pDoc=(CMyDoc*)this->m_pDocument;//
	this->SetWindowText(pDoc->strDoc);
}
class CMyChild : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CMyChild)
public:
	virtual BOOL OnCreateClient(
		LPCREATESTRUCT lpcs,CCreateContext* pContext);
	CSplitterWnd split;
};
IMPLEMENT_DYNCREATE(CMyChild,CMDIChildWnd)
BOOL CMyChild::OnCreateClient(
		LPCREATESTRUCT lpcs,CCreateContext* pContext)
{
	split.CreateStatic(this,1,2);
	split.CreateView(0,0,RUNTIME_CLASS(CMyView),
		CSize(100,100),pContext);
	split.CreateView(0,1,RUNTIME_CLASS(CMyView),
		CSize(100,100),pContext);
	return TRUE;
}
class CMyFrameWnd : public CMDIFrameWnd
{
};
class CMyWinApp : public CWinApp
{
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL InitInstance();
	afx_msg void OnNew();
	afx_msg void OnData();
};
BEGIN_MESSAGE_MAP(CMyWinApp,CWinApp)
	ON_COMMAND(ID_NEW,OnNew)
	ON_COMMAND(ID_DATA,OnData)
END_MESSAGE_MAP()
void CMyWinApp::OnData()
{
	CDocManager *pManager = this->m_pDocManager;
	POSITION nPos = pManager->GetFirstDocTemplatePosition();
	CMultiDocTemplate* pTemplate =
		(CMultiDocTemplate*)pManager->GetNextDocTemplate(nPos);
	nPos = pTemplate->GetFirstDocPosition();
	pTemplate->GetNextDoc(nPos);
	pTemplate->GetNextDoc(nPos);
	CMyDoc* pDoc=(CMyDoc*)pTemplate->GetNextDoc(nPos);
	pDoc->strDoc = "hello";
	nPos = pDoc->GetFirstViewPosition();
	pDoc->GetNextView(nPos);
	CMyView* pView =(CMyView*)pDoc->GetNextView(nPos);
	pDoc->UpdateAllViews(pView);//²ÎÊýÌíË­²»Ë¢Ë­
}
void CMyWinApp::OnNew()
{
	this->OnFileNew();
}
CMyWinApp theApp;
BOOL CMyWinApp::InitInstance()
{
	CMultiDocTemplate *pTemplate = new CMultiDocTemplate(
		IDR_MENU1,
		RUNTIME_CLASS(CMyDoc),
		RUNTIME_CLASS(CMyChild),
		RUNTIME_CLASS(CMyView));
	AddDocTemplate(pTemplate);
	CMyFrameWnd *pFrame = new CMyFrameWnd;
	pFrame->LoadFrame(IDR_MENU2);
	m_pMainWnd = pFrame;
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}