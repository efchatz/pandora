<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/efchatz/pandora/blob/main/images/pandora-logo.PNG">
    <img src="images/pandora-logo.PNG" alt="Logo" width="700" height="500">
  </a>

  <h3 align="center">Pandora</h3>

  <p align="center">
    A red team tool to extract credentials from password managers.
    <br />
    <a href="https://github.com/efchatz/pandora/issues">Report Bug</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#prerequisites">Prerequisites</a></li>
    <li><a href="#methodology">Methodology</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This is a red team tool that assists in gathering credentials from different password managers. They are separated into three categories, Windows 10 desktop applications, browsers, and browser plugins. This may work on other OS, like Linux, but it is not tested yet. In this release (v1.0), the tool supports 14 password managers, with 18 different implementations (e.g., the tool could dump credentials either from the desktop app, or the browser plugin of the same product). Specifically, in most cases, password managers must be up and unlocked for the tool to work. 

The tool can be executed in Full, Fast, and Local modes. Full mode dumps and checks all processes of this password manager. Fast mode checks the most common process that usually contains the credentials. Local mode checks the dump file locally. Also, local mode has the "merge" option that can assist in merging multiple dump files into one, before doing the analysis. Additionally, the tool can check if a directory of a password manager exists to assist the user in identifying which password manager can be used in this host. The tool will only need common **user's permissions** to be able to dump a process from a password manager. Only the 1Password desktop app requires high integrity privileges for the user to be able to dump the process.

So, the purpose of this tool is to provide an additional attack vector in red team engagements, since many users are using password managers. Three different videos have been uploaded to assist in understanding how this tool works.

Regarding fixing these issues, most vendors responded that such issues are out-of-scope for them since the attacker needs local access or AV/EDR should protect the user against such attacks. Although some products may provide fixes, their exploits will be released at a later date (they are still under disclosure). Two vendors so far have acknowledged this issue and provided fixes with **CVE-2023-23349 (Kaspersky)** and **CVE-2024-9203 (Enpass)**.

This is not a completely new concept. It has been well-known for some time that there is no de facto way for desktop applications to be protected against such attacks. However, and to the best of my knowledge, this is the first time such a tool has been presented to the public. Feel free to provide any feedback and/or recommendations/improvements. **The tool only handles the relevant versions. A password manager update could potentially change the pattern that the tool uses to identify the credentials.**

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![C++][C++]][C-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Simply, clone the code, and compile it. For the development phase, Visual Studio 2022 was used.



### Installation

1. Install Visual Studio 2022, with all C++ dependencies.
2. Clone the repo.
   ```sh
   git clone https://github.com/efchatz/pandora.git
   ```
3. Open the project.
4. Build this project as a release.

In case of an issue with "DbgHelp.lib", do the following:
1. In Project->Properties->Linker->Input, choose in the "Configuration" dropdown "All Configurations".
2. Add in the "Additional Dependencies" the "DbgHelp.lib".
3. In the same tab, in "Ignore All Default Libraries", choose "No".
4. Press "OK".

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- METHODOLOGY -->
## Methodology
The code is structured as follows:
1. The user chooses the mode (full, fast, local). Full mode will dump all processes from a password manager and fast will dump the most common one that in most cases will contain the credentials. Local mode is done locally while providing the dump file.
2. The user then has the option to check which password manager is installed for either an app or a plugin with a yes/no choice. The code checks if the default installation path of each password manager exists and provides the output. Note that during installation, most password managers do not allow the user to change the default installation path. For instance, Keeper is installed directly from the MS Store. So, this method could assist in identifying which password manager is installed. Note that in Full mode, the tool will not validate the actual size of each process file that will be created. So, if the host does not have the required free space, some processes will not be dumped and no error message will be shown.

![pass-exists](https://github.com/efchatz/pandora/assets/43434138/00834f80-86a6-4f12-be7f-654eeee00cdb)

4. The user chooses the relevant password manager.
5. If the user chooses the "local" mode, then they will be asked if they want to merge different dump files. If yes, they must provide their filenames, each one per line, and enter "done" at the end. Otherwise, they will only have to provide their dump filename.
6. Based on the relevant password manager, the tool dumps the process into a file.
7. The dump file then is analyzed to identify any relevant pattern within it, to extract credentials.
8. In some cases, some junk data will be presented to the user. These data will be noted as unparsed characters. So, they can be easily recognized.
9. The user then can identify the credentials (either in the cmd output or in the relevant txt file).

It should be noted that in some cases password managers store in plaintext other types of data, like credit card details, addresses, Wi-Fi passwords etc. Users should be wary of such attacks and should not execute untrusted files, enable 2FA, etc.

Regarding the exploits, the methodology is simple, i.e., the purpose is to identify a pattern or a keyword that would pinpoint the relevant credentials within the dump file. Each password manager is different, so, each exploitation method differs. However, the concept is the same, i.e., finding the relevant pattern can pinpoint the credentials within this file. In some cases, the exploit finds when the credentials start and then gathers the next bytes, say 100. I did some extensive testing to identify these values correctly, but they may differ in a real-case scenario. Open an issue if you want to propose another password manager to be included in this tool which contains credentials in plaintext format within the process. 

Note that the tool will delete the relevant 'app.dmp' file at the end of execution. Consider commenting out this line in the code 'remove("app.dmp");', in case you want to keep the relevant dump file. Generally, it is advised to first execute the code in a constrained environment in which the master/entry credentials will be known, observe the relevant output, and then execute it in another host. 

Any further details can be found in our research work titled ["Keep your memory dump shut: Unveiling data leaks in password managers"](https://arxiv.org/abs/2404.00423)


<!-- USAGE EXAMPLES -->
## Usage

To use this tool, simply execute the compiled executable in the relevant host and type the name of the password manager. Based on the password manager, there are some requirements for the tool to be able to extract credentials. However, I kept in most cases password managers who needed basic interaction to store their credentials in the memory of their process. After executing the tool, it will automatically dump the relevant process based on the chosen password manager, print the credentials in the cmd, and save them into a file (the location of the file is the current folder of the .exe). 

Three videos have been uploaded to assist in how this tool works. The videos depict the phase in which an attacker would be able to gather the credentials from a password manager. In the case of Avira and similar password managers, this can be done without any user interaction (check relevant video).

The following table depicts a high-level view of the tool's capabilities. Note that Firefox and the relevant Firefox plugins of password managers may not work correctly. They need further research for the tool to be able to extract the credentials in every case. This is because Firefox changes its pattern with each execution.

Note: The Users column refers to the number of users mentioned in the Chrome Web Store for each browser plugin.

| Name         | Location   | Credentials               | Browser             | Stability    | Version    | Users |
|--------------|------------|---------------------------|---------------------|--------------|------------|-------|
| 1Password    | App/Plugin | Master(App)/Master(Plugin) | Chrome             | Yes          |8.10.44.34  | +5M   |
| Avira        | Plugin     | Entries                   | Chrome              | Yes          |2.21.0.4971 | +6M   |
| Bitdefender  | Plugin     | Master                    | Chrome              | Yes          |1.3.1       | +100K |
| Bitwarden    | Plugin     | Entries                   | Chrome              | Yes          |2024.10.1   | +4M   |
| Bitwarden    | App        | Master                    | N/A                 | Yes          |2024.9.0    | N/A   |
| Chromium     | Browser    | Entries                   | Chrome/MSEdge/Brave/Opera | Yes          |130.0.6723.59| N/A   |
| Enpass       | App        | Entries (fixed)           | N/A                 | Yes          |6.9.3 (patched) | N/A |
| Dashlane     | Plugin     | Master/Entries            | Chrome              | Yes          |6.2440.1    | +2M   |
| Firefox      | Browser    | Entries                   | N/A                 | Partial      |131.0       | N/A   |
| Ironvest     | Plugin     | Entries                   | Chrome              | Yes          |9.9.12      | +90K  |
| Kaspersky    | Plugin     | Entries (fixed)           | Chrome              | Yes          |24.0.0.427 (patched) | +2M |
| Keeper       | App        | Master/Entries            | N/A                 | Yes          |16.11.3     | +1M   |
| LastPass     | Plugin     | Master/Entries            | Chrome              | Yes          |4.134.0     | +9M  |
| NordPass     | App        | Master                    | N/A                 | Yes          |5.23.10     | N/A   |
| Norton       | Plugin     | Entries                   | Chrome              | Yes          |8.2.1.388   | +4M   |
| Passwarden   | App        | Entries                   | N/A                 | Yes          |3.3.0       | +1K   |
| Passwordboss | App        | Entries                   | N/A                 | Yes          |5.5.5249.0  | +20K  |
| Roboform     | App/Plugin | Master(Plugin)/Entries(Both) | Chrome              | Yes          |9.6.8.0     | +600K |


Regarding the extraction of credentials, some exploits are based on a specific number of bytes, to extract the credentials. So, maybe, in some cases, this number must be increased to extract this information correctly. During the experiments, common usernames and passwords were used. So, in most cases, this would be sufficient.

Another note is relevant to the version of each password manager of a browser plugin. If a change is made in the code and affects the process, the tool may be unable to identify these credentials. So, keep in mind that there is a possibility to mishandle some credentials if an older/newer version of the tool is used, or a different OS is running (tested on Windows 10 Pro).

In most cases, the following will be needed to extract the credentials:
1. The relevant app (browser or desktop app) is up, unlocked, and running.
2. In some cases, like in Chromium browsers, an interaction needs to be made with either the relevant plugin or the embedded password manager of the browser.
3. In other cases, some password managers keep these credentials cleartext in memory, even after being locked. This behavior was noted in Keeper.
4. In case of 1Password, high integrity privilege is required. So, execute the .exe with high privileges, or provide the dump file as input.
5. All tests were made with the default settings of each password manager.

It is sufficient to mention that since user behavior is to open such apps and leave them open, it would provide an additional attack vector for lateral movement. Another keypoint is that most of these tools will automatically be locked when the user is completely idle. This means that even if the app or browser plugin is idle and the user is using their host for other activities, these apps will not be locked. Also, in some cases, it is possible to completely avoid user interaction. For instance, some browser plugins remain unlocked for some time. As a result, it is possible to start this process from cmd, without needing the user and extract the credentials. Check Avira's video example to understand this process.

It should be noted that there were some cases like KeePass, StickyPassword, and Opera in which no credentials were found to be cleartext within the memory.

We are working on releasing an academic paper that will describe the experiments and any other relevant details.

<!-- Prerequisites -->
## Prerequisites
This section is devoted to any prerequisites the tool will need to be able to dump the credentials from a password manager.

### 1Password

1Password process needs high integrity privileges for the tool to be able to dump the relevant process and extract the credentials. To extract the credentials, I opened the app, entered the master password, and waited for at least 1 min. Then, I executed the tool to dump the credentials. The following screenshot illustrates the execution of the tool when the relevant app is running. Hidden data refers to the master password. Note that the output data may contain redudant characters at the end of the returned string; in the screenshot only the last character is not included in the master password. It should also be noted that the tool cannot extract the master password if the user pasted in the relevant field. For some reason, 1password does not store the master password in the process, if the user pasted it. Regarding 1Password plugin, master credentials are available. 

![1password](https://github.com/user-attachments/assets/9821e913-db58-4bde-b01f-34e529a42e69)



### Avira

https://github.com/efchatz/pandora/assets/43434138/807d2d87-d240-47f1-8b35-41701cde4a06

The video was paused to shorten the size. First, Chrome is opened from cmd, then waited for at least 1 min. This means that an attacker could possibly start Chrome process without any user's interaction since Avira does not request for the user to enter their master password. After that, I executed pandora and waited to retrieve the credentials. The tool searches for the relevant entries. As can be observed, every entry is shown in a specific line, i.e., the name of the site, the password, and the relevant username. Note that headless mode does not start browser plugins. So, for this attack to work Chrome must be visible.


### Bitdefender

Bitdefender stores entries only when they are needed, like when the user is visiting a url that belongs to an entry. However, the master password is being stored after the user enters it. As a result, there is a case in which an attacker could dump the master password. The tool does not check for entries, only for the master password.

![bitdefender](https://github.com/efchatz/pandora/assets/43434138/61637ca4-d368-40a8-b51d-9be44f007340)


### Bitwarden

Bitwarden imports all entries immediately when the vault is unlocked. Some entries will be shown multiple times, as the tool finds them and dumps them from the dump file. 

![bitwarden](https://github.com/efchatz/pandora/assets/43434138/b3ad4474-fd07-461e-99bd-06f2fd74a1f4)

For the app, only the master password and username are available. It should be noted that the app clear the master password from the memory after some time (appox. 10 min). The following screenshots illustrate the data retrieval of the master password (returned two times) and the username.

![bitwarden](https://github.com/efchatz/pandora/assets/43434138/8effb234-de22-4489-9810-4d1d71993795)

![bitwarden2](https://github.com/efchatz/pandora/assets/43434138/69a4dea0-995c-49b6-9404-2787ad48a44d)


### NordPass

NordPass stores the master username and password. So, both of them can be retrieved from the relevant process memory. Regarding master password, only one pattern will be returned. For the username, the following screenshot illustrates the output.

![nordpass](https://github.com/efchatz/pandora/assets/43434138/cf7f91ca-5669-4b1c-bcc5-499e741600e6)


### Chromium

#### Chrome, Brave, and Opera

Both browsers have the same behavior, they keep the username and password of a login form they interact with and they have saved its credentials, but to get all entries, the user must visit the password manager functionality of the browser or the attacker to open the browser and visit this page. Consider changing the keyword to look for a specific website or email address within the process. Additionally, all chromium browsers can start without needing user interaction. For example, a VBS script (not so OPSEC) could be used to start the browser and visit "chrome://password-manager/passwords". Then, the tool can extract all entries as shown in the following screenshot:

![11121](https://github.com/user-attachments/assets/ac438e9e-de37-4e9c-814c-0fdf4bcf55ad)

Note that the password manager page must be visited once, i.e., even if the password manager is closed and the browser is not terminated and starts another process, the credentials will be stored within the memory. Another case would be for the user to visit a webpage where the password manager has saved its credentials, and then these credentials will be stored in the process.

#### MSEdge

MSEdge is different, i.e., only the browser needs to be open. It is not required for someone to visit the password manager page. MSEdge seems to preload the password manager immediately when opens. As a result, the tool can extract all entries, having the same output as with the other two browsers.


### Dashlane 

When Dashlane is unlocked and interacted in any way, for the next 1 minute, entries will be available. After that, only the master password remains in the process. Depending on the case, the tool will gather the relevant credentials as depicted in the following screenshots. The first screenshot illustrates the case when the master password is available and the second screenshot when entries are.

![1231](https://github.com/user-attachments/assets/bd017386-1ac4-4b61-a2c8-029f600a604d)

![12312](https://github.com/user-attachments/assets/3280be3d-8515-4f24-a004-c11881b6a954)

### Enpass

Regarding Enpass, the app automatically selects the last entry the user has clicked before closing the app. As a result, it is possible with minimum user interaction (simply by opening the app), to extract this entry from the process. It should be noted that sometimes the app does not autoselect the last entry when the user opens it. So, to speed up the recording process, the user manually selects an entry. This issue is fixed in v6.11.3. 

https://github.com/user-attachments/assets/613d8b78-8716-4950-a055-3526ef7aab9c

### Firefox

Firefox uses a different pattern each time it loads the credentials either from the embedded password manager or from another browser plugin. For this reason, the search is being made based on common email addresses that are used as usernames too, like "@gmail.com". The code will search for this string and print some relevant data before and after that. It should be noted that the user can include additional strings (check file getCredsfirefox2.h), but the output will be huge (especially, if a user dumps all processes). So, I suggest using different strings for each analysis, say first with "@gmail.com", identify any set of credentials within it, and then use another string, like "@yahoo.com" to identify any possible password within the process. Generally, to gain access to the stored credentials, the user must visit the password manager page or visit a stored webpage in which the password manager has stored a set of credentials. In the latter case, the process will only contain the credentials of this entry. For instance, if a user has saved the credentials of "Facebook" and visits this webpage, the process will only contain the "Facebook" credentials. Lastly, Firefox has no issue starting from cmd with a command like "start firefox about:logins".

![firefox-pass](https://github.com/efchatz/pandora/assets/43434138/1e43bd52-ae6d-4b4a-8f41-45b286a70f25)


### Ironvest

For Ironvest the relevant webapp must be up. Since this password manager does not require the master password from the user when it opens and keeps them auto logged-in, I started the Chrome from cmd, by visiting "ironvest.com/app". Then, I used the tool to extract all entries. The following screenshot illustrates this issue. Since entries are stored multiple times, they are dumped each time the tool identifies them within the dump file. Note that if the user or the attacker does not visit the Ironvest dashboard page, the entries are not loaded in the process. Another way of getting an entry is when the user visits the URL of a stored entry. Autofill feature will get these credentials in the process, but only for that entry. It should be noted that Ironvest clears the entries from the process after approximately 2-3 minutes. Also, passwords seem to be contain between specific three characters and they end with a comma.

![121212](https://github.com/user-attachments/assets/c77bb9a1-519e-417b-8232-dde06eb66611)


### Kaspersky

For Kaspersky the exploit worked only for the Chrome browser. When a user opened their browser and the autofill option was enabled, the Native Messaging Server process of the password manager kept each entry in plaintext format and did not clear the process. So, if an attacker has access to this host and waited at least 1 min, they could exploit this issue and retrieved any stored entry from this process.


### Keeper

For Keeper, I started the app, entered the master password, and executed the tool. The response of the tool was the following:

![kepepep](https://github.com/efchatz/pandora/assets/43434138/145c0c6b-7e08-4617-ae8c-b1b5280fff45)

The tool will extract all entries and the master username and password of the user. If an entry is empty this means that this user has no other entry in the vault. For example, if the tool prints 5 entries with 4 of them having data and 1 without any data, then the user has stored 4 entries within the password manager.

### LastPass

https://github.com/efchatz/pandora/assets/43434138/69a9e752-0485-428e-b4a8-516ececdf1a1

LastPass automatically logins the user into the vault, when the Chrome browser opens. So, to retrieve the master password, the user must have logged out and logged in manually (entering the master password), without terminating the browser. In every other case, all entries and the master username should be retrieved. In the video above, I started LastPass from cmd. The tool dumped all entries, and the master username, along with some junk data at the end that matched the searched pattern. It is suggested to check the .txt file as it is easier to identify the credentials since the console will include multiple junk rows.


### Norton

Norton uses keywords to store credentials. So, the following screenshot illustrates the credentials the tool dumped. An important fact was that Norton password manager automatically stored the username and password of the user's Norton account within the vault. So, since all relevant entries are available, if the user did not delete the entry with their Norton account username/password, then the tool will extract them too. These are the credentials that were removed from the console output. Wait 30 sec after starting the browser to extract the credentials with the tool. This relevant version asks the user to enter the master password every time they open the browser. 

![123123](https://github.com/user-attachments/assets/e9923364-23af-497d-95a8-3fad9d2d3617)


### Passwarden

The usual procedure was needed. As can be observed from the following screenshot, all data are noted with different keywords:

![passwarden](https://github.com/efchatz/pandora/assets/43434138/c785f0a4-0cc9-4b91-b1f8-1005dd026853)

In the new version of the tool, the master username can be also extracted from the password manager. The master password also exists in plaintext format within the process, but there is no stable way of extracting it, yet.

### PasswordBoss

https://github.com/efchatz/pandora/assets/43434138/f8f3b7fa-41f7-4182-9845-3430ec33486b

The video was paused to shorten the size. First, the passwordboss app is executed, I entered then the master password and minimized the app. After that, I executed the tool and waited 3-4 min. As can be observed, the tool retrieved all relevant entries. Some of them, like Amazon were empty, but others like Facebook, Google, and a custom one named aegean were filled with the username and password of the user. Usually, entries with data, contain the "[]" symbol. 


### Roboform

Roboform automatically unlocks the vault when the user opens the Chrome browser. Specifically, Roboform needs interaction with any saved entry URL or for the user to click the plugin to load the entries. So, it is possible to start the Chrome process from cmd or powershell command and then execute the tool to extract the credentials. Additionally, the master password is available by simply opening the browser. The following screenshot depicts the credentials the tool dumped, after starting the Chrome from cmd. The first screenshot illustrates the output of the extracted entries, while the second one demonstrates the extraction of the master password.

![123121](https://github.com/user-attachments/assets/5041d189-4a18-4d5d-a961-29c6507fab1a)

![1221](https://github.com/user-attachments/assets/24875302-10e8-4b05-9a4c-cc76fb76b2d7)

Regarding Roboform app, things are simpler. If the app is running, all entries can be extracted. Specifically, entries will be available as being stored in the password manager. This means that all possible entries will be returned, along with the ones the user has saved. Below there is an example of the extracted entry passwords.


![roboform_screen_entries](https://github.com/user-attachments/assets/2b041d10-d261-4973-8bfd-9d90fc120c6b)


<!-- Also, an example of Repetitiveness has been added to assist in finding the master password of the Roboform app quickly. Specifically, the tool evaluates all possible master password credentials it gathered due to the relevant pattern (136 entries) and then checks which of these entries exist exactly 1 time within the dump. Since only the master password exists exactly 1 time in the dump, the tool prints only the relevant entry.

![tool1-1](https://github.com/efchatz/pandora/assets/43434138/0ac2bc79-2ebf-4a5c-a035-936db4108fea) -->


## Repetitiveness

Regarding Repetitiveness, current application editions do not need any additional adjustments. As a result, only pattern-based extraction can assist in identifying and extracting the necessary information. However, for the sake of completeness, the following code demonstrates the usage of Repetitiveness in Roboform app v9.5.2.0. First, we must count the number of times a set of credentials is shown in plaintext format within the process of the application. Then, we can use the `countOccurrences` function to count the number of times a given set of data is stored within the process. After that, we can use `getCredsroboformapp4` function to open a file with the extracted data, and check how many times each line of text exists in the process. If the number of times from `countOccurrences` is equal to the number of times the occurrence is shown in the process, then we can print this line of text. The purpose here is to shorten the output of the extracted text and identify a set of credentials with ease. In the current example, the output text of the pattern extraction was 136 lines. After using the repetitiveness, only the master password was kept.

```C++
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "../../core/saveFile.h"

//Repetitiveness for Roboform
// Helper function to find occurrences of a sequence in the file data
int countOccurrences(const std::vector<unsigned char>& data, const std::vector<unsigned char>& sequence) {
    int count = 0;
    auto it = data.begin();
    while (it != data.end()) {
        it = std::search(it, data.end(), sequence.begin(), sequence.end());
        if (it != data.end()) {
            ++count;
            ++it; // Move iterator to continue search after this match
        }
    }
    return count;
}

int getCredsroboformapp4(std::string filename) {
    //Due to using saveFile2 in getCredsroboformapp2.h
    std::ifstream sequencesFile("credentials2.txt");
    std::ifstream dataFile(filename, std::ios::binary);

    if (!sequencesFile.is_open()) {
        std::cerr << "Error opening the sequences file." << std::endl;
        return 1;
    }

    if (!dataFile.is_open()) {
        std::cerr << "Error opening the data file." << std::endl;
        return 1;
    }

    // Read the entire data file into memory
    std::vector<unsigned char> fileData((std::istreambuf_iterator<char>(dataFile)), std::istreambuf_iterator<char>());
    dataFile.close();

    std::string line;
    while (std::getline(sequencesFile, line)) {
        // Convert the line to a sequence of unsigned char
        std::vector<unsigned char> sequence(line.begin(), line.end());

        // Count occurrences of the sequence in the file data
        int occurrences = countOccurrences(fileData, sequence);

        // Print and save the results only if found exactly once
        if (occurrences == 1) {
            std::cout << "Sequence: " << line << " found " << occurrences << " time." << std::endl;
            saveFile(line + "\n");
        }
    }

    sequencesFile.close();

    return 0;
}
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information. This tool is provided as is, for educational purposes and/or legitimate assessments.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Efstratios Chatzoglou - efchatzoglou@gmail.com


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

I would like to thank Zisis Tsiatsikas and Vyron Kampourakis. They assist me in identifying which process contains cleartext credentials for some password managers. Kaspersky team for assigning [CVE-2023-23349](https://nvd.nist.gov/vuln/detail/CVE-2023-23349#) and for the [security advisory.](https://support.kaspersky.com/vulnerability/list-of-advisories/12430#180324). Also, I would like to thank VulnDB team, for assigning [CVE-2024-9203](https://vuldb.com/?id.278561) for Enpass.
 
* [Choose an Open Source License](https://choosealicense.com)
* [Img Shields](https://shields.io)
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/badge/Contributors-3-brightgreen?style=for-the-badge
[contributors-url]: https://github.com/efchatz/pandora/graphs/contributors
[forks-shield]: https://img.shields.io/badge/Forks-78-blue?style=for-the-badge
[forks-url]: https://github.com/efchatz/pandora/network/members
[stars-shield]: https://img.shields.io/badge/Stars-571-blue?style=for-the-badge
[stars-url]: https://github.com/efchatz/pandora/stargazers
[issues-shield]: https://img.shields.io/badge/Issues-0-lightgrey?style=for-the-badge
[issues-url]: https://github.com/efchatz/pandora/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/efchatz/pandora/LICENSE
[product-screenshot]: images/screenshot.png
[C++]: https://img.shields.io/badge/C++-blue?style=for-the-badge&logo=c++&logoColor=white
[C-url]: https://cplusplus.com/
