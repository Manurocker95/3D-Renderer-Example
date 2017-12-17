#include "Model.h"
#include "SceneManager.h"
// Other
#include <cmath>
#include <cassert>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>
#include "tiny_obj_loader.h"
#include "Settings.h"

namespace ManuelRodriguezMatesanz
{
	// Default Model for Default Scene (Z-Buffer one)
	Model::Model()
	{
		this->width = window_width;
		this->height = window_height;
		this->moving = true;
		this->scale = default_scale;
		this->position[0] = 0;
		this->position[1] = 0;
		this->position[2] = -10;
		this->rotation[0] = 0;
		this->rotation[1] = 0.025f;
		this->rotation[2] = 0;

		meshes.reserve(1);
		// We have just one object in default Scene (As it is Z-Buffer example)
		for (size_t i = 0; i < 1; i++)
		{
			std::shared_ptr<Mesh> m(new Mesh());
			meshes.push_back(m);
		}
	}

	Model::Model(std::string obj_file_path, size_t width, size_t height, float scale, Vector3f position, Vector3f rotation, bool moving)
		:
		width(width),
		height(height),
		position(position),
		rotation(rotation),
		scale(scale),
		moving(moving)
	{
		//Load data from obj with tinyobj library
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> obj_meshes;
		std::vector<tinyobj::material_t> materials;
		std::string error;
		bool can_load = tinyobj::LoadObj(&attrib, &obj_meshes, &materials, &error, obj_file_path.c_str());

		if (can_load)
		{
			// If there's any error message, we show it and (maybe) save it in errorlog to have it for the future
			if (!error.empty())
			{

				SceneManager::instance()->show_error("No se puede cargar correctamente el OBJ con ruta:  " + obj_file_path + "   debido al error:\n\n" + error+"\n\nEl programa va a continuar.", "Error al cargar el OBJ en clase Model");
			}

			materials.reserve(obj_meshes.size());
			meshes.reserve(obj_meshes.size());
			
			for (size_t i = 0; i < obj_meshes.size(); i++)
			{
				//std::shared_ptr<Mesh> m (new Mesh(obj_meshes[i], &attrib));
				std::shared_ptr<Mesh> m(new Mesh(obj_meshes[i], &attrib, materials[obj_meshes[i].mesh.material_ids.at(i)]));
				meshes.push_back(m);
			}
			
			loaded = true;
		}
		else
		{
			SceneManager::instance()->show_error("No se puede cargar el OBJ. Revisa el XML.", "Fatal Error", MB_OK, false);
			loaded = false;
		}
	}

	//Method called from Check Inputs in View.cpp - 0 = X, 1 = y, 2 = z
	void Model::Rotate(float rotation, int axis)
	{
		this->rotation[axis] += rotation;
	}

	void Model::update(float delta_time)
	{
		Node::update(delta_time);

		if (moving)
		{
			static float angleX = 0.f;
			static float angleY = 0.f;
			static float angleZ = 0.f;

			angleX += rotation[0];
			angleY += rotation[1];
			angleZ += rotation[2];

			Translation3f translation(position[0], position[1], position[2]);
			transform = Projection3f(5, 15, 60, float(width) / float(height));

			Node::translate(translation);
			Node::rotate_around_x(angleX);
			Node::rotate_around_y(angleY);
			Node::rotate_around_z(angleZ);
		}
		else
		{
			Translation3f translation(position[0], position[1], position[2]);
			transform = Projection3f(5, 15, 20, float(width) / float(height));

			Node::translate(translation);
			Node::rotate_around_x(rotation[0]);
			Node::rotate_around_y(rotation[1]);
			Node::rotate_around_z(rotation[2]);
		}

		Node::scale(scale);

		for (auto & mesh : meshes)
		{
			mesh->update(delta_time, transform);
		}
	}

	void Model::render(Rasterizer <Color_Buffer> & rasterizer, const toolkit::Transformation3f parent_transform)
	{
		Node::render(rasterizer, parent_transform);
		for (auto & mesh : meshes) 
		{
			mesh->render(rasterizer, this->transform);
		}
	}
}