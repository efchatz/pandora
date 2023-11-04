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
  <a href="https://github.com/efchatz/pandora/images/pandora-logo.PNG">
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
    <li><a href="#methodology">Methodology</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This is a red team tool that assists in gathering credentials from different password managers. They are separated into three categories, Windows 10 desktop applications, browsers, and browser plugins. This may work on other OS, like Linux, but it is not tested yet. In this release (v0.5), the tool supports 14 password managers, with 18 different implementations (e.g., the tool could dump credentials either from the desktop app, or the browser plugin of the same product). Specifically, in most cases, password managers must be up and unlocked for the tool to work. 

So, the purpose of this tool is to provide an additional attack vector in red team engagements, since many users are using password managers. Three different videos have been uploaded to assist in understanding how this tool works.

Regarding fixing these issues, most vendors responded that such issues are out-of-scope for them since the attacker needs local access or AV/EDR should protect the user against such attacks. Although some products may provide fixes, their exploits will be released at a later date (they are still under disclosure).

This is not a completely new concept. It has been well-known for some time that there is no de facto way for desktop applications to be protected against such attacks. However, and to the best of my knowledge, this is the first time such a tool has been presented to the public. Feel free to provide any feedback and/or recommendations/improvements.

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



<!-- USAGE EXAMPLES -->
## Usage

To use this tool, simply execute the compiled executable in the relevant host and type the name of the password manager. Based on the password manager, there are some requirements for the tool to be able to extract credentials. However, I kept in most cases password managers who needed basic interaction to store their credentials in the memory of their process. After executing the tool, it will automatically dump the relevant process based on the chosen password manager, print the credentials in the cmd, and save them into a file (the location of the file is the current folder of the .exe). 

Three videos have been uploaded to assist in how this tool works. The videos depict the phase in which an attacker would be able to gather the credentials from a password manager. In the case of Avira and similar password managers, this can be done without any user interaction (check relevant video).

The following table depicts a high-level view of the tool's capabilities. Note that Firefox and the relevant Firefox plugins of password managers may not work correctly. They need further research for the tool to be able to extract the credentials in every case. This is due to the fact that Firefox changes its pattern with each execution.

| Name         | Location   | Credentials               | Browser             | Stability    | Version    | Users      |
|--------------|------------|---------------------------|---------------------|--------------|------------|------------|
| Chromium     | Browser    | Entries                   | Chrome/MSEdge/Brave | Yes          |121.0.6106.0| N/A        |
| 1Password    | App/Plugin | Master(Both)/Entries(App) | Chrome/Firefox      | Yes          |8.10.18     | +4M        |
| Firefox      | Browser    | Entries                   | N/A                 | No           |119.0       | N/A        |
| Dashlane     | Plugin     | Master/Entries            | Chrome/Firefox      | Yes (Chrome) |6.2344.1    | +2M        |
| Keeper       | App        | Entries                   | N/A                 | Yes          |16.10.9     | N/A        |
| LastPass     | Plugin     | Master/Entries            | Chrome              | Yes          |4.123.0     | +10M       |
| Roboform     | Plugin     | Entries                   | Chrome              | Yes          |9.5.2.0     | +600K      |
| Bitwarden    | Plugin     | Master/Entries            | Chrome              | Yes          |2023.10.1   | +3M        |
| Norton       | Plugin     | Entries                   | Chrome              | Yes          |8.1.0.73    | +4M        |
| Bitdefender  | Plugin     | Master/Entries            | Chrome              | Yes          |1.3.0       | +90K       |
| Ironvest     | Plugin     | Entries                   | Chrome              | Yes          |9.8.15      | +90K       |
| Passwarden   | App        | Entries                   | N/A                 | Yes          |3.3         | +1K        |
| Avira        | Plugin     | Entries                   | Chrome              | Yes          |2.19.14.4461| +6M        |
| Passwordboss | App        | Entries                   | N/A                 | Yes          |5.5.5104    | +20K       |


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

### Chromium

#### Chrome and Brave 

Both browsers have the same behavior, they keep the username and password of a login form they interact with and they have saved its credentials, but to get all entries, the user must visit the password manager functionality of the browser or the attacker to open the browser and visit this page. Then, the tool can extract all entries as showed in the following screenshot:

![brave](https://github.com/efchatz/pandora/assets/43434138/6e011874-8c04-4034-9b60-17a2a493346d)

Note that the password manager page must be visited once, i.e., even if the password manager is closed and the browser is not terminated and start another process, the credentials will be stored within the memory.

#### MSEdge

MSEdge is different, i.e., only the browser needs to be open. It is not required for someone to visit the password manager page. MSEdge seems to preload the password manager immediatelly when opens. As a result, the tool can extract all entries, having the same output as with the other two browsers.

### 1Password

1Password process needs high integrity privileges for the tool to be able to dump the relevant process and extract the credentials. To extract the credentials, I opened the app, entered the master password and waited for at least 1 min. Then, I executed the tool to dump the credentials. The following screenshot illustrates the execution of the tool, when the relevant app is running. Hidden data are the relevant usernames and passwords.

![1password](https://github.com/efchatz/pandora/assets/43434138/fb18312d-22a4-416f-bde9-3150983d7571)


### Firefox

TBA.

### Dashlane 

https://github.com/efchatz/pandora/assets/43434138/3ff4faa8-8a1e-4293-a6ae-48db8ca1bdc1

The video was paused to shorten the size. First, Chrome is being opened, I entered the master password and waited for at least 1 min. After that, I executed pandora and waited to retrieve the credentials. The tool first search for entries and then for master username and password. It will need 2-3 min to find these credentials. As can be observed, all data are available, both master username and password, along with the username and password of three different entries. It should be noted that the relevant data are noted, i.e., the master password is noted as "masterPassword". The same follows the remaining data.

### Keeper

For Keeper, I started the app, entered the master password and executed the tool. The response of the tool was the following:

![keeper](https://github.com/efchatz/pandora/assets/43434138/24f41499-230a-4d6c-92b7-c94cf8678b17)

The tool could have also extract other entries, if a user had used them. For this reason, the second entry search return no credentials.

### LastPass

TBA.

### Roboform

TBA.

### Bitwarden

TBA.

### Norton

TBA.

### Bitdefender

TBA.

### Ironvest

TBA.

### Passwarden

The usual procedure was needed. As can be observed from the following screenshot, all data are noted with different keywords:

![passwarden](https://github.com/efchatz/pandora/assets/43434138/c785f0a4-0cc9-4b91-b1f8-1005dd026853)


### Avira

https://github.com/efchatz/pandora/assets/43434138/807d2d87-d240-47f1-8b35-41701cde4a06

The video was paused to shorten the size. First, Chrome is being opened from cmd, then waited for for at least 1 min. This means that an attacker could possibly start Chrome process without any user's interaction since Avira does not request for the user to enter their master password. After that, I executed pandora and waited to retrieve the credentials. The tool search for the relevant entries. As can be observed, every entry is showed in a specific line, i.e., the name of the site, the password and the relevant username. 

### PasswordBoss

https://github.com/efchatz/pandora/assets/43434138/f8f3b7fa-41f7-4182-9845-3430ec33486b

The video was paused to shorten the size. First, the passwordboss app is executed, I entered then the master password and minimized the app. After that, I executed the tool and waited 3-4 min. As can be observed, the tool retrieved all relevant entries. Some of them, like Amazon were empty, but others like Facebook, Google and a custom one named aegean were filled with the username and the password of the user. Usually, entries with data, contain the "[]" symbol. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- METHODOLOGY -->
## Methodology
The code is structured as follows:
1. The user chooses the relevant password manager or may request for additional input.
2. Based on the relevant password manager, the tool dumps the process into a file.
3. The dump file then is analyzed to identify any relevant pattern within it, with the purpose of extracting credentials.
4. In some cases, some junk data will be presented to the user. These data will be noted as unparsed characters. So, they can be easily recognized.
5. The user then can identify the credentials (either in cmd or in the relevant txt file).

It should be noted that in some cases password managers store in plaintext other types of data, like credit card details, addresses, Wi-Fi passwords etc. Users should be wary of such attacks and should not execute untrusted files, enable 2FA, etc.

Regarding the exploits, the methodology is simple, i.e., the purpose is to identify a pattern or a keyword that would pinpoint the relevant credentials within the dump file. Each password manager is different, so, each exploitation method differs. However, the concept is the same, i.e., finding the relevant pattern can pinpoint the credentials within this file. In some cases, the exploit finds when the credentials start and then gathers the next bytes, say 100. I did some extensive testing to identify these values correctly, but they may differ in a real-case scenario. Open an issue if you want to propose another password manager to be included in this tool.

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

* [Choose an Open Source License](https://choosealicense.com)
* [Img Shields](https://shields.io)
* [Best-README-Template](https://github.com/othneildrew/Best-README-Template)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/badge/Contributors-1-brightgreen?style=for-the-badge
[contributors-url]: https://github.com/efchatz/pandora/graphs/contributors
[forks-shield]: https://img.shields.io/badge/Forks-0-blue?style=for-the-badge
[forks-url]: https://github.com/efchatz/pandora/network/members
[stars-shield]: https://img.shields.io/badge/Stars-1-blue?style=for-the-badge
[stars-url]: https://github.com/efchatz/pandora/stargazers
[issues-shield]: https://img.shields.io/badge/Issues-0-lightgrey?style=for-the-badge
[issues-url]: https://github.com/efchatz/pandora/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/efchatz/pandora/LICENSE
[product-screenshot]: images/screenshot.png
[C++]: https://img.shields.io/badge/C++-blue?style=for-the-badge&logo=c++&logoColor=white
[C-url]: https://cplusplus.com/
