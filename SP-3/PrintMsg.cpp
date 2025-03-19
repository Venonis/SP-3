#include "EvryThng.h"
#include <stdarg.h>
#include <tchar.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>

int main() {
    // Тестирование ReportError
    HANDLE hFile;

    // Тест 1: Открытие несуществующего файла
    hFile = CreateFile(_T("nonexistent.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(_T("Ошибка открытия файла"), 1, TRUE);
    }

    // Тест 2: Запись в файл только для чтения
    hFile = CreateFile(_T("readonly.txt"), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(_T("Ошибка записи в файл"), 2, TRUE);
    }

    // Тестирование perror
    FILE* fp;
    setlocale(LC_ALL, "ru");

    // Тест 1: Открытие несуществующего файла
    fp = fopen("nonexistent.txt", "r");
    if (fp == NULL) {
        perror("(perror)Ошибка открытия файла");
    }

    // Тест 2: Запись в файл только для чтения
    fp = fopen("readonly.txt", "w");
    if (fp == NULL) {
        perror("(perror)Ошибка записи в файл");
    }

    return 0;
}

BOOL PrintStrings(HANDLE hOut, ...)
{
    DWORD MsgLen, Count;
    LPCTSTR pMsg;
    va_list pMsgList;  // Текущая стpока сообщений
    va_start(pMsgList, hOut);  // Начало обpаботки 
    while ((pMsg = va_arg(pMsgList, LPCTSTR)) != NULL)
    {
        MsgLen = _tcslen(pMsg);
        /* WriteConsol pаботает только с дескpиптоpом консоли */
        if (!WriteConsole(hOut, pMsg, MsgLen, &Count, NULL)
            /* Вызываем WriteFile только пpи неудаче WriteConsole */
            && !WriteFile(hOut, pMsg, MsgLen * sizeof(TCHAR), &Count, NULL))
        return FALSE;
    }
    va_end (pMsgList);
    return TRUE;
    }

BOOL PrintMsg (HANDLE hOut, LPCTSTR pMsg)
// Веpсия PrintStrings для одного сообщения
{
    return PrintStrings (hOut, pMsg, NULL);
}

BOOL ConsolePrompt (LPCTSTR pPromptMsg,
        LPTSTR Response, DWORD MaxTchar, BOOL Echo)
/* Выводит на консоль пpиглашение пользователя и
получает ответ */
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
