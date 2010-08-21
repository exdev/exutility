// ======================================================================================
// File         : exWindow.cpp
// Author       : Wu Jie 
// Last Change  : 02/25/2009 | 22:07:06 PM | Wednesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exwinop.h"

///////////////////////////////////////////////////////////////////////////////
// define global variables 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const TCHAR g_ClassName[] = TEXT("exWindowClass");
const TCHAR g_WindowName[] = TEXT("exWindow");
HWND g_hMainWindow = NULL;
HWND g_hOptionsWindow = NULL;
HWND g_hAboutWindow = NULL;
HWND g_hHotKeysWindow = NULL;
HINSTANCE g_hInstance = NULL;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

monitor_handles_t g_MonitorHandles;
monitor_descs_t g_MonitorDescs;
dialog_handles_t g_DialogHandles;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL InitApp ( HINSTANCE _hInstance )
{
    //
    BOOL bSuccess = CreateMonitorList (); 
    if ( !bSuccess )
        return FALSE;

    //
    UnregisterHotKey( g_hMainWindow, IDH_LEFT );
    UnregisterHotKey( g_hMainWindow, IDH_RIGHT );
    UnregisterHotKey( g_hMainWindow, IDH_UP );
    UnregisterHotKey( g_hMainWindow, IDH_DOWN );

    //
    RegisterHotKey( g_hMainWindow, IDH_LEFT, MOD_CONTROL | MOD_SHIFT, VK_LEFT );
    RegisterHotKey( g_hMainWindow, IDH_RIGHT, MOD_CONTROL | MOD_SHIFT, VK_RIGHT );
    RegisterHotKey( g_hMainWindow, IDH_UP, MOD_CONTROL | MOD_SHIFT, VK_UP );
    RegisterHotKey( g_hMainWindow, IDH_DOWN, MOD_CONTROL | MOD_SHIFT, VK_DOWN );

    HICON hIcon = (HICON)LoadImage(_hInstance, MAKEINTRESOURCE(IDI_TRAY), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    AddTrayIcon( g_hMainWindow, IDI_TRAY, hIcon, g_WindowName );

    //
    return TRUE;
}
