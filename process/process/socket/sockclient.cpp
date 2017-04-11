/*
#define MFDSET(m,fd,fds)
do
{ 
	if( (fd) >= 0 )
	{ 
		FD_SET((fd),(fds));
		m = m < (fd) ? (fd) : (m) ;
	} 
} while (0)
*/
#include "stdafx.h"
#include <WINSOCK2.H>
#pragma  comment(lib,"ws2_32.lib")

#define MIP "10.0.2.20"
#define PORT 8080
#define PORT2 8081

#define	MFDSET(m,fd,fds)    do { if( (fd) >= 0 ) { FD_SET((fd),(fds)); m = m < (fd) ? (fd) : (m) ; } } while (0)

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
	svrAddr.sin_port=htons(PORT);

#if 0
	SOCKADDR_IN svrAddr2={0};
	svrAddr2.sin_family=AF_INET;
	svrAddr2.sin_port=htons(8081);
	svrAddr2.sin_addr.S_un.S_addr=INADDR_ANY;
	bind(hSockClient, (SOCKADDR*)&svrAddr2,sizeof(svrAddr2));
#endif
	//block or noblock
	unsigned long ul=0;
	ioctlsocket(hSockClient,FIONBIO,(unsigned long *)&ul);
	//此处ip为服务器的ip
	svrAddr.sin_addr.S_un.S_addr=inet_addr(MIP);

	int n = connect(hSockClient,(SOCKADDR*)&svrAddr,sizeof(svrAddr));

#if 1
	SOCKET fd= 0;
	fd_set rds,myset;
	FD_ZERO(&myset);
	MFDSET(fd, hSockClient, &myset);
	struct timeval timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 100*1000;
	
	while (true)
	{
		puts("idle");
		rds = myset;
		int ret = select(fd+1, &rds, &rds, NULL, &timeout);
		if (ret == 0)
		{
			puts("time out");
		}else if(ret <0)
		{
			puts("getlasterror");
		}
		if (hSockClient >0 && FD_ISSET(hSockClient, &rds))
		{
			char buff[1024] = {0};
			int err = recv(hSockClient, buff, 1024, 0);
			if (err == 0)
			{
				puts("the socket has been close gracefully");
				break;
			}
			puts(buff);
			send(hSockClient, buff, 1024, 0);
		}
	}
#endif
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
	svrAddr.sin_port=htons(PORT);
	svrAddr.sin_addr.S_un.S_addr=inet_addr(MIP);

	SOCKADDR_IN svrAddr2={0};
	svrAddr2.sin_family=AF_INET;
	svrAddr2.sin_port=htons(PORT2);
	svrAddr2.sin_addr.S_un.S_addr=inet_addr(MIP);
	bind(hSockClient, (const sockaddr*)&svrAddr2, sizeof(svrAddr2));

	fd_set myset;
	SOCKET m = 0;
	FD_ZERO(&myset);
	MFDSET(m, hSockClient, &myset);
	
	while(true)
	{
		int ret = select(m+1, &myset, NULL, NULL, NULL);
		if (ret == 0)
		{
			puts("time out");
		}
		if (ret < 0)
		{
			puts("getlasterror");
		}
		if (hSockClient > 0 && FD_ISSET(hSockClient, &myset))
		{
			char buff[1024] = {0};
			recvfrom(hSockClient, buff, 1024, 0, NULL, NULL);
			puts(buff);
			sendto(hSockClient, buff, 1024, 0, (const sockaddr*)&svrAddr, sizeof(svrAddr));
		}
	}
	closesocket(hSockClient);
}
int main(int argc, char* argv[])
{
	WSADATA wsa={0};
	WSAStartup(MAKEWORD(2,2),&wsa);
#if 1
	TCPClient();
#else
	UDPClient();
#endif
	WSACleanup();
	return 0;
}
