#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <string>

// Function to find the process ID by name
DWORD FindSimpleProcPID(const char* processName) {
    // Convert processName to a wide character string (wchar_t)
    std::wstring wProcessName(processName, processName + strlen(processName) + 1);

    // Initialize a process entry structure with wide character strings
    PROCESSENTRY32W processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32W);

    // Create a snapshot of the system's processes
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create process snapshot." << std::endl;
        return 0; // Return 0 to indicate an error
    }

    // Find the first process in the snapshot
    if (Process32FirstW(hSnapshot, &processEntry)) {
        do {
            // Check if the process name matches the one you're looking for
            if (wcscmp(processEntry.szExeFile, wProcessName.c_str()) == 0) {
                // Return the PID
                return processEntry.th32ProcessID;
            }
        } while (Process32NextW(hSnapshot, &processEntry));
    }

    CloseHandle(hSnapshot);

    // Return 0 to indicate that the process was not found
    return 0;
}
