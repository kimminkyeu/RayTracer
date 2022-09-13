/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/13 17:28:09 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av)
{
	t_device	*device;

	/** (1) Init engine */
	device = engine_init(800, 800, "42GL Engine v.1.0");


	/** NOTE: Viewport_content */
	engine_new_image(device, gl_vec2(800, 800), gl_vec2(0, 0), update_func);


	/** (2) Load files. (Map data etc...) then store data to [t_device] structure */
	// NOTE: (t_device)'s location : engine/gl_core/device.h --> add additional data in here!
	(void)av; (void)ac;


	// (3) NOTE: 
	engine_render(device);


	return (0);
}
