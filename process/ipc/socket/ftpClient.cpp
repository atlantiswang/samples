#include "ftpClient.h"

#ifdef WIN32
#include <direct.h>
#include <io.h>
#include "mylog.h"
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <dirent.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#define  closesocket close
#define  Sleep(n)    usleep((n)*1000)
#define  mkdir(path) mkdir(path, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)

#endif

#include <stdio.h>
#include <fcntl.h>

#define DEBUG_LOG
#define FTPLOGFILE  "c:\\Huatech_FTPlog.txt"

#ifdef DEBUG_LOG
#include "comm_ht.h"
#endif


//====================================================================================

char* ltrim(char* psString, const char* pChars)
{
	char *pCurr = NULL;
	if((!psString) || psString[0]=='\0') return psString;

	for(pCurr=psString; (*pCurr)!='\0'; pCurr++)
	{
		int bFound = 0;
		for(const char* pX=pChars; *pX!=0; ++pX)
		{
			if(*pCurr==*pX) 
			{
				bFound = 1;
				break;
			}
		}
		if(!bFound) break;
	}

	if((*pCurr)=='\0') psString[0]='\0';
	else memmove(psString, pCurr, strlen(pCurr)+1);

	return psString;
}

char* rtrim(char* psString, const char* pChars)
{
	int iLen = 0;
	char *pCurr = NULL;
	if((!psString) || psString[0]=='\0') return psString;

	iLen = (int)strlen(psString);
	for(pCurr=psString+iLen-1; pCurr>=psString; pCurr--)
	{
		int bFound = 0;
		for(const char* pX=pChars; *pX!=0; ++pX)
		{
			if(*pCurr==*pX) 
			{
				bFound = 1;
				break;
			}
		}
		if(!bFound) break;
	}

	*(pCurr+1) = '\0';
	return psString;
}

char* lrtrim(char* psString, const char* pChars)
{
	return rtrim(ltrim(psString, pChars), pChars);
}

const char*  StrFindFirstOf(const char* pstring, const char* psToFindOneOf)
{
	const char* pOneOf = psToFindOneOf;
	const char* pPos = pstring;
	for( ; *pPos!='\0'; ++pPos)
	{
		pOneOf = psToFindOneOf;
		for(; *pOneOf!='\0'; ++pOneOf)
		{
			if(*pOneOf==*pPos)
			{
				return pPos;
			}
		}
	}
	return NULL;
}

void  StrSplitByOneOf(std::vector<std::string>& vMultiStrings, const char* pstring, const char* psToFindOneOf)
{
	const char* pBegin = pstring;
	const char* pEnd = NULL;
	for(;;)
	{
		pEnd = StrFindFirstOf(pBegin, psToFindOneOf);
		if(pEnd==NULL)
		{
			vMultiStrings.push_back(std::string(pBegin));
			return ;
		}
		else
		{
			vMultiStrings.push_back(std::string(pBegin, pEnd-pBegin));
			pBegin = pEnd+1;
		}       
	}
}

int read(SOCKET sock, string& buffer)
{
	int count = 0;
	buffer.clear();

	while(1)
	{
		char buf[1024] = {0};

		int ret = ::recv(sock, buf, 1024, 0);
		if (ret>0)
		{
			buffer += buf;
			count += ret;
		}

		if (ret<1024)
		{
			break;
		}
	}

	return count;
}

int read(SOCKET sock, const char* local_file, const char* mode)
{
	if (-1==access(local_file, 0))
		return -1;

	char buf[1024] = {0};
	FILE* fp = fopen(local_file, mode);

	while(1)
	{
		int ret = fread(buf, 1, 1024, fp);
		if (ret>0)
		{
			send(sock, buf, ret, 0);
		}

		if (ret < 1024)
		{
			break;
		}
	}

	fclose(fp);

	return 0;
}

int write(SOCKET sock, const char* local_file, const char* mode)
{
	char buf[1024] = {0};
	FILE* fp = fopen(local_file, mode);
	if (NULL==fp)
	{
		return -1;
	}

	int length =0;
	while(length = recv(sock, buf, 1024, 0))  
	{  
		if (length < 0)  
		{  
			printf("Receve Data   Failed!\n" );  
			break;  
		}  

		int write_length = fwrite(buf, sizeof(char), length, fp);  
		if (write_length < length)  
		{  
			printf("", local_file);  
			break;  
		}  
		memset(buf,0,1024);
	}  


	fclose(fp);

	return 0;
}


int execcmd(SOCKET sock, const char* command, const char* checkcode, string& result)
{
	int  ret = -1;

	ret = send(sock, command, strlen(command), 0);
	if (ret<=0)
	{
		return -1;
	}
	//printf("%s\n", command);
#ifdef DEBUG_LOG
	writeLog(FTPLOGFILE,command, strlen(command));
#endif

	Sleep(50);
	ret = read(sock, result);
	if (ret>0)
	{
		//printf("%s\n", result.c_str());
#ifdef DEBUG_LOG
		writeLog(FTPLOGFILE, result.c_str(), result.length());
#endif

		if (string::npos == result.find(checkcode))
		{
			//对于检测150的应答码，有的版本FTP是125
			if (strncmp(checkcode,"150",3)==0)
			{
				if(string::npos == result.find("125"))
					return -1;
				else
					return 0;
			}

			return -1;
		}
		else
			return 0;
	}
		
	return -1;
}

int execcmd(SOCKET sock, const char* command, const char* checkcode)
{
	string result;
	return execcmd(sock, command, checkcode, result);
}

//============================================================================================

ftpclient::ftpclient(const char* connmode/*="port"*/, const char* transmode/*="binary"*/)
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
#endif

	strncpy(connmode_, connmode, 8);
	strncpy(transmode_, transmode, 8);
	controlsock_ = -1;
}


ftpclient::~ftpclient(void)
{
	disconnect();
#ifdef _WIN32
	WSACleanup();
#endif
}


int ftpclient::connect(const char* addr, unsigned short port)
{
	string buffer;
	struct sockaddr_in svr_addr = {0};

	controlsock_ = socket(AF_INET, SOCK_STREAM, 0);
	svr_addr.sin_addr.s_addr = inet_addr(addr);
	svr_addr.sin_family = AF_INET;
	svr_addr.sin_port = htons(port);

	// 设置成非阻塞connect [10/27/2016 wh]
// 	unsigned int ul = 1;
// 	::ioctlsocket(controlsock_, FIONBIO, (unsigned long *)&ul);

	int ret= ::connect(controlsock_,(struct sockaddr *)&svr_addr, sizeof(svr_addr));
	if (ret==-1)
	{
// 		struct timeval timeout ;
// 		fd_set r;
// 
// 		FD_ZERO(&r);
// 		FD_SET(controlsock_, &r);
// 		timeout.tv_sec = 2;
// 		timeout.tv_usec =0;
// 		int ret = select(0, 0, &r, 0, &timeout);
// 		if (ret <= 0)
// 		{
// 			printf("[ftp]:connect time out.\n");
// 			return -1;
// 		}
		printf("[ftp]:connect time out.\n");
		return -1;
	}
	// 恢复成阻塞模式 [10/27/2016 wh]
// 	ul = 0;
// 	::ioctlsocket(controlsock_, FIONBIO, (unsigned long *)&ul);
	printf("[ftp]:connect is success.\n");

	/* 客户端接收服务器端的一些欢迎信息 */
	ret = read(controlsock_, buffer);
	if (ret>0)
	{
		printf("[ftp]:%s\n", buffer.c_str());
	}
	else
	{
		printf("[ftp]:ret <= 0");
		return -1;
	}

	return 0;
}

int ftpclient::disconnect()
{
	if (-1!=controlsock_)
	{
		::closesocket(controlsock_);
		controlsock_ = -1;
	}
	
	return 0;
}

int ftpclient::login(const char* username, const char* passwd)
{
	char  command[256] = {0};

	/* 命令 ”USER username\r\n” */
	sprintf(command,"USER %s\r\n",username);

	/* 客户端接收服务器的响应码和信息，正常为 ”331 User name okay, need password.” */
	if (-1==execcmd(controlsock_, command, "331"))
	{
		return -1;
	}

	/* 命令 ”PASS password\r\n” */
	sprintf(command,"PASS %s\r\n",passwd);

	/* 客户端接收服务器的响应码和信息，正常为 ”230 User logged in, proceed.” */
	if (-1==execcmd(controlsock_, command, "230"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::get(const char* remotefile, const char* localfile)
{
	if (-1!=access(localfile,0))
	{
		return -1;
	}

	if (0==strcmp("pasv", connmode_))
	{
		SOCKET data_sock;
		char   addr[16] = {0};
		unsigned short   port = 0;
		string buffer;

		if (-1==PASV(addr, port))
		{
			return -1;
		}

		if (-1==datasock(data_sock, addr, port))
		{
			return -1;
		}

		char mode[4] = {0};
		if (0==strcmp("ascii", transmode_))
		{
			strcpy(mode, "wt");
			if (-1==ASCII())
			{
				return -1;
			}
		}
		else
		{
			strcpy(mode, "wb");
			if (-1==BINARY())
			{
				return -1;
			}
		}

		if (-1==RETR(remotefile))
		{
			return -1;
		}

		Sleep(20);

		if (-1==write(data_sock, localfile, mode))
		{
			return -1;
		}

		do 
		{
			::closesocket(data_sock);

			read(controlsock_, buffer);
			//printf("%s\n", buffer.c_str());
			if (string::npos == buffer.find("226"))
			{
				return -1;
			}
		} while (0);
	}
	else
	{
		SOCKET data_sock;
		SOCKET server_sock;
		struct sockaddr_in  client_addr = {0};
		char   addr[16] = {0};
		unsigned short   port = 123*256+124;
		char   hostname[128] = {0};
		struct hostent *hp = NULL;
		string buffer;

		if (-1==serversock(server_sock, "", port))
		{
			return -1;
		}

		gethostname(hostname, 128);
		hp = gethostbyname(hostname);
		strcpy(addr, (char*)inet_ntoa(*(struct in_addr*)hp->h_addr));

		if (-1==PORT(addr, port))
		{
			return -1;
		}

		char mode[4] = {0};
		if (0==strcmp("ascii", transmode_))
		{
			strcpy(mode, "wt");
			if (-1==ASCII())
			{
				return -1;
			}
		}
		else
		{
			strcpy(mode, "wb");
			if (-1==BINARY())
			{
				return -1;
			}
		}

		if (-1==RETR(remotefile))
		{
			return -1;
		}

		data_sock = accept(server_sock,(struct sockaddr *)&client_addr, NULL);

		Sleep(20);

		if (-1==write(data_sock, localfile, mode))
		{
			return -1;
		}

		do 
		{
			::closesocket(data_sock);
			::closesocket(server_sock);

			read(controlsock_, buffer);
			//printf("%s\n", buffer.c_str());
			if (string::npos == buffer.find("226"))
			{
				return -1;
			}
		} while (0);
	}

	return 0;
}

int ftpclient::put(const char* localfile, const char* remotefile)
{
	if (-1==access(localfile,0))
	{
		return -1;
	}

	if (0==strcmp("pasv", connmode_))
	{
		SOCKET data_sock;
		char   addr[16] = {0};
		unsigned short   port = 0;
		string buffer;

		if (-1==PASV(addr, port))
		{
			return -1;
		}

		if (-1==datasock(data_sock, addr, port))
		{
			return -1;
		}

		Sleep(20);

		char mode[4] = {0};
		if (0==strcmp("ascii", transmode_))
		{
			strcpy(mode, "rt");
			if (-1==ASCII())
			{
				return -1;
			}
		}
		else
		{
			strcpy(mode, "rb");
			if (-1==BINARY())
			{
				return -1;
			}
		}

		if (-1==STOR(remotefile))
		{
			return -1;
		}

		Sleep(20);

		if (-1==read(data_sock, localfile, mode))
		{
			return -1;
		}

		do 
		{
			::closesocket(data_sock);

			read(controlsock_, buffer);
			//printf("%s\n", buffer.c_str());
			if (string::npos == buffer.find("226"))
			{
				return -1;
			}
		} while (0);
	}
	else
	{
		SOCKET data_sock;
		SOCKET server_sock;
		struct sockaddr_in  client_addr = {0};
		char   addr[16] = {0};
		unsigned short   port = 123*256+124;
		char   hostname[128] = {0};
		struct hostent *hp = NULL;
		string buffer;

		if (-1==serversock(server_sock, "", port))
		{
			return -1;
		}

		gethostname(hostname, 128);
		hp = gethostbyname(hostname);
		if(hp == NULL)
			printf("gethostbyname is error %s\n", strerror(errno));
		strcpy(addr, (char*)inet_ntoa(*(struct in_addr*)hp->h_addr));

		if (-1==PORT(addr, port))
		{
			return -1;
		}

		char mode[4] = {0};
		if (0==strcmp("ascii", transmode_))
		{
			strcpy(mode, "rt");
			if (-1==ASCII())
			{
				return -1;
			}
		}
		else
		{
			strcpy(mode, "rb");
			if (-1==BINARY())
			{
				return -1;
			}
		}

		if (-1==STOR(remotefile))
		{
			return -1;
		}

		data_sock = accept(server_sock,(struct sockaddr *)&client_addr, NULL);
		Sleep(20);
		if (-1==read(data_sock, localfile, mode))
		{
			return -1;
		}

		do 
		{
			::closesocket(data_sock);
			::closesocket(server_sock);

			read(controlsock_, buffer);
			//printf("%s\n", buffer.c_str());
			if (string::npos == buffer.find("226"))
			{
				return -1;
			}
		} while (0);
	}
	return 0;
}

int ftpclient::gets(const char* remotedir, const char* localdir)
{
	if (-1==access(localdir,0))
	{
		return -1;
	}

	vector<string> result;
	if (-1==dir(remotedir, result))
	{
		return -1;
	}

	vector<string>::iterator iter = result.begin();
	for (;iter!=result.end();iter++)
	{
		char buf[1024] = {0};
		strncpy(buf, (*iter).c_str(), 1024);
		lrtrim(buf, " ");
		string str = buf;
		int index = str.rfind(" ");
		str = str.substr(index+1, str.size()-index-1);

		string remote_file;
		string local_file;

		if (remotedir[strlen(remotedir)-1]=='/'||remotedir[strlen(remotedir)-1]=='\\')
		{
			remote_file = remotedir + str;
		}
		else
		{
			remote_file = remotedir + string("/") + str;
		}

		if (localdir[strlen(localdir)-1]=='/'||localdir[strlen(localdir)-1]=='\\')
		{
			local_file = localdir + str;
		}
		else
		{
			local_file = localdir + string("/") + str;
		}

		if (buf[0]=='d')
		{
			if(-1==mkdir(local_file.c_str()))
			{
				//return -1;
			}

			if (-1==gets(remote_file.c_str(), local_file.c_str()))
			{
				return -1;
			}
		}
		else if (buf[0]=='-')
		{
			if (-1==get(remote_file.c_str(), local_file.c_str()))
			{
				return -1;
			}
		}
	}

	return 0;
}

int ftpclient::puts(const char* localdir, const char* remotedir)
{
	if (-1==access(localdir,0))
	{
		return -1;
	}

	vector<string> result;
	if (-1==ldir(localdir, result))
	{
		return -1;
	}

	vector<string>::iterator iter = result.begin();
	for (;iter!=result.end();iter++)
	{
		char buf[256] = {0};
		strncpy(buf, (*iter).c_str(), 256);
		lrtrim(buf, " ");
		string str = buf;
		int index = str.rfind(" ");
		str = str.substr(index+1, str.size()-index-1);

		string remote_file;
		string local_file;

		if (localdir[strlen(localdir)-1]=='/'||localdir[strlen(localdir)-1]=='\\')
		{
			local_file = localdir + str;
		}
		else
		{
			local_file = localdir + string("/") + str;
		}

		if (remotedir[strlen(remotedir)-1]=='/'||remotedir[strlen(remotedir)-1]=='\\')
		{
			remote_file = remotedir + str;
		}
		else
		{
			remote_file = remotedir + string("/") + str;
		}

		if (buf[0]=='d')
		{
			if(-1==mkdir(remote_file.c_str()))
			{
				//return -1;
			}

			if (-1==puts(local_file.c_str(), remote_file.c_str()))
			{
				return -1;
			}
		}
		else if (buf[0]=='-')
		{
			if (-1==put(local_file.c_str(), remote_file.c_str()))
			{
				return -1;
			}
		}
	}
	return 0;
}

int ftpclient::dir(const char* remotedir, vector<string>& result)
{
	if (0==strcmp("pasv", connmode_))
	{
		SOCKET data_sock;
		char   addr[16] = {0};
		unsigned short   port = 0;
		string buffer;

		if (-1==PASV(addr, port))
		{
			return -1;
		}

		if (-1==datasock(data_sock, addr, port))
		{
			return -1;
		}

		char mode[4] = {0};
		if (0==strcmp("ascii", transmode_))
		{
			strcpy(mode, "wt");
			if (-1==ASCII())
			{
				return -1;
			}
		}
		else
		{
			strcpy(mode, "wb");
			if (-1==BINARY())
			{
				return -1;
			}
		}

		if (-1==LIST(remotedir))
		{
			return -1;
		}

		Sleep(20);

		do 
		{
			vector<char> result_buf;
			int   index = 0;
			char  buf[1024] = {0};

			result_buf.resize(1024*10);
			char* ptr = &*result_buf.begin();

			while(1)
			{
				int ret = recv(data_sock, buf, 1024, 0);
				if (ret>0)
				{
					if (ret>result_buf.size()-index)
					{
						result_buf.resize(index+1024*10);
						ptr = &*result_buf.begin();
						memcpy(ptr+index, buf, ret);
						index += ret;
					}
					else
					{
						memcpy(ptr+index, buf, ret);
						index += ret;
					}
				}

				if (ret < 1024)
				{
					break;
				}
			}

			StrSplitByOneOf(result, ptr, "\r\n");

		} while (0);

		do 
		{
			::closesocket(data_sock);

			read(controlsock_, buffer);
			//printf("%s\n", buffer.c_str());
			if (string::npos == buffer.find("226"))
			{
				return -1;
			}

		} while (0);
	}
	else
	{
		SOCKET data_sock;
		SOCKET server_sock;
		struct sockaddr_in  client_addr = {0};
		char   addr[16] = {0};
		unsigned short   port = 123*256+124;
		char   hostname[128] = {0};
		struct hostent *hp = NULL;
		string buffer;

		if (-1==serversock(server_sock, "", port))
		{
			return -1;
		}

		gethostname(hostname, 128);
		hp = gethostbyname(hostname);
		strcpy(addr, (char*)inet_ntoa(*(struct in_addr*)hp->h_addr));

		if (-1==PORT(addr, port))
		{
			return -1;
		}

		char mode[4] = {0};
		if (0==strcmp("ascii", transmode_))
		{
			strcpy(mode, "wt");
			if (-1==ASCII())
			{
				return -1;
			}
		}
		else
		{
			strcpy(mode, "wb");
			if (-1==BINARY())
			{
				return -1;
			}
		}

		if (-1==LIST(remotedir))
		{
			return -1;
		}

		data_sock = accept(server_sock,(struct sockaddr *)&client_addr, NULL);

		Sleep(20);

		do 
		{
			vector<char> result_buf;
			int   index = 0;
			char  buf[1024] = {0};

			result_buf.resize(1024*10);
			char* ptr = &*result_buf.begin();

			while(1)
			{
				int ret = recv(data_sock, buf, 1024, 0);
				if (ret>0)
				{
					if (ret>result_buf.size()-index)
					{
						result_buf.resize(index+1024*10);
						ptr = &*result_buf.begin();
						memcpy(ptr+index, buf, ret);
						index += ret;
					}
					else
					{
						memcpy(ptr+index, buf, ret);
						index += ret;
					}
				}

				if (ret < 1024)
				{
					break;
				}
			}

			StrSplitByOneOf(result, ptr, "\r\n");

		} while (0);

		do 
		{
			::closesocket(data_sock);
			::closesocket(server_sock);

			read(controlsock_, buffer);
			//printf("%s\n", buffer.c_str());
			if (string::npos == buffer.find("226"))
			{
				return -1;
			}
		} while (0);
	}

	return 0;
}

int ftpclient::ldir(const char* localdir, vector<string>& result)
{
	string local_path; 

	if (localdir[strlen(localdir)-1]=='/'|| localdir[strlen(localdir)-1]=='\\')
	{
		local_path = string(localdir) + "*.*";
	}
	else
	{
		local_path = string(localdir) + "/*.*";
	}

#ifdef _WIN32
	long   handle = 0;
	struct _finddata_t fileinfo;
	
	handle = _findfirst(local_path.c_str(), &fileinfo);
	if (-1==handle)
	{
		return -1;
	}
	
	do
	{
		if (0==strcmp(".", fileinfo.name)||0==strcmp("..", fileinfo.name))
		{
			continue;
		}

		if (fileinfo.attrib&_A_SUBDIR)
		{
			local_path = string("d ") + fileinfo.name;
		}
		else
		{

			local_path = string("- ") + fileinfo.name;
		}

		result.push_back(local_path);

	} while(!_findnext(handle, &fileinfo));

	_findclose(handle);
#else

	DIR *dp = NULL;
	struct dirent *dirp = NULL;

//	if ((dp=opendir(local_path.c_str()))==NULL)
	if ((dp=opendir(localdir))==NULL)
	{
		return -1;
	}

	while((dirp=readdir(dp))!=NULL)
	{
		if (0==strcmp(".", dirp->d_name)||0==strcmp("..", dirp->d_name))
		{
			continue;
		}

		if (dirp->d_type&DT_DIR)
		{
			local_path = string("d ") + dirp->d_name;
		}
		else
		{

			local_path = string("- ") + dirp->d_name;
		}
		result.push_back(local_path);
	}

	closedir(dp);

#endif
	return 0;
}

int ftpclient::PWD(char* remotedir)
{
	char  command[256] = {0};

	/* 命令 ”PWD filename\r\n” */
	sprintf(command,"PWD %s\r\n", remotedir);

	/* 客户端接收服务器的响应码和信息，正常为 ”257 <size>” */
	if (-1==execcmd(controlsock_, command, "257"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::CD(const char* remotedir)
{
	char command[256] = {0};

	/* 命令 ”CWD dirname\r\n” */
	sprintf(command,"CWD %s\r\n", remotedir);

	/* 客户端接收服务器的响应码和信息，正常为 ”250 Command okay.” */
	if (-1==execcmd(controlsock_, command, "250"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::DEL(const char* remoteFile)
{
	char command[256] = {0};

	/* 命令 ”DELE remoteFile\r\n” */
	sprintf(command,"DELE %s\r\n", remoteFile);

	/* 客户端接收服务器的响应码和信息，正常为 ”250 Requested file action okay, deleted xxx */
	if (-1==execcmd(controlsock_, command, "250"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::MKDIR(const char* remotedir)
{
	char command[256] = {0};

	/* 命令 ”XMKD dirname\r\n” */
	sprintf(command,"XMKD %s\r\n", remotedir);

	/* 客户端接收服务器的响应码和信息，正常为 ”257 "/home/sscc/test3" created” */
	if (-1==execcmd(controlsock_, command, "257"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::SIZE(const char* remotefile, int& length)
{
	char   command[256] = {0};
	char   result[16] = {0};
	string buffer;

	/* 命令 ”SIZE filename\r\n” */
	sprintf(command,"SIZE %s\r\n",remotefile);

	/* 客户端接收服务器的响应码和信息，正常为 ”213 <size>” */
	if (-1==execcmd(controlsock_, command, "213", buffer))
	{
		return -1;
	}

	buffer = buffer.substr(buffer.find("213")+3, buffer.size()-buffer.find("213")-3);
	strcpy(result, buffer.c_str());

	return atol(lrtrim(result, ""));
}

int ftpclient::ASCII()
{
	char  command[256] = {0};

	/* 命令 ”ASCII\r\n” */
	sprintf(command,"TYPE A\r\n");

	/*正常为 ”227 Entering passive mode (<h1,h2,h3,h4,p1,p2>)” */
	if (-1==execcmd(controlsock_, command, "200"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::BINARY()
{
	char  command[256] = {0};

	/* 命令 ”BIN\r\n” */
	sprintf(command,"TYPE I\r\n");

	/*正常为 ”227 Entering passive mode (<h1,h2,h3,h4,p1,p2>)” */
	if (-1==execcmd(controlsock_, command, "200"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::PASV(char* addr, unsigned short & port)
{
	char    command[256] = {0};
	string  buffer;
	vector<std::string> vAddrElem;

	/* 命令 ”PASV\r\n” */
	sprintf(command,"PASV\r\n");

	/*客户端接收服务器的响应码和新开的端口号，
	* 正常为 ”227 Entering passive mode (<h1,h2,h3,h4,p1,p2>)” */
	if (-1==execcmd(controlsock_, command, "227", buffer))
	{
		return -1;
	}

	buffer = buffer.substr(buffer.find('(')+1, buffer.find(')')-buffer.find('(')-1);

	StrSplitByOneOf(vAddrElem, buffer.c_str(), ",");

	sprintf(addr, "%s.%s.%s.%s", vAddrElem[0].c_str(), vAddrElem[1].c_str(), vAddrElem[2].c_str(), vAddrElem[3].c_str());

	port = atoi(vAddrElem[4].c_str())*256 + atoi(vAddrElem[5].c_str());

	return 0;
}

int ftpclient::PORT(const char* addr, unsigned short  port)
{
	char   command[256] = {0};
	char*  ptr = command;

	/* 命令 ”PORT \r\n” */
	sprintf(command,"PORT %s,%d,%d\r\n", addr, port/256, port%256);

	while(*ptr++!='\0')
	{
		if (*ptr=='.')
		{
			*ptr = ',';
		}
	}

	/* 客户端接收服务器的响应码和信息，正常为 ”200 Port command successful” */
	if (-1==execcmd(controlsock_, command, "200"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::LIST(const char* remotedir)
{
	char command[256] = {0};

	sprintf(command,"LIST %s\r\n", remotedir);

	/* 客户端接收服务器的响应码和信息，正常为 ”150 Opening data channel for file transfer.” */
	if (-1==execcmd(controlsock_, command, "150"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::RETR(const char* remotefile)
{
	char command[256] = {0};

	sprintf(command,"RETR %s\r\n", remotefile);

	/* 客户端接收服务器的响应码和信息，正常为 ”150 Opening data channel for file transfer.” */
	if (-1==execcmd(controlsock_, command, "150"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::STOR(const char* remotefile)
{
	char command[256] = {0};

	sprintf(command,"STOR %s\r\n", remotefile);

	/* 客户端接收服务器的响应码和信息，正常为 ”150 Opening data channel for file transfer.” */
	if (-1==execcmd(controlsock_, command, "150"))
	{
		return -1;
	}

	return 0;
}

int ftpclient::serversock(SOCKET& sock, const char* addr, unsigned short  port)
{
	struct  sockaddr_in  serveraddr = {0};

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htons(INADDR_ANY);
	serveraddr.sin_port = htons(port);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1==sock)
	{
		return -1;
	}

	if (-1==bind(sock, (struct sockaddr *)&serveraddr, sizeof(serveraddr)))
	{
		return -1;
	}

	/* 客户端开始监听端口p1*256+p2 */
	if (-1==listen(sock, 64))
	{
		return -1;
	}

	return 0;
}

int ftpclient::datasock(SOCKET& sock, const char* addr, unsigned short  port)
{
	struct  sockaddr_in serveraddr = {0};

	serveraddr.sin_addr.s_addr = inet_addr(addr);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (-1==sock)
	{
		return -1;
	}

	if (-1==::connect(sock,(struct sockaddr *)&serveraddr, sizeof(serveraddr)))
	{
		return -1;
	}

	return 0;
}
