# isomod-GUI
A simple GUI that simplifies the use of isomod. (Intended for PaRappa the Rapper 2 Modding)

# Installing and using
You can build from source or you can use a pre-built executable file (if available).

## From source
To build isomod-gui, you need the following dependencies on your system: **Qt5** (or newer), **CMake 3.5** (or newer), and a C++ compiler. At the root of the directory, you will need to run these commands:

    mkdir build
    cd build
    cmake ..
    make
    make install (not necessary but can be used if wanted)

Output will be in the root directory in a folder called "out". (isomod-gui/out)

## Pre-built
If there are any executables pre-built and available, you can find them on the [Releases](https://github.com/CryptoCANINE/isomod-gui/releases) page. Pre-built executables are planned to be there for Windows (x86/x64) and Linux (x86/x64). This can be ran on macOS, but it must be built from source on a Macintosh.

# What is isomod?
isomod is an application that allows the injection of files into ISO images (ISO9660) without re-building the image (kind of like in UltraISO). This tool is used here for making the modding of PaRappa the Rapper 2 easier and quicker.

# To-do
- Polish the GUI
- Create Windows Release
- Make things work and look better overall
- Remove Sweets, and add more Noodles
