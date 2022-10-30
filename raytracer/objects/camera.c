/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:18:58 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:27:37 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "gl_vec2.h"
#include "gl_vec3.h"
#include "ray.h"

/**_______________________________________________________
 *                                                        *
 *                          Y-axis                        *
 *                                                        *
 *                          [1.0f]                        *
 *                            |                           *
 *                c.len       |                           *
 *    CAM +-------------------|---------> Z-axis          *
 *  (Thera = FOV)             |                           *
 *                            |                           *
 *                         [-1.0f]                        *
 *                                                        *
 *    1.0f / C.len = cotangent( Fov / 2 )                 *
 * _______________________________________________________*
 */
void	update_camera_geometry(t_device *device)
{
	t_camera *const	camera = device->camera;

	camera->look_at = gl_vec3_normalize(camera->look_at);
	camera->up_direction = gl_vec3_normalize((camera->up_direction));
	camera->right_direction = gl_vec3_cross(camera->look_at, \
												camera->up_direction);
	camera->camera_length \
		= 1.0f / tanf(gl_get_radian(camera->fov / 2.0f));
	camera->projection_screen_center \
		= gl_vec3_add_vector(camera->pos, \
			gl_vec3_multiply_scalar(camera->look_at, \
				camera->camera_length));
}

/**
 *                     [World Coord]
 * __________________________________________________________
 *                                                          *
 *                         -1.0                             *
 *                           |                              *
 *                           |                              *
 *  -1.0 * aspect ------------------------ 1.0 * aspect     *
 *                           |                              *
 *                           |                              *
 *                          1.0                             *
 * _________________________________________________________*
 *
 * Change screen coord (i,j) to camera_world coord. */

static t_vec3	calculate_camera_world_coord(t_camera *camera, \
												float dx, float dy)
{
	const t_vec3	u_len = \
		gl_vec3_multiply_scalar(camera->right_direction, dx);
	const t_vec3	v_len = \
		gl_vec3_multiply_scalar(camera->up_direction, dy);
	const t_vec3	world_1 = \
		gl_vec3_add_vector(camera->projection_screen_center, u_len);
	const t_vec3	world_coord_final = \
		gl_vec3_add_vector(world_1, v_len);

	return (world_coord_final);
}

t_vec3	transform_screen_to_camera_world(t_camera *camera, t_image *img, \
										t_vec2 pos_screen)
{
	const float	x_scale = 2.0f / img->img_size.width;
	const float	y_scale = 2.0f / img->img_size.height;
	const float	aspect_ratio = \
		(float)img->img_size.width / img->img_size.height;
	const float	dx = (pos_screen.x * x_scale - 1.0f) * aspect_ratio;
	const float	dy = -pos_screen.y * y_scale + 1.0f;

	return (calculate_camera_world_coord(camera, dx, dy));
}
