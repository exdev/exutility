// ======================================================================================
// File         : Monitor.cpp
// Author       : Wu Jie 
// Last Change  : 02/19/2009 | 23:27:50 PM | Thursday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exwinop.h"
#include "Monitor.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL CreateMonitorList ()
{
    //
    g_MonitorHandles.clear ();
    EnumDisplayMonitors ( NULL, NULL, MonitorEnumProc, 0 );

    // check if user have more than one monitor
    if ( g_MonitorHandles.size () < 2 )
    {
        MessageBox( g_hMainWindow, TEXT("you don't have double screen"), TEXT("ERROR"), MB_OK | MB_ICONERROR );
        return FALSE;
    }

    // TODO: use Graph data-struct in boost
    for ( monitor_handles_t::iterator iter = g_MonitorHandles.begin(); iter != g_MonitorHandles.end(); ++iter ) 
    {
        //
        MONITORINFO monitorInfo; 
        monitorInfo.cbSize = sizeof (MONITORINFO);

        // get monitor info
        if ( GetMonitorInfo ( (*iter), &monitorInfo ) )
        {
            // create SMonitorDesc 
            SMonitorDesc monitorDesc;
            ZeroMemory ( &monitorDesc, sizeof(SMonitorDesc) );
            monitorDesc.hMonitor = (*iter);

            // loop to compare other monitor
            for ( monitor_handles_t::iterator iterComp = g_MonitorHandles.begin(); iterComp != g_MonitorHandles.end(); ++iterComp ) 
            {
                // skip self
                if ( iter == iterComp )
                    continue;

                // get monitor info
                MONITORINFO monitorInfoComp; 
                monitorInfoComp.cbSize = sizeof (MONITORINFO);
                if ( GetMonitorInfo ( (*iterComp), &monitorInfoComp ) )
                {
                    // check left
                    if ( monitorInfo.rcMonitor.left == monitorInfoComp.rcMonitor.right )
                    {
                        monitorDesc.hLeft = (*iterComp); 
                        continue;
                    }

                    // check right
                    if ( monitorInfo.rcMonitor.right == monitorInfoComp.rcMonitor.left )
                    {
                        monitorDesc.hRight = (*iterComp); 
                        continue;
                    }

                    // check top
                    if ( monitorInfo.rcMonitor.top == monitorInfoComp.rcMonitor.bottom )
                    {
                        monitorDesc.hUp = (*iterComp); 
                        continue;
                    }

                    // check bottom
                    if ( monitorInfo.rcMonitor.bottom  == monitorInfoComp.rcMonitor.top )
                    {
                        monitorDesc.hDown = (*iterComp); 
                        continue;
                    }
                }
            }

            //
            g_MonitorDescs.push_back ( monitorDesc );
        }
    }

    //
    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL CALLBACK MonitorEnumProc ( HMONITOR _hMonitor, HDC _hdcMonitor, LPRECT _lprcMonitor, LPARAM _dwData )
{
    g_MonitorHandles.push_back ( _hMonitor );
    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL MoveWindowAcrossMonitor ( HWND _hwnd, EMoveTo _eMoveTo )
{
    // monitor operations
    HMONITOR hMonitor = MonitorFromWindow ( _hwnd, MONITOR_DEFAULTTONEAREST );
    HMONITOR hMonitorTo = NULL;

    //
    monitor_descs_t::iterator iter = g_MonitorDescs.end();
    for ( iter = g_MonitorDescs.begin(); iter != g_MonitorDescs.end(); ++iter )
    {
        // found the monitor we want
        if ( hMonitor == (*iter).hMonitor ) 
        {
            break;
        }
    }

    //
    if ( iter != g_MonitorDescs.end() )
    {
        // get dest monitor handle
        switch ( _eMoveTo )
        {
        case eMoveTo_Left:
            hMonitorTo = (*iter).hLeft; 
            break;

        case eMoveTo_Right:
            hMonitorTo = (*iter).hRight; 
            break;

        case eMoveTo_Up:
            hMonitorTo = (*iter).hUp; 
            break;

        case eMoveTo_Down:
            hMonitorTo = (*iter).hDown; 
            break;

        default:
            hMonitorTo = NULL;
            break;
        }

        //
        if ( hMonitorTo ) 
        {
            return MoveWindowToMonitor ( _hwnd, hMonitor, hMonitorTo, _eMoveTo );
        }
    }

    return TRUE;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL MoveWindowToMonitor ( HWND _hwnd, HMONITOR _hMonitorFrom, HMONITOR _hMonitorTo, EMoveTo _eMoveTo )
{
    // window operations
    WINDOWPLACEMENT wndPlacement;
    BOOL ret = GetWindowPlacement ( _hwnd, &wndPlacement );
    UINT wndWidth = wndPlacement.rcNormalPosition.right - wndPlacement.rcNormalPosition.left; 
    UINT wndHeight = wndPlacement.rcNormalPosition.bottom - wndPlacement.rcNormalPosition.top; 

    // get "from" monitor info 
    MONITORINFO monitorInfoFrom; 
    monitorInfoFrom.cbSize = sizeof (MONITORINFO);
    ret = GetMonitorInfo ( _hMonitorFrom, &monitorInfoFrom );

    // get "to" monitor info 
    MONITORINFO monitorInfoTo; 
    monitorInfoTo.cbSize = sizeof (MONITORINFO);
    ret = GetMonitorInfo ( _hMonitorTo, &monitorInfoTo );

    // if we confirm dest monitor handle
    UINT showCmd = SW_SHOW;
    BOOL bCross = false;
    BOOL bFitMonitor = true;
    BOOL bOutOfMonitor = false;
    RECT rect = { 0, 0, 10, 10 };

    //
    if ( wndPlacement.showCmd == SW_SHOWMAXIMIZED )
    {
        wndPlacement.showCmd = SW_RESTORE; 
        SetWindowPlacement ( _hwnd, &wndPlacement );
        showCmd = SW_MAXIMIZE;
    }

    // check if cross two monitor.
    switch ( _eMoveTo )
    {
    case eMoveTo_Left: 
        if ( wndPlacement.rcNormalPosition.left < monitorInfoFrom.rcWork.left ) 
            bCross = true; 
        break;
    case eMoveTo_Right: 
        if ( wndPlacement.rcNormalPosition.right > monitorInfoFrom.rcWork.right ) 
            bCross = true; 
        break;
    case eMoveTo_Up: 
        if ( wndPlacement.rcNormalPosition.top < monitorInfoFrom.rcWork.top ) 
            bCross = true; 
        break;
    case eMoveTo_Down: 
        if ( wndPlacement.rcNormalPosition.bottom > monitorInfoFrom.rcWork.bottom ) 
            bCross = true; 
        break;
    default: 
        break;
    }

    // check if fit the "to" monitor
    if ( wndWidth  > UINT(monitorInfoTo.rcWork.right - monitorInfoTo.rcWork.left) ||
         wndHeight > UINT(monitorInfoTo.rcWork.bottom - monitorInfoTo.rcWork.top) )
    {
        bFitMonitor = false;
    }

    // when fit the new monitor, we still don't know the window is in the monitor or out of the monitor 
    // so check if out of the "to" monitor
    if ( bFitMonitor ) // TODO: if ( bCross )
    {
        int toLeft = abs( monitorInfoFrom.rcWork.left - wndPlacement.rcNormalPosition.left );
        int toRight = abs( monitorInfoFrom.rcWork.right - wndPlacement.rcNormalPosition.right );
        int toTop = abs( monitorInfoFrom.rcWork.top - wndPlacement.rcNormalPosition.top );
        int toBottom = abs( monitorInfoFrom.rcWork.bottom - wndPlacement.rcNormalPosition.bottom );

        // horizontal 
        if ( toLeft <= toRight ) // if near left
        {
            rect.left = monitorInfoTo.rcWork.left + toLeft;
            rect.right = rect.left + wndWidth;
        }
        else // if near right
        {
            rect.right = monitorInfoTo.rcWork.right - toRight;
            rect.left = rect.right - wndWidth;
        }

        // vertical
        if ( toTop <= toBottom ) // if near top
        {
            rect.top = monitorInfoTo.rcWork.top + toTop;
            rect.bottom = rect.top + wndHeight;
        }
        else // if near bottom
        {
            rect.bottom = monitorInfoTo.rcWork.bottom - toBottom;
            rect.top = rect.bottom - wndHeight;
        }
    }
    else
    {
        //
        int monitorFromWidth = monitorInfoFrom.rcWork.right - monitorInfoFrom.rcWork.left;
        int monitorFromHeight = monitorInfoFrom.rcWork.bottom - monitorInfoFrom.rcWork.top;

        //
        int monitorToWidth = monitorInfoTo.rcWork.right - monitorInfoTo.rcWork.left;
        int monitorToHeight = monitorInfoTo.rcWork.bottom - monitorInfoTo.rcWork.top;

        // get new width & height 
        int newWidth = int((wndWidth * monitorToWidth) / monitorFromWidth);  
        int newHeight = int((wndHeight * monitorToHeight) / monitorFromHeight);  

        //
        int toTop = abs( monitorInfoFrom.rcWork.top - wndPlacement.rcNormalPosition.top );
        int toLeft = abs( monitorInfoFrom.rcWork.left - wndPlacement.rcNormalPosition.left );

        // get new toLeft & toTop
        int newToTop = int((toTop * monitorToHeight) / monitorFromHeight);  
        int newToLeft = int((toLeft * monitorToWidth) / monitorFromWidth);  

        // 
        rect.top = monitorInfoTo.rcWork.top + newToTop;
        rect.left = monitorInfoTo.rcWork.left + newToLeft;
        rect.bottom = rect.top + newHeight;
        rect.right = rect.left + newWidth;
    }

    // process moving
    wndPlacement.showCmd = showCmd; 
    wndPlacement.rcNormalPosition = rect;
    SetWindowPlacement ( _hwnd, &wndPlacement );

    //
    return TRUE;
}
