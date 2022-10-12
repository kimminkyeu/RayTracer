/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/12 13:59:17 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"

// error checking for rt format
void print_objs_iter(void *data)
{
	t_object *obj = data;
	if (obj->type == TYPE_SPHERE)
	{
		printf("[Sphere] : center(%f,%f,%f) . ", obj->sphere.center.x, obj->sphere.center.y, obj->sphere.center.z);
		printf("radius(%f) . ", obj->sphere.radius);
		printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
		printf("ks(%f) . ", obj->material.ks);
		printf("alpha(%f)\n", obj->material.alpha);
	}
	else if (obj->type == TYPE_TRIANGLE)
	{
		printf("[Triangle] : v0(%f,%f,%f) . ", obj->triangle.v0.x, obj->triangle.v0.y, obj->triangle.v0.z);
		printf("v1(%f,%f,%f) . ", obj->triangle.v1.x, obj->triangle.v1.y, obj->triangle.v1.z);
		printf("v2(%f,%f,%f) . ", obj->triangle.v2.x, obj->triangle.v2.y, obj->triangle.v2.z);
		printf("diffuse(%f,%f,%f) . ", obj->material.diffuse.r, obj->material.diffuse.g, obj->material.diffuse.b);
		printf("specular(%f,%f,%f) . ", obj->material.specular.r, obj->material.specular.g, obj->material.specular.b);
		printf("ks(%f) . ", obj->material.ks);
		printf("alpha(%f)\n", obj->material.alpha);
	}
	// TODO:  add more objects here!
	// ...
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

int	main(int ac, char **av)
{
	t_device	*device;

	if (ac != 2)
	{
		//... err message
		return (EXIT_FAILURE);
	}

	/** (1) Init engine && create image */
	device = engine_init(1200, 800, "42 Mini-RayTracing");
	engine_new_image(device, gl_vec2_2f(1200, 800), gl_vec2_2f(0,0), update);

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
