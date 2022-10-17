/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/17 14:56:59 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/main.h"
#include "helper.h"
#include "libft.h"
#include "thread.h"

int	main(int ac, char **av)
{
	t_device	*device;

	if (ac != 2)
	{
		//... err message
		return (EXIT_FAILURE);
	}

	const int WIDTH = 1000;
	const int HEIGHT = 800;
	/** (1) Init engine && create image */
	device = engine_init(WIDTH, HEIGHT, "42 Mini-RayTracing");
	engine_new_image(device, gl_vec2_2f(WIDTH, HEIGHT), gl_vec2_2f(0,0), update);

	/** (2) Load files. (Map data etc...) then store data to [t_device] structure */
	parse_rt_file_to_device(device, av[1]);

	// TODO:  Delete later. just for parse check.
	// print_rt_data(device);

	// THREAD TEST
	t_thread_info *info = &device->thread_info;
	const int THREAD_NUM = 24;
	info->thread_group = ft_calloc(1, sizeof(t_thread) * THREAD_NUM);
	info->thread_num = THREAD_NUM;
	info->finished_thread_num = 0;
	if (pthread_mutex_init(&(info->finished_num_mutex), NULL) != 0)
		print_error_and_exit(device, "error in pthread_mutex_init()\n");

	/** (3) start rendering */
	engine_render(device);

	/** (4) loop mlx */
	mlx_loop(device->mlx);

	return (0);
}
