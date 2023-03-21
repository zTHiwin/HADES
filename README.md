#Hiwin API Development Environmental System (HADES)

HADES is a project directory system which makes use of batch files, cmake, make or visual studios,
    in order to make, build and run your applications

## Usage

The directory is not a necessary format, the CMakeLists and batch files
should give an understanding of what is necessary for linking and including.

The HIMC_API.dll, msvcp110.dll, and msvcr110.dll are necessary to 
include with the application(.exe) after successfully building the project.

## Installation

The following software are need for building:
    Win32 (x86):
        Most Recent Version of Visual Studios
        CMake version 3.26+

    x64:
        Most recent version of mingw64
        CMake version 3.26+
        Most recent version of make

'''**It is recommended to use chocolatey to install these software**'''
This can be installed using Windows Powershell (under admin mode) using the following command:
'''bash
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
'''
