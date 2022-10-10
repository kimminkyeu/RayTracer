/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 17:19:30 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"

// error checking for rt format
void print_sphere_iter(void *data)
{
	t_sphere *sp = data;
	printf("[Sphere] : center(%f,%f,%f) . radius(%f) . color(%f,%f,%f)\n", sp->center.x, sp->center.y, sp->center.z, sp->radius, sp->color.x, sp->color.y, sp->color.z);
}

void print_rt_data(t_device *device)
{
	device->objects.spheres->iterate(device->objects.spheres, print_sphere_iter);
}

int	main(int ac, char **av)
{
	t_device	*device;

	if (ac != 2)
	{
		//... err message
		return (EXIT_FAILURE);
	}

	/** (1) Init engine */
	device = engine_init(800, 800, "42 Mini-RayTracing");

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
