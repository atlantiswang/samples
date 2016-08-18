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
#include "stdafx.h"
#include <WINSOCK2.H>
#pragma  comment(lib,"ws2_32.lib")
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
	//绑定IP地址和端口
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(5678);
	svrAddr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&svrAddr,
		sizeof(svrAddr));
	listen(hSockSvr,5);
	printf("等待客户端连接...\n");
	SOCKADDR_IN clientAddr={0};
	int nLen=sizeof(clientAddr);
	////////////////////////////////////
	while(1){
	SOCKET hClientSock=
		accept(hSockSvr,(SOCKADDR*)&clientAddr,&nLen);
	//接收数据
	char szRecv[256]={0};
	int nRecv=recv(hClientSock,szRecv,256,0);
	char *ClientIP=inet_ntoa(clientAddr.sin_addr);
	printf("%s:%s\n",ClientIP,szRecv);
	printf("DataLen:%d\n",nRecv);
	//发送数据
	char szSend[]="hello,i am a Server";
	send(hClientSock,szSend,strlen(szSend),0);
	closesocket(hClientSock);
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
	//绑定地址和端口
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(5679);
	svrAddr.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockSvr,(SOCKADDR*)&svrAddr,sizeof(svrAddr));
	//数据收发
	//服务器端首先接收数据
	char szRecv[256]={0};
	SOCKADDR_IN clientAddr={0};
	int nLen=sizeof(clientAddr);
	int nRecv=recvfrom(hSockSvr,szRecv,sizeof(szRecv),0,
		(SOCKADDR*)&clientAddr,&nLen);
	char *IP=inet_ntoa(clientAddr.sin_addr);
	printf("%s:%s\n",IP,szRecv);
	printf("DataLen:%d\n",nRecv);
	//然后发送
	char szSend[]="hello,i am a UDPsender";
	sendto(hSockSvr,szSend,strlen(szSend),0,
		(SOCKADDR*)&clientAddr,nLen);
	//关闭套接字
	closesocket(hSockSvr);
}
int main(int argc, char* argv[])
{
	//初始化socket库
	WSADATA wsa={0};
	WSAStartup(MAKEWORD(2,2),&wsa);
	//具体的通信
	TCPServer();
	//UDPServer();
	//卸载socket
	WSACleanup();
	return 0;
}

