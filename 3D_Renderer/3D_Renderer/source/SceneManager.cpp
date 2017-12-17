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

#include "SceneManager.h"

namespace ManuelRodriguezMatesanz
{
	// Static instance for singleton
	SceneManager* SceneManager::Instance = NULL;

	// Static method to return the singleton instance, if we don't have any instance, we create it
	SceneManager* SceneManager::instance()
	{
		if (!Instance)
			Instance = new SceneManager;

		return Instance;
	}

	// We delete the pointers when the SceneManager is destroyed so we don't have leaks
	SceneManager::~SceneManager()
	{
		delete window;
		delete view;
	}

	// Initialization of variables in SceneManager
	void SceneManager::Start(Window * _window)
	{
		running = true;
		window = _window;
	}

	void SceneManager::AddView(View * _view)
	{
		view = _view;
	}

	// Draw: It calls the paint method of the scene
	void SceneManager::Draw()
	{
		view->paint();
	}

	// Update: It calls the update method of the scene
	void SceneManager::Update(float delta_time)
	{
		view->update(delta_time);
	}

	// Check Inputs:  It calls the checkInput method of the scene for inputs and attend the global events such as closing the window
	void SceneManager::CheckInputs()
	{
		// Attend the window events:
		Event event;

		while (window->pollEvent(event))
		{
			// If the event is closing the window, we close it
			if (event.type == Event::Closed)
			{
				// We are not running the program anymore, so we close the window from main
				running = false;
			}

			if (event.type == Event::KeyPressed)
			{
				view->checkInputs(event);
			}
			
		}
	}

	// I'd have a MessageManager, but I'll set this here now
	// Show Error: Displays a Message with Window's API when an error is produced during the program exec
	// We can also save this error in a txt (Set true in settings.h)
	void SceneManager::show_error(std::string msg, std::string windowname, UINT button, bool savinginlog)
	{
		std::wstring wide_string = std::wstring(windowname.begin(), windowname.end());
		const wchar_t* window_name = wide_string.c_str();

		std::wstring stemp = std::wstring(msg.begin(), msg.end());
		LPCWSTR  error = (LPCWSTR)stemp.c_str();
		MessageBox(NULL, error, window_name, button);

		// If we can save the errorlog
		if (save_errorlog && savinginlog)
		{
			MessageBox(NULL, L"Se va a guardar el error en la carpeta Errorlog", L"Guardando Errorlog", button);
			// If errorlog folder doesn't exists, we create it
			_mkdir(errorLog_Folder);

			// We add the error to the errorlog file. If it doesn't exists, it's created
			std::ofstream outfile;
			outfile.open(errorlog, std::ios_base::app);

			if (outfile.good())
			{
				outfile << msg + "\n";
				outfile.close();
			}
		}
	}

	// We show an error and close the window.
	void SceneManager::show_error_and_close(std::string msg, std::string windowname, bool savinginlog)
	{
		show_error(msg, windowname, MB_OK, savinginlog);
		running = false;
	}

	// As we have only one instance for SceneManager and this method is (may be) called from anywhere, I set this here
	// Checks if a file (Need full path) exists in the computer. Example: Check if the OBJ exists.
	bool SceneManager::File_Checker(std::string fileName)
	{
		std::ifstream infile(fileName);
		return infile.good();
	}
}