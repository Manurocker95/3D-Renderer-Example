#pragma once

// Rasterizer y Buffers
#include "Color_Buffer_Rgba8888.hpp"
#include "Rasterizer.hpp"

// Tiny Obj
#include "tiny_obj_loader.h"

//Otros
#include "Transformation.hpp"
#include "Vector.hpp"

namespace ManuelRodriguezMatesanz
{
	using toolkit::Vector3f;

	class Mesh
	{

	private:
	
		typedef Color_Buffer_Rgba8888 Color_Buffer;
		typedef Color_Buffer::Color   Color;
		typedef Point4f               Vertex;
		typedef std::vector< Vertex > Vertex_Buffer;
		typedef std::vector< int    > Index_Buffer;
		typedef std::vector< Color  > Vertex_Colors;

		Vertex_Buffer     original_vertices; //positions de la mesh
		Index_Buffer      original_indices;
		Vertex_Colors     original_colors;
		Vertex_Buffer     transformed_vertices;
		std::vector< Point4i > display_vertices;

	private:
		size_t width;
		size_t height;

		float scale;
		Vector3f position;
		Vector3f rotation;
		Vector3f light_vector;
		tinyobj::shape_t test_mesh;

	public:
		Mesh();
		Mesh(tinyobj::shape_t & mesh, tinyobj::attrib_t * attribute);
		Mesh(tinyobj::shape_t & mesh, tinyobj::attrib_t * attribute, tinyobj::material_t materials);
		void update(float delta_time, const toolkit::Transformation3f transform);
		void render(Rasterizer <Color_Buffer> & rasterizer, const toolkit::Transformation3f transform);
		bool is_frontface(const Vertex * const projected_vertices, const int * const indices);
		float Calculate_Light_Intensity(const Vector3f & l, const float & divisor1, const Point4f & p1, const Point4f & p2, const Point4f & p3);
		size_t clip_polygon(const toolkit::Point4i * vertices_data, int * indices, int * otherindices, toolkit::Point4i clipped_pol [10]);
	};
}