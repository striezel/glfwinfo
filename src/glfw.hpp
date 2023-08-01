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

#ifndef GLFWINFO_GLFW_HPP
#define GLFWINFO_GLFW_HPP

#include <string>

/** \brief Gets the WebP library version.
 *
 * \return Returns a string containing the GLFW version, e.g. "1.2.3".
 */
std::string glfw_version();

/** \brief Show information about OpenGL renderer and vendor on standard output.
 *
 * \remarks This needs an active OpenGL context to work properly.
 */
void show_open_gl_info();

/** \brief Show information about all monitors on standard output.
 */
void show_monitors();

#endif // GLFWINFO_GLFW_HPP
