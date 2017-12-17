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

#include "View.h"
#include "SceneManager.h"
#include <cmath>
#include <cassert>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include "Model.h"
#include "Scene.h"
#include <Vector.hpp>

using namespace toolkit;

namespace ManuelRodriguezMatesanz
{

	View::View(size_t width, size_t height, std::string xml_path, Window * window)
		:
		width(width),
		height(height),
		Color_buffer(width, height),
		rasterizer(Color_buffer),
		projection(1.f, 1000.f, 60.f, float(width) / height)
	{
		this->window = window;
		
		showing_default_scene = false;

		if (!LoadDataFromXML(xml_path, *window))
		{
			if (close_if_loading_error)
			{
				SceneManager::instance()->show_error_and_close("No se ha podido leer el XML correctamente.\nRevisa que todo esté correcto y vuelva a ejecutar el programa.","Fatal Error", false);
			}
			else
			{
				showing_default_scene = true;
				SceneManager::instance()->show_error("No se han podido cargar los datos correctamente.\nSe va a cargar una escena por defecto.", "Error encontrado", MB_OK, false);
				default_scene();
			}
		}
		
	}

	View::~View()
	{
		//delete (window);
	}

	bool View::LoadDataFromXML(std::string xml_path, Window & window)
	{
		xml_document<> doc;
		xml_node<> * root_node;

		bool can_read = false;

		// We open the xml
		std::ifstream xml_file(xml_path);

		if (xml_file.good())
		{
			can_read = true;
		}
		else
		{
			return false;
		}

		if (can_read)
		{
			vector<char> buffer((std::istreambuf_iterator<char>(xml_file)), std::istreambuf_iterator<char>());
			buffer.push_back('\0');

			// Parseamos el buffer parseando la librería a Doc
			doc.parse<0>(&buffer[0]);

			// Encontramos el primer nodo (Nodo raíz = Scene)
			root_node = doc.first_node("scene");

			// Si la escena tiene nombre, se lo ponemos a la ventana, sino se llama "scene"
			if (root_node->first_attribute("name") && root_node->first_attribute("name")->value_size() > 0)
			{
				window.setTitle(root_node->first_attribute("name")->value());
			}

			std::shared_ptr<Scene> current_scene(new Scene());
			scene = current_scene;

			std::shared_ptr<Camera> cam(new Camera());
			camera = cam;

			scene->add_child(camera);

			// strings parsed

			std::string file_name;
			Vector3f position, rotation;
			float scale;
			bool moving;
			// We iterate every object of the XML
			for (xml_node<> * object_node = root_node->first_node("object"); object_node; object_node = object_node->next_sibling())
			{
				// We check if file node exists in XML
				if (object_node->first_node("file"))
				{
					xml_node<> * file_node = object_node->first_node("file");
					file_name = file_node->value();
				}
				else
				{
					return false;
				}

				// We check if position node exists in XML
				if (object_node->first_node("position"))
				{
					xml_node<> * position_node = object_node->first_node("position");
					position = string_to_vector3f(position_node->value());
				}
				else
				{
					return false;
				}

				// We check if rotation node exists in XML
				if (object_node->first_node("rotation"))
				{
					xml_node<> * rotation_node = object_node->first_node("rotation");
					rotation = string_to_vector3f(rotation_node->value());
				}
				else
				{
					return false;
				}

				// We check if scale node exists in XML
				if (object_node->first_node("scale"))
				{
					xml_node<> * scale_node = object_node->first_node("scale");
					scale = string_to_float(scale_node->value());
				}
				else
				{
					return false;
				}

				// We check if scale node exists in XML
				if (object_node->first_node("moving"))
				{
					xml_node<> * moving_node = object_node->first_node("moving");
					moving = string_to_bool(moving_node->value());
				}
				else
				{
					return false;
				}

				// We check if we can generate the object 
				if (!generate_gameobject(file_name, scale, position, rotation, moving))
				{
					return false;
				}

				std::cout << std::endl;
			}
		}

		return true;
	}

	///Object Generation by files loaded from external file
	bool View::generate_gameobject(string file_name, float scale, Vector3f position, Vector3f rotation, bool moving)
	{
		//We check if the object exits in default path 
		if (!SceneManager::instance()->File_Checker(default_obj_path + file_name))
		{
			SceneManager::instance()->show_error("El objeto " + file_name + " no existe en la ruta " + default_obj_path + " y por lo tanto no puede ser cargado.", "Error al intentar cargar el archivo OBJ.");
			return false;
		}
		else
		{
			// We have to add it to Scene, now we only use one and no graph yet
			std::shared_ptr<Node> generated_model(new Model(default_obj_path + file_name, width, height, scale, position, rotation, moving));
			
			//If we cannot load the model because something
			if (!generated_model->loaded_correctly())
			{
				// We return so we can load the default scene or close the window (by the variable in Settings.h)
				return false;
			}
			else
			{
				scene->add_child(generated_model);
				return true;
			}
		}

		return true;
	}

	bool View::string_to_bool(std::string s)
	{
		bool ret = false;

		if (s.compare("true") == 0)
		{
			ret = true;
		}
		else
		{
			ret = false;
		}

		return ret;
	}

	/// Convert string to float
	float View::string_to_float(std::string s)
	{
		std::string::size_type sz;
		float ret = std::stof(s, &sz);

		return ret;
	}

	/// Convert string to Vector3 of floats
	Vector3f View::string_to_vector3f(std::string s)
	{
		std::vector<float> v3_values;
		std::stringstream ss(s);

		float i;

		while (ss >> i)
		{
			v3_values.push_back(i);

			if (ss.peek() == ',' || ss.peek() == ' ')
			{
				ss.ignore();
			}
		}

		Vector3f v;

		v[0] = v3_values.at(0);
		v[1] = v3_values.at(1);
		v[2] = v3_values.at(2);

		return v;
	}

	// 
	void View::default_scene()
	{
		// Create the scene
		std::shared_ptr<Scene> current_scene(new Scene());
		scene = current_scene;

		std::shared_ptr<Camera> cam(new Camera());
		camera = cam;

		scene->add_child(camera);

		// Create default game object and add it to the scene, so we have a scene graph
		std::shared_ptr<Node> generated_model(new Model());
		scene->add_child(generated_model);
	}

	void View::update(float delta_time)
	{
		scene->update(delta_time);
	}

	void View::paint()
	{
		// Se borra el framebúffer y se dibujan los triángulos:

		rasterizer.clear();

		scene->render(rasterizer, projection);
	}

	void View::checkInputs(Event event)
	{
		switch (event.key.code)
		{
		case Keyboard::Right:
			scene->rotate_around_x(1);
			break;
		case Keyboard::Left:
			scene->rotate_around_x(-1);
			break;
		}
	}
}
