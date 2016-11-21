// SockSvr.cpp : Defines the entry point for the console application.
//
/*
	send可以循环判断是否发送完全
	int nleft = nsize;
	while(nleft > 0)
	{
		int nsend = send(socket, psend, nleft, 0);	
		nleft -= nsend;
		psend += nsend;
	}
	
 */
#include <stdafx.h>
#include <WINSOCK2.H>
#include <windows.h>
#include <process.h>
#include <stdio.h>
#pragma  comment(lib,"ws2_32.lib")
#define MYPORT 8080

static unsigned int g_clientno = 0;

typedef struct _param{
	SOCKET clientsocket;
	SOCKADDR_IN clientaddr;
	unsigned int clientno;
}PARAM, *PPARAM;

#define	MFDSET(m,fd,fds)   \
do { if( (fd) >= 0 ) { FD_SET((fd),(fds)); m = m < (fd) ? (fd) : (m) ; } } while (0)

void __cdecl clientpro(void *pParam)
{
	PPARAM pP = (PPARAM)pParam;
	fd_set myset;
	FD_ZERO(&myset);
	SOCKET m = 0;
	MFDSET(m, pP->clientsocket, &myset);
	while(true){
		int ret = select(m, &myset, NULL, NULL, NULL);
		if (ret == 0)
		{
			puts("time out");
		}
		if (ret < 0)
		{
			puts("getlasterror");
		}
		if (pP->clientsocket, FD_ISSET(pP->clientsocket, &myset))
		{
			char szRecv[256]={0};
			int nret = recv(pP->clientsocket, szRecv, 256, 0);
			if (nret == 0)
			{
				system("cls");
				break;
			}
			char szSendBuff[256] = {0};
			sprintf(szSendBuff, "------------------\r\nclientNo:%d, %s",pP->clientno, szRecv);
			puts(szSendBuff);
			send(pP->clientsocket, szSendBuff, 256, 0);
		}
	}
	delete pParam;
}
//TCP服务器端
void TCPServer()
{
	//创建监听套接字
	SOCKET hSockSvr=
		socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (hSockSvr==INVALID_SOCKET)
	{
		return;
	}

// 	unsigned long ul=1;
// 	ioctlsocket(hSockSvr,FIONBIO,(unsigned long *)&ul);
	//绑定IP地址和端口
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(MYPORT);
	svrAddr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&svrAddr,
		sizeof(svrAddr));
	//listen是不阻塞的。
	listen(hSockSvr, SOMAXCONN);
	printf("等待客户端连接...\n");
	//////////////////////////////////////////////////////////////////////////
	fd_set myset;
	SOCKET m = 0;
	FD_ZERO(&myset);
	MFDSET(m, hSockSvr, &myset);
	
	while (true)
	{
		int ret = select(m, &myset, NULL, NULL, NULL);
		if (ret == 0)
		{
			puts("time out");
		}
		if (ret < 0)
		{
			puts("getlasterror");
		}
		if (hSockSvr && FD_ISSET(hSockSvr, &myset))
		{
			PPARAM pPara = new PARAM;
			memset(pPara, 0, sizeof(PARAM));
			int nLen=sizeof(pPara->clientaddr);
			pPara->clientsocket = accept(hSockSvr,(SOCKADDR*)&pPara->clientaddr,&nLen);
			pPara->clientno = g_clientno++;
			_beginthread(clientpro, 0, pPara);
		}
	}
	closesocket(hSockSvr);
}
void UDPServer()
{
	//创建套接字
	SOCKET hSockSvr=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (hSockSvr==INVALID_SOCKET)
	{
		return;
	}

	unsigned long ul=0;
	ioctlsocket(hSockSvr,FIONBIO,(unsigned long *)&ul);
	//绑定地址和端口
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(5679);
	svrAddr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&svrAddr,sizeof(svrAddr));
	//数据收发
	fd_set myset;
	FD_ZERO(&myset);
	SOCKET m = 0;
	MFDSET(m, hSockSvr, &myset);
	while(true)
	{
		int ret = select(m, &myset, NULL, NULL, NULL);
		if (ret == 0)
		{
			puts("time out");
		}
		if (ret < 0)
		{
			puts("getlasterr");
		}
		if (hSockSvr, FD_ISSET(hSockSvr, &myset))
		{
			SOCKADDR_IN addrclent = {0};
			int nlen = sizeof(addrclent);
			char buff[1024] = {0};
			recvfrom(hSockSvr, buff, 1024, 0, (sockaddr*)&addrclent, &nlen);
			puts(buff);
			sendto(hSockSvr, buff, 1024, 0, (const sockaddr*)&addrclent, nlen);
		}
	}
	closesocket(hSockSvr);
}
int main(int argc, char* argv[])
{
	//初始化socket库
	WSADATA wsa={0};
	WSAStartup(MAKEWORD(2,2),&wsa);
	//具体的通信
#if 0
	TCPServer();
#else
	UDPServer();
#endif
	WSACleanup();
	system("pause");
	return 0;
}