// IniFile.cpp:  Implementation of the CIniFile class.
// Written by:   Adam Clauss
// Email: cabadam@tamu.edu
// You may use this class/code as you wish in your programs.  Feel free to distribute it, and
// email suggested changes to me.
//
// Rewritten by: Shane Hill
// Date:         21/08/2001
// Email:        Shane.Hill@dsto.defence.gov.au
// Reason:       Remove dependancy on MFC. Code should compile on any
//               platform. Tested on Windows/Linux/Irix
//
// YUHZ[2/15/2007]
// 参考SIMPLEINI的实现，做如下改进
// 1、保存时，要保证行位置的不变
// 2、针对KEY=VALUE，使用MAP，提高执行效率 
// YUHZ[2/16/2007] 
// 增加了对COMMENT的处理，遇到了一点小麻烦，绕开了。 
//////////////////////////////////////////////////////////////////////
 
#ifndef CIniFile_H
#define CIniFile_H
#ifdef _MSC_VER
	#pragma warning (disable: 4127 4503 4702 4786)
#endif
 
 
// C++ Includes
#include <string>
#include <map>
#include <list>
#include <functional>
 
using namespace std;
 
// C Includes
#include <stdlib.h>
 

#ifdef INIFILE
#define APP _declspec(dllexport)
#else
#define APP _declspec(dllimport)
#endif

// VALUE最大长度，按EFFICTIVE C++的建议，改为CONST定义
const int MAX_VALUEDATA = 2048;
 
class APP CIniFile  
{
public:
	/** key entry */
	struct Entry
	{
		string sName;
		string sComment;
		int    nOrder;
 
		Entry(string a_pszItem = "", int a_nOrder = 0)
			: sName(a_pszItem)
			, sComment("")
			, nOrder(a_nOrder)
		{}
		// YUHZ[2/15/2007] 拷贝构造与赋值需要定义
		Entry(const Entry & rhs) 
		{ 
			operator = (rhs);
		}
		Entry & operator = (const Entry & rhs) 
		{
			sName    = rhs.sName;
			sComment = rhs.sComment;
			nOrder   = rhs.nOrder;
			return *this;
		}
 
	#if defined(_MSC_VER) && _MSC_VER <= 1200
		/** STL of VC6 doesn't allow me to specify my own comparator for list::sort() */
		bool operator<(const Entry & rhs) const { return LoadOrder()(*this, rhs);}
		bool operator>(const Entry & rhs) const { return LoadOrder()(rhs, *this);}
	#endif
 
		/** Strict less ordering by name of key only */
		struct KeyOrder : std::binary_function<Entry, Entry, bool>
		{
			bool operator()(const Entry & lhs, const Entry & rhs) const {
				return (lhs.sName < rhs.sName);
			}
		};
 
		/** Strict less ordering by order, and then name of key */
		struct LoadOrder : std::binary_function<Entry, Entry, bool>
		{
			bool operator()(const Entry & lhs, const Entry & rhs) const {
				if (lhs.nOrder != rhs.nOrder)
				{
					return lhs.nOrder < rhs.nOrder;
				}
				return KeyOrder()(lhs.sName, rhs.sName);
			}
		};
	};
 
	/** map keys to value */
	typedef std::map<Entry, string, Entry::KeyOrder> TKeyValue;
 
	/** map sections to key/value map */
	typedef std::map<Entry, TKeyValue, Entry::KeyOrder> TSection;
 
	/** 
	保存时，为保持加载顺序，需要以下类型定义
	*/
	typedef std::list<Entry> TNamesDepend;
 
	CIniFile( string const iniPath = "");
	virtual ~CIniFile()                            {}
 
	// Sets whether or not keynames and valuenames should be case sensitive.
	// The default is case insensitive.
	void CaseSensitive()                           {caseInsensitive = false;}
	void CaseInsensitive()                         {caseInsensitive = true;}
 
	// Sets path of ini file to read and write from.
	void SetPath(string const newPath)                {path = newPath;}
	string GetPath() const                            {return path;}
 
	// Reads ini file specified using path.
	// Returns true if successful, false otherwise.
	bool ReadFile();
 
	// Writes data stored in class to ini file.
	bool WriteFile(); 
 
	// Deletes all stored ini data.
	void Erase();
	void Clear()                                   {Erase();}
	void Reset()                                   {Erase();}
 
 
	// Add a Section by name.
	unsigned AddSection( string const keyname);
 
	// Returns number of values stored for specified key.
	unsigned NumKeyValues( string const keyname);
	unsigned GetNumKeyValues( string const keyname)   {return NumKeyValues( keyname);}
 
 
	// Gets value of [keyname] valuename =.
	// Overloaded to return string, int, and double.
	// Returns defValue if key/value not found.
	string GetValue(string const keyname, string const valuename, string const defValue = "") const; 
	int    GetValueI(string const keyname, string const valuename, int const defValue = 0) const;
	double   GetValueF(string const keyname, string const valuename, double const defValue = 0.0) const;
 
	// Sets value of [keyname] valuename =.
	// Specify the optional paramter as false (0) if you do not want it to create
	// the key if it doesn't exist. Returns true if data entered, false otherwise.
	// Overloaded to accept string, int, and double.
	bool SetValue( string const keyname, string const valuename, string const value, bool const create = true);
	bool SetValueI( string const keyname, string const valuename, int const value, bool const create = true);
	bool SetValueF( string const keyname, string const valuename, double const value, bool const create = true);
 
	// Deletes specified "key = value".
	// Returns true if value existed and deleted, false otherwise.
	bool DeleteValue( string const keyname, string const valuename);
 
	// Deletes specified section and all values contained within.
	// Returns true if key existed and deleted, false otherwise.
	bool DeleteSection(string keyname);
 
	// Add a section comment.
	bool     SetSectionComment( string const keyname, string const comment);
	// Return a section comment.
	string   GetSectionComment( string const keyname) const;
	// Delete a section comment.
	bool     DeleteSectionComment( string const keyname);
 
private:
	bool   caseInsensitive;
	string path;
	/** Parsed INI data. Section -> (Key -> Value). */
	TSection m_Sections;
	/** Next order value, used to ensure sections and keys are output in the
		same order that they are loaded/added.
	 */
	int m_nOrder;
	// YUHZ[2/15/2007] 临时收集注释
	string m_sTmpComment;
 
	string CheckCase( string s) const;
	// YUHZ[2/15/2007] 以下两个过程，只在写文件过程中，为排序做准备时使用。 
	void GetAllSections(TNamesDepend & a_names) const;
	void GetAllKeyValues(TNamesDepend & a_names, const TKeyValue & a_keyval) const;
};
//////////////////////////////////////////////////////////////////////////
// 该实现用标准C＋＋，可以跨平台，功能强大，基本可用。
// yuhz: [10/24/2003] TODO:
// 1　保存时，要保证行位置的不变，主要是因为现在的实现中，注释和设置
// 是分开存放的。保存时，只能将注释集中到前面。可以设置一个记录行的VECTOR，行分为3类
// 空行、注释、SECTION。 行的VECTOR中可保存行的类型ID和一个对象指针。对SECTION同样有三类
// 空行、注释、设置（KEY＝VALUE）。可以用相似的方法解决。设置用MAP表示更合理。
// 2　 对VECTOR的增加用的是RESIZE（），不知是不是用PUSH＿BACK（）更有效？
// 设置（KEY＝VALUE）用MAP表示更合理?
// 3　 读写V不一定有必要，因为可以先生成STRING。不要象现在这样代码很难看。
// 另外，最好增加一个对二进制流的读写功能，DELPHI中有一个实现。  
#endif