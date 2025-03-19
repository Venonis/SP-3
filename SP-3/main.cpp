#include "EvryThng.h"
#include <iostream>

void TestReportError();
void TestPerror();

int main() {
    setlocale(LC_ALL, "ru");
    int n;
    std::cin >> n;
    if(n == 1)
        TestReportError();
    else
        TestPerror();

    return 0;
}

void TestReportError() {
    HANDLE hFile;

    std::cout << "[Тест 1] Попытка открыть несуществующий файл...\n";
    hFile = CreateFile(_T("nonexistent.txt"), GENERIC_READ, 0, NULL, 
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(_T("Ошибка открытия файла"), 1, TRUE);
    }

    std::cout << "\n[Тест 2] Попытка записи в файл с атрибутом 'только для чтения'...\n";

    hFile = CreateFile(_T("readonly.txt"), GENERIC_WRITE, 0, NULL, 
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        ReportError(_T("Ошибка записи в файл"), 2, TRUE);
    }
    CloseHandle(hFile);
}

void TestPerror() {
    FILE* fp;

    std::cout << "[Тест 1] Попытка открыть несуществующий файл...\n";
    fp = fopen("nonexistent.txt", "r");
    if (fp == NULL) {
        perror("(perror) Ошибка открытия файла");
    }
    else {
        fclose(fp);
    }

    std::cout << "\n[Тест 2] Попытка записи в файл с атрибутом 'только для чтения'...\n";
    fp = fopen("readonly.txt", "w");
    if (fp == NULL) {
        perror("(perror) Ошибка записи в файл");
    }
    else {
        fclose(fp);
    }
}