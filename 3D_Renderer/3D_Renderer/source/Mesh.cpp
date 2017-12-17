#include "Mesh.h"

// Other
#include "View.h"
#include <cmath>
#include <cassert>
#include <Scaling.hpp>
#include <Rotation.hpp>
#include <Projection.hpp>
#include <Translation.hpp>

namespace ManuelRodriguezMatesanz
{
#pragma region z-buffer-example
	//Default Mesh: For default scene (Cube turning around - The same as Z-Buffer)
	Mesh::Mesh()
	{
		// Se definen los datos de los vértices:

		{
			light_vector[0] = 0.25f;
			light_vector[1] = 0.5f;
			light_vector[2] = 0.25f;

			static const int vertices[][4] =
			{
				{ -4, -4, +4, 1 },      // 0    // vértices del cubo
				{ +4, -4, +4, 1 },      // 1
				{ +4, +4, +4, 1 },      // 2
				{ -4, +4, +4, 1 },      // 3
				{ -4, -4, -4, 1 },      // 4
				{ +4, -4, -4, 1 },      // 5
				{ +4, +4, -4, 1 },      // 6
				{ -4, +4, -4, 1 },      // 7
				{ -5, -5,  0, 1 },      // 8    // vértices de los polígonos cortantes
				{ +5, -5,  0, 1 },      // 9
				{ +5, +5,  0, 1 },      // 10
				{ -5, +5,  0, 1 },      // 11
				{ 0, -5, +5, 1 },      // 12
				{ 0, +5, +5, 1 },      // 13
				{ 0, +5, -5, 1 },      // 15
				{ 0, -5, -5, 1 },      // 14
			};

			// Se cargan en un búffer los datos del array:

			size_t number_of_vertices = sizeof(vertices) / sizeof(int) / 4;

			original_vertices.resize(number_of_vertices);

			for (size_t index = 0; index < number_of_vertices; index++)
			{
				original_vertices[index] = Vertex(vertices[index]);
			}

			transformed_vertices.resize(number_of_vertices);
			display_vertices.resize(number_of_vertices);

			// Se definen los datos de color de los vértices:

			static const int colors[][3] =
			{
				{ 255,   0,   0 },      // 0
				{ 0, 255,   0 },      // 1
				{ 0,   0, 255 },      // 2
				{ 0,   0, 255 },      // 3
				{ 255, 255,   0 },      // 4
				{ 255,   0, 255 },      // 5
				{ 255,   0,   0 },      // 6
				{ 255,   0,   0 },      // 7
				{ 175, 175, 175 },      // 8
				{ 175, 175, 175 },      // 9
				{ 175, 175, 175 },      // 10
				{ 175, 175, 175 },      // 11
				{ 225, 225, 225 },      // 12
				{ 225, 225, 225 },      // 13
				{ 225, 225, 225 },      // 14
				{ 225, 225, 225 },      // 15
			};

			size_t number_of_colors = sizeof(colors) / sizeof(int) / 3;

			assert(number_of_colors == number_of_vertices);             // Debe haber el mismo número
																		// de colores que de vértices
			original_colors.resize(number_of_colors);

			for (size_t index = 0; index < number_of_colors; index++)
			{
				original_colors[index].set(colors[index][0], colors[index][1], colors[index][2]);
			}

			// Se generan los índices de los triángulos:

			static const int triangles[][3] =
			{
				{ 0,  1,  2 },         // cube front
				{ 0,  2,  3 },
				{ 4,  0,  3 },         // cube left
				{ 4,  3,  7 },
				{ 5,  4,  7 },         // cube back
				{ 5,  7,  6 },
				{ 1,  5,  6 },         // cube right
				{ 1,  6,  2 },
				{ 3,  2,  6 },         // cube top
				{ 3,  6,  7 },
				{ 0,  4,  5 },         // cube bottom
				{ 0,  5,  1 },
				{ 8,  9, 10 },         // middle frontface
				{ 8, 10, 11 },
				{ 10,  9,  8 },         // middle backface
				{ 11, 10,  8 },
				{ 12, 13, 14 },         // middle leftface
				{ 12, 14, 15 },
				{ 14, 13, 12 },         // middle rightface
				{ 15, 14, 12 },
			};

			size_t number_of_triangles = sizeof(triangles) / sizeof(int) / 3;

			original_indices.resize(number_of_triangles * 3);

			Index_Buffer::iterator indices_iterator = original_indices.begin();

			for (size_t triangle_index = 0; triangle_index < number_of_triangles; triangle_index++)
			{
				*indices_iterator++ = triangles[triangle_index][0];
				*indices_iterator++ = triangles[triangle_index][1];
				*indices_iterator++ = triangles[triangle_index][2];
			}
		}
	}
#pragma endregion

	Mesh::Mesh(tinyobj::shape_t & meshShape, tinyobj::attrib_t * attribute) : test_mesh(meshShape)
	{
		// We set the mesh stuff as we did in Z-Buffer:

		// Original vertices.
		original_vertices.reserve(attribute->vertices.size());
		//Original colors
		original_colors.resize(attribute->vertices.size());

		for (size_t i = 0, counter = 0; i < attribute->vertices.size(); counter++, i += 3)
		{
			int attr[4] = { attribute->vertices[i], attribute->vertices[i + 1], attribute->vertices[i + 2], 1 };
			original_vertices.push_back(Vertex(attr));

			int o_colors[4] = { rand() % 255, rand() % 255 , rand() % 255, 1 };
			original_colors[counter].set(o_colors[0], o_colors[1], o_colors[2]);
		}

		for (size_t i = 0; i < meshShape.mesh.indices.size(); i++)
		{
			original_indices.push_back(meshShape.mesh.indices.at(i).vertex_index);
		}

		//Transformed vertices 
		transformed_vertices.resize(original_vertices.size());
		//Displayed vertices
		display_vertices.resize(original_vertices.size());

		light_vector[0] = 0.25f;
		light_vector[1] = 0.5f;
		light_vector[2] = 0.25f;
	}

	Mesh::Mesh(tinyobj::shape_t & meshShape, tinyobj::attrib_t * attribute, tinyobj::material_t materials) : test_mesh (meshShape)
	{
		light_vector[0] = 0.25f;
		light_vector[1] = 0.5f;
		light_vector[2] = 0.25f;

		// We set the mesh stuff as we did in Z-Buffer:

		// Original vertices.
		original_vertices.reserve(attribute->vertices.size());
		//Original colors
		original_colors.resize(attribute->vertices.size());

		for (size_t i = 0, counter = 0; i < attribute->vertices.size(); counter++, i += 3)
		{
			int attr[4] = { attribute->vertices[i], attribute->vertices[i + 1], attribute->vertices[i + 2], 1 };
			original_vertices.push_back(Vertex(attr));

			original_colors[counter].set(materials.diffuse[0]*255, materials.diffuse[1] * 255, materials.diffuse[2] * 255);
		}

		for (size_t i = 0; i < meshShape.mesh.indices.size(); i++)
		{
			original_indices.push_back(meshShape.mesh.indices.at(i).vertex_index);
		}

		//Transformed vertices 
		transformed_vertices.resize(original_vertices.size());
		//Displayed vertices
		display_vertices.resize(original_vertices.size());
	}
	
	void Mesh::update(float delta_time, const toolkit::Transformation3f transform)
	{
		// We set the transformation by the parent: Model. The rest is the same from Z-Buffer.
		for (size_t index = 0, number_of_vertices = original_vertices.size(); index < number_of_vertices; index++)
		{
			// We multiply all the original vertices by the transform matrix got from the parent and
			// we save the result in other vertex buffer:
			Vertex & vertex = transformed_vertices[index] = Matrix44f(transform) * Matrix41f(original_vertices[index]);

			float divisor = 1.f / vertex[3];

			vertex[0] *= divisor;
			vertex[1] *= divisor;
			vertex[2] *= divisor;
			vertex[3] = 1.f;
		}
	}

	void Mesh::render(Rasterizer<Color_Buffer> & rasterizer, const toolkit::Transformation3f transform)
	{
		// Se convierten las coordenadas transformadas y proyectadas a coordenadas
		// de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
		// La coordenada Z se escala a un valor suficientemente grande dentro del
		// rango de int (que es lo que espera fill_convex_polygon_z_buffer).

		width = rasterizer.get_color_buffer().get_width();
		height = rasterizer.get_color_buffer().get_height();

		Scaling3f        scaling = Scaling3f(float(width / 2), float(height / 2), 100000000.f);
		Translation3f    translation = Translation3f(float(width / 2), float(height / 2), 0.f);
		Transformation3f transformation = translation * scaling;

		for (size_t index = 0, number_of_vertices = transformed_vertices.size(); index < number_of_vertices; index++)
		{
			display_vertices[index] = Point4i(Matrix44f(transformation) * Matrix41f(transformed_vertices[index]));
		}

		// We set this here in case we want to modify the light somewhere
		float divisor_escalar1 = sqrt((light_vector[0] * light_vector[0]) + (light_vector[1] * light_vector[1]) + (light_vector[2] * light_vector[2]));

		Point4i clipped_polygon[10];
		static const int clipped_indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		for (int * indices = original_indices.data(), *end = indices + original_indices.size(); indices < end; indices += 3)
		{
			if (is_frontface(transformed_vertices.data(), indices))
			{
				// Se establece el color del polígono a partir del color de su primer vértice:
				//rasterizer.set_color(original_colors[*indices]);

				/* TO DO: Clip_polygon method to clip polygons when needed */
				if (clip_polygons)
				{
					size_t clipped_polygon_size = clip_polygon(display_vertices.data(), indices, indices + 3, clipped_polygon);

					if (clipped_polygon_size > 2)
					{
						float intensity = Calculate_Light_Intensity(light_vector, divisor_escalar1, transformed_vertices[*indices], transformed_vertices[*(indices + 1)], transformed_vertices[indices[2]]);

						intensity += 0.3f; // 0.3f: Intensidad ambiente

						if (intensity < 0)
						{
							intensity = 0;
						}

						if (intensity > 1)
						{
							intensity = 1;
						}

						Color o_color = original_colors[*indices];
						Color n_color;

						n_color.set(o_color.data.component.r*intensity, o_color.data.component.g*intensity, o_color.data.component.b*intensity);
						rasterizer.set_color(n_color);

						// Se rellena el polígono:
						rasterizer.fill_convex_polygon_z_buffer(clipped_polygon, clipped_indices, clipped_indices + clipped_polygon_size);
					}
				}
				else
				{

					// We calculate the intensity of light

					float intensity = Calculate_Light_Intensity(light_vector, divisor_escalar1, transformed_vertices[*indices], transformed_vertices[*(indices + 1)], transformed_vertices[*(indices + 2)]);

					intensity += extra_light;

					// if we have less than 0, we set it to 0 (min)
					if (intensity < 0)
					{
						intensity = 0;
					}

					// If we have more than 1, we set it to 1 (max)
					if (intensity > 1)
					{
						intensity = 1;
					}

					// We are going to set a new color based in the old color multiplied by the intensity
					Color o_color = original_colors[*indices];
					Color n_color;

					// We set the new color and send it to the rasterizer so it can render it
					n_color.set(o_color.data.component.r*intensity, o_color.data.component.g*intensity, o_color.data.component.b*intensity);
					rasterizer.set_color(n_color);

					// Se rellena el polígono:
					rasterizer.fill_convex_polygon_z_buffer(display_vertices.data(), indices, indices + 3);
				}
			}
		}

		// Se copia el framebúffer oculto en el framebúffer de la ventana:

		rasterizer.get_color_buffer().gl_draw_pixels(0, 0);
	}

	// Light intensity calculator
	float Mesh::Calculate_Light_Intensity(const Vector3f & l, const float & divisor1, const Point4f & p1, const Point4f & p2, const Point4f & p3)
	{
		float ret = 1;

		//				P2
		//			   /  \
		//		      P1--P3 	

		// First vector: between Point One and Point 2
		Vector3f p1p2;
		p1p2[0] = p2[0] - p1[0];
		p1p2[1] = p2[1] - p1[1];
		p1p2[2] = p2[2] - p1[2];

		// Second vector: between Point One and Point 3 
		Vector3f p1p3;
		p1p3[0] = p3[0] - p1[0];
		p1p3[1] = p3[1] - p1[1];
		p1p3[2] = p3[2] - p1[2];

		// The vectorial product of V1 and V2: VP
		Vector3f normal;
		normal[0] = (p1p2[1] * p1p3[2]) - (p1p2[2] * p1p3[1]);
		normal[1] = (p1p2[0] * p1p3[2]) - (p1p2[2] * p1p3[0]);
		normal[2] = (p1p2[0] * p1p3[1]) - (p1p2[1] * p1p3[0]);

		// We normalize VP
		float sqr = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
		Vector3f normal_normalized;
		normal_normalized[0] = normal[0] / sqr;
		normal_normalized[1] = normal[1] / sqr;
		normal_normalized[2] = normal[2] / sqr;

		float divisor2 = sqrt(normal_normalized[0] * normal_normalized[0] + normal_normalized[1] * normal_normalized[1] + normal_normalized[2] * normal_normalized[2]);

		ret = ((light_vector[0] * normal_normalized[0]) + (light_vector[1]  * normal_normalized[1]) + (light_vector[2] * normal_normalized[2])) / (divisor1 * divisor2);

		return ret;
	}

	// Check if the polygon is front face so it is visible
	bool Mesh::is_frontface(const Vertex * const projected_vertices, const int * const indices)
	{
		const Vertex & v0 = projected_vertices[indices[0]];
		const Vertex & v1 = projected_vertices[indices[1]];
		const Vertex & v2 = projected_vertices[indices[2]];

		// Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
		// Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

		return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) > 0.f);
	}

	// Method that clips the polygon and says how many sides are inside the viewport (3 for painting)
	size_t Mesh::clip_polygon(const toolkit::Point4i * vertices_data, int * indices, int * otherindices, toolkit::Point4i clipped_pol [10])
	{
		size_t ret = 3;

		return ret;
	}

}