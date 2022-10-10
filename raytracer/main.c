/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 14:41:44 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"

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
	int status = parse_rt_file_to_device(device, av[1]);


	/** (3) start rendering */
	engine_render(device);

	/** (4) loop mlx */
	mlx_loop(device->mlx);

	return (0);
}
