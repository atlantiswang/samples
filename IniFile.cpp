// IniFile.cpp:  Implementation of the CIniFile class.
// Written by:   Adam Clauss
// Email: cabadam@houston.rr.com
// You may use this class/code as you wish in your programs.  Feel free to distribute it, and
// email suggested changes to me.
//
// Rewritten by: Shane Hill
// Date:         21/08/2001
// Email:        Shane.Hill@dsto.defence.gov.au
// Reason:       Remove dependancy on MFC. Code should compile on any
//               platform.
//
// YUHZ[2/15/2007]
// 参考SIMPLEINI的实现，做如下改进
// 1、保存时，要保证行位置的不变
// 2、针对KEY=VALUE，使用MAP，提高执行效率 
//////////////////////////////////////////////////////////////////////

// Local Includes
#define INIFILE

#include "iniFile.h"


// C++ Includes
#include <iostream>
#include <fstream>

using namespace std;

// C Includes
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#if defined(WIN32)
#define iniEOL endl
#define NEWLINE   "\r\n"
#else
#define iniEOL '\r' << endl
#define NEWLINE   "\n"
#endif
// YUHZ[2/15/2007] 尽量使用初始化列表进行构造 
CIniFile::CIniFile( string const iniPath)
: path(iniPath)
, caseInsensitive(true)
, m_nOrder(0)
, m_sTmpComment("")
{
}

bool CIniFile::ReadFile()
{
	// Normally you would use ifstream, but the SGI CC compiler has
	// a few bugs with ifstream. So ... fstream used.
	fstream f;
	string   line;
	string   keyname = ""; // YUHZ[2/15/2007] 赋初值 
	string   valuename, value;
	string::size_type pLeft, pRight;

	f.open( path.c_str(), ios::in);
	if ( f.fail())
		return false;

	while ( getline( f, line))
	{
		// To be compatible with Win32, check for existence of '\r'.
		// Win32 files have the '\r' and Unix files don't at the end of a line.
		// Note that the '\r' will be written to INI files from
		// Unix so that the created INI file can be read under Win32
		// without change.
		if ( line[line.length() - 1] == '\r')
			line = line.substr( 0, line.length() - 1);

		if ( line.length())
		{
			// Check that the user hasn't openned a binary file by checking the first
			// character of each line!
			// YUHZ[2/15/2007] 这一判断，限制使用中文的KEY。 
			if ( !isprint( line[0]))
			{
				printf( "Failing on char %d\n", line[0]);
				f.close();
				return false;
			}
			if (( pLeft = line.find_first_of(";#[=")) != string::npos)
			{
				switch ( line[pLeft])
				{
				case '[':
					if ((pRight = line.find_last_of("]")) != string::npos &&
						pRight > pLeft)
					{
						keyname = line.substr( pLeft + 1, pRight - pLeft - 1);
						AddSection(keyname);
					}
					break;

				case '=':
					valuename = line.substr( 0, pLeft);
					value = line.substr( pLeft + 1);
					if (!SetValue( keyname, valuename, value, true))
					{
						// YUHZ[2/15/2007]如没有SECTION，如果设置了多次同一个KEY，只保留最后一次的VALUE 
						cerr << "Failing on [" << keyname << "] --> " << valuename << " = " << value << endl;
						f.close();
						return false;
					}
					break;

				case ';':
				case '#':
					m_sTmpComment += line.substr( pLeft) + NEWLINE;
					break;

				default: cerr << "世界末日"  << endl; // YUHZ[2/15/2007] 不可能到此 
				}
			}
		}
		else
		{ // YUHZ[2/15/2007] 空行也保留，以保持格式上的一致 
			m_sTmpComment += NEWLINE;
		}
	}

	f.close();
	if ( m_Sections.size())
		return true;
	return false;
}

bool CIniFile::WriteFile()
{
	// Normally you would use ofstream, but the SGI CC compiler has
	// a few bugs with ofstream. So ... fstream used.
	fstream f;

	f.open( path.c_str(), ios::out);
	if ( f.fail())
		return false;

	// get all of the sections sorted in load order
	TNamesDepend oSections;
	GetAllSections(oSections);
#if defined(_MSC_VER) && _MSC_VER <= 1200
	oSections.sort();
#else
	oSections.sort(Entry::LoadOrder());
#endif
	TNamesDepend::const_iterator i = oSections.begin();
	for (; i != oSections.end(); ++i)
	{
		// YUHZ[2/15/2007] section comment
		if (i->sComment != "")
		{
			f << i->sComment;
		}
		f << "[ " << i->sName << " ]" << iniEOL;
		// YUHZ[2/15/2007] KEY=VALUE s
		TSection::const_iterator iSection = m_Sections.find(i->sName);
		// YUHZ[2/15/2007] 下面的判断应该总是成立 
		if (iSection != m_Sections.end())
		{
			const TKeyValue & oKeyVal = iSection->second;
			// YUHZ[2/15/2007] 也需要排序 
			TNamesDepend oKey;
			GetAllKeyValues(oKey, oKeyVal);
#if defined(_MSC_VER) && _MSC_VER <= 1200
			oKey.sort();
#else
			oKey.sort(Entry::LoadOrder());
#endif
			TNamesDepend::const_iterator iKey = oKey.begin();
			for (; iKey != oKey.end(); ++iKey)
			{

				TKeyValue::const_iterator iKeyval = oKeyVal.find(iKey->sName);
				// YUHZ[2/15/2007] 其实，下面的判断应该总是成立 
				if(iKeyval != oKeyVal.end())
				{
					// YUHZ[2/15/2007] Key comment
					if (iKeyval->first.sComment != "")
					{
						f << iKeyval->first.sComment;
					}
					f <<  iKeyval->first.sName << " = " << iKeyval->second << iniEOL;
				}
			}
		}
	}
	f.close();

	return true;
}

// YUHZ[2/15/2007] 增加一个SECTION，如果指定的SECTION已经存在，则不做任何动作。返回目前有多少个SECTION 
unsigned CIniFile::AddSection( string const keyname)
{
	// check for existence of the section first 
	TSection::iterator iSection = m_Sections.find(keyname);
	// create the section entry
	if (iSection == m_Sections.end())
	{
		Entry oKey(keyname, ++m_nOrder);
		if (m_sTmpComment != "")
		{
			oKey.sComment = m_sTmpComment;
			m_sTmpComment = "";
		}
		TSection::value_type oEntry(oKey, TKeyValue());
		typedef TSection::iterator SectionIterator;
		std::pair<SectionIterator,bool> i =	m_Sections.insert(oEntry);
		// YUHZ[2/15/2007] 可以根据i判断插入是否成功，但为什么会不成功呢？ 
	}
	return m_Sections.size() - 1;
}

// YUHZ[2/15/2007] 返回指定的SECTION中有多少个KEY=VALUE对 
unsigned CIniFile::NumKeyValues( string const keyname)
{
	TSection::const_iterator iSection = m_Sections.find(keyname);
	if (iSection != m_Sections.end()) return (iSection->second).size();
	return 0;
}

// YUHZ[2/15/2007] 根据参数，可以增加
bool CIniFile::SetValue( string const keyname, string const valuename, string const value, bool const create)
{
	// check for existence of the section first 
	// YUHZ[2/15/2007] 此处有一个隐含的Entry的构造 
	TSection::iterator iSection = m_Sections.find(keyname);
	// if not found return false
	if (iSection == m_Sections.end()) return false;
	// check for existence of the key
	TKeyValue & keyval = iSection->second;
	TKeyValue::iterator iKey = keyval.find(valuename);
	// if found return false
	if (iKey == keyval.end()) 
	{
		if (!create)
		{
			return false;
		}
		// create the key entry
		Entry oKey(valuename, ++m_nOrder);
		if (m_sTmpComment != "")
		{
			oKey.sComment = m_sTmpComment;
			m_sTmpComment = "";
		}
		TKeyValue::value_type oEntry(oKey, value);
		keyval.insert(oEntry);
	}
	else
	{
		iKey->second = value;
	}

	return true;
}

bool CIniFile::SetValueI( string const keyname, string const valuename, int const value, bool const create)
{
	char svalue[MAX_VALUEDATA];

	sprintf( svalue, "%d", value);
	return SetValue( keyname, valuename, svalue, create);
}

bool CIniFile::SetValueF( string const keyname, string const valuename, double const value, bool const create)
{
	char svalue[MAX_VALUEDATA];

	sprintf( svalue, "%f", value);
	return SetValue( keyname, valuename, svalue, create);
}

// YUHZ[2/15/2007] 如果找不到，就返回缺省值 
string CIniFile::GetValue( string const keyname, string const valuename, string const defValue) const
{
	// check for existence of the section first 
	// YUHZ[2/15/2007] 不知为何find()总返回const_iterator？同样的代码在SetValue()中就可以？
	// YUHZ[2/16/2007] 看看函数定义最后，就知道上面的问题出在何处了，；) 
	TSection::const_iterator iSection = m_Sections.find(keyname);
	// if not found return false
	if (iSection == m_Sections.end()) return defValue;
	// check for existence of the key
	const TKeyValue & keyval = iSection->second;
	TKeyValue::const_iterator iKey = keyval.find(valuename);
	// if found return false
	if (iKey == keyval.end()) return defValue;

	return iKey->second;
}

int CIniFile::GetValueI(string const keyname, string const valuename, int const defValue) const
{
	char svalue[MAX_VALUEDATA];

	sprintf( svalue, "%d", defValue);
	return atoi( GetValue( keyname, valuename, svalue).c_str()); 
}

double CIniFile::GetValueF(string const keyname, string const valuename, double const defValue) const
{
	char svalue[MAX_VALUEDATA];

	sprintf( svalue, "%f", defValue);
	return atof( GetValue( keyname, valuename, svalue).c_str()); 
}

// YUHZ[2/15/2007] 删除一个KEY=VALUE对 
bool CIniFile::DeleteValue( string const keyname, string const valuename)
{
	TSection::iterator iSection = m_Sections.find(keyname);
	// if not found return false
	if (iSection == m_Sections.end()) return false;
	TKeyValue & keyval = iSection->second;
	TKeyValue::iterator iKey = keyval.find(valuename);
	// if found return false
	if (iKey == keyval.end()) return false;
	keyval.erase(iKey);

	return true;
}

// YUHZ[2/15/2007] 删除整个SECTION 
bool CIniFile::DeleteSection( string const keyname)
{
	TSection::iterator iSection = m_Sections.find(keyname);
	// if not found return false
	if (iSection == m_Sections.end()) return false;
	m_Sections.erase(iSection);

	return true;
}

void CIniFile::Erase()
{
	m_Sections.clear();
}

string CIniFile::CheckCase( string s) const
{
	if ( caseInsensitive)
		for ( string::size_type i = 0; i < s.length(); ++i)
			s[i] = tolower(s[i]);
	return s;
}

void CIniFile::GetAllSections(TNamesDepend & a_names) const
{
	TSection::const_iterator i = m_Sections.begin();
	for (; i != m_Sections.end(); ++i)
	{
		a_names.push_back(i->first);
	}
}

void CIniFile::GetAllKeyValues(TNamesDepend & a_names, const TKeyValue & a_keyval) const
{
	TKeyValue::const_iterator i = a_keyval.begin();
	for (; i != a_keyval.end(); ++i)
	{
		a_names.push_back(i->first);
	}
}

// Add a section comment.
bool     CIniFile::SetSectionComment( string const keyname, string const comment)
{
	TSection::iterator iSection = m_Sections.find(keyname);
	// if not found return false
	if (iSection == m_Sections.end()) return false;
	//	iSection->first.sComment = comment;
	// YUHZ[2/16/2007] 上面的做法是异想天开，因为MAP是不允许修改KEY的(const)，只能修改VALUE。所以，要另想办法
	Entry oKey(iSection->first);
	oKey.sComment = comment + NEWLINE;
	TSection::value_type oEntry(oKey, iSection->second);
	// YUHZ[2/16/2007] 此处注意，要先删除，否则会插入失败! 
	m_Sections.erase(iSection);
	typedef TSection::iterator SectionIterator;
	std::pair<SectionIterator,bool> i =	m_Sections.insert(oEntry);
	if (!(i.second))
	{
		cerr << "insert error" << endl;
	}
	return true;
}

// Return a section comment.
string   CIniFile::GetSectionComment( string const keyname) const
{
	TSection::const_iterator iSection = m_Sections.find(keyname);
	// if not found return false
	if (iSection == m_Sections.end()) return "";
	return iSection->first.sComment;
}

// Delete a section comment.
bool     CIniFile::DeleteSectionComment( string const keyname)
{
	return SetSectionComment(keyname, "");
}