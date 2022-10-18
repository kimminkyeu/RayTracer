/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:02:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/19 00:14:32 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_RAY_H
# define TRACE_RAY_H

#include <float.h> // float max (FLT_MAX)
#include "gl_vec3.h"
#include "gl_device.h"
#include "ray.h"
#include "hit.h"
#include "objects.h"
#include "texture.h"
#include "helper.h"

int do_ray_tracing_and_return_color(t_device *device, t_image *img, int x, int y);

t_vec3 trace_ray(t_device *device, t_ray *ray);

t_vec3 super_sampling_anti_aliasing(t_image *img, t_vec3 pixel_pos_world, const float dx, const int recursive_level);

t_hit check_ray_collision(t_ray *ray, t_object *obj);

t_hit find_closet_collision(t_device *device, t_ray *ray);

t_vec3 transform_screen_to_world(t_image *img, t_vec2 pos_screen);

t_vec3 phong_shading_model(t_device *device, t_ray *ray, t_hit hit);

#endif /** trace_ray.h */
