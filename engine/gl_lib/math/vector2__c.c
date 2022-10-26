/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2__c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:26:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:20:34 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec2.h"

float	gl_vec2_dot(t_vec2 v1, t_vec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

float	gl_vec2_get_magnitude(t_vec2 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}

t_vec2	gl_vec2_normalize(t_vec2 v)
{
	float	len;

	len = gl_vec2_get_magnitude(v);
	return (gl_vec2_2f(v.x / len, v.y / len));
}
