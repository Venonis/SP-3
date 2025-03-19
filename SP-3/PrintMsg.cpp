#include "EvryThng.h"
#include <stdarg.h>
#include <tchar.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

int main() {
    // ������������ ReportError
    HANDLE hFile;

    // ���� 1: �������� ��������������� �����
    hFile = CreateFile(_T("nonexistent.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(_T("������ �������� �����"), 1, TRUE);
    }

    // ���� 2: ������ � ���� ������ ��� ������
    hFile = CreateFile(_T("readonly.txt"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(_T("������ ������ � ����"), 2, TRUE);
    }

    // ������������ perror
    FILE* fp;
    setlocale(LC_ALL, "ru");

    // ���� 1: �������� ��������������� �����
    fp = fopen("nonexistent.txt", "r");
    if (fp == NULL) {
        perror("(perror)������ �������� �����");
    }

    // ���� 2: ������ � ���� ������ ��� ������
    fp = fopen("readonly.txt", "w");
    if (fp == NULL) {
        perror("(perror)������ ������ � ����");
    }

    return 0;
}

BOOL PrintStrings(HANDLE hOut, ...)
{
    DWORD MsgLen, Count;
    LPCTSTR pMsg;
    va_list pMsgList;  // ������� ��p��� ���������
    va_start(pMsgList, hOut);  // ������ ��p������ 
    while ((pMsg = va_arg(pMsgList, LPCTSTR)) != NULL)
    {
        MsgLen = _tcslen(pMsg);
        /* WriteConsol p������� ������ � ����p����p�� ������� */
        if (!WriteConsole(hOut, pMsg, MsgLen, &Count, NULL)
            /* �������� WriteFile ������ �p� ������� WriteConsole */
            && !WriteFile(hOut, pMsg, MsgLen * sizeof(TCHAR), &Count, NULL))
        return FALSE;
    }
    va_end (pMsgList);
    return TRUE;
    }

BOOL PrintMsg (HANDLE hOut, LPCTSTR pMsg)
// ��p��� PrintStrings ��� ������ ���������
{
    return PrintStrings (hOut, pMsg, NULL);
}

BOOL ConsolePrompt (LPCTSTR pPromptMsg,
        LPTSTR Response, DWORD MaxTchar, BOOL Echo)
/* ������� �� ������� �p��������� ������������ �
�������� ����� */
{
    HANDLE hStdIn, hStdOut;
    DWORD TcharIn, EchoFlag;
    BOOL Success;
    hStdIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    hStdOut = CreateFile(_T("CONOUT$"), GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    EchoFlag = Echo ? ENABLE_ECHO_INPUT : 0;
    Success = SetConsoleMode(hStdIn, ENABLE_LINE_INPUT | EchoFlag | ENABLE_PROCESSED_INPUT) 
        && SetConsoleMode(hStdOut, ENABLE_WRAP_AT_EOL_OUTPUT | ENABLE_PROCESSED_OUTPUT)
        && PrintStrings(hStdOut, pPromptMsg, NULL)
        && ReadConsole(hStdIn, Response, MaxTchar, &TcharIn, NULL);
    if (Success) Response[TcharIn - 2] = '\0';
    CloseHandle(hStdIn);
    CloseHandle(hStdOut);
    return Success;
}
