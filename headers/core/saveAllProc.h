#pragma once
#include <iostream>
#include <cstdio>

// Function to create a dump file for a process
void CreateDumpFile(DWORD pid) {
    WCHAR dumpFileName[MAX_PATH];
    swprintf_s(dumpFileName, MAX_PATH, L"app.dmp");

    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (process == NULL) {
        std::cerr << "Failed to open the process. Error: " << GetLastError() << std::endl;
        return;
    }

    HANDLE dumpFile = CreateFileW(dumpFileName, FILE_APPEND_DATA, 0, nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (dumpFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create or open the dump file. Error: " << GetLastError() << std::endl;
        CloseHandle(process);
        return;
    }

    // Move the file pointer to the end of the file
    SetFilePointer(dumpFile, 0, NULL, FILE_END);

    MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
    exceptionInfo.ThreadId = GetCurrentThreadId();
    exceptionInfo.ExceptionPointers = nullptr;
    exceptionInfo.ClientPointers = FALSE;

    if (!MiniDumpWriteDump(process, pid, dumpFile, MiniDumpWithFullMemory, &exceptionInfo, nullptr, nullptr)) {
        std::cerr << "MiniDumpWriteDump failed. Error: " << GetLastError() << std::endl;
    }
    else {
        std::wcout << L"Data appended to the dump file: " << dumpFileName << std::endl;
    }

    CloseHandle(dumpFile);
    CloseHandle(process);
}
