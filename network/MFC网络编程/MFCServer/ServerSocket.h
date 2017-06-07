#if !defined(AFX_SERVERSOCKET_H__8ACA6FDC_9384_44C9_8CCD_655C8A43A0B6__INCLUDED_)
#define AFX_SERVERSOCKET_H__8ACA6FDC_9384_44C9_8CCD_655C8A43A0B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

class CServerSocket : public CAsyncSocket
{
// Attributes
public:
	
// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();
	//初始化服务器端(创建、绑定、监听)
	BOOL InitServer(UINT nPort);
	BOOL RecvData(CSocket& client,BYTE* pData,long nLen);
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSOCKET_H__8ACA6FDC_9384_44C9_8CCD_655C8A43A0B6__INCLUDED_)
