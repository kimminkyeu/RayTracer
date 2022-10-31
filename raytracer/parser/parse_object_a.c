/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:26:03 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 21:51:38 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"
#include "objects.h"
#include "parser.h"

void	parse_sphere(t_device *device, char *line)
{
	t_object	*obj;
	t_material	*mat;
	t_sphere	*sp;
	int			cnt;

	printf("Parsing sphere\n");
	obj = custom_allocator_for_object(TYPE_SPHERE);
	sp = obj->obj_data;
	mat = &(obj->material);
	cnt = ft_lscanf(line, "sp%w%f,%f,%f%w%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n", \
					&sp->center.x, &sp->center.y, &sp->center.z, \
					&sp->radius, \
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b, \
					&mat->alpha, \
					&mat->reflection, \
					&mat->transparency, \
					&mat->ior);
	if (cnt < 4 || mat->transparency + mat->reflection > 1.0f)
		print_error_and_exit(device, "parse_sphere(): .rt file error\n");
	parse_texture(device, obj, line);
	device->objects->push_back(device->objects, obj);
}

void	parse_plane(t_device *device, char *line)
{
	t_object	*obj;
	t_material	*mat;
	t_plane		*pl;
	int			cnt;

	printf("Parsing plane\n");
	obj = custom_allocator_for_object(TYPE_PLANE);
	pl = obj->obj_data;
	mat = &(obj->material);
	cnt = ft_lscanf(line, "pl%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n", \
					&pl->pos.x, &pl->pos.y, &pl->pos.z, \
					&pl->normal.x, &pl->normal.y, &pl->normal.z, \
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b, \
					&mat->alpha, \
					&mat->reflection, \
					&mat->transparency, \
					&mat->ior);
	if (cnt < 6)
		print_error_and_exit(device, "parse_plane(): .rt file error\n");
	pl->normal = normal3(pl->normal);
	device->objects->push_back(device->objects, obj);
}

void	parse_cylinder(t_device *device, char *line)
{
	t_object	*obj;
	t_material	*mat;
	t_cylinder	*cy;
	int			cnt;

	printf("Parsing cylinder\n");
	obj = custom_allocator_for_object(TYPE_CYLINDER);
	cy = obj->obj_data;
	mat = &(obj->material);
	cnt = ft_lscanf(line, \
				"cy%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n", \
					&cy->pos.x, &cy->pos.y, &cy->pos.z, \
					&cy->orientation.x, &cy->orientation.y, &cy->orientation.z, \
					&cy->radius, &cy->height, \
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b, \
					&mat->alpha, \
					&mat->reflection, \
					&mat->transparency, \
					&mat->ior);
	if (cnt < 8)
		print_error_and_exit(device, "parse_cylinder(): .rt file error\n");
	cy->orientation = normal3(cy->orientation);
	device->objects->push_back(device->objects, obj);
}

void	parse_cone(t_device *device, char *line)
{
	t_object	*obj;
	t_material	*mat;
	t_cone		*co;
	int			cnt;

	printf("Parsing cone\n");
	obj = custom_allocator_for_object(TYPE_CONE);
	co = obj->obj_data;
	mat = &(obj->material);
	cnt = ft_lscanf(line, \
			"co%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n", \
					&co->pos.x, &co->pos.y, &co->pos.z, \
					&co->orientation.x, &co->orientation.y, &co->orientation.z, \
					&co->radius, &co->height, \
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b, \
					&mat->alpha, \
					&mat->reflection, \
					&mat->transparency, \
					&mat->ior);
	if (cnt < 8)
		print_error_and_exit(device, "parse_cone(): .rt file error\n");
	co->orientation = normal3(co->orientation);
	device->objects->push_back(device->objects, obj);
}
