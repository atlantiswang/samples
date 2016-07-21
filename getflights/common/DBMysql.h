// DBMysql.h: interface for the CDBMysql class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMYSQL_H__820820C7_8A4D_45F5_951E_6333EB571CA7__INCLUDED_)
#define AFX_DBMYSQL_H__820820C7_8A4D_45F5_951E_6333EB571CA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef WIN32
#include <winsock.h>
#endif
#include<string>
#include "common/mysql.h"

class CDBMysql  
{
public:
	CDBMysql();
	virtual ~CDBMysql();
	int connect(const char *host,const char *user,const char *passwd,const char *db,unsigned int port = MYSQL_PORT,const char *unix_socket = NULL,unsigned int client_flag = 0);
	int query(const char *sql);
	int query_and_store(const char *sql);
	int update(const char *sql);	
	unsigned long rows();
	MYSQL_ROW next();
	bool usenext();
	int getint(int index);
	std::string getstring(int index);
	float getfloat(int index);
	void seek(unsigned long pos);
	const char *getlasterror(){return m_sLastError;};
	int start_transaction(){return update("START TRANSACTION");};
	bool commit(){return (bool)mysql_commit(&m_MySQL) ;};
	bool rollback(){return (bool)mysql_rollback(&m_MySQL);}
	unsigned long getinsertid(){
		if(m_bConnected)
			return mysql_insert_id(&m_MySQL);
		return 0;
	};
	
private:
	int reconnect();
	int doquery(const char *sql,bool store = false);
	int setcharset(MYSQL *mysql, const char *charset);
private:	
	bool	m_bConnected;
	MYSQL_ROW	m_CurRow;
	MYSQL  m_MySQL;
	MYSQL_RES *m_pMySQL_RES;
	char	m_sHost[32];
	char	m_sUserName[32];
	char	m_sPassword[32];
	char	m_sDBName[32];
	int		m_nPort;
	char	m_sLastError[512];
	unsigned int m_nClient_Flag;
	char	m_sCharSet[32];
};

#endif // !defined(AFX_DBMYSQL_H__820820C7_8A4D_45F5_951E_6333EB571CA7__INCLUDED_)
