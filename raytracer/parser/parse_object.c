/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:26:03 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 05:51:37 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**       NOTE:  [ Ambient Light ]
 *       Intensity	    Color
 * A     0.3            50,50,50
*/
void	parse_ambient_light(t_device *device, char *line)
{
	t_ambient_light	*p;
	int				cnt;

	printf("Parsing ambient light\n");
	p = device->ambient_light;
	cnt = ft_lscanf(line, "A%w%f%w%f,%f,%f\n", &p->brightness_ratio, &p->color.r, &p->color.g, &p->color.b);

	if (!(p->has_ambient_light == false && cnt == 4))
		print_error_and_exit(device, "parse_ambient_light(): .rt file error\n");
	p->has_ambient_light = true;
}

/**     NOTE:   [ Camera ]
 *     position         loot_at (dir)       up_dir             FOV(0~180)
 * C   0.0,0.0,-1.0     0.0,0.0,1.0        0.0,1.0,0.0         90
*/
void	parse_camera(t_device *device, char *line)
{
	t_camera	*p;
	int			cnt;

	printf("Parsing carmera\n");
	p = device->camera;
	cnt = ft_lscanf(line, "C%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f\n",\
					&p->pos.x, &p->pos.y, &p->pos.z,\
					&p->look_at.x, &p->look_at.y, &p->look_at.z,\
					&p->up_direction.x, &p->up_direction.y, &p->up_direction.z,\
					&p->fov);

	if (!(p->has_camera == false && cnt == 10))
		print_error_and_exit(device, "parse_camera(): .rt file error\n");
	p->has_camera = true;
	update_camera_geometry(device);
}

/**    NOTE:  [ Light ]
 *     pos             intensity     color
 * L   1.0,1.0,-1.0     0.5           255,255,255
*/
void	parse_light(t_device *device, char *line)
{
	t_light	*p;
	int		cnt;

	printf("Parsing light\n");
	p = ft_calloc(1, sizeof(*p));
	cnt = ft_lscanf(line, "L%w%f,%f,%f%w%f%w%f,%f,%f\n",\
					&p->pos.x, &p->pos.y, &p->pos.z,\
					&p->brightness_ratio,\
					&p->color.r, &p->color.g, &p->color.b);

	if (cnt != 7)
		print_error_and_exit(device, "parse_ambient_light(): .rt file error\n");
	device->point_lights->push_back(device->point_lights, p);
}

#define IMAGE_FILE_LOACATION ("./raytracer/image/")

void	parse_texture(t_device *device, t_object *object, char *line)
{
	char	*str;
	char	**split;

	str = ft_strchr(line, '|');
	if (str == NULL)
		return ;
	str++;
	str = ft_strtrim(str, "\n");
	if (str == NULL)
		return ;

	split = ft_split(str, ' ');

	if (get_strs_count(split) > 0)
	{
		if (ft_strncmp("checker", split[0], 7) == 0)
			object->diffuse_texture = new_texture_checkerboard(device, 32, 32);
		else
		{
			str = ft_strjoin(IMAGE_FILE_LOACATION, split[0]);
			object->diffuse_texture = new_texture(device, str);
			free(str);
		}
		if (get_strs_count(split) == 2)
		{
			str = ft_strjoin(IMAGE_FILE_LOACATION, split[1]);
			object->normal_texture = new_texture(device, str);
			free(str);
		}
	}
	free_split_char(split);
}

/*
#   [ Sphere ]                                  | --> optional
#   center          radius   diffuseColor(rgb)   alpha    reflection  transparency  IOR(glass=1.5|water=1.3)  |   textureM   normalM
*/
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
	cnt = ft_lscanf(line, "sp%w%f,%f,%f%w%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n",\
					&sp->center.x, &sp->center.y, &sp->center.z,\
					&sp->radius,\
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b,\
					&mat->alpha,\
					&mat->reflection,\
					&mat->transparency,\
					&mat->ior);

	if (cnt < 4 || mat->transparency + mat->reflection > 1.0f)
		print_error_and_exit(device, "parse_sphere(): .rt file error\n");
	parse_texture(device, obj, line);
	device->objects->push_back(device->objects, obj);
}

/**
 * #      [ Plain ]
 * #      xyzCoordinates     FaceNormal      diffuseColor(rgb)    |   alpha    reflection  transparency  IOR(glass=1.5|water=1.3)
 * # pl   0.0,-1.0,0.0      0.0,1.0,0.0      128,128,128
*/

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
	cnt = ft_lscanf(line, "pl%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n",\
					&pl->pos.x, &pl->pos.y, &pl->pos.z,\
					&pl->normal.x,&pl->normal.y,&pl->normal.z,\
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b,\
					&mat->alpha,\
					&mat->reflection,\
					&mat->transparency,\
					&mat->ior);

	if (cnt < 6)
		print_error_and_exit(device, "parse_plane(): .rt file error\n");
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
	cnt = ft_lscanf(line, "cy%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n",\
					&cy->pos.x, &cy->pos.y, &cy->pos.z,\
					&cy->orientation.x, &cy->orientation.y, &cy->orientation.z,\
					&cy->radius, &cy->height,\
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b,\
					&mat->alpha,\
					&mat->reflection,\
					&mat->transparency,\
					&mat->ior);

	if (cnt < 8)
		print_error_and_exit(device, "parse_cylinder(): .rt file error\n");
	device->objects->push_back(device->objects, obj);
}

void parse_cone(t_device *device, char *line)
{
	t_object	*obj;
	t_material	*mat;
	t_cone		*co;
	int 		cnt;

	printf("Parsing cone\n");
	obj = custom_allocator_for_object(TYPE_CONE);
	co = obj->obj_data;
	mat = &(obj->material);
	cnt = ft_lscanf(line, "co%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n",
					&co->pos.x, &co->pos.y, &co->pos.z,
					&co->orientation.x, &co->orientation.y, &co->orientation.z,
					&co->radius, &co->height,
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b,
					&mat->alpha,
					&mat->reflection,
					&mat->transparency,
					&mat->ior);

	if (cnt < 8)
		print_error_and_exit(device, "parse_cone(): .rt file error\n");
	device->objects->push_back(device->objects, obj);
}

void	parse_triangle(t_device *device, char *line)
{
	t_object	*obj;
	t_material	*mat;
	t_triangle	*tr;
	int			cnt;

	printf("Parsing triangle\n");
	obj = custom_allocator_for_object(TYPE_TRIANGLE);
	tr = obj->obj_data;
	mat = &(obj->material);
	cnt = ft_lscanf(line, "tr%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n",\
					&tr->v0.x, &tr->v0.y, &tr->v0.z,\
					&tr->v1.x, &tr->v1.y, &tr->v1.z,\
					&tr->v2.x, &tr->v2.y, &tr->v2.z,\
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b,\
					&mat->alpha,\
					&mat->reflection,\
					&mat->transparency,\
					&mat->ior);

	if (cnt < 9 || mat->transparency + mat->reflection > 1.0f)
		print_error_and_exit(device, "parse_triangle(): .rt file error\n");

	// *   FIX:  UV 좌표계 고치기. (checker 텍스쳐 기준으로 작업 진행)
	tr->uv0 = gl_vec2_2f(0.0f, 0.0f);
	tr->uv1 = gl_vec2_2f(0.0f, 1.0f);
	tr->uv2 = gl_vec2_2f(1.0f, 1.0f);

	parse_texture(device, obj, line);
	device->objects->push_back(device->objects, obj);
}

void	parse_square(t_device *device, char *line)
{
	t_object	*obj;
	t_material	*mat;
	t_square	*sq;
	t_vec3		v[4];
	int			cnt;

	printf("Parsing square\n");
	obj = custom_allocator_for_object(TYPE_SQUARE);
	sq = obj->obj_data;
	mat = &(obj->material);
	cnt = ft_lscanf(line, "sq%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f%w%f%w%f%w%f\n",\
					&v[0].x, &v[0].y, &v[0].z,\
					&v[1].x, &v[1].y, &v[1].z,\
					&v[2].x, &v[2].y, &v[2].z,\
					&v[3].x, &v[3].y, &v[3].z,\
					&mat->diffuse.r, &mat->diffuse.g, &mat->diffuse.b,\
					&mat->alpha,\
					&mat->reflection,\
					&mat->transparency,\
					&mat->ior);

	if (cnt < 12 || mat->transparency + mat->reflection > 1.0f)
		print_error_and_exit(device, "parse_square(): .rt file error\n");

	// *   FIX:  UV 좌표계 고치기. (checker 텍스쳐 기준으로 작업 진행)
	sq->tri_1 = create_triangle(v[0], v[1], v[2]);
	sq->tri_1.uv0 = gl_vec2_2f(0.0f, 0.0f);
	sq->tri_1.uv1 = gl_vec2_2f(1.0f, 0.0f);
	sq->tri_1.uv2 = gl_vec2_2f(1.0f, 1.0f);

	sq->tri_2 = create_triangle(v[0], v[2], v[3]);
	sq->tri_2.uv0 = gl_vec2_2f(0.0f, 0.0f);
	sq->tri_2.uv1 = gl_vec2_2f(1.0f, 1.0f);
	sq->tri_2.uv2 = gl_vec2_2f(0.0f, 1.0f);

	parse_texture(device, obj, line);
	device->objects->push_back(device->objects, obj);
}
