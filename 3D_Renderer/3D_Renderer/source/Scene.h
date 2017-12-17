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


/* 
The scene implements Node to have a full graph like this:

<Scene>
	<Camera></Camera>
	
	<Light></light>
	
	<Gameobject1>
		<subgameobject1></subgameobject1>
	</Gameobject1>

	<Gameobject2>
		<subgameobject2></subgameobject2>
	</Gameobject2>
</Scene>

*/
#pragma once
#include "Node.h"
namespace ManuelRodriguezMatesanz
{
	class Scene : public Node
	{
	public:
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
