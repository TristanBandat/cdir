<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** github_username, repo_name, twitter_handle, email, project_title, project_description
-->


<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/TristanBandat/cdir">
<!--    <img src="images/logo.png" alt="Logo" width="80" height="80"> -->
  </a>

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
</p>



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
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
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
_Note: If you do not have a folder called `.bin` in your home directory you should create one first or 
   copy the files directly into your home directory (not recommended)._<br><br>
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

Of course the function has a help page (-h or -? or --help or help). <br>
In the C Version only '-h' displays the help page.

_For more examples, please refer to the [Documentation](https://example.com)_



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/TristanBandat/cdir/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



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
[contributors-shield]: https://img.shields.io/github/contributors/TristanBandat/repo.svg?style=for-the-badge
[contributors-url]: https://github.com/TristanBandat/repo/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/TristanBandat/repo.svg?style=for-the-badge
[forks-url]: https://github.com/TristanBandat/repo/network/members
[stars-shield]: https://img.shields.io/github/stars/TristanBandat/repo.svg?style=for-the-badge
[stars-url]: https://github.com/TristanBandat/repo/stargazers
[issues-shield]: https://img.shields.io/github/issues/TristanBandat/repo.svg?style=for-the-badge
[issues-url]: https://github.com/TristanBandat/repo/issues
[license-shield]: https://img.shields.io/github/license/TristanBandat/repo.svg?style=for-the-badge
[license-url]: https://github.com/TristanBandat/repo/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/TristanBandat
