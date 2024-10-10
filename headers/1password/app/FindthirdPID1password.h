#include <iostream>
#include <fstream>

using namespace std;

string FindsecondPID1password()
{
    ofstream file;
    file.open("1password.ps1");

    string powershell;
    powershell = "$processes = Get-Process -Name \"1Password\" | Select-Object Id, @{Name=\"PrivateWorkingSet (MB)\"; Expression={[math]::Round($_.PrivateMemorySize64 / 1MB, 2)}}\n";
    powershell += "$sortedProcesses = $processes | Sort-Object \"PrivateWorkingSet (MB)\" -Descending\n";
    powershell += "$secondLargest = $sortedProcesses[1]\n";
    powershell += "$secondLargest.Id\n";
    file << powershell << endl;
    file.close();

    // Execute the PowerShell script and capture the output
    string powershellCommand = "powershell -ExecutionPolicy Bypass -F 1password.ps1";
    string scriptOutput = "";

    FILE* fp = _popen(powershellCommand.c_str(), "r");
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        scriptOutput += buffer;
    }
    _pclose(fp);

    // Now, 'scriptOutput' contains the output of the PowerShell script
    cout << "PowerShell script output: " << scriptOutput;

    remove("1password.ps1");

    return scriptOutput;
}
