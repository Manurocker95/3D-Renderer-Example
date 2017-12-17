/*
This file is part of the first practice of Graphic Programming

Started 21 / 02 / 2017

Copyright (C) 2017 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.

> email: manuelrodriguezmatesanz@gmail.com

*/

#pragma once

//Scene settings:
static const size_t window_width = 800;										// Window Width
static const size_t window_height = 600;									// Window Height
static const size_t max_game_objects = 100;									// Maximum game objects that can be loaded
static const float default_scale = 0.02f;									// Default scale (for Z-Buffer example, only used in default scene)
static const float extra_light = 0.3f;										// Extra light added in Mesh.cpp when calculating lights
static const char * default_obj_path = "Assets\\Graphics\\Models\\";		// Default path for objs. So you can pass only the name of the obj
static const char * default_skybox_path = "Assets\\Graphics\\Skybox\\";		// Default path for Skybox
static const char * errorLog_Folder = "Errorlogs\\";						// Folder for saving errorlogs
static const char * errorlog = "Errorlogs\\ErrorLog.txt";					// Errorlog path (Including errorlog folder)
static const bool clip_polygons = false; 									// Boolean that checks if we cut the triangles or not. Setting to false, may cause bugs when the polygons go out from the viewport.					
static const bool save_errorlog = true;										// Boolean that checks if we save or not the error log after showing an error
static const bool close_if_loading_error = false;							// Boolean that checks if we have to close the window when showing an error or load a default object