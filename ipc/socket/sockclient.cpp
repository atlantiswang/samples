// SockClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WINSOCK2.H>
#pragma  comment(lib,"ws2_32.lib")

void TCPClient()
{
	SOCKET hSockClient=
		socket(AF_INET,SOCK_STREAM,0);
	if (hSockClient==INVALID_SOCKET)
	{
		return;
	}
	//绑定IP地址和端口
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(5678);
	//此处ip为服务器的ip
	svrAddr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	connect(hSockClient,(SOCKADDR*)&svrAddr,sizeof(svrAddr));
	//数据收发
	int err;
	unsigned long ul=1;
	//异步操作
	ioctlsocket(hSockClient,FIONBIO,(unsigned long *)&ul);
	char szSend[]="hello,i am a client!";
	while(getchar())
	{
		send(hSockClient,szSend,strlen(szSend),0);
		//然后接收数据
		char szRecv[256]={0};
		int nRecv;
		while(true)
		{
			Sleep(400);
			nRecv=recv(hSockClient,szRecv,256,0);
			if (nRecv == SOCKET_ERROR)
			{
				err = WSAGetLastError();
				if (err == WSAEWOULDBLOCK)
				{
					continue;
				}
				else if(err == WSAETIMEDOUT)
				{
					puts("time out");
				}
				else if(err == WSAENETDOWN)
				{
					puts("connect down");
				}
				else break;
			}
			else if(nRecv > 0)
			{
				printf("%s\n",szRecv);
				printf("DataLen:%d\n",nRecv);
				break;
			}
		}	
	}
	closesocket(hSockClient);
}
void UDPClient()
{
	SOCKET hSockClient=
		socket(AF_INET,SOCK_DGRAM,0);
	if(hSockClient==INVALID_SOCKET)
		return;
	SOCKADDR_IN svrAddr={0};
	svrAddr.sin_family=AF_INET;
	svrAddr.sin_port=htons(5679);
	svrAddr.sin_addr.S_un.S_addr=inet_addr("172.17.1.251");
	//数据收发
	char szSend[]="hello,i am a UDPclient";
	int nLen=sizeof(svrAddr);
	sendto(hSockClient,szSend,strlen(szSend),0,
		(SOCKADDR*)&svrAddr,nLen);
	//接收数据
	char szRecv[256]={0};
	recvfrom(hSockClient,szRecv,sizeof(szRecv),0,
		(SOCKADDR*)&svrAddr,&nLen);
	char *IP=inet_ntoa(svrAddr.sin_addr);
	printf("%s:%s\n",IP,szRecv);
	//关闭
	closesocket(hSockClient);
}
int main(int argc, char* argv[])
{
	WSADATA wsa={0};
	WSAStartup(MAKEWORD(2,2),&wsa);
	TCPClient();
	//UDPClient();
	WSACleanup();
	return 0;
}
