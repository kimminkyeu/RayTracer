/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:32:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 15:22:37 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

#include "gl_vec3.h"
#include "gl_vec2.h"
// #include "objects.h"

typedef struct s_object t_object;
typedef struct s_hit {

	float		distance; 	// hit distance;
	t_vec3		point;		// 충돌 위치
	t_vec3		normal; 	// 충돌 위치의 표면의 수직 벡터.
	t_object	*obj; // hit object pointer

	t_vec2		uv; 		// 텍스쳐 좌표

}	t_hit;

extern t_hit create_hit(float distance, t_vec3 normal, t_vec3 point);

#endif /** hit.h */
