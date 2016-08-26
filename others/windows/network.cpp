#include <stdio.h>
#include <Winsock2.h>
#include <iphlpapi.h>
#include <windows.h>
#include <process.h>
#include <string>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "iphlpapi.lib")

void fun(LPVOID pParam)
{
	OVERLAPPED overlap;
	overlap.hEvent = CreateEvent(NULL, TRUE, FALSE, "HHHHHH");
	HANDLE hand = NULL;
	
	do
	{
		struct in_addr addr;
		char buff2[128] ={0};
		wchar_t buf[128] = L"hellow";
		sprintf(buff2, "%s", buf);

		char name[65];
		gethostname(name, sizeof(name));
		printf("hostname = %s\n", name);

		struct hostent *remoteHost = gethostbyname(name);

		int i = 0;
		if (remoteHost->h_addrtype == AF_INET)
		{
			while (remoteHost->h_addr_list[i] != 0) {
				addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
				printf("\tIP Address #%d: %s\n", i, inet_ntoa(addr));
			}
		}
		else if (remoteHost->h_addrtype == AF_INET6)
		{   
			printf("IPv6 address was returned\n");
		}
		DWORD ret = NotifyAddrChange(&hand, &overlap);
	}while(WaitForSingleObject(overlap.hEvent, INFINITE) == WAIT_OBJECT_0);
}

int main()
{
	WSADATA wsa={0};
	WSAStartup(MAKEWORD(2,2),&wsa);
	   
	_beginthread(fun, 0, NULL);
	getchar();
	WSACleanup();
}
