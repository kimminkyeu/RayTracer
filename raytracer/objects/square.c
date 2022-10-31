/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:17:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/27 22:09:36 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

// TODO : 안씀
/** ------------------------------ *
 *  |     Square hit detection     | --> 무한 평면이 아닌 4개의 point를 입력하는 사각형.
 *  ------------------------------ */
t_hit	square_intersect_ray_collision(const t_ray *ray, t_square *square)
{
	t_hit	h1 ;
	t_hit	h2;
	t_hit	hit_result;

	h1 = triangle_intersect_ray_collision(ray, &square->tri_1);
	h2 = triangle_intersect_ray_collision(ray, &square->tri_2);
	if (h1.distance >= 0.0f && h2.distance >= 0.0f)
	{
		if (h1.distance < h2.distance)
			hit_result = h1;
		else
			hit_result = h2;
	}
	else if (h1.distance >= 0.0f)
		hit_result = h1;
	else
		hit_result = h2;
	return (hit_result);
}

