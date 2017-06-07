#if !defined(AFX_CLIENTSOCKET_H__33DC167C_45A1_49A5_8DDF_E36A82B73D06__INCLUDED_)
#define AFX_CLIENTSOCKET_H__33DC167C_45A1_49A5_8DDF_E36A82B73D06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target

class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();
	//初始化客户端(创建、连接)
	BOOL InitClient(char* pIP,UINT nPort);
	BOOL SendData(BYTE* pData,long nLen);
	BOOL SendFile(CString sPath);
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__33DC167C_45A1_49A5_8DDF_E36A82B73D06__INCLUDED_)
