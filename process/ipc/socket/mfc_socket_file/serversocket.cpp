// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "MFCServer.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions
BOOL CServerSocket::InitServer(UINT nPort)
{//Create的第二个参数决定是TCP还是UDP通信
	if (!Create(nPort))
	{
		return FALSE;
	}
	return Listen();
}
//定义文件信息的结构体
typedef struct _tagHeader
{
	char szName[128];
	long nLen;
}HEADER,*LPHEADER;
void CServerSocket::OnAccept(int nErrorCode) 
{
	//接收客户端连接
	CSocket client;
	Accept(client);
	//数据收发(接收文件)
	//首先接收文件信息(名称和长度)
	HEADER header={0};
	RecvData(client,(BYTE*)&header,sizeof(header));
	//然后，接收文件数据
	BYTE *pData=(BYTE*)malloc(header.nLen);
	RecvData(client,pData,header.nLen);
	//将文件数据保存到服务器端
	CString sPath="c:/";
	sPath+=header.szName;
	AfxMessageBox(sPath);
	CFile file;
	file.Open(sPath,CFile::modeCreate|CFile::modeWrite);
	file.Write(pData,header.nLen);
	file.Close();
	free(pData);
	//关闭
	client.Close();
	CAsyncSocket::OnAccept(nErrorCode);
}

BOOL CServerSocket::RecvData(CSocket& client,
							 BYTE* pData,long nLen)
{
	BYTE* pTmpData=pData;
	long nLeft=nLen;//表示剩余的还没有接收的数据的长度
	while (nLeft>0)
	{
		int nRecv=client.Receive(pTmpData,nLeft);
		if (nRecv==SOCKET_ERROR)
		{
			return FALSE;
		}
		nLeft-=nRecv;
		pTmpData+=nRecv;
	}
	return TRUE;
}
