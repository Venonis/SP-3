// ReportError.cpp
#include "EvryThng.h"
#include <locale.h>

VOID ReportError(LPCTSTR UserMessage, DWORD ExitCode, BOOL PrintErrorMsg) {
    DWORD eMsgLen, LastErr = GetLastError();
    LPTSTR lpvSysMsg;
    HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
    TCHAR convertedMsg[1024];

    // Преобразование пользовательского сообщения в OEM (если необходимо)
#ifdef UNICODE
    char tempUserMsg[1024];
    WideCharToMultiByte(CP_ACP, 0, UserMessage, -1, tempUserMsg, 1024, NULL, NULL);
    CharToOemA(tempUserMsg, tempUserMsg);
    MultiByteToWideChar(CP_ACP, 0, tempUserMsg, -1, convertedMsg, 1024);
#else
    CharToOemA(UserMessage, convertedMsg);
#endif

    PrintStrings(hStdErr, convertedMsg, _T("\n"), NULL);

    if (PrintErrorMsg) {
        eMsgLen = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, LastErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&lpvSysMsg, 0, NULL
        );

        if (eMsgLen > 0) {
            TCHAR sysMsg[1024];
#ifdef UNICODE
            char tempSysMsg[1024];
            WideCharToMultiByte(CP_ACP, 0, lpvSysMsg, -1, tempSysMsg, 1024, NULL, NULL);
            CharToOemA(tempSysMsg, tempSysMsg);
            MultiByteToWideChar(CP_ACP, 0, tempSysMsg, -1, sysMsg, 1024);
#else
            CharToOemA(lpvSysMsg, sysMsg);
#endif
            PrintStrings(hStdErr, sysMsg, _T("\n"), NULL);
            HeapFree(GetProcessHeap(), 0, lpvSysMsg);
        }
    }

    if (ExitCode > 0) ExitProcess(ExitCode);
}