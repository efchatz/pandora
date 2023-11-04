#pragma once
#include <Windows.h>
#include <dbghelp.h>


// Function to find PIDs by process name
std::vector<DWORD> FindPIDsByProcessName(const char* processName)
{
    std::vector<DWORD> pids;
    DWORD processes[1024];
    DWORD cbNeeded;

    if (EnumProcesses(processes, sizeof(processes), &cbNeeded))
    {
        DWORD numProcesses = cbNeeded / sizeof(DWORD);
        for (DWORD i = 0; i < numProcesses; i++)
        {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
            if (hProcess)
            {
                char buffer[MAX_PATH];
                if (GetModuleBaseNameA(hProcess, NULL, buffer, MAX_PATH) > 0)
                {
                    if (strcmp(buffer, processName) == 0)
                    {
                        pids.push_back(processes[i]);
                    }
                }
                CloseHandle(hProcess);
            }
        }
    }
    return pids;
}

// Function to get Private Working Set sizes for a list of PIDs
std::vector<std::pair<DWORD, double>> GetPrivateWorkingSetSizes(const std::vector<DWORD>& pids)
{
    std::vector<std::pair<DWORD, double>> pidSizePairs;

    for (DWORD pid : pids)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
        if (hProcess)
        {
            PROCESS_MEMORY_COUNTERS_EX pmc;
            if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
            {
                SIZE_T privateWorkingSetSizeBytes = pmc.PrivateUsage;
                double privateWorkingSetSizeMB = static_cast<double>(privateWorkingSetSizeBytes) / (1024 * 1024);
                pidSizePairs.push_back(std::make_pair(pid, privateWorkingSetSizeMB));
            }
            CloseHandle(hProcess);
        }
    }

    return pidSizePairs;
}
