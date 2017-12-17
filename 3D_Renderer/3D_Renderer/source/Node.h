#pragma once

#include "tiny_obj_loader.h"
#include "Color_Buffer_Rgba8888.hpp"
#include "Rasterizer.hpp"
#include <memory>
#include "Vector.hpp"
#include "Translation.hpp"

namespace ManuelRodriguezMatesanz
{
	using namespace std;
	
	class Node
	{
		
	protected:
		
		typedef Color_Buffer_Rgba8888 Color_Buffer;

		toolkit::Transformation3f transform;
		toolkit::Transformation3f combined_transform;
		vector <shared_ptr <Node>> children;
		std::string node_name;
		bool loaded;
	public:

		virtual void update(float delta_time)
		{
			for (auto & child : children)
			{
				child->update(delta_time);
			}
		}


		virtual void render( Rasterizer< Color_Buffer > & rasterizer, const toolkit::Transformation3f parent_transform)
		{
			toolkit::Transformation3f final_transform = parent_transform * transform;
			for (auto & child : children) 
			{
				child->render(rasterizer, final_transform);
			}
		}

		void add_child(shared_ptr<Node> & child)
		{
			children.push_back(child);
		}

		vector <shared_ptr <Node>> get_children()
		{
			return children;
		}

		void set_name(std::string name)
		{
			node_name = name;
		}

		bool loaded_correctly() { return loaded; }

		void translate(const toolkit::Translation3f & displacement);

		void scale(float scale);

		void rotate_around_x(const float & angle);

		void rotate_around_y(const float & angle);

		void rotate_around_z(const float & angle);

		
	};
}