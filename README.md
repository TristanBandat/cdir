[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![Pull Requests][pulls-shield]][pulls-url]
[![MIT License][license-shield]][license-url]
[![closed Pull Requests][closed_pulls-shield]][closed_pulls-url]
[![closed Issues][closed_issues-shield]][closed_issues-url]
<!-- [![LinkedIn][linkedin-shield]][linkedin-url] -->



<!-- PROJECT LOGO -->
<p align="center">
  <!-- <a href="https://github.com/TristanBandat/cdir">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a> -->
  <h3 align="center">CDIR</h3>
  <p align="center">
    Script for creating new folders with consecutive numbering
    <br />
    <a href="https://github.com/TristanBandat/cdir"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <!-- <a href="https://github.com/TristanBandat/cdir">View Demo</a>
    · -->
    <a href="https://github.com/TristanBandat/cdir/issues">Report Bug</a>
    ·
    <a href="https://github.com/TristanBandat/cdir/issues">Request Feature</a>
  </p>
<!-- </p> -->



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
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
        <!-- <li><a href="#prerequisites">Prerequisites</a></li> -->
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <!-- <li><a href="#acknowledgements">Acknowledgements</a></li> -->
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

The goal of this project is to create a function that makes folder creating much faster.<br>
The function detects on its own if there is an existing folder structure 
`[FOLDERNAME]_[NUMBER]` and creates a folder with the directory name 
`[FOLDERNAME]_[NUMBER+1]`.<br>
This works with the function call in the corresponding folder only - 
no additional arguments required.


### Built With

* [PyCharm](https://www.jetbrains.com/pycharm/)
* [CLion](https://www.jetbrains.com/clion/)
* [Vim](https://www.vim.org/)



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

<!-- ### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ``` -->

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/TristanBandat/cdir.git
   ```
2. Choose between the Python or the C version.<br>
The Python version will get updates first but is a little slower and needs a Python 3 Interpreter
   (at least Python 3.6). <br>The C version is more stable but the releases take a little bit longer.
   

3. Copy the chosen file in a separate folder<br><br>
_Note: If you do not have a folder called `.bin` in your home directory you should create one first 
   (recommended) or copy the files directly into your home directory (not recommended)._<br><br>
Python:
   ```sh
   cp cdir.py ~/.bin/.
   ```
   C:<br>
   _Note: If may have to compile the included C file for your system!_
   ```sh
   cp C_development/cdir_dev.out ~/.bin/.
   ```


4. Paste function call into your rc file<br><br>
   Python:
   ```sh
   function cdir() {                                                                                      
      python3 ~/.bin/cdir.py "$*"                                                                   
   }
   ```
   C:
   ```sh
   function cdir() {                                                                                      
      ~/.bin/cdir_dev.out "$*"                                                                   
   }
   ```


5. Update your rc file, restart your terminal or restart your system


   

<!-- USAGE EXAMPLES -->
## Usage

If there exists at least one directory with the correct naming convention, one can simply call 
the program without additional arguments. _CDIR_ will automatically choose the correct directory name.

   ```sh
   ~/Folder/% cdir
   ```

_Note:_ _CDIR will always choose the directory with the highest occurrence if you do not parse
an additional argument with the preferred name._

If the function gets a directory name as argument, the function detects any existing folders 
with that name (if they exist) and creates a new directory with the given name and 
the next available number:

   ```sh
   ~/Folder/% cdir New_Folder
   ```

_Note:_ _If the directory with given name does not exist, the numbering will start at 0._

If the function gets a directory name and a number as argument, the function will, additionally to the folder detection,
create as many directories in consecutive numbering as specified.<br>
For example if you want to create 10 folders with the name 'Exercise' just type:

   ```sh
   ~/Folder/% cdir Exercise 10
   ```


### Flags

* Help<br>
Visit the help page with one of the following flags:<br>
  <b>Python:</b>
    <ul>
        <li>-h</li>
        <li>-? </li>
        <li>--help</li>
        <li>help</li>
    </ul>
  <b>C:</b>
    <ul>
        <li>-h</li>
        <li>--help</li>
    </ul>


* Version<br>
Get the current version of CDIR:<br>
  <ul>
    <li>-v</li>
    <li>-V</li>
    <li>--version</li>
  </ul>


<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/TristanBandat/cdir/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create.<br> 
Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

_Note: Look into the TODO file for open features and in which release they will be included._



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Tristan Bandat - [@TBandat](https://twitter.com/TBandat) - tristan.bandat@gmail.com

Project Link: [https://github.com/TristanBandat/cdir](https://github.com/TristanBandat/cdir)



<!-- ACKNOWLEDGEMENTS 
## Acknowledgements

* []()
* []()
* []()

-->



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/TristanBandat/cdir.svg?style=for-the-badge
[contributors-url]: https://github.com/TristanBandat/cdir/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/TristanBandat/cdir.svg?style=for-the-badge
[forks-url]: https://github.com/TristanBandat/cdir/network/members
[stars-shield]: https://img.shields.io/github/stars/TristanBandat/cdir.svg?style=for-the-badge
[stars-url]: https://github.com/TristanBandat/cdir/stargazers
[issues-shield]: https://img.shields.io/github/issues/TristanBandat/cdir.svg?style=for-the-badge
[issues-url]: https://github.com/TristanBandat/cdir/issues
[pulls-shield]: https://img.shields.io/github/issues-pr/TristanBandat/cdir.svg?style=for-the-badge
[pulls-url]: https://github.com/TristanBandat/cdir/pulls
[license-shield]: https://img.shields.io/github/license/TristanBandat/cdir.svg?style=for-the-badge
[license-url]: https://github.com/TristanBandat/cdir/blob/master/LICENSE.txt
[closed_pulls-shield]: https://img.shields.io/github/issues-pr-closed/TristanBandat/cdir?style=for-the-badge
[closed_pulls-url]: https://github.com/TristanBandat/cdir/pulls?q=is%3Apr+is%3Aclosed
[closed_issues-shield]: https://img.shields.io/github/issues-closed/TristanBandat/cdir?style=for-the-badge
[closed_issues-url]: https://github.com/TristanBandat/cdir/issues?q=is%3Aissue+is%3Aclosed
<!-- [linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/TristanBandat -->
