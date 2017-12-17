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
#include <SFML/OpenGL.hpp>		// OpenGL para sfml
#include <SFML/Window.hpp>		// Cargamos la ventana
#include <sstream>
#include <fstream>
#include <iostream>
#include <direct.h>  
#include <stdlib.h>  
#include <stdio.h> 
#include "windows.h"
#include "View.h"

using namespace sf;

namespace ManuelRodriguezMatesanz
{
	class SceneManager
	{
	public:
		static SceneManager* instance();
		~SceneManager();
		void Start(Window * window);
		void AddView(View * view);
		void CheckInputs();
		void Draw();
		void Update(float delta_time);
		void show_error(std::string msg = "Se ha encontrado un error", std::string windowname = "Error encontrado", UINT button = MB_OK, bool savinginlog = true);
		void show_error_and_close(std::string msg = "Se ha encontrado un error", std::string windowname = "Fatal Error", bool savinginlog = true);
		bool getRunning() { return running; }
		void setRunning(bool value) { running = value; }
		bool File_Checker(std::string fileName);

	private:
		Window * window;
		View * view;
		bool running;
		SceneManager() {};  // Private so that it can  not be called
		SceneManager(SceneManager const&) {};             // copy constructor is private
		SceneManager& operator=(SceneManager const&) {};  // assignment operator is private
		static SceneManager* Instance;
	};
}