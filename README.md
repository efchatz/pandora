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
    ·
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

This is a red team tool that would assist in gathering credentials from different password managers. They are separated into three categories, Windows 10 desktop applications, browsers, and browser plugins. This may work on other OS, like Linux, but it is not tested. In this release (v0.5), the tool supports 14 password managers, with 18 different implementations (e.g., the tool could extract credentials either from the desktop app, or the browser plugin of the same product). So, the purpose of this tool is to provide an additional attack vector in red team engagements, since many users are using password managers. Three different videos have been uploaded to assist in understanding how this tool works.

This is not a completely new concept. It has been well-known for some time that there is no de facto way for desktop applications to be protected against such attacks. However, and to the best of my knowledge, this is the first time such a tool has been presented to the public. Feel free to provide any feedback and/or recommendations/improvements. Regarding fixing these issues, most vendors responded that this issue is out-of-scope for them since the attacker needs local access or AV/EDR should protect the user against such attacks. Although one browser plugin and two desktop apps may provide fixes, so their exploits will be released at a later date (they are still under disclosure).

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![C++][C++]][C-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

Simply, clone the code, and compile it. For the development phase, Visual Studio 2022 was used.



### Installation


1. Clone the repo.
   ```sh
   git clone https://github.com/efchatz/pandora.git
   ```
2. Install Visual Studion 2022, with all C++ dependencies.
3. Open the project.
4. In Project->Properties->Linker->Input, choose in the "Configuration" dropdown "All Configurations".
5. Add in the "Additional Dependencies" the "DbgHelp.lib".
6. In the same tab, in "Ignore All Default Libraries", choose "No".
7. Press "OK".
8. Build this project.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

To use this tool, simply execute the compiled executable in the relevant host and type the name of the password manager. Based on the password manager, there are some requirements for the tool to be able to extract credentials. However, I kept in most cases password managers who needed basic interaction to store their credentials in the memory of their process. After executing the tool, it will automatically dump the relevant process based on the chosen password manager, print the credentials in the cmd, and save them into a file (the location of the file is the current folder of the .exe). Three videos have been uploaded to assist in how this tool works. The videos depict the phase in which an attacker would be able to gather the credentials from a password manager. In the case of Avira and similar password managers, this can be done without any user interaction.

The following table depicts a high-level view of the tool's capabilities. Note that Firefox and the relevant Firefox plugins of password managers may not work correctly. They need further research for the tool to be able to extract the credentials in every case. This is due to the fact that Firefox changes its pattern with each execution.

| Name         | Location   | Credentials               | Browser             | Stability    | Version    |
|--------------|------------|---------------------------|---------------------|--------------|------------|
| Chromium     | Browser    | Entries                   | Chrome/MSEdge/Brave | Yes          |121.0.6106.0|
| 1Password    | App/Plugin | Master(Both)/Entries(App) | Chrome/Firefox      | Yes          |8.10.18     |
| Firefox      | Browser    | Entries                   | N/A                 | No           |119.0       |
| Dashlane     | Plugin     | Master/Entries            | Chrome/Firefox      | Yes (Chrome) |6.2344.1    |
| Keeper       | App        | Entries                   | N/A                 | Yes          |16.10.9     |
| LastPass     | Plugin     | Master/Entries            | Chrome              | Yes          |4.123.0     |
| Roboform     | Plugin     | Entries                   | Chrome              | Yes          |9.5.2.0     |
| Bitwarden    | Plugin     | Master/Entries            | Chrome              | Yes          |2023.10.1   |
| Norton       | Plugin     | Entries                   | Chrome              | Yes          |8.1.0.73    |
| Bitdefender  | Plugin     | Master/Entries            | Chrome              | Yes          |1.3.0       |
| Ironvest     | Plugin     | Entries                   | Chrome              | Yes          |9.8.15      |
| Passwarden   | App        | Entries                   | N/A                 | Yes          |3.3         |
| Avira        | Plugin     | Entries                   | Chrome              | Yes          |2.19.14.4461|
| Passwordboss | App        | Entries                   | N/A                 | Yes          |5.5.5104    |


Regarding the extraction of credentials, some exploits are based on a specific number of bytes, to extract the credentials. So, maybe, in some cases, this number must be increased to extract this information correctly. During the experiments, common usernames and passwords were used. So, in most cases, this would be sufficient.

Another note is relevant to the version of each password manager of a browser plugin. If a change is made in the code and affects the process, the tool may be unable to identify these credentials. So, keep in mind that there is a possibility to mishandle some credentials if an older/newer version of the tool is used, or a different OS is running (tested on Windows 10 Pro).

In most cases, the following will be needed to extract the credentials:
1. The relevant app (browser or desktop app) is up, unlocked, and running.
2. In some cases, like in Chromium browsers, an interaction needs to be made with either the relevant plugin or the embedded password manager of the browser.
3. In other cases, some password managers keep these credentials in memory in cleartext, even after being locked. This behavior was noted in Keeper.
4. In case of 1Password, high integrity privilege is required. So, execute the .exe with high privileges, or provide the dump file as input.

It is sufficient to mention that since user behavior is to open such tools and leave them be, it would provide an additional attack vector for lateral movement. Another keypoint is that most of these tools will automatically be locked when the user is completely idle. This means that even if the app or browser plugin is idle and the user is using their host for other activities, these apps will not be locked. Also, in some cases, it is possible to completely avoid user interaction. For instance, some browser plugins remain unlocked for some time. As a result, it is possible to start this process from cmd, without needing the user and extract the credentials. Check Avira's video example to understand this process.

It should be noted that there were some cases like KeePass and StickyPassword, in which no credentials were found to be cleartext within the memory. Also, in some cases like Kaspersky, I was unable to identify a pattern to draw the credentials from the memory, while they were stored in plaintext.

We are working on releasing an academic paper that will describe the experiments and any other relevant details.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- METHODOLOGY -->
## Methodology
The code is structured as follows:
1. The user chooses the relevant password manager.
2. Based on the relevant password manager, the tool dumps the process into a file.
3. The dump file then is analyzed to identify any relevant pattern within it, with the purpose of extracting credentials.
4. In some cases, some junk data will be presented to the user. These data will be noted as unparsed characters. So, they can be easily recognized.
5. The user then can identify the credentials (either in cmd or in the relevant txt file).

It should be noted that in some cases password managers store in plaintext other types of data, like credit card details, addresses, etc. Users should be wary of such attacks and do not execute untrusted files.

Regarding the exploits, the methodology is simple, i.e., the purpose is to identify a pattern or a keyword that would pinpoint the relevant credentials within the dump file. Each password manager is different, so, each exploitation method differs. However, the concept is the same, i.e., finding the relevant pattern can pinpoint the credentials within this file. In some cases, the exploit finds when the credentials start and then gathers the next bytes, say 100. I did some extensive testing to identify these values correctly, but they may differ in a real-case scenario.

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information. This tool is provided as is, for educational purposes. Use it only when you have written permission to do so, say in a red team engagement.

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
