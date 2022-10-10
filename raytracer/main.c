/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 19:54:37 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"

// error checking for rt format
void print_sphere_iter(void *data)
{
	t_sphere *sp = data;
	printf("[Sphere] : center(%f,%f,%f) . radius(%f) . color(%f,%f,%f)\n", sp->center.x, sp->center.y, sp->center.z, sp->radius, sp->color.r, sp->color.g, sp->color.b);
}

void print_ambient_light_iter(void *data)
{
	t_ambient_light *sp = data;
	printf("[Ambient Light] : brightness_ratio(%f) . color(%f,%f,%f)\n", sp->brightness_ratio, sp->color.r, sp->color.g, sp->color.b);
}

void print_light_iter(void *data)
{
	t_light *sp = data;
	printf("[Light] : position(%f,%f,%f) . brightness_ratio(%f) . color(%f,%f,%f)\n", sp->pos.x, sp->pos.y, sp->pos.z, sp->brightness_ratio, sp->color.r, sp->color.g, sp->color.b);
}

void print_camera_iter(void *data)
{
	t_camera *sp = data;
	printf("[Camera] : position(%f,%f,%f) . direction(%f,%f,%f) . FOV(%f)\n", sp->pos.x, sp->pos.y, sp->pos.z, sp->dir.x, sp->dir.y, sp->dir.z, sp->fov);
}

void print_rt_data(t_device *device)
{
	print_camera_iter(&device->camera);
	if (device->objects.ambient_lights->size != 0)
		device->objects.ambient_lights->iterate(device->objects.ambient_lights, print_ambient_light_iter);
	if (device->objects.lights->size != 0)
		device->objects.lights->iterate(device->objects.lights, print_light_iter);
	if (device->objects.spheres->size != 0)
		device->objects.spheres->iterate(device->objects.spheres, print_sphere_iter);
	// TODO:  add more objects here!

}

int	main(int ac, char **av)
{
	t_device	*device;

	if (ac != 2)
	{
		//... err message
		return (EXIT_FAILURE);
	}

	/** (1) Init engine && create image */
	device = engine_init(800, 800, "42 Mini-RayTracing");
	engine_new_image(device, gl_vec2_2f(800, 800), gl_vec2_2f(0,0), update);

	/** (2) Load files. (Map data etc...) then store data to [t_device] structure */
	parse_rt_file_to_device(device, av[1]);

	// TODO:  Delete later. just for parse check.
	print_rt_data(device);

	/** (3) start rendering */
	engine_render(device);

	/** (4) loop mlx */
	mlx_loop(device->mlx);

	return (0);
}
