/*
 -------------------------------------------------------------------------------
    This file is part of glfwinfo.
    Copyright (C) 2023  Dirk Stolle

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
 -------------------------------------------------------------------------------
*/

#include <iostream>
#include <GLFW/glfw3.h>
#include "glfw.hpp"

/** \brief exit code for invalid command line parameters */
const int rcInvalidParameter = 1;

/** \brief exit code for GLFW-related failure */
const int rcGlfwError = 2;

void showVersion()
{
  std::cout << "glfwinfo, version 0.2.0, 2023-08-02\n";
}

void showHelp()
{
  std::cout << "glfwinfo [OPTIONS]\n"
            << "\n"
            << "Shows information about the current system using GLFW.\n"
            << "\n"
            << "options:\n"
            << "  -? | --help        - Shows this help message.\n"
            << "  -v | --version     - Shows version information.\n"
            << "  --skip-video-modes - Do not show available video modes of monitors.\n";
}

int main(int argc, char** argv)
{
  VideoModes video_modes = VideoModes::Show;
  if ((argc > 1) && (argv != nullptr))
  {
    for (int i = 1; i < argc; ++i)
    {
      if (argv[i] == nullptr)
      {
        std::cerr << "Error: Parameter at index " << i << " is null pointer!\n";
        return rcInvalidParameter;
      }
      const std::string param(argv[i]);
      if ((param == "-v") || (param == "--version"))
      {
        showVersion();
        return 0;
      }
      else if ((param == "-?") || (param == "/?") || (param == "--help"))
      {
        showHelp();
        return 0;
      }
      else if ((param == "--skip-video-modes") || (param == "--no-video-modes"))
      {
        if (video_modes == VideoModes::Skip)
        {
          std::cerr << "Error: " << param << " was specified more than once.\n";
          return rcInvalidParameter;
        }
        video_modes = VideoModes::Skip;
      }
      else
      {
        std::cerr << "Error: Unknown parameter " << param << "!\n"
                  << "Use --help to show available parameters." << std::endl;
        return rcInvalidParameter;
      }
    }
  } // if arguments are there

  std::cout << "GLFW version " << glfw_version() << std::endl;
  if (!glfwInit())
  {
    std::cerr << "Error: Initialization of GLFW failed!\n";
    return rcGlfwError;
  }

  // We need a window to get a GL context, but we do not want to show the
  // window to the user, so make it invisible.
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  GLFWwindow* offscreen = glfwCreateWindow(320, 240, "", nullptr, nullptr);
  if (nullptr == offscreen)
  {
    std::cerr << "Error: Creation of GLFW context failed!\n";
    return rcGlfwError;
  }
  glfwMakeContextCurrent(offscreen);
  show_open_gl_info();

  show_monitors(video_modes);

  glfwDestroyWindow(offscreen);
  glfwTerminate();
  return 0;
}
