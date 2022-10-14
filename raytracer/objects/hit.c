/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:15:37 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 15:16:20 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit.h"

t_hit create_hit(float distance, t_vec3 normal, t_vec3 point)
{
	t_hit	hit;

	hit.distance = distance;
	hit.normal = normal;
	hit.point = point;
	return (hit);
}
