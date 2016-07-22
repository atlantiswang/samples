#include "StdAfx.h"
#include "ctray.h"
#include "resource.h"

CTray::CTray(void)
{ 
	m_tray.cbSize = sizeof(NOTIFYICONDATA);
	m_tray.uID	  = IDR_MAINFRAME;
	m_tray.hIcon  = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_tray.szTip, 64, L"tray_mfc");
	m_tray.uCallbackMessage = WM_USER_NOTIFYICON;
	m_tray.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
}

CTray::~CTray(void)
{
	Shell_NotifyIcon(NIM_DELETE, &m_tray);
}

void CTray::modifytray(WCHAR *ptitle, WCHAR *pinfo)
{
	m_tray.uFlags |= NIF_INFO;
	wcscpy_s(m_tray.szInfoTitle, 64, ptitle);
	wcscpy_s(m_tray.szInfo, 256, pinfo);
	m_tray.dwInfoFlags = NIIF_ERROR;
	Shell_NotifyIcon(NIM_MODIFY, &m_tray);
}

void CTray::init()
{
	m_tray.hWnd = AfxGetMainWnd()->GetSafeHwnd();
	addtray();
}

bool CTray::addtray()
{
	return Shell_NotifyIcon(NIM_ADD, &m_tray);
}
