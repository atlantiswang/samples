// UserChangePassword.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <string>
#include <lm.h>
using namespace std;

#if 0
void ChangePassword(int argc, _TCHAR* argv[])
{
	DWORD dwError = 0;
	NET_API_STATUS nStatus;
	//
	// All parameters are required.
	//
	if (argc != 5)
	{
		fwprintf(stderr, L"Usage: %s \\\\ServerName UserName OldPassword NewPassword\n", argv[0]);
		exit(1);
	}
	//
	// Call the NetUserChangePassword function.
	//
	nStatus = NetUserChangePassword(argv[1], argv[2], argv[3], argv[4]);
	//
	// If the call succeeds, inform the user.
	//
	if (nStatus == NERR_Success)
		fwprintf(stderr, L"User password has been changed successfully\n");
	//
	// Otherwise, print the system error.
	//
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
}
#endif

void GetInfo(char *strDns)
{
	NET_API_STATUS nStatus;
	wchar_t strwDns[128] = {0};
	MultiByteToWideChar(CP_ACP, 0, strDns, -1, strwDns, 128);
	LPCWSTR pwszServerName = strwDns;//NULL;
	WCHAR* pwszGroup[] =
	{
		L"Administrators",
		L"Users",
		L"Guests"
	};
	TCHAR* pszGroup[] =
	{
		_T("Administrators"),
		_T("Users"),
		_T("Guests")
	};
	DWORD dwLevel = 3;
	LPLOCALGROUP_MEMBERS_INFO_3 pBuf = NULL;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	DWORD_PTR dwResumeHandle = 0;
	for(int j=0; j<sizeof(pwszGroup)/sizeof(WCHAR*); j++)
	{
		nStatus = NetLocalGroupGetMembers(
			pwszServerName,
			pwszGroup[j],
			dwLevel,
			(LPBYTE*)&pBuf,
			dwPrefMaxLen,
			&dwEntriesRead,
			&dwTotalEntries,
			&dwResumeHandle);
		if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
		{
			MessageBoxW(NULL, pBuf->lgrmi3_domainandname, NULL, MB_OK);
		}
	}
}




#include <Iptypes.h>
#include <iphlpapi.h>
typedef struct tagNetworkCfg 
{
	char szIP[18];
	char szNetmask[18];
	char szGateway[18];
	char szDns1[18];
	char szDns2[18];
}NetworkCfg;
bool GetNetworkCfg(NetworkCfg *cfg)
{
	printf("Get network config");
	//获取网卡名称 网卡名称，网卡别名
	string strAdapterName,strAdapterAlias;
	HKEY hKey, hSubKey, hNdiIntKey;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"System\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}",
		0,
		KEY_READ,
		&hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwIndex = 0;
	DWORD dwBufSize = 256;
	DWORD dwDataType;
	char szSubKey[256];
	unsigned char szData[256];

	while(RegEnumKeyEx(hKey, dwIndex++, szSubKey, &dwBufSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
	{
		if(RegOpenKeyEx(hKey, szSubKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
		{    
			if(RegOpenKeyEx(hSubKey, "Ndi\\Interfaces", 0, KEY_READ, &hNdiIntKey) == ERROR_SUCCESS)
			{
				dwBufSize = 256;
				if(RegQueryValueEx(hNdiIntKey, "LowerRange", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
				{
					if(strstr((char*)szData, "ethernet") != NULL)//  判断是不是以太网卡
					{
						dwBufSize = 256;
						if(RegQueryValueEx(hSubKey, "DriverDesc", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
						{
							strAdapterName = (LPCTSTR)szData;
							dwBufSize = 256;
							if(RegQueryValueEx(hSubKey, "NetCfgInstanceID", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
							{
								strAdapterAlias = (LPCTSTR)szData;
								break;
							}
						}
					}
				}
				RegCloseKey(hNdiIntKey);
			}
			RegCloseKey(hSubKey);
		}

		dwBufSize = 256;
	}  /* end of while */

	RegCloseKey(hKey);
	if (strAdapterName.empty() || strAdapterAlias.empty())
	{
		printf("failed to get network config");
		return false;
	}
	string strKeyName = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
	strKeyName += strAdapterAlias;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		strKeyName.c_str(),
		0,
		KEY_READ,
		&hKey) != ERROR_SUCCESS)
		return FALSE;
	dwBufSize = 256;
	if(RegQueryValueEx(hKey, "DhcpIPAddress", 0,&dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		strcpy(cfg->szIP,(LPCTSTR)szData);
	else{
		if(RegQueryValueEx(hKey, "IPAddress", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
			strcpy(cfg->szIP,(LPCTSTR)szData);
	}

	dwBufSize = 256;
	if(RegQueryValueEx(hKey, "DhcpSubnetMask", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		strcpy(cfg->szNetmask,(LPCTSTR)szData);
	else
	{
		if(RegQueryValueEx(hKey, "SubnetMask", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
			strcpy(cfg->szNetmask,(LPCTSTR)szData);
	}

	dwBufSize = 256;
	if(RegQueryValueEx(hKey, "DhcpDefaultGateway", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		strcpy(cfg->szGateway,(LPCTSTR)szData);
	else
	{
		if(RegQueryValueEx(hKey, "DefaultGateway", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
			strcpy(cfg->szGateway,(LPCSTR)szData);
	}
	RegCloseKey(hKey);

	//获取DNS服务器信息
	FIXED_INFO *fi = (FIXED_INFO *)GlobalAlloc(GPTR,sizeof( FIXED_INFO));
	ULONG ulOutBufLen = sizeof(FIXED_INFO);
	DWORD ret = GetNetworkParams(fi, &ulOutBufLen);
	if(ret != ERROR_SUCCESS) 
	{ 
		GlobalFree(fi);
		fi = (FIXED_INFO *) GlobalAlloc( GPTR, ulOutBufLen );
		ret = GetNetworkParams(fi, &ulOutBufLen);
		if(ret != ERROR_SUCCESS) 
		{
			printf("Get Dns server failed"); 
			return false; 
		}
	}
	strcpy(cfg->szDns1,fi->DnsServerList.IpAddress.String);
	IP_ADDR_STRING *pIPAddr = fi->DnsServerList.Next;
	if(pIPAddr != NULL) 
		strcpy(cfg->szDns2, pIPAddr->IpAddress.String);
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
//	ChangePassword(argc, argv);
	/*ERROR_CANT_ACCESS_DOMAIN_INFO*/
//	GetInfo();
//	testNetUserEnum(argc, argv);
// 	NetworkCfg cfg;
// 	GetNetworkCfg(&cfg);
	char strDns[128] = {0};
	FIXED_INFO *fi = (FIXED_INFO *)GlobalAlloc(GPTR,sizeof( FIXED_INFO));
	ULONG ulOutBufLen = sizeof(FIXED_INFO);
	DWORD ret = GetNetworkParams(fi, &ulOutBufLen);
	if(ret != ERROR_SUCCESS) 
	{ 
		GlobalFree(fi);
		fi = (FIXED_INFO *) GlobalAlloc( GPTR, ulOutBufLen );
		ret = GetNetworkParams(fi, &ulOutBufLen);
		if(ret != ERROR_SUCCESS) 
		{
			printf("Get Dns server failed"); 
			return false; 
		}
	}
	strcpy(strDns,fi->DnsServerList.IpAddress.String);
	char UserName[128] = {0};
	DWORD dwLen = 128;
	GetUserName((LPSTR)UserName, &dwLen);
	puts(UserName);
	wchar_t strwDns[128] = {0};
	wchar_t strwUserName[128] = {0};
	MultiByteToWideChar(CP_ACP, 0, UserName, -1, strwUserName, 128);
	MultiByteToWideChar(CP_ACP, 0, strDns, -1, strwDns, 128);
	NET_API_STATUS nStatus;
	LPWSTR name;
	NETSETUP_JOIN_STATUS  buffType;
	nStatus = NetGetJoinInformation(
		strwDns,
		&name,
		&buffType
		);

	if (nStatus == NERR_Success)
	{
		MessageBoxW(NULL, name, NULL, MB_OK);
	}
		
	puts(strDns);
//	GetInfo("127.0.0.1");
	////////////////////////////
	system("pause");
	return 0;
}
