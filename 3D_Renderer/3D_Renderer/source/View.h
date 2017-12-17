
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

#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "Node.h"
#include "Camera.h"
#include "Object_pool.hpp"
#include "Settings.h"

#include "Rasterizer.hpp"
#include "Color_Buffer_Rgb565.hpp"
#include "Color_Buffer_Rgba8888.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Vector.hpp"
#include "Projection.hpp"

#include <SFML/Window.hpp>		// Cargamos la ventana
#include <SFML/OpenGL.hpp>		// OpenGL para sfml

#include "rapidxml.hpp"
#include <windows.h>

namespace ManuelRodriguezMatesanz
{

	using std::vector;
	using toolkit::Point4i;
	using toolkit::Point4f;
	using toolkit::Vector3f;

	using sf::Window;
	using namespace rapidxml;
	using namespace toolkit;
	using namespace sf;

	class View
	{
	private:

		typedef Color_Buffer_Rgba8888 Color_Buffer;
		typedef Color_Buffer::Color   Color;
		typedef Point4f               Vertex;
		typedef vector< Vertex >      Vertex_Buffer;
		typedef vector< int    >      Index_Buffer;
		typedef vector< Color  >      Vertex_Colors;

	private:

		size_t width;
		size_t height;

		Color_Buffer               Color_buffer;
		Rasterizer< Color_Buffer > rasterizer; 

	public:
		~View();
		View (size_t width, size_t height, std::string xml_path, Window * window);
		void default_scene();
		bool generate_gameobject(std::string file_name, float scale, Vector3f position, Vector3f rotation, bool moving);
		void update(float delta_time);
		void paint();
		void checkInputs(Event event);
		bool LoadDataFromXML(std::string xml_path, Window & window);
		Vector3f string_to_vector3f(std::string s);
		float string_to_float(std::string);
		bool View::string_to_bool(std::string s);
	private:
		
		Window * window;
		std::shared_ptr<Node> scene;		// The Scene is also a node
		std::shared_ptr<Node> camera;		// The Camera is also a node
		toolkit::Projection3f projection;	// Projection of the camera.
		bool showing_default_scene;
	};

}

#endif
