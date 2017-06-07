#ifndef _FTPCLIENT_H__
#define _FTPCLIENT_H__
#include <string>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#else
#define SOCKET int
#endif

using namespace std;

#ifdef _WIN32
class  __declspec(dllexport)   ftpclient 
#else
class ftpclient
#endif
{
public:
	ftpclient(const char* connmode="port", const char* transmode="binary");
	~ftpclient(void);

	int connect(const char* addr, unsigned short  port);
	int disconnect();
	int login(const char* username, const char* passwd);

	int get(const char* remotefile, const char* localfile);
	int put(const char* localfile, const char* remotefile);
	int gets(const char* remotedir, const char* localdir);
	int puts(const char* localdir, const char* remotedir);
	int dir(const char* remotedir, vector<string>& result);
	int ldir(const char* localdir, vector<string>& result);

	int PWD(char* remotedir);
	int CD(const char* remotedir);
	int MKDIR(const char* remotedir);
	int SIZE(const char* remotefile, int& length);
	//add by lbw
	int DEL(const char* remoteFile);

protected:
	int ASCII();
	int BINARY();
	int PASV(char* addr,  unsigned  short& port);
	int PORT(const char* addr, unsigned short port);

	int LIST(const char* remotedir);
	int RETR(const char* remotefile);
	int STOR(const char* remotefile);

	int serversock(SOCKET& sock, const char* addr, unsigned  short port);
	int datasock(SOCKET& sock, const char* addr,  unsigned short port);

	//command
private:
	SOCKET controlsock_;
	char   connmode_[8];
	char   transmode_[8];

};

#endif //_FTPCLIENT_H__



