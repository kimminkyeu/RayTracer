/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 18:16:30 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:19:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>

#include "libft.h"
#include "lights.h"
#include "camera.h"
#include "gl_engine.h"
#include "gl_vec2.h"

extern void		custom_deallocator_for_object(void *data);
extern void		engine_set_key_event(t_device *device, \
				int (*f_key_press)(), int (*f_key_release)());
extern void		engine_set_mouse_event(t_device *device, \
				int (*f_mouse_press)(), int (*f_mouse_release)());
extern int		handle_key_press(int key_code, void *param);
extern int		handle_key_release(int key_code, void *param);
extern int		handle_mouse_press(int key_code, int x, int y, void *param);
extern int		handle_mouse_release(int key_code, int x, int y, void *param);
extern void		destory_images(t_device *device);
extern void		parse_rt_file_to_device(t_device *device, char *file);

void	engine_exit(t_device *device, bool is_error)
{
	printf("Engine Exit()...\n");
	if (device != NULL && device->objects != NULL)
		delete_vector(&device->objects);
	if (device != NULL && device->camera != NULL)
		free(device->camera);
	if (device != NULL && device->ambient_light != NULL)
		free(device->ambient_light);
	if (device != NULL && device->point_lights != NULL)
		delete_vector(&device->point_lights);
	destory_images(device);
	if (device->win != NULL)
		mlx_destroy_window(device->mlx, device->win);
	if (device != NULL && device->mlx != NULL)
		free(device->mlx);
	pthread_mutex_destroy(&(device->thread_info.finished_num_mutex));
	if (device->thread_info.thread_group != NULL)
		free(device->thread_info.thread_group);
	if (device != NULL)
		free(device);
	if (is_error == ERROR)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

int	handle_exit(t_device *device)
{
	ft_putstr_fd("Closing Program....\n", STDOUT);
	engine_exit(device, SUCCESS);
	return (0);
}

void	init_camera_and_objects_vector(t_device *device, char *rt_file)
{
	device->camera = ft_calloc(1, sizeof(t_camera));
	device->camera->has_camera = false;
	device->ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	device->ambient_light->has_ambient_light = false;
	device->point_lights = new_vector(5);
	device->objects = new_vector_with_custom_deallocator(8, \
								custom_deallocator_for_object);
	parse_rt_file_to_device(device, rt_file);
}

t_device	*engine_init(char *title, char *rt_file)
{
	t_device *const	device = ft_calloc(1, sizeof(*device));

	if (device == NULL)
		engine_exit(device, ERROR);
	device->mlx = mlx_init();
	if (device->mlx == NULL)
		engine_exit(device, ERROR);
	init_camera_and_objects_vector(device, rt_file);
	device->win = mlx_new_window(device->mlx, \
								device->renderer_settings.win_width, \
								device->renderer_settings.win_height, title);
	if (device->win == NULL)
		engine_exit(device, ERROR);
	device->screen_image = engine_new_image(device, \
		gl_vec2_2f(device->renderer_settings.win_width, \
					device->renderer_settings.win_height), gl_vec2_2f(0, 0));
	device->pixel_image = engine_new_image(device, \
		gl_vec2_2f(device->renderer_settings.win_width \
					* device->renderer_settings.resolution_ratio, \
					device->renderer_settings.win_height \
					* device->renderer_settings.resolution_ratio), \
						gl_vec2_2f(0, 0));
	engine_set_key_event(device, handle_key_press, handle_key_release);
	engine_set_mouse_event(device, handle_mouse_press, handle_mouse_release);
	return (device);
}
