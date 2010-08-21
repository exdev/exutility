// ======================================================================================
// File         : main.cpp
// Author       : Wu Jie 
// Last Change  : 02/15/2009 | 10:03:34 AM | Sunday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exwinop.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

LRESULT CALLBACK WndProc( HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam )
{
    switch (_msg)
    {
        //
    case WM_HOTKEY: 
        {
            // ======================================================== 
            // 
            // ======================================================== 

            EMoveTo eMoveTo = eMoveTo_None;
            switch (_wParam) 
            {
                //
            case IDH_LEFT:
                eMoveTo = eMoveTo_Left;
                break;

                //
            case IDH_RIGHT:
                eMoveTo = eMoveTo_Right;
                break;

                //
            case IDH_UP:
                eMoveTo = eMoveTo_Up;
                break;

                //
            case IDH_DOWN:
                eMoveTo = eMoveTo_Down;
                break;

                //
            default:
                eMoveTo = eMoveTo_None;
                break;
            }

            // ======================================================== 
            // 
            // ======================================================== 

            // HWND hActiveWnd = GetActiveWindow ();
            HWND hForegroundWnd = GetForegroundWindow ();
            if ( hForegroundWnd )
            {
                MoveWindowAcrossMonitor ( hForegroundWnd, eMoveTo );
            }
        }
        break;

        //
    case EXWIN_TRAYMSG:
        {
            if ( _lParam == WM_RBUTTONUP ) 
            {
                ShowTrayMenu ( _hwnd );
            }
        }
        break;

        // 
    case WM_CLOSE:
        DestroyWindow (_hwnd);
        break;

        //
    case WM_DESTROY:
        DeleteTrayIcon ( _hwnd, IDI_TRAY );
        PostQuitMessage (0);
        break;

        //
    default:
        return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
    }
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int WINAPI WinMain( HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow )
{

    // ======================================================== 
    // start up core
    // ======================================================== 

    int ret = 1;

    // ======================================================== 
    // win main 
    // ======================================================== 

    {
        //
        WNDCLASSEX wc;
        MSG msg;

        //
        g_hInstance = GetModuleHandle (NULL);
        g_hMainWindow = FindWindowEx ( NULL/*HWND_MESSAGE*/, NULL, g_ClassName, g_WindowName );
        if ( IsWindow(g_hMainWindow) ) 
        {
            MessageBox( g_hMainWindow, TEXT("exWindow already running"), TEXT("NOTE"), MB_OK | MB_ICONINFORMATION );
            ret = 0;
            goto TEAR_DOWN;
        }

        // Registering the Window Class
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = WndProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = g_hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;
        wc.lpszClassName = g_ClassName;
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        //
        if ( !RegisterClassEx (&wc) )
        {
            MessageBox ( NULL, TEXT("Window Registration Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK );

            ret = 0;
            goto TEAR_DOWN;
        }

        // Creating the Window
        g_hMainWindow = CreateWindowEx( WS_EX_TOOLWINDOW,
                                        g_ClassName,
                                        g_WindowName,
                                        WS_OVERLAPPEDWINDOW,
                                        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
                                        NULL, NULL, g_hInstance, NULL );
        if ( g_hMainWindow == NULL )
        {
            MessageBox ( NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK );

            ret = 0;
            goto TEAR_DOWN;
        }

        //
        if ( !InitApp( g_hInstance ) )
        {
            ret = 0;
            goto TEAR_DOWN;
        }

        // The Message Loop
        while ( GetMessage( &msg, NULL, 0, 0 ) > 0 )
        {
            TranslateMessage ( &msg );
            DispatchMessage ( &msg );
        }
        ret = int(msg.wParam);
    }

    // ======================================================== 
    // tear down core
    // ======================================================== 

TEAR_DOWN:

    return ret;
}

