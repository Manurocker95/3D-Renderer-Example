#pragma once

#include "Node.h"

namespace ManuelRodriguezMatesanz
{
	class Camera : public Node
	{
		void update(float delta_time) override
		{
			Node::update(delta_time);
		}

		void render(Rasterizer< Color_Buffer > & rasterizer, const toolkit::Transformation3f parent_transform) override
		{
			Node::render(rasterizer, parent_transform);
		}
	};
}