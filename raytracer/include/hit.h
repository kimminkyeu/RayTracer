/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:32:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/13 15:03:53 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

#include "gl_vec3.h"
#include "objects.h"

#define TYPE_NO_HIT		(0)
#define TYPE_SPHERE		(1)
#define TYPE_PLAIN		(2)
#define TYPE_CYLINDER	(3)
#define TYPE_CONE		(4)

typedef struct s_hit {

	float		distance; 	// hit distance;
	t_vec3		point;		// 충돌 위치
	t_vec3		normal; 	// 충돌 위치의 표면의 수직 벡터.
	t_vec2		uv; 		// 텍스쳐 좌표

	t_object	*obj; // hit object pointer

}	t_hit;

#endif /** hit.h */
