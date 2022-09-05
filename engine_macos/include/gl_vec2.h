/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_vec2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:23:51 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:09:53 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2
# define VECTOR2

# include <math.h>

typedef union u_vec2 {
	struct {
		float	x;
		float	y;
	};
	float	v[2];
}	t_vec2;

/* Create R-value vec2 and returns data */
extern t_vec2	gl_vec2(float _x, float _y);
extern float	gl_vec2_dot_product(t_vec2 v1, t_vec2 v2);
extern float	gl_vec2_get_magnitude(t_vec2 v);
extern t_vec2	gl_vec2_normalize(t_vec2 v);

#endif /* VECTOR2 */
