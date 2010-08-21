// ======================================================================================
// File         : exWindow.h
// Author       : Wu Jie 
// Last Change  : 02/25/2009 | 22:07:04 PM | Wednesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include <vector>

#include "windows.h"
#include "windowsx.h"
#include "commctrl.h"

#include "APIs.h"
#include "Tray.h"
#include "Monitor.h"
#include "Options.h"
#include "About.h"
#include "HotKeys.h"

#include "../resource.h"

///////////////////////////////////////////////////////////////////////////////
// define global macros
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// hotkey defines
#define IDH_LEFT					1000
#define IDH_RIGHT					1001
#define IDH_UP					    1002
#define IDH_DOWN					1003
#define IDH_ESCAPE					1004

// menu defines
#define IDM_EXIT                    2000                    
#define IDM_OPTIONS                 2001                    

// tray defines
#define EXWIN_TRAYMSG			    (WM_USER + 100)

///////////////////////////////////////////////////////////////////////////////
// define enums
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

enum EMoveTo
{
    eMoveTo_Left,
    eMoveTo_Right,
    eMoveTo_Up,
    eMoveTo_Down,
    eMoveTo_None,
}; // end enum EMoveTo 

///////////////////////////////////////////////////////////////////////////////
// decl global variables 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern const TCHAR g_ClassName[];
extern const TCHAR g_WindowName[];
extern HWND g_hMainWindow;
extern HWND g_hOptionsWindow;
extern HWND g_hAboutWindow;
extern HWND g_hHotKeysWindow;
extern HINSTANCE g_hInstance;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

typedef std::vector<HMONITOR> monitor_handles_t;
extern monitor_handles_t g_MonitorHandles;

typedef std::vector<SMonitorDesc> monitor_descs_t; 
extern monitor_descs_t g_MonitorDescs;

typedef std::vector<HWND> dialog_handles_t; 
extern dialog_handles_t g_DialogHandles;

///////////////////////////////////////////////////////////////////////////////
// global functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ReleaseGlobalVariables ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL InitApp ( HINSTANCE _hInstance );
