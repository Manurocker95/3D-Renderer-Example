#pragma once

#include "Node.h"
#include <iostream>
#include "Material.h"
#include "Mesh.h"
#include <string>
#include "Vector.hpp"
#include "tiny_obj_loader.h"
#include "SceneManager.h"

namespace ManuelRodriguezMatesanz
{
	using toolkit::Vector3f;
	using namespace std;

	class View;

	class Model : public Node
	{
	private:

		std::vector <shared_ptr<Material>> materials;
		std::vector <shared_ptr<Mesh>> meshes;
		size_t width;
		size_t height;
		Vector3f position;
		Vector3f rotation;
		float scale;
		bool moving;
	public:

		Model();
		Model(std::string obj_file_path, size_t width, size_t height, float scale, Vector3f position, Vector3f rotation, bool moving);
		void update(float delta_time) override;
		void render(Rasterizer <Color_Buffer> & rasterizer, const toolkit::Transformation3f parent_transform) override;
		void Rotate(float rotation, int axis);
	};
}