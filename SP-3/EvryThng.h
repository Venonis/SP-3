#pragma once
// Исключить определения, не нужные в примерах
#define WIN32_LEAN_AND_MEAN
#define NOATOM
#define NOCLIPBOARD
#define NOCOMM
#define NOCTLMGR
#define NOCOLOR
#define NODFERWINDOWPOS
#define NODESKTOPDRAWTEXT
#define NOEXTAPIGDICAPMASKS
#define NOHELP
#define NOICONS
#define NOTIME
#define NOIMM
#define NOKANJI
#define NOKERNEL
#define NOKEYSTATES
#define NOMCX
#define NOMEMMGR
#define NOMENUS
#define NOMETAFILE
#define NOMSG
#define NONCMESSAGE
#define NOPROFILER
#define NORASTEROPS
#define NORESOURCE
#define NOSCROLL
#define NOSERVICE
#define NOSHOWWINDOW
#define NOSOUND
#define NOSYSCOMMANDS
#define NOSYSMETRICS
#define NOSYSPARAMS
#define NOTEXTMETRICS
#define NOVIRTUALKEYCODES
#define NOWH
#define NOWINDOWSTATION
#define NOWINMASSEGES
#define NOWINOFFSETS
#define NOWINSTYLES
#define OEMRESORCE

// Можно определить UNICODE в проекте
//#define UNICODE  
#undef UNICODE  
#ifdef UNICODE
#define _UNICODE
#else
#undef _UNICODE
#endif

// Общие заголовочные файлы
#include <windows.h>
#include <tchar.h>	
#include <stdio.h>
#include <io.h>
#include <stdlib.h>

// Символьные константы и служебные функции
#define YES _T("y")
#define CR 0x0D
#define LF 0x0A
#define TSIZE sizeof(TCHAR)
#define MAX_OPTIONS 20
#define TYPE_FILE 1
#define TYPE_DIR 2
#define TYPE_DOT 3

BOOL PrintStrings(HANDLE hOut, ...);
BOOL PrintMsg(HANDLE hOut, LPCTSTR pMsg);
BOOL ConsolePrompt(LPCTSTR pPromptMsg, LPTSTR pResponse, DWORD MaxTchar, BOOL Echo);
VOID ReportError(LPCTSTR UserMessage, DWORD ExitCode, BOOL PrintErrorMsg);
DWORD Options(int argc, LPTSTR argv[], LPCTSTR OptStr, ...);
BOOL Asc2Un(LPCTSTR fIn, LPCTSTR fOut, BOOL bFailIfExists);
VOID ReportException(LPCTSTR UserMessage, DWORD ExcetionCode);

#ifdef _UNICODE
#define _memtchr wmemchr
#else
#define _memtchr memchr
#endif