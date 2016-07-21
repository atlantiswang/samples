// DBMysql.cpp: implementation of the CDBMysql class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DBMysql.h"
//#include "Log.h"
#include <assert.h>
#include <cstring>
#pragma comment(lib,"libmysql")
//extern CLog g_Log;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBMysql::CDBMysql()
{	
	m_bConnected = false;
	m_sHost[0] = '\0';
	m_sUserName[0] = '\0';
	m_sPassword[0] = '\0';
	m_sDBName[0] = '\0';
	m_nPort = 0;		
	m_nClient_Flag = 0;
	m_pMySQL_RES = NULL;
	strcpy(m_sCharSet,"gb2312");
	mysql_library_init(-1, NULL, NULL);
}

CDBMysql::~CDBMysql()
{
	if(m_pMySQL_RES)
	{
		mysql_free_result(m_pMySQL_RES);
		m_pMySQL_RES = NULL;
	}
	if(m_bConnected)
	{
		mysql_close(&m_MySQL);		
	}
	mysql_library_end();
}

int CDBMysql::setcharset(MYSQL *mysql, const char *charset)
{
	if (mysql_options(mysql, MYSQL_SET_CHARSET_NAME, charset)) 
	{
//		g_Log.printf(LOG_ERROR, "%s:%d|Failed to set character set: %s\n", __FILE__, __LINE__, mysql_error(mysql));
		return -1;
	}
	strcpy(m_sCharSet,charset);
	return 0;
}

int CDBMysql::connect(const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned int client_flag)
{
	char *p;
	if(!mysql_init(&m_MySQL))
		return -1;

	if (setcharset(&m_MySQL, m_sCharSet))
		return -1;

	if(!mysql_real_connect(&m_MySQL, host, user, passwd, db, port, unix_socket,client_flag))	
	{
		p = (char *)mysql_error(&m_MySQL);
//		g_Log.printf(LOG_ERROR,"%s,%d\n %s",__FILE__,__LINE__,p);
		strcpy(m_sLastError,p);
		mysql_close(&m_MySQL);
		return -1;
	}
		
	m_bConnected = true;
	if(host)
		strcpy(m_sHost,host);
	if(user)
		strcpy(m_sUserName,user);
	if(passwd)
		strcpy(m_sPassword,passwd);
	if(db)
		strcpy(m_sDBName,db);
	m_nPort = port;
	//if(unix_socket)
	//	strcpy(m_sUnix_Socket,unix_socket);
	m_nClient_Flag = client_flag;
	return 0;	
}

int CDBMysql::doquery(const char *sql,bool store)
{
	if(!m_bConnected)
	{
       if(reconnect() != 0)
        {
			strcpy(m_sLastError,mysql_error(&m_MySQL));
//            g_Log.printf(LOG_ERROR, "%s,%d\nreconnectdb  error: %s, %s",__FILE__,__LINE__, sql, m_sLastError);
            return -1;
        }
	}
    try
    {
        if(mysql_real_query(&m_MySQL,sql,strlen(sql)))
        {
			strcpy(m_sLastError,mysql_error(&m_MySQL));
//            g_Log.printf(LOG_ERROR, "%s,%d\nquery mysql error: %s, %s", __FILE__,__LINE__,sql, m_sLastError);
            if(reconnect() != 0)
            {
				strcpy(m_sLastError,mysql_error(&m_MySQL));
//                g_Log.printf(LOG_ERROR, "%s,%d\nreconnectdb  error: %s, %s",__FILE__,__LINE__, sql, m_sLastError);
                return -1;
            }
            else
            {
                if(mysql_real_query(&m_MySQL,sql,strlen(sql)))
                {
                    strcpy(m_sLastError,mysql_error(&m_MySQL));
//                    g_Log.printf(LOG_ERROR, "%s,%d\nquery mysql error: %s, %s", __FILE__,__LINE__,sql, m_sLastError);
                    return -1;
                }
            }
        }
    }
    catch(...)
    {
//		g_Log.printf(LOG_ERROR, "%s,%d\n query mysql error: %s, %s",__FILE__,__LINE__, sql, mysql_error(&m_MySQL));
    }
    //Before free result when using mysql_use_result, will get "out of sync" error if do query    
	if(m_pMySQL_RES)
	{
		mysql_free_result(m_pMySQL_RES);
		m_pMySQL_RES = NULL;
	} 
	if(store == false)
		m_pMySQL_RES = mysql_use_result(&m_MySQL);
	else
		m_pMySQL_RES = mysql_store_result(&m_MySQL);
	return 0;
}
int CDBMysql::query(const char *sql)
{
	if(m_pMySQL_RES)
	{
		mysql_free_result(m_pMySQL_RES);
		m_pMySQL_RES = NULL;
	}
	return doquery(sql,false);	
}
int CDBMysql::query_and_store(const char *sql)
{
	if(m_pMySQL_RES)
	{
		mysql_free_result(m_pMySQL_RES);
		m_pMySQL_RES = NULL;
	}
	return doquery(sql,true);
}
int CDBMysql::update(const char *sql)
{
	if(m_pMySQL_RES)
	{
		mysql_free_result(m_pMySQL_RES);
		m_pMySQL_RES = NULL;
	}
	return doquery(sql,false);	
}

int CDBMysql::reconnect()
{
	if(m_pMySQL_RES)
	{
		mysql_free_result(m_pMySQL_RES);
		m_pMySQL_RES = NULL;
	}

	if(m_bConnected)
	{
		mysql_close(&m_MySQL);
		m_bConnected = false;
	}
	
	if(!mysql_init(&m_MySQL))
		return -1;
	
	if (setcharset(&m_MySQL, m_sCharSet))
		return -1;

	if(!mysql_real_connect(&m_MySQL, m_sHost,m_sUserName,m_sPassword, m_sDBName, m_nPort,NULL,m_nClient_Flag))	
	{
		char *p = (char *)mysql_error(&m_MySQL);
//		g_Log.printf(LOG_ERROR,"%s,%d\n %s",__FILE__,__LINE__,p);
		strcpy(m_sLastError,p);
		mysql_close(&m_MySQL);
		return -1;
	}
	m_bConnected = true;
	return 0;
}

unsigned long CDBMysql::rows()
{
	if(m_pMySQL_RES)
		return mysql_num_rows(m_pMySQL_RES);
	else
		return 0;
}

MYSQL_ROW CDBMysql::next()
{	
	if(m_pMySQL_RES == NULL)
		return 0;
	return mysql_fetch_row(m_pMySQL_RES);
}
void CDBMysql::seek(unsigned long pos)
{
	mysql_data_seek(m_pMySQL_RES,pos);	
}


bool CDBMysql::usenext()
{
	m_CurRow = next();
	if(m_CurRow)
		return true;
	return false;
}
int CDBMysql::getint(int index)
{
	if(m_CurRow[index])
		return atoi(m_CurRow[index]);
	return 0;
}
std::string CDBMysql::getstring(int index)
{
	if(m_CurRow[index])
		return m_CurRow[index];
	return "";
}

float CDBMysql::getfloat(int index)
{
	if(m_CurRow[index])
		return atof(m_CurRow[index]);
	return 0.0;
}
