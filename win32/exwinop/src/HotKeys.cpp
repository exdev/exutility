// ======================================================================================
// File         : HotKeys.cpp
// Author       : Wu Jie 
// Last Change  : 03/03/2009 | 23:48:59 PM | Tuesday,March
// Description  : 
// ======================================================================================

#pragma once 

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exwinop.h"
#include "HotKeys.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INT_PTR CALLBACK DlgHotKeysProc ( HWND _hwndDlg, UINT _msg, WPARAM _wParam, LPARAM _lParam )
{
    // for HANDLE_MSG
    WPARAM wParam = _wParam;
    LPARAM lParam = _lParam;

    //
    switch ( _msg )
    {
    HANDLE_MSG( _hwndDlg, WM_INITDIALOG, HotKeys_OnInitDialog );
    HANDLE_MSG( _hwndDlg, WM_COMMAND, HotKeys_OnCommand );
    }

    return (0);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL HotKeys_OnInitDialog ( HWND _hwnd, HWND _hwndFocus, LPARAM _lParam )
{
    //
    g_hHotKeysWindow = _hwnd;

    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void HotKeys_OnCommand ( HWND _hwnd, int _id, HWND _hwndCtl, UINT _codeNotify )
{
}
