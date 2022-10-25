/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:26:03 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/25 21:33:01 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**   [ Ambient Light ]
 *           Intensity	    Color
 *     A     0.3            50,50,50
*/
void	parse_ambient_light_2(t_device *device, char *line)
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

/**
 * #    [ Camera ]
 * #    position         loot_at (dir)       up_dir             FOV(0~180)
 * C    0.0,0.0,-1.0     0.0,0.0,1.0        0.0,1.0,0.0         90
*/
void	parse_camera_2(t_device *device, char *line)
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

void	parse_light_2(t_device *device, char *line)
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


void	set_default_material(t_material *m)
{
	m->diffuse = gl_vec3_1f(255.0f);
	m->specular = gl_vec3_1f(255.0f);
	m->alpha = 10.0f;
	m->ks = 0.7f;
	m->transparency = 0.0f;
	m->reflection = 0.0f;
	m->ior = 1.5f;
}

/*
#   [ Sphere ]
#   center        radius  diffuseColor(rgb)  |  alpha   textureM  normalM  |  reflection  transparency  IOR(glass=1.5|water=1.3)
sp  0.5,-0.5,1.0   0.5    0,250,0               10.0                          0.0         0.0           10.0
*/
void	parse_sphere_2(t_device *device, char *line)
{
	t_object	*p;
	t_material	*m;
	t_sphere	*s;
	int			cnt;

	printf("Parsing sphere\n");
	p = custom_allocator_for_object(TYPE_SPHERE);
	set_default_material(&p->material);

	s = p->obj_data;
	m = &(p->material);
	cnt = ft_lscanf(line, "sp%w%f,%f,%f%w%f%w%f,%f,%f%w%f%w%f%w%f%w%f",\
					&s->center.x, &s->center.y, &s->center.z,\
					&s->radius,\
					&m->diffuse.r, &m->diffuse.g, &m->diffuse.b,\
					&m->alpha,\
					&m->reflection,\
					&m->transparency,\
					&m->ior\
					);

	printf("cnt: %d\n", cnt);

	if (cnt < 4)
		print_error_and_exit(device, "parse_sphere(): .rt file error [1]\n");
	if (m->transparency + m->reflection > 1.0f)
		print_error_and_exit(device, "parse_sphere(): .rt file error [2]\n");

	printf("center : %f %f %f\n", s->center.x, s->center.y, s->center.z);
	printf("reflection : %f\n", m->reflection);
	printf("transparency : %f\n", m->transparency);
	printf("alpha : %f\n", m->alpha);
	printf("ior : %f\n", m->ior);

	// NOTE: read texture info



	device->objects->push_back(device->objects, p);
}














