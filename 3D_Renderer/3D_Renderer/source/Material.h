#pragma once

#include "tiny_obj_loader.h"
#include "Texture.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace ManuelRodriguezMatesanz
{
	class Material
	{
	private:

		Texture textures;
		//Color color;

		float ka;
		float kd;
		float ks;
		float kp;

	public:
		Material(tinyobj::material_t & Material);
	};
}