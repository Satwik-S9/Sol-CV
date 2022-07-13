# Computer Vision Algorithms and Methods

- [Computer Vision Algorithms and Methods](#computer-vision-algorithms-and-methods)
  - [1. Description](#1-description)
  - [2. QuickStart](#2-quickstart)
    - [2.1 Setting Up the Environment | Python](#21-setting-up-the-environment--python)
    - [2.2 Setting up Environment | C++](#22-setting-up-environment--c)

> <span><u>@author</u></span>: [Satwik Srivastava](#) <br>
> <span><u>Last Revision Date</u></span>: 06 | 07 | 2022 <br>
> `version` : 0.1.0

## 1. Description
This is a repo of all my favourite Computer Vision Projects. This Repo Currently Contains.
1. [Emotion Detector](https://github.com/Satwik-S9/Sol-CV/tree/main/object-detection/emotion-detector)
2. [Basic-CV Algorithms written from Scratch in C++](https://github.com/Satwik-S9/Sol-CV/tree/main/basic-cv)

## 2. QuickStart

### 2.1 Setting Up the Environment | Python

#### For `basic-cv`

  - Using the provided `environment.yml` file and `conda`.
    - for a global environment.

    ```bash
      conda env create --file environment.yml
    ```
    - for local environment.

    ```bash
      conda env create --prefix PATH/TO/ENV/ENV_NAME --file environment.yml
    ```

  - Or Manually install packages listed in the file.

**NOTE:** For The setup of environments of other projects see their repective READMEs.

### 2.2 Setting up Environment | C++

  - Follow Instructions from here [(Linux](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html), [Windows)](https://docs.opencv.org/4.x/d3/d52/tutorial_windows_install.html) to install opencv on your respective system for C++.
  - If you are using Visual Studio / VSCode Windows the setup is easy and the guides online are sufficient.
  - For Linux, copy the `Makefile` to setup compilation. 
