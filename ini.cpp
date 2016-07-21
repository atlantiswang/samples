#define INICTRL_EXPORT

#include "ini.h"

bool inictrl::open(char *path, char *pfilename)
{
	char pathname[512] = {0};
	strcpy(pathname, path);
	strcat(pathname, pfilename);
	if((fp = fopen(pathname, "r")) == NULL)
		return false;
}
//readstring
bool inictrl::readstring(const char *proot,const char *plevel, char *pbuff, int size)
{
	bool nret = true;
	//find the proot

	pack(proot);
	plev = (char *)malloc(strlen(plevel)+1);
	strcpy(plev, plevel);
	while(fgets(pbuff, size, fp))
	{
		if (!feof(fp))
		{
			pbuff[strlen(pbuff)-1] = 0;
		}
		if( strcmp(psection, pbuff) == 0)
			break;
	}
	if(feof(fp))
	{
		nret = false;
		goto r_exit;
	}
	while(fgets(pbuff, size, fp))
	{
		if ('[' == pbuff[0])
		{
			nret = false;
			goto r_exit;
		}
		if (!feof(fp))
		{
			pbuff[strlen(pbuff)-1] = 0;
		}
		char szbefore[512] = {0};
		strcpy(szbefore, pbuff);
		*strchr(szbefore, '=') = 0;

		if(strcmp(plev, trim(szbefore)) == NULL)
		{
			char* plocation = strchr(pbuff, '=');
			strcpy(pbuff, trim(++plocation));
			goto r_exit;
		}
	}
	if(feof(fp))
	{
		nret =false;
		goto r_exit;
	}

r_exit:
	if(plev) free(plev), plev = NULL;
	if(psection) free(psection), psection = NULL;
	fseek(fp, 0, SEEK_SET);
	return nret;
}
//read int
bool inictrl::readint(const char *proot,const char *plevel, int *pint)
{
	bool bret = true;
	do 
	{
		char szbuff[512] = {0};
		if(!readstring(proot, plevel, szbuff, 512))
		{
			bret = false;
			break;
		}

		*pint = myatoi(trim(szbuff));
		if(*pint<0)
		{
			bret = false;
			break;
		}

	} while (0);

	if(plev) free(plev), plev = NULL;
	if(psection) free(psection), psection = NULL;
	fseek(fp, 0, SEEK_SET);
	return bret;
}

int inictrl::myatoi(char *p)
{
	int n = strlen(p);
	if(1==n && p[0] =='0')
		return 0;
	int num = atoi(p);
	for(int i = 0; i< n; ++i)
	{
		if (num == 0)
			return -1;
		if(p[i]<'0' || p[i] >'9')
			return -1;
	}
	return num;
}
//delete the space
char* inictrl::trim(char *p)
{
	int nlen = strlen(p);
	for (int i = 0; i<nlen; ++i)
	{
		if (p[nlen-1-i]==' ')
		{
			p[nlen-1-i]=0;
		}else break;
	}
	if (p[nlen-1]==' ')
	{
		p[nlen-1]=0;
	}
	for(int i = 0; i < nlen; ++i)
	{
		if(p[0] == ' ')
		{
			p++;
		}else break;
	}
	return p;
}

char* inictrl::pack(const char *p)
{
	int nlen = strlen(p);
	psection = (char *)malloc(nlen+3);
	memset(psection, 0, nlen+3);
	psection[0] = '[';
	strcat(psection, p);
	psection[nlen+1] = ']';
	psection[nlen+2] = 0;
	return psection;
}