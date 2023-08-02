# glfwinfo - a command-line tool to show information about GLFW

[![GitHub CI Clang status](https://github.com/striezel/glfwinfo/workflows/Clang/badge.svg)](https://github.com/striezel/glfwinfo/actions)
[![GitHub CI GCC status](https://github.com/striezel/glfwinfo/workflows/GCC/badge.svg)](https://github.com/striezel/glfwinfo/actions)
[![GitHub CI MSYS2 status](https://github.com/striezel/glfwinfo/workflows/MSYS2/badge.svg)](https://github.com/striezel/glfwinfo/actions)

`glfwinfo` is a program that prints information about GLFW to the standard
output.

## Building from source

### Prerequisites

To build glfwinfo from source you need a C++ compiler with support for C++17,
CMake 3.8 or later, OpenGL, and the GLFW library.
pkg-config is required to make it easier to find compiler options for the
installed libraries.

It also helps to have Git, a distributed version control system, on your build
system to get the latest source code directly from the Git repository.

All of that can usually be installed be typing

    apt-get install cmake g++ git libgl-dev libglfw3-dev pkg-config

or

    yum install cmake gcc-c++ git glfw-devel pkgconfig

into a root terminal.

### Getting the source code

Get the source directly from Git by cloning the Git repository and change to
the directory after the repository is completely cloned:

    git clone https://gitlab.com/striezel/glfwinfo.git
    cd glfwinfo

That's it, you should now have the current source code on your machine.

### Build process

The build process is relatively easy, because CMake does all the preparations.
Starting in the root directory of the source, you can do the following steps:

    mkdir build
    cd build
    cmake ../
    make -j4

If you want to run the test suite, too, then there is one more step:

    ctest -V

## Usage

```
glfwinfo [OPTIONS]

Shows information about the current system using GLFW.

options:
  -? | --help        - Shows this help message.
  -v | --version     - Shows version information.
  --skip-video-modes - Do not show available video modes of monitors.
```

## History of changes

A changelog is provided as [separate file](./changelog.md).

## Copyright and Licensing

Copyright 2023  Dirk Stolle

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
