/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:12:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 15:25:02 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_ray create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray ray;
	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
