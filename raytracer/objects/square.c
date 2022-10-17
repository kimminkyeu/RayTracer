/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:17:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/18 01:43:14 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "square.h"

/** ------------------------------ *
 *  |     Square hit detection     | --> 무한 평면이 아닌 4개의 point를 입력하는 사각형.
 *  ------------------------------ */
t_hit square_intersect_ray_collision(t_ray *ray, t_square *square)
{
	// Create two triangle. check each.
	// t_triangle t1 = create_triangle(square->v0, square->v1, square->v2);
	t_hit h1 = triangle_intersect_ray_collision(ray, &square->tri_1);

	// t_triangle t2 = create_triangle(square->v0, square->v2, square->v3);
	t_hit h2 = triangle_intersect_ray_collision(ray, &square->tri_2);



	/**    v0           v1
	 *     --------------
	 *     |  .         |
	 *     |    .  t1   |
	 *     |  t2   .    |
	 *     |         .  |
	 *     --------------
	 *    v3            v2
	 */


	if (h1.distance >= 0.0f && h2.distance >= 0.0f)
	{
		if (h1.distance < h2.distance)
			return (h1);
		else
			return (h2);
	}
	else if (h1.distance >= 0.0f)
	{
		return (h1);
	}
	else
	{
		return (h2);
	}
}

