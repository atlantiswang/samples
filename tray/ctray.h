#pragma once
#define WM_USER_NOTIFYICON WM_USER +1


class Ctray
{
public:
	Ctray(void);
	~Ctray(void);

	void modifytray(WCHAR *ptitle, WCHAR *pinfo);

	void init();
	bool addtray();
	

protected:

private:
	NOTIFYICONDATA m_tray;;
};
