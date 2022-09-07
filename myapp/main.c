/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 14:31:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void draw_render_time(t_device *device, int _x, int _y, int argb)
{
	char	*str;

	mlx_string_put(device->mlx, device->win, _x, _y, argb, "Last render(ms)");
	mlx_string_put(device->mlx, device->win, _x, _y + 20, argb, ":");
	str = ft_itoa(device->render_time);
	mlx_string_put(device->mlx, device->win, _x + 12, _y + 20, argb, str);
	free(str);
}

int	main(int ac, char **av)
{
	t_device	*device;

	/** (1) Init engine */
	device = engine_init(800, 200, 800, "42GL Engine v.1.0");

	/** (2) Load files. (Map data etc...) then store data to [t_device] structure */
	// NOTE: (t_device)'s location : engine/gl_core/device.h --> add additional data in here!
	(void)av; (void)ac;

	/** (3) Start rendering.
	 * engine calls [render_layer()] function every loop */
	engine_start_loop(device, render_layer);
	return (0);
}

int render_layer(t_device *device)
{
	long long	render_start_time;
	long long	render_end_time;

	/** (4) checking rendering time performance(in ms) */
	render_start_time = get_time_ms();
	if (device->viewport.width > 0)
	{
		render_viewport(device, &device->viewport); 
		engine_push_image(device, &device->viewport, 0, 0);
	}
	render_end_time = get_time_ms();
	device->render_time = render_end_time - render_start_time;
	if (device->panel.width > 0)
	{
		render_panel(device, &device->panel); 
		engine_push_image(device, &device->panel, device->viewport.width, 0);
		draw_render_time(device, device->viewport.width + 15, 20, GRAY);
	}
	return (0);
}
