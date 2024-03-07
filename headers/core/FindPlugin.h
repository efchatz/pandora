#pragma once

bool findPlugin(const std::wstring& username, const std::wstring& extensionName) {
    std::wstring extensionPath = L"C:\\Users\\" + username + L"\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Extensions\\" + extensionName;

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

//Brave
bool findAppBrave() {
    std::wstring extensionPath = L"C:\\Program Files\\BraveSoftware\\Brave-Browser\\Application";

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

//Firefox
bool findAppFirefox() {
    std::wstring extensionPath = L"C:\\Program Files\\Mozilla Firefox";

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

//MSEdge
bool findAppEdge() {
    std::wstring extensionPath = L"C:\\Program Files (x86)\\Microsoft\\Edge\\Application";

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

//Chrome
bool findAppChrome() {
    std::wstring extensionPath = L"C:\\Program Files\\Google\\Chrome\\Application";

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

//Passwarden
bool findAppPasswarden() {
    std::wstring extensionPath = L"C:\\Program Files (x86)\\Passwarden";

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

//1Password
bool findApp1Password(const std::wstring& username) {
    std::wstring extensionPath = L"C:\\Users\\" + username + L"\\AppData\\Local\\1Password\\app\\8";

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}

//PasswordBoss
bool findAppPasswordBoss(const std::wstring& username) {
    std::wstring extensionPath = L"C:\\Users\\" + username + L"\\AppData\\Local\\PasswordBoss";

    DWORD attributes = GetFileAttributesW(extensionPath.c_str());

    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}


//Keeper is usually installed from MS Store
bool DirectoryContainsKeeperSecurityInc()
{
    // Get the %LOCALAPPDATA% environment variable to construct the path.
    WCHAR localAppData[MAX_PATH];
    if (GetEnvironmentVariableW(L"LOCALAPPDATA", localAppData, MAX_PATH) > 0)
    {
        std::wstring localAppDataPath(localAppData);
        localAppDataPath += L"\\Packages";

        WIN32_FIND_DATAW findFileData;
        HANDLE hFind = FindFirstFileW((localAppDataPath + L"\\*").c_str(), &findFileData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    std::wstring folderName(findFileData.cFileName);
                    if (folderName.find(L"KeeperSecurityInc") != std::wstring::npos)
                    {
                        FindClose(hFind);
                        std::wcout << L"Folder found: " << localAppDataPath + L"\\" + folderName << std::endl;
                        std::wcout << "\n";
                        return true;
                    }
                }
            } while (FindNextFileW(hFind, &findFileData) != 0);

            FindClose(hFind);
        }
    }

    return false;
}



