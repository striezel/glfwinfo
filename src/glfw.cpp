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

#include "glfw.hpp"
#include <iostream>
#include <string_view>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

std::string glfw_version()
{
  int major = -1;
  int minor = -1;
  int rev = -1;
  glfwGetVersion(&major, &minor, &rev);
  return std::to_string(major).append(".")
      + std::to_string(minor).append(".")
      + std::to_string(rev);
}

void show_open_gl_info()
{
  std::cout << "OpenGL version:  " << glGetString(GL_VERSION) << "\n"
            << "OpenGL vendor:   " << glGetString(GL_VENDOR) << "\n"
            << "OpenGL renderer: " << glGetString(GL_RENDERER) << "\n";
}

void show_monitor_name(GLFWmonitor* mon, const std::string_view indentation)
{
  std::cout << indentation << "Name: ";
  const char* name = glfwGetMonitorName(mon);
  if (name == nullptr)
    std::cout << "unknown\n";
  else
    std::cout << name << '\n';
}

void show_monitor_size(GLFWmonitor* mon, const std::string_view indentation)
{
  std::cout << indentation << "Physical size (width x height): ";
  int width = -1;
  int height = -1;
  glfwGetMonitorPhysicalSize(mon, &width, &height);
  if ((width == 0) && (height == 0))
    std::cout << "unknown\n";
  else
    std::cout << width << " mm x " << height << " mm\n";
}

void show_monitor_position(GLFWmonitor* mon, const std::string_view indentation)
{
  std::cout << indentation << "Virtual position: ";
  int x = -1;
  int y = -1;
  (void) glfwGetError(nullptr); // clears any previous error codes
  glfwGetMonitorPos(mon, &x, &y);
  const int error_code = glfwGetError(nullptr);
  if ((error_code != GLFW_NO_ERROR) && (x == 0) && (y == 0))
    std::cout << "unknown\n";
  else
    std::cout << "X = " << x << ", Y = " << y << '\n';
}

void show_monitor_work_area(GLFWmonitor* mon, const std::string_view indentation)
{
  std::cout << indentation << "Work area: ";
  int x = -1;
  int y = -1;
  int width = -1;
  int height = -1;
  glfwGetMonitorWorkarea(mon, &x, &y, &width, &height);
  if ((x == 0) && (y == 0) && (width == 0) && (height == 0))
    std::cout << "unknown\n";
  else
    std::cout << "X = " << x << ", Y = " << y
              << ", Width = " << width << ", Height = " << height << '\n';
}

void show_video_mode(const GLFWvidmode mode, const std::string_view indentation)
{
  std::cout << '\n' << indentation
            << mode.width << " x " << mode.height << ", ";
  const int total_bits = mode.redBits + mode.greenBits + mode.blueBits;
  std::cout << total_bits << " bits colour depth (R" << mode.redBits << "/G"
            << mode.greenBits << "/B" << mode.blueBits << "), "
            << mode.refreshRate << " Hz";
}

void show_video_modes(GLFWmonitor* mon, const std::string_view indentation)
{
  std::cout << indentation << "Video modes: ";
  int count = -1;
  const auto modes = glfwGetVideoModes(mon, &count);
  if (modes == nullptr)
  {
    std::cout << " none found\n";
    return;
  }
  std::cout << count << " modes found";

  const auto new_indentation = std::string("    ").append(indentation);
  for (int i = 0; i < count; ++i)
  {
    show_video_mode(modes[i], new_indentation);
  }
  std::cout << "\n" << indentation << "Current video mode: ";
  const auto current_mode = glfwGetVideoMode(mon);
  if (current_mode == nullptr)
  {
    std::cout << " unknown\n";
    return;
  }
  show_video_mode(*current_mode, new_indentation);
  std::cout << '\n';
}

void show_monitor(GLFWmonitor* mon, const std::string_view indentation, const VideoModes video_modes)
{
  show_monitor_name(mon, indentation);
  show_monitor_size(mon, indentation);
  show_monitor_position(mon, indentation);
  show_monitor_work_area(mon, indentation);
  if (video_modes == VideoModes::Show)
  {
    show_video_modes(mon, indentation);
  }
}

void show_monitors(const VideoModes video_modes)
{
  std::cout << "Monitors:\n";
  int count = 0;
  const auto monitors = glfwGetMonitors(&count);
  if (monitors == nullptr)
  {
    std::cout << "    None found\n";
    return;
  }

  std::cout << "    Found " << count << " monitor(s).\n";
  for (int i = 0; i < count; ++i)
  {
    std::cout << "\nMonitor " << (i + 1) << ":\n";
    show_monitor(monitors[i], "    ", video_modes);
  }
}
