
#ifndef ZL_UTIL_H_
#define  ZL_UTIL_H_

#include <string>
using namespace std;

extern std::string UrlEncode(const std::string& szToEncode);
extern std::string UrlDecode(const std::string& szToDecode);
extern std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
extern std::wstring s2ws(const string& s);


#endif //ZL_UTIL_H_

