#pragma once
#include <windows.h>
#include <psapi.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <dbghelp.h>

// Function to find the PID with the second-largest Private Working Set size
DWORD FindSecondPID(const std::vector<std::pair<DWORD, double>>& pidSizePairs)
{
    std::vector<std::pair<DWORD, double>> sortedPairs = pidSizePairs;
    std::sort(sortedPairs.begin(), sortedPairs.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    if (sortedPairs.size() >= 2)
    {
        return sortedPairs[1].first; // Second largest PID
    }
    else
    {
        return 0; // No second largest PID found
    }
}



