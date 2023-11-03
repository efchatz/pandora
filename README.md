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
    <a href="https://github.com/efchatz/pandora/videos/passwordboss">View Demo (Passwordboss)</a>
    ·
    <a href="https://github.com/efchatz/pandora/videos/dashlane">View Demo (Dashlane)</a>
    ·
    <a href="https://github.com/efchatz/pandora/videos/avira">View Demo (Avira)</a>
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

This is a red team tool that would assist in gathering credentials from different password managers. They are separated into three categories, Windows 10 desktop applications, browsers, and browser plugins. In this release (v0.5), the tool supports 14 password managers, with 18 different implementations (e.g., the tool could extract credentials either from the desktop app, or the browser plugin of the same product). So, the purpose of this tool is to provide an additional attack vector in red team engagements, since many users are using password managers.

This is not a completely new concept. It has been well-known for some time that there is no de facto way for desktop applications to be protected against such attacks. However, and to the best of my knowledge, this is the first time such a tool has been presented to the public. Feel free to provide any feedback and/or recommendations/improvements.

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

To use this tool, simply execute the compiled executable in the relevant host. Based on the password manager, there are some requirements for the tool to be able to extract credentials. However, I kept in most cases password managers who needed basic interaction to store their credentials in the memory of their process. The following table depicts a high-level view of the tool's capabilities. Note that Firefox and the relevant Firefox plugins of password managers may not work correctly. They need further research for the tool to be able to extract the credentials in every case.

| Name         | Location   | Credentials               | Browser             | Stability    |
|--------------|------------|---------------------------|---------------------|--------------|
| Chromium     | Browser    | Entries                   | Chrome/MSEdge/Brave | Yes          |
| 1Password    | App/Plugin | Master(Both)/Entries(App) | Chrome/Firefox      | Yes          |
| Firefox      | Browser    | Entries                   | N/A                 | No           |
| Dashlane     | Plugin     | Master/Entries            | Chrome/Firefox      | Yes (Chrome) |
| Keeper       | App        | Entries                   | N/A                 | Yes          |
| LastPass     | Plugin     | Master/Entries            | Chrome              | Yes          |
| Roboform     | Plugin     | Entries                   | Chrome              | Yes          |
| Bitwarden    | Plugin     | Master/Entries            | Chrome              | Yes          |
| Norton       | Plugin     | Entries                   | Chrome              | Yes          |
| Bitdefender  | Plugin     | Master/Entries            | Chrome              | Yes          |
| Ironvest     | Plugin     | Entries                   | Chrome              | Yes          |
| Passwarden   | App        | Entries                   | N/A                 | Yes          |
| Avira        | Plugin     | Entries                   | Chrome              | Yes          |
| Passwordboss | App        | Entries                   | N/A                 | Yes          |


Regarding the extraction of credentials, some exploits are based on a specific number of bytes, to extract the credentials. So, maybe, in some cases, this number must be increased to extract this information correctly. During the experiments, common usernames and passwords were used. So, in most cases, this would be sufficient.

Another note is relevant to the version of each password manager of a browser plugin. If a change is made in the code and affects the process, the tool will be unable to identify these credentials. So, keep in mind that there is a possibility to mishandle some credentials if an older/newer version of the tool is used, or a different OS (tested on Windows 10 Pro).

In most cases, the following will be needed to extract the credentials:
1. The relevant app (browser or desktop app) is up, unlocked, and running.
2. In some cases, like in Chromium browsers, an interaction needs to be made with either the relevant plugin or the embedded password manager of the browser.
3. In other cases, some password managers keep these credentials in memory in cleartext, even after being locked. This behavior was noted in Keeper.
4. In case of 1Password, high integrity privilege is required. So, execute the .exe with high privileges, or provide the dump file as input.

It is sufficient to mention that since user behavior is to open such tools and leave them be, it would provide an additional attack vector for lateral movement. Another keypoint is that most of these tools will automatically be locked when the user is completely idle. This means that even if the app or browser plugin is idle and the user is using their host for other activities, these apps will not be locked. Also, in some cases, it is possible to completely avoid user interaction. For instance, some browser plugins remain unlocked for some time. As a result, it is possible to start this process from cmd, without needing the user and extract the credentials. Check Avira's video example to understand this process.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- METHODOLOGY -->
## Methodology


<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information. This tool is provided as is, for educational purposes. Use it only when you have written permission to do so, under a red team assessment.

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
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/efchatz/pandora/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/efchatz/pandora/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/efchatz/pandora/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/efchatz/pandora/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/efchatz/pandora/LICENSE
[product-screenshot]: images/screenshot.png
[C++]: https://img.shields.io/badge/C++-blue?style=for-the-badge&logo=c++&logoColor=white
[C-url]: https://cplusplus.com/
