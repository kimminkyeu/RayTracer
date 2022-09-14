/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:54:43 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/14 16:24:41 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "gl_device.h"
#include "mlx_linux.h"

/** TODO:  move this function to engine header. 
 * on error, return -1
*/
int	engine_new_xpm_image(t_device *device, char *filename, t_vec2 img_location, int (*update_func)())
{
	t_vector *images = device->images;
	t_image	*new_image;

	if (device == NULL || filename == NULL)
		return (-1);
	new_image = ft_calloc(1, sizeof(*new_image));

	// int t1 = 0;
	// int t2 = 0;
	// new_image->img_ptr = mlx_xpm_file_to_image(device->mlx, filename, &t1, &t2);
	new_image->img_ptr = mlx_xpm_file_to_image(device->mlx, filename, (int *)&(new_image->img_size.width), (int *)&(new_image->img_size.height));

	if (new_image->img_ptr == NULL)
	{
		free(new_image);
		return (-1);
	}
	new_image->addr = mlx_get_data_addr(new_image->img_ptr, \
				&(new_image->bits_per_pixel), \
				&(new_image->line_length), &(new_image->endian));
	new_image->img_location = img_location;
	new_image->img_update_func = update_func;
	images->push_back(images, new_image);
	return (0);
}


int	main(int ac, char **av)
{
	t_device	*device;

	/** (1) Init engine */
	device = engine_init(1280, 720, "42GL Engine v.1.0");

	/** Viewport_content */
	// engine_new_image(device, gl_vec2(500, 500), gl_vec2(0, 0), update_func);
	int status = engine_new_xpm_image(device, "./myapp/image/image_1.xpm", gl_vec2(0, 0), update_func);
	if (status == -1)
		printf("Error while opening xpm image\n");

	/** (2) Load files. (Map data etc...) then store data to [t_device] structure */
	// (t_device)'s location : engine/gl_core/device.h --> add additional data in here!
	(void)av; (void)ac;



	// (3) FIX: 이 부분도 구조 어떻게 바꾸는게 좋을지 토의할 것.
	engine_render(device);
	// (3) FIX: --> mlx_loop을 여기로 뺐는데, 그 이유는 매초 새로 렌더링하는걸 방지하려고... ---> 추후 토의 필요.
	mlx_loop(device->mlx);
	return (0);
}
