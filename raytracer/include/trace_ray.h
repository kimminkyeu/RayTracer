/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:02:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 22:34:05 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_RAY_H
# define TRACE_RAY_H

#include <float.h> /** float max (FLT_MAX) */
#include "gl_vec3.h"
#include "gl_device.h"
#include "ray.h"
#include "hit.h"
#include "objects.h"
#include "texture.h"
#include "helper.h"

int		do_ray_tracing_and_return_color(t_device *device, t_image *img, int x, int y);

void	update_4_sub_pixels(t_image *img, t_vec3 pixel_pos_world, const float dx, t_vec3 *sample_color);
t_vec3	super_sampling_anti_aliasing(t_image *img, t_vec3 pixel_pos_world, const float dx, const int recursive_level);
bool	is_4_sub_pixels_are_same(t_image *img, t_vec3 pixel_pos_world, const float dx, t_vec3 *colors);
t_vec3	do_recur_super_sampling(t_image *img, t_vec3 pixel_pos_world, const float sub_dx, const int super_sampling_recursive_level);

bool	is_in_shadow(t_device *device, t_hit hit, t_light *light, const t_vec3 hit_point_to_light);
t_vec3	calcuate_ambient(t_device *device, t_hit hit);
t_vec3	calculate_diffuse(t_hit hit, t_light *light, t_vec3 hit_point_to_light);
t_vec3	calcalate_specular(const t_ray *ray, t_hit hit, t_light *light, t_vec3 hit_point_to_light);
t_vec3	calculate_phong(t_device *device, const t_ray *ray, t_hit hit, t_light *light);
t_vec3	calculate_reflection(t_device *device, const t_ray *ray, t_hit hit, const int reflection_recursive_level);
t_vec3	get_refracted_direction(const t_ray *ray, float eta, t_vec3 normal);
t_vec3	calculate_refraction(t_device *device, const t_ray *ray, t_hit hit, const int reflection_recursive_level);

t_vec3	calculate_pixel_color(t_device *device, const t_ray *ray, t_hit hit, const int reflection_recursive_level);

t_vec3	trace_ray(t_device *device, const t_ray *ray, const int recursive_level);
t_hit	check_ray_collision(const t_ray *ray, t_object *obj);
t_hit	find_closet_collision(t_device *device, const t_ray *ray);

#endif /** trace_ray.h */
