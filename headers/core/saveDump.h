#pragma once
#include <windows.h>
#include <dbghelp.h>

// Function to create a dump file for a process
int saveDump(DWORD largestPid)
{
    DWORD pid = largestPid; // Replace with the desired PID
    std::wcout << L"process PID: " << largestPid << std::endl;
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (process == NULL) {
        std::cerr << "Failed to open the process. Error: " << GetLastError() << std::endl;
        return 1;
    }

    WCHAR dumpFileName[MAX_PATH];
    swprintf_s(dumpFileName, MAX_PATH, L"app.dmp", pid);

    HANDLE dumpFile = CreateFileW(dumpFileName, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (dumpFile == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create the dump file. Error: " << GetLastError() << std::endl;
        CloseHandle(process);
        return 1;
    }

    MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
    exceptionInfo.ThreadId = GetCurrentThreadId();
    exceptionInfo.ExceptionPointers = nullptr;
    exceptionInfo.ClientPointers = FALSE;

    if (!MiniDumpWriteDump(process, pid, dumpFile, MiniDumpWithFullMemory, &exceptionInfo, nullptr, nullptr)) {
        std::cerr << "MiniDumpWriteDump failed. Error: " << GetLastError() << std::endl;
    }
    else {
        std::wcout << L"Dump file created: " << dumpFileName << std::endl;
    }

    CloseHandle(dumpFile);
    CloseHandle(process);

}
