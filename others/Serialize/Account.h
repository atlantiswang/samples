#pragma once

// CAccount ÃüÁîÄ¿±ê

class CAccount : public CObject
{
public:
	CAccount();
	CAccount(CString, CString);
	virtual ~CAccount();

	DECLARE_SERIAL(CAccount)
	virtual void Serialize(CArchive& ar);

	CString getData(){return m_name + m_age;}
private:
	CString m_name;
	CString m_age;
};


