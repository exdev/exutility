// ======================================================================================
// File         : About.cpp
// Author       : Wu Jie 
// Last Change  : 03/03/2009 | 23:48:59 PM | Tuesday,March
// Description  : 
// ======================================================================================

#pragma once 

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exwinop.h"
#include "About.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INT_PTR CALLBACK DlgAboutProc ( HWND _hwndDlg, UINT _msg, WPARAM _wParam, LPARAM _lParam )
{
    // for HANDLE_MSG
    WPARAM wParam = _wParam;
    LPARAM lParam = _lParam;

    //
    switch ( _msg )
    {
    HANDLE_MSG( _hwndDlg, WM_INITDIALOG, About_OnInitDialog );
    HANDLE_MSG( _hwndDlg, WM_COMMAND, About_OnCommand );
    }

    return (0);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL About_OnInitDialog ( HWND _hwnd, HWND _hwndFocus, LPARAM _lParam )
{
    //
    g_hAboutWindow = _hwnd;

    //
    // WCHAR buffer[1024];			

    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void About_OnCommand ( HWND _hwnd, int _id, HWND _hwndCtl, UINT _codeNotify )
{
}
