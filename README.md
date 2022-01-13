<div id="top"></div>


[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/MiniJoko/NightStander">
    <img src="resources/img/nightstander.png" alt="Logo" width="200">
  </a>

<h3 align="center">NightStander</h3>

  <p align="center">
    A small device for viewing Nightscout data and sending remote overrides to Loop
    <br />
    <a href="https://github.com/MiniJoko/NightStander"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/MiniJoko/NightStander">View Demo</a>
    ·
    <a href="https://github.com/MiniJoko/NightStander/issues">Report Bug</a>
    ·
    <a href="https://github.com/MiniJoko/NightStander/issues">Request Feature</a>
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
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://example.com)


<p align="right">(<a href="#top">back to top</a>)</p>



### Built With

* [Platform.io](https://platformio.org/)
* [Nightscout API](https://nightscout.info/)
* [image2cpp](https://javl.github.io/image2cpp/)


<p align="right">(<a href="#top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started
The following instructions should be able to guide through the process of building this device yourself

### Prerequisites
The following components are needed to build this device:
https://sizable.se/P.JKY/esp32
https://sizable.se/P.LZ7/0.96%22-i2c-oled-vit

knapplänk

motståndslänk


* plattformio
  ```sh

  ```

### Installation

1. Install Visual Studio Code
   * Download from https://code.visualstudio.com/
   * Follow instructions to install for your operating system
   * Click on Extensions in the left-hand menu and search for "PlatformIO IDE"
   * Click Install

2. Clone the repo
   * Open a new terminal and paste the following:

     ```
     git clone https://github.com/minijoko/NightStander.git
     ```
   * Navigate into the new folder that was created with the clone command with:
     ```
     cd NightStander
     ```

3. Install PIO libraries
   * In the same terminal paste this: 
     ```sh
     pio lib install
     ```
4. Build to ESP
   * You should now be able to build to your ESP32 by connecting it to your computer and pressing Build
   

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage



<p align="right">(<a href="#top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap


See the [open issues](https://github.com/minijoko/NightStander/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- CONTACT -->
## Contact
---
### Daniel Mini Johansson  
daniel@codebymini.se

[![Linkedin][linkedin]][linkedin-url-daniel]

[![Github][github]][github-url-daniel]


---

### Jonathan Koitsalu

[![Linkedin][linkedin]][linkedin-url-joko]

[![Github][github]][github-url-joko]

---

Project Link: [https://github.com/minijoko/NightStander](https://github.com/minijoko/NightStander)

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin]: https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white

[github]: https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white

[contributors-shield]: https://img.shields.io/github/contributors/minijoko/NightStander.svg?style=for-the-badge
[contributors-url]: https://github.com/minijoko/NightStander/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/minijoko/NightStander.svg?style=for-the-badge
[forks-url]: https://github.com/minijoko/NightStander/network/members
[stars-shield]: https://img.shields.io/github/stars/minijoko/NightStander.svg?style=for-the-badge
[stars-url]: https://github.com/minijoko/NightStander/stargazers
[issues-shield]: https://img.shields.io/github/issues/minijoko/NightStander.svg?style=for-the-badge
[issues-url]: https://github.com/minijoko/NightStander/issues
[license-shield]: https://img.shields.io/github/license/minijoko/NightStander.svg?style=for-the-badge
[license-url]: https://github.com/minijoko/NightStander/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url-daniel]: https://www.linkedin.com/in/daniel-johansson-4b099219a/
[product-screenshot]: images/screenshot.png
[linkedin-url-joko]: https://www.linkedin.com/in/jonathan-koitsalu-5885b3160/
[github-url-joko]: https://github.com/jonathankoitsalu/
[github-url-daniel]: https://github.com/codebymini
<!-- README template from https://github.com/othneildrew/Best-README-Template -->