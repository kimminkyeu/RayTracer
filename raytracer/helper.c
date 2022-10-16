/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:43:34 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 15:59:37 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "objects.h"
#include "texture.h"


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
void print_objs_iter(void *data)
{
	t_object *obj = data;
	if (obj->type == TYPE_SPHERE)
	{
		printf("[Sphere] : center(%f,%f,%f) . ", ((t_sphere *)obj->obj_data)->center.x, ((t_sphere *)obj->obj_data)->center.y, ((t_sphere *)obj->obj_data)->center.z);
		printf("radius(%f) . ", ((t_sphere *)obj->obj_data)->radius);
		printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
		printf("ks(%f) . ", obj->material.ks);
		printf("alpha(%f)\n", obj->material.alpha);

		if (obj->ambient_texture != NULL)
			printf("ambient texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);
	}
	else if (obj->type == TYPE_TRIANGLE)
	{
		printf("[Triangle] : v0(%f,%f,%f) . ", ((t_triangle *)obj->obj_data)->v0.x, ((t_triangle *)obj->obj_data)->v0.y, ((t_triangle *)obj->obj_data)->v0.z);
		printf("v1(%f,%f,%f) . ", ((t_triangle *)obj->obj_data)->v1.x, ((t_triangle *)obj->obj_data)->v1.y, ((t_triangle *)obj->obj_data)->v1.z);
		printf("v2(%f,%f,%f) . ", ((t_triangle *)obj->obj_data)->v2.x, ((t_triangle *)obj->obj_data)->v2.y, ((t_triangle *)obj->obj_data)->v2.z);

		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
		printf("ks(%f) . ", obj->material.ks);
		printf("alpha(%f)\n", obj->material.alpha);

		if (obj->ambient_texture != NULL)
			printf("ambient texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);

	}
	else if (obj->type == TYPE_PLAIN)
	{
		printf("[Plain] : pos(%f,%f,%f) . ", ((t_plane *)obj->obj_data)->pos.x, ((t_plane *)obj->obj_data)->pos.y, ((t_plane *)obj->obj_data)->pos.z);
		printf("normal(%f,%f,%f) . ", ((t_plane *)obj->obj_data)->normal.x, ((t_plane *)obj->obj_data)->normal.y, ((t_plane *)obj->obj_data)->normal.z);
		printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
		printf("ks(%f) . ", obj->material.ks);
		printf("alpha(%f)\n", obj->material.alpha);

		// if (obj->ambient_texture != NULL)
			// printf("texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);

	}
	else if (obj->type == TYPE_SQUARE)
	{
		// printf("[Square] : v0(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v0.x, ((t_square *)obj->obj_data)->v0.y, ((t_square *)obj->obj_data)->v0.z);
		// printf("v1(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v1.x, ((t_square *)obj->obj_data)->v1.y, ((t_square *)obj->obj_data)->v1.z);
		// printf("v2(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v2.x, ((t_square *)obj->obj_data)->v2.y, ((t_square *)obj->obj_data)->v2.z);
		// printf("v3(%f,%f,%f) . ", ((t_square *)obj->obj_data)->v3.x, ((t_square *)obj->obj_data)->v3.y, ((t_square *)obj->obj_data)->v3.z);
		// printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
		// printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
		// printf("ks(%f) . ", obj->material.ks);
		// printf("alpha(%f)\n", obj->material.alpha);

		if (obj->ambient_texture != NULL)
			printf("ambient texture (w%d/h%d)\n", obj->ambient_texture->width, obj->ambient_texture->height);

	}
	// TODO:  add more objects here!
	// ...
	else if (obj->type == TYPE_PLAIN)
	{}
	else if (obj->type == TYPE_CYLINDER)
	{}
	else if (obj->type == TYPE_CONE)
	{}
	else
	{}
}

void print_rt_data(t_device *device)
{
	if (device->camera->has_camera == true)
		printf("[Camera] : position(%f,%f,%f) . direction(%f,%f,%f) . FOV(%f)\n", device->camera->pos.x, device->camera->pos.y, device->camera->pos.z, device->camera->dir.x, device->camera->dir.y, device->camera->dir.z, device->camera->fov);
	if (device->ambient_light->has_ambient_light == true)
		printf("[Ambient Light] : brightness_ratio(%f) . color(%f,%f,%f)\n", device->ambient_light->brightness_ratio, device->ambient_light->color.r, device->ambient_light->color.g, device->ambient_light->color.b);
	if (device->light->has_light == true)
		printf("[Light] : position(%f,%f,%f) . brightness_ratio(%f) . color(%f,%f,%f)\n", device->light->pos.x, device->light->pos.y, device->light->pos.z, device->light->brightness_ratio, device->light->color.r, device->light->color.g, device->light->color.b);
	if (device->objects->size != 0)
		device->objects->iterate(device->objects, print_objs_iter);

}

