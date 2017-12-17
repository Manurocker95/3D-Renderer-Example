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

#include "Settings.h"
#include <SFML/Window.hpp>		// Cargamos la ventana
#include <SFML/OpenGL.hpp>		// OpenGL para sfml

#include <iostream>
#include "View.h"
#include "SceneManager.h"

using namespace sf;
using namespace ManuelRodriguezMatesanz;

// Arguments: 0 = program, 1 = Scene
int main(int number_of_arguments, const char * args[])
{
	// if we don't send 2 arguments, we show an error
	if (number_of_arguments != 2)
	{
		// We show the error and close the window 
		SceneManager::instance()->show_error("Hay que indicar un archivo de escena.","Error de inicializacion");
		return -1;
	}
	
	// We take the window name from the path of the scene file
	std::string window_name = args[1];
	size_t offset = window_name.find_last_of('\\') + 1;
	window_name = window_name.substr(offset, (window_name.length() - 4) - offset);

	// Create the window and the view that will be shown within the window:
	Window window(VideoMode(window_width, window_height), window_name, Style::Titlebar | Style::Close, ContextSettings(32));
	
	// We initialize the SceneManager. For being simple, we will use View Class as Scene class. 
	SceneManager::instance()->Start(&window);

	View view(window_width, window_height, args[1], &window);
	SceneManager::instance()->AddView(&view);


	// Initialization:
	window.setVerticalSyncEnabled(true);

	glDisable(GL_BLEND);
	glDisable(GL_DITHER);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GLdouble(window_width), 0, GLdouble(window_height), -1, 1);

	Clock timer;
	float delta_time = 0.017f;          // ~60 fps

	do
	{
		if (SceneManager::instance()->getRunning())
		{
			// Check the player inputs by the manager
			SceneManager::instance()->CheckInputs();

			// Update the scene by the manager:
			SceneManager::instance()->Update(delta_time);

			// Repaint the scene by the manager:
			SceneManager::instance()->Draw();

			// Swap the OpenGL buffers:
			window.display();

			delta_time = (delta_time + timer.getElapsedTime().asSeconds()) * 0.5f;
		}

	} while (SceneManager::instance()->getRunning());

	// Close the application:
	return (EXIT_SUCCESS);
}
