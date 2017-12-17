
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

#include "Texture.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

namespace ManuelRodriguezMatesanz
{
	using namespace std;
	using std::map;
	using std::string;

	class Texture_Pool
	{
		map < string, shared_ptr < Texture> >textures;

	public:

		Texture * load(const string & path)
		{
			
			if (textures.count(path) > 0)
			{
				return textures [path].get();
			}
			else
			{
				Texture * texture = Texture::load_image (path);

				if (texture)
				{
					textures.insert({ path, shared_ptr<Texture> (texture)});

					return texture;
				}
			}

			return nullptr;
		}
	};
}