// ======================================================================================
// File         : Options.cpp
// Author       : Wu Jie 
// Last Change  : 03/01/2009 | 11:57:52 AM | Sunday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exwinop.h"
#include "Options.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL ShowOptionsDialog ( HWND _hwnd )
{
	DialogBox( g_hInstance, MAKEINTRESOURCE(IDD_OPTIONS), NULL, DlgOptionsProc );

    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

INT_PTR CALLBACK DlgOptionsProc ( HWND _hwndDlg, UINT _msg, WPARAM _wParam, LPARAM _lParam )
{
    // for HANDLE_MSG
    WPARAM wParam = _wParam;
    LPARAM lParam = _lParam;

    //
    switch ( _msg )
    {
    HANDLE_MSG( _hwndDlg, WM_INITDIALOG, Options_OnInitDialog );
    HANDLE_MSG( _hwndDlg, WM_COMMAND, Options_OnCommand );

    case WM_CLOSE:
        EndDialog ( _hwndDlg, FALSE );
        break;

    case WM_DESTROY:
        DestroyWindow (_hwndDlg);
        break;

    case WM_HOTKEY: 
        {
            switch (_wParam) 
            {
            case IDH_ESCAPE:
                PostMessage( _hwndDlg, WM_COMMAND, IDC_CANCEL, 0 );
				break;
            }
        }
		break;

    case WM_NOTIFY:
        {
            LPNMHDR pnmhdr = (LPNMHDR)lParam;
			if ( pnmhdr->idFrom == IDC_TAB ) 
            {
				switch ( pnmhdr->code )
                {
                case TCN_SELCHANGE:
                    HWND hTabWnd = GetDlgItem ( g_hOptionsWindow, IDC_TAB );
                    UINT i = TabCtrl_GetCurSel ( hTabWnd );
                    ShowSelectItem ( hTabWnd, i );
                    break;
				}
            }
        }
        break;
    }

    return (0);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL Options_OnInitDialog ( HWND _hwnd, HWND _hwndFocus, LPARAM _lParam )
{
    //
    g_hOptionsWindow = _hwnd;
    RegisterHotKey( g_hOptionsWindow, IDH_ESCAPE, NULL, VK_ESCAPE );

    // ======================================================== 
    // adjust options window to the center of the monitor taskbar in 
    // ======================================================== 

    //
    WINDOWPLACEMENT wndPlacement;
    GetWindowPlacement ( g_hOptionsWindow, &wndPlacement );
    RECT rect = wndPlacement.rcNormalPosition;

    // set dialog window at center of the monitor as taskbar window in
    HWND hTaskbarWnd = FindWindow( TEXT("Shell_TrayWnd"), TEXT("") );
    if ( !hTaskbarWnd )
        hTaskbarWnd = g_hMainWindow;

    HMONITOR hMonitor = MonitorFromWindow ( hTaskbarWnd, MONITOR_DEFAULTTONEAREST );
    MONITORINFO monitorInfo; 
    monitorInfo.cbSize = sizeof (MONITORINFO);
    GetMonitorInfo ( hMonitor, &monitorInfo );

    //
    int mcenter_x = monitorInfo.rcWork.left + (monitorInfo.rcWork.right - monitorInfo.rcWork.left)/2; 
    int mcenter_y = monitorInfo.rcWork.top + (monitorInfo.rcWork.bottom - monitorInfo.rcWork.top)/2; 

    //
    int wndWidth = wndPlacement.rcNormalPosition.right - wndPlacement.rcNormalPosition.left;
    int wndHeight = wndPlacement.rcNormalPosition.bottom - wndPlacement.rcNormalPosition.top;
    rect.left = mcenter_x - wndWidth/2;
    rect.top = mcenter_y - wndHeight/2;
    rect.right = rect.left + wndWidth;
    rect.bottom = rect.top + wndHeight;

    //
    wndPlacement.rcNormalPosition = rect;
    SetWindowPlacement ( g_hOptionsWindow, &wndPlacement );

    // ======================================================== 
    // create tab-ctrl
    // ======================================================== 

    // get tab-ctrl window handle
    HWND hTabWnd = GetDlgItem ( g_hOptionsWindow, IDC_TAB );
    if ( !hTabWnd )
        return FALSE;

    //
    AddDialogTab ( hTabWnd, TEXT("HotKeys"), IDD_HOTKEYS, DlgHotKeysProc );
    AddDialogTab ( hTabWnd, TEXT("About"), IDD_ABOUT, DlgAboutProc );

    //
    ShowSelectItem ( hTabWnd, TabCtrl_GetCurSel(hTabWnd) );

    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void Options_OnCommand ( HWND _hwnd, int _id, HWND _hwndCtl, UINT _codeNotify )
{
	if ( _codeNotify == BN_CLICKED ) 
    {
        switch (_id) 
        {
        case IDC_APPLY: 
            // TODO { 
            // if (!SaveSettings(TRUE))
            //     ReportError(_hwnd, IDS_ERR_SAVESETTINGS);
            // EnableWindow(GetDlgItem(_hwnd, IDC_APPLY), FALSE);
            // //LoadSettings();				
            // HWND _hwndTs = FindWindowEx(NULL/*HWND_MESSAGE*/, NULL, g_szMainWnd, g_szWindowName);
            // if (IsWindow(_hwndTs))
            //     SendMessage(_hwndTs, WM_RELOADSETTINGS, 0, 0);
            // } TODO end 
            break;

        case IDC_OK: 
            // TODO { 
            // if (!SaveSettings())
            //     ReportError(_hwnd, IDS_ERR_SAVESETTINGS);
            // HWND _hwndTs = FindWindowEx(NULL/*HWND_MESSAGE*/, NULL, g_szMainWnd, g_szWindowName);
            // if (IsWindow(_hwndTs))
            //     SendMessage(_hwndTs, WM_RELOADSETTINGS, 0, 0);
            // } TODO end 
            EndDialog ( _hwnd, TRUE );
            break;

        case IDC_CANCEL:
            EndDialog ( _hwnd, FALSE );
            break;
		}
	}
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL AddDialogTab ( HWND _hTabWnd, LPTSTR _tabText, UINT _dialogID, DLGPROC _dlgProc ) 
{
    //
    TCITEM tcItem;
    ZeroMemory ( &tcItem, sizeof(TCITEM) );
    tcItem.mask = TCIF_TEXT;
    tcItem.pszText = _tabText;
    TabCtrl_InsertItem ( _hTabWnd, g_DialogHandles.size(), &tcItem );

    //
    HWND hDialog = CreateDialog ( g_hInstance, MAKEINTRESOURCE(_dialogID), _hTabWnd, _dlgProc );
    g_DialogHandles.push_back ( hDialog );

    //
    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ShowSelectItem ( HWND _hTabWnd, UINT _selIdx )
{
    // NOTE: should adjust after all item been added
    // get tab display rect
    RECT rcTab;
    GetClientRect( _hTabWnd, &rcTab );
	TabCtrl_AdjustRect( _hTabWnd, FALSE, &rcTab );

    //
    for ( UINT i = 0; i < g_DialogHandles.size(); ++i )
    {
        if ( i == _selIdx )
        {
            SetWindowPos ( g_DialogHandles[i], NULL, rcTab.left, rcTab.top, rcTab.right-rcTab.left, rcTab.bottom-rcTab.top, SWP_NOZORDER|SWP_SHOWWINDOW );
        }
        else 
        {
            ShowWindow ( g_DialogHandles[i], SW_HIDE );
        }
    }
}
