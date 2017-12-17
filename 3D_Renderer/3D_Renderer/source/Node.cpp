#include "Node.h"

#include <cmath>
#include <cassert>
#include <Vector.hpp>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>

namespace ManuelRodriguezMatesanz
{
	void Node::translate(const toolkit::Translation3f & displacement) 
	{
		transform = transform * toolkit::Translation3f(displacement);
	}

	void Node::scale(float scale)
	{
		transform = transform * toolkit::Scaling3f(scale, scale, scale);
	}

	void Node::rotate_around_x(const float & angle)
	{
		toolkit::Rotation3f rotation;
		rotation.set<toolkit::Rotation3f::AROUND_THE_X_AXIS >(angle);
		transform = transform * rotation;
	}

	void Node::rotate_around_y(const float & angle)
	{
		toolkit::Rotation3f rotation;
		rotation.set<toolkit::Rotation3f::AROUND_THE_Y_AXIS >(angle);
		transform = transform * rotation;
	}

	void Node::rotate_around_z(const float & angle)
	{
		toolkit::Rotation3f rotation;
		rotation.set<toolkit::Rotation3f::AROUND_THE_Z_AXIS >(angle);
		transform = transform * rotation;
	}
}