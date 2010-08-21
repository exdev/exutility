// ======================================================================================
// File         : Tray.cpp
// Author       : Wu Jie 
// Last Change  : 02/25/2009 | 22:10:26 PM | Wednesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exwinop.h"
#include "Tray.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL AddTrayIcon ( HWND _hwnd, UINT _uID, HICON _hIcon, LPCTSTR _szTip ) 
{

	NOTIFYICONDATA nid; 
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.hWnd = _hwnd;
	nid.uID = _uID;
	nid.uCallbackMessage = EXWIN_TRAYMSG;
	nid.hIcon = _hIcon;
	lstrcpyn ( nid.szTip, _szTip, sizeof(nid.szTip)/sizeof(nid.szTip[0]) );

	return (Shell_NotifyIcon ( NIM_ADD, &nid) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL DeleteTrayIcon ( HWND _hwnd, UINT _uID ) 
{
	NOTIFYICONDATA nid; 
	nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = _hwnd;
    nid.uID = _uID;
	return ( Shell_NotifyIcon( NIM_DELETE, &nid ) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL ShowTrayMenu ( HWND _hwnd )
{
    BOOL ret = TRUE;

    //
    HMENU hmenu = CreatePopupMenu();
    AppendMenu( hmenu, MF_STRING, IDM_OPTIONS, TEXT("Options") );
    InsertMenu( hmenu, IDM_EXIT, MF_SEPARATOR | MF_BYCOMMAND, 0, NULL );
    AppendMenu( hmenu, MF_STRING, IDM_EXIT, TEXT("Exit") );

    //
    SetForegroundWindow( _hwnd );

    //
    POINT pt;
    GetCursorPos(&pt);
    UINT menuID = TrackPopupMenu( hmenu, 
                                  TPM_RIGHTALIGN | TPM_RIGHTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD,
                                  pt.x, pt.y, 0, _hwnd, NULL );
    PostMessage( _hwnd, WM_NULL, 0, 0 );
    DestroyMenu( hmenu );

    //
    ret = ProcessTrayMenu (  _hwnd, menuID );

    //
    return ret;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL ProcessTrayMenu ( HWND _hwnd, UINT _menuID )
{
    switch ( _menuID )
    {
    case IDM_EXIT:
        DestroyWindow (g_hMainWindow);
        break;

    case IDM_OPTIONS:
        ShowOptionsDialog (g_hMainWindow);
        break;

    default:
        return TRUE;
    }

    return TRUE;
}
