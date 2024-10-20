#pragma once
#include "../core/findPlugin.h"

int assistUser() {
    wchar_t username[256];
    DWORD usernameSize = sizeof(username) / sizeof(username[0]);

    //1Password
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"aeblfdkhhhdcdjpifhhbdiojplfjncoa";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"1Password Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Bitdefender
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"ibkoenhablealnikeefmjineccmgegmh";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Bitdefender Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Dashlane
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"fdjamakpfbbddfjaooikfcpapjohcfmg";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Dashlane Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Kaspersky
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"dhnkblpjbkfklfloegejegedcafpliaa";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Kaspersky Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //LastPass
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"hdokiejnpimakedhajhdlcegeplioahd";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"LastPass Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Roboform
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"pnlccmojcmeohlpggmfnbbiapkmbliob";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Roboform Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Bitwarden
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"nngceckbapebfimnlniiiahkandclblb";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Bitwarden Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Norton
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"admmjipmmciaobhojoghlmleefbicajg";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Norton Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Ironvest
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"epanfjkfahimkgomnigadpkobaefekcd";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Ironvest Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Avira
    if (GetUserNameW(username, &usernameSize)) {
        // Replace this value with the extension name you want to check
        std::wstring extensionName = L"caljgklbbfbcjjanaijlacgncafpegll";

        if (findPlugin(username, extensionName)) {
            std::wcout << L"Avira Chrome Plugin Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }


    //Brave
    if (findAppBrave()) {
        std::wcout << L"Brave Directory exists!\n" << std::endl;
    }
    else {
        std::wcerr << L"An error occured." << std::endl;
        return 1;
    }

    //Roboform app
    if (findAppRoboform()) {
        std::wcout << L"Roboform App Directory exists!\n" << std::endl;
    }
    else {
        std::wcerr << L"An error occured." << std::endl;
        return 1;
    }

    //Firefox
    if (findAppFirefox()) {
        std::wcout << L"Firefox Directory exists!\n" << std::endl;
    }
    else {
        std::wcerr << L"An error occured." << std::endl;
        return 1;
    }

    //MSEdge
    if (findAppEdge()) {
        std::wcout << L"MSEdge Directory exists!\n" << std::endl;
    }
    else {
        std::wcerr << L"An error occured." << std::endl;
        return 1;
   

    //Chrome
    if (findAppChrome()) {
        std::wcout << L"Chrome Directory exists!\n" << std::endl;
    }
    else {
        std::wcerr << L"An error occured." << std::endl;
        return 1;
    }

    //Enpass
    if (findAppEnpass()) {
        std::wcout << L"Enpass Directory exists!\n" << std::endl;
    }
    else {
        std::wcerr << L"An error occured." << std::endl;
        return 1;
    }

    //Passwarden
    if (findAppPasswarden()) {
        std::wcout << L"Passwarden App Directory exists!\n" << std::endl;
    }
    else {
        std::wcerr << L"An error occured." << std::endl;
        return 1;
    }

    //1Password
    if (GetUserNameW(username, &usernameSize)) {
        if (findApp1Password(username)) {
            std::wcout << L"1Password App Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //PasswordBoss
    if (GetUserNameW(username, &usernameSize)) {
        if (findAppPasswordBoss(username)) {
            std::wcout << L"PasswordBoss App Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Bitwarden
    if (GetUserNameW(username, &usernameSize)) {
        if (findAppBitwarden(username)) {
            std::wcout << L"Bitwarden App Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }

    //Opera
    if (GetUserNameW(username, &usernameSize)) {
        if (findAppOpera(username)) {
            std::wcout << L"Opera App Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }


    //NordPass
    if (GetUserNameW(username, &usernameSize)) {
        if (findAppNordPass(username)) {
            std::wcout << L"NordPass App Directory exists!\n" << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to get the current user's login name." << std::endl;
        return 1;
    }
}
