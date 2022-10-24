/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/24 10:50:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "objects.h"
#include "texture.h"


// return w0, w1, w2 weights
t_vec3 get_barycentric_coord(t_vec3 v0, t_vec3 v1, t_vec3 v2, t_vec3 point)
{
	float w0, w1, w2;
	// 작은 삼각형들 3개의 normal 계산. 이때, ( WARN:  cross-product는 오른손 좌표계)
	// 이때, 방향만 알면 되기 때문에 normalize를 할 필요가 없음.
	// const t_vec3 normal0 = gl_vec3_normalize(gl_vec3_cross(gl_vec3_subtract_vector(*point, v2), gl_vec3_subtract_vector(v1, v2)));
	const t_vec3 cross0 = gl_vec3_cross(gl_vec3_subtract_vector(point, v2), gl_vec3_subtract_vector(v1, v2));
	// const t_vec3 normal1 = gl_vec3_normalize(gl_vec3_cross(gl_vec3_subtract_vector(*point, v0), gl_vec3_subtract_vector(v2, v0)));
	const t_vec3 cross1 = gl_vec3_cross(gl_vec3_subtract_vector(point, v0), gl_vec3_subtract_vector(v2, v0));
	// const t_vec3 normal2 = gl_vec3_normalize(gl_vec3_cross(gl_vec3_subtract_vector(v1, v0), gl_vec3_subtract_vector(*point, v0)));
	const t_vec3 cross2 = gl_vec3_cross(gl_vec3_subtract_vector(v1, v0), gl_vec3_subtract_vector(point, v0));

	const float area0 = gl_vec3_get_magnitude(cross0) * 0.5f;
	const float area1 = gl_vec3_get_magnitude(cross1) * 0.5f;
	const float area2 = gl_vec3_get_magnitude(cross2) * 0.5f;

	const float area_sum = area0 + area1 + area2;
	w0 = area0 / area_sum;
	w1 = area1 / area_sum;
	w2 = 1.0f - w0 - w1;
	return (gl_vec3_3f(w0, w1, w2));
}

/** helper function. (min) */
float min_float(float f1, float f2)
{
	if (f1 >= f2)
		return (f2);
	else
		return (f1);
}

/** helper function. (max) */
float max_float(float f1, float f2)
{
	if (f1 >= f2)
		return (f1);
	else
		return (f2);
}

/** helper function. (abs) */
float abs_float(float f)
{
	if (f >= 0.0f)
		return (f);
	else
		return (-f);
}

int clamp_int(int i, int min, int max)
{
	if (i < min)
		return (min);
	else if (i > max)
		return (max);
	else
		return (i);
}

size_t	get_strs_count(char **split)
{
	size_t i;

	i = 0;
	while (split[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	free_split_char(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
	{
		free(split[i]);
		split[i] = NULL;
	}
	free(split);
}

// error checking for rt format
// void print_objs_iter(void *data)
// {
// 	t_object *obj = data;
// 	if (obj->type == TYPE_SPHERE)
// 	{
// 		printf("[Sphere] : center(%f,%f,%f) . ", ((t_sphere *)obj->obj_data)->center.x, ((t_sphere *)obj->obj_data)->center.y, ((t_sphere *)obj->obj_data)->center.z);
// 		printf("radius(%f) . ", ((t_sphere *)obj->obj_data)->radius);
// 		printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
// 		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
// 		printf("ks(%f) . ", obj->material.ks);
// 		printf("alpha(%f)\n", obj->material.alpha);

// 		if (obj->ambient_texture != NULL)
// 			printf("ambient texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);
// 	}
// 	else if (obj->type == TYPE_TRIANGLE)
// 	{
// 		printf("[Triangle] : v0(%f,%f,%f) . ", ((t_triangle *)obj->obj_data)->v0.x, ((t_triangle *)obj->obj_data)->v0.y, ((t_triangle *)obj->obj_data)->v0.z);
// 		printf("v1(%f,%f,%f) . ", ((t_triangle *)obj->obj_data)->v1.x, ((t_triangle *)obj->obj_data)->v1.y, ((t_triangle *)obj->obj_data)->v1.z);
// 		printf("v2(%f,%f,%f) . ", ((t_triangle *)obj->obj_data)->v2.x, ((t_triangle *)obj->obj_data)->v2.y, ((t_triangle *)obj->obj_data)->v2.z);

// 		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
// 		printf("ks(%f) . ", obj->material.ks);
// 		printf("alpha(%f)\n", obj->material.alpha);

// 		if (obj->ambient_texture != NULL)
// 			printf("ambient texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);

// 	}
// 	else if (obj->type == TYPE_PLAIN)
// 	{
// 		printf("[Plain] : pos(%f,%f,%f) . ", ((t_plane *)obj->obj_data)->pos.x, ((t_plane *)obj->obj_data)->pos.y, ((t_plane *)obj->obj_data)->pos.z);
// 		printf("normal(%f,%f,%f) . ", ((t_plane *)obj->obj_data)->normal.x, ((t_plane *)obj->obj_data)->normal.y, ((t_plane *)obj->obj_data)->normal.z);
// 		printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
// 		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
// 		printf("ks(%f) . ", obj->material.ks);
// 		printf("alpha(%f)\n", obj->material.alpha);

// 		// if (obj->ambient_texture != NULL)
// 			// printf("texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);

// 	}
// 	else if (obj->type == TYPE_SQUARE)
// 	{
// 		// printf("[Square] : v0(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v0.x, ((t_square *)obj->obj_data)->v0.y, ((t_square *)obj->obj_data)->v0.z);
// 		// printf("v1(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v1.x, ((t_square *)obj->obj_data)->v1.y, ((t_square *)obj->obj_data)->v1.z);
// 		// printf("v2(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v2.x, ((t_square *)obj->obj_data)->v2.y, ((t_square *)obj->obj_data)->v2.z);
// 		// printf("v3(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v3.x, ((t_square *)obj->obj_data)->v3.y, ((t_square *)obj->obj_data)->v3.z);
// 		// printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
// 		// printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
// 		// printf("ks(%f) . ", obj->material.ks);
// 		// printf("alpha(%f)\n", obj->material.alpha);

// 		if (obj->ambient_texture != NULL)
// 			printf("ambient texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);

// 	}
// 	// TODO:  add more objects here!
// 	// ...
// 	else if (obj->type == TYPE_PLAIN)
// 	{}
// 	else if (obj->type == TYPE_CYLINDER)
// 	{}
// 	else if (obj->type == TYPE_CONE)
// 	{}
// 	else
// 	{}
// }
