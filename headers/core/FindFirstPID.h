#pragma once
#include <windows.h>
#include <psapi.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <dbghelp.h>

// Function to find the PID with the first-largest Private Working Set size
DWORD FindFirstPID(const std::vector<std::pair<DWORD, double>>& pidSizePairs)
{
    std::vector<std::pair<DWORD, double>> sortedPairs = pidSizePairs;
    std::sort(sortedPairs.begin(), sortedPairs.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    if (sortedPairs.size() >= 2)
    {
        return sortedPairs[0].first; // First largest PID
    }
    else
    {
        return 0; // No first largest PID found
    }
}



