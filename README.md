# Hiwin API Development Environmental System (HADES)

HADES is a project directory system which makes use of batch files, cmake, make, and mingw (or visual studios),
    in order to make, build and run your applications which include the HIwin Motion Controller (HIMC). For use with the Simulator, install the  
    HIMC companion application iAStudio2.0.1 from:  
```bash
https://www.hiwinmikro.tw/Handlers/DownloadFile.ashx?id=ba60a075-b44b-48eb-925f-411c4e45141c&lang=en  
```

## Usage:

The directory is not a necessary format, the CMakeLists and batch files
should give an understanding of what is necessary for linking and including.

The HIMC_API.dll, msvcp110.dll, and msvcr110.dll are necessary to 
include with the application(.exe) after successfully building the project.

## Installation:

The following software are need for building:  
&emsp;&ensp; Win32 (x86):  
&emsp;&emsp;&emsp; - Most Recent Version of Visual Studios  
&emsp;&emsp;&emsp; - CMake version 3.26+  
&emsp;&ensp; x64:  
&emsp;&emsp;&emsp; - Most recent version of mingw64  
&emsp;&emsp;&emsp; - CMake version 3.26+  
&emsp;&emsp;&emsp; - Most recent version of make  

**It is recommended to use chocolatey to install these software**

***This can be installed using Windows Powershell (under admin mode) using the following command:***
```bash
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```
***From here run the following commands***
```bash
choco install mingw  
choco install cmake  
choco install make
```  
**In order to use these modules, the following binary directories will need to be added to  
environmental variable PATH:  
C:\ProgramData\chocolatey\lib\mingw\tools\install\mingw64\bin  
C:\ProgramData\chocolatey\lib\make\bin  
C:\Program Files\CMake\bin**

## How to use HADES:

HADES is a platform that is meant to be used as a reference or as a platform to build your project off of.  
In order to compile/build the project, run the build batch file for Win32 or x64 depending on your operating system. 

If compiling for x64 OS, you can use the run batch file, or you can go to the /build directory and run the application.   
If compiling for x86 OS, you and go to the /build/debug directory and run the application from there. 

For use with the iAStudio Simulator, comment the HIMC_ConnectCtrl and uncomment HIMC_ConnectToSimulator

## How to change Application (.exe) Name:
Open build/x64/CMakeLists.txt or build/Win32/CMakeLists.txt  
In line 2, change the "HADESApp" to "desired app name goes here"
