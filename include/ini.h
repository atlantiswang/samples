/*
 *	author wh_2396
 *	2016-04-18
 *	inictrl in;
 *	in.init("path", "filename");
 *	in.readstring("one", "num1", buff);	
 *	in.close();
 *  over
 */

#ifndef INI_H
#define INI_H
#include "stdio.h"
#include <string.h>
#include "stdlib.h"

#ifdef INICTRL_EXPORT
#define API _declspec(dllexport)
#else
#define API _declspec(dllimport)
#endif

#ifdef _WIN32
class /*API*/ inictrl
#else
class inictrl
#endif
{
public:
	inictrl():fp(NULL), psection(NULL), plev(NULL){};
	bool open(char *path, char *pfilename);
	bool close(){
		free(psection);
		free(plev);
		return fclose(fp);
	}

public:
	//(basic reader)
	bool readstring(const char *proot,const char *plevel, char *pbuff, int size);
	//read int
	bool readint(const char *proot,const char *plevel, int *pint);
	
private:
	int myatoi(char *p);
	//delete the space
	char* trim(char *p);
	char *pack(const char *p);

	char *psection;
	char *plev;
	FILE *fp;
};

#endif