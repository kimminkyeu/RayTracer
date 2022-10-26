/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dvector2__c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:06:50 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 12:07:17 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_dvec2.h"

double	gl_dvec2_dot(t_dvec2 v1, t_dvec2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

double	gl_dvec2_get_magnitude(t_dvec2 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
}

t_dvec2	gl_dvec2_normalize(t_dvec2 v)
{
	double	len;

	len = gl_dvec2_get_magnitude(v);
	return (gl_dvec2_2d(v.x / len, v.y / len));
}
