// ======================================================================================
// File         : Monitor.h
// Author       : Wu Jie 
// Last Change  : 02/19/2009 | 23:27:48 PM | Thursday,February
// Description  : 
// ======================================================================================

#pragma once 

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// class SMonitorDesc
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

struct SMonitorDesc
{
    HMONITOR hMonitor;
    HMONITOR hLeft;
    HMONITOR hRight;
    HMONITOR hUp;
    HMONITOR hDown;
}; // end struct SMonitorDesc

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL CreateMonitorList ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL CALLBACK MonitorEnumProc ( HMONITOR _hMonitor, HDC _hdcMonitor, LPRECT _lprcMonitor, LPARAM _dwData );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL MoveWindowAcrossMonitor ( HWND _hwnd, enum EMoveTo _eMoveTo );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

BOOL MoveWindowToMonitor ( HWND _hwnd, HMONITOR _hMonitorFrom, HMONITOR _hMonitorTo, EMoveTo _eMoveTo );