/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:32:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 18:34:38 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

#include "gl_vec3.h"

typedef struct s_hit {

	float	distance; // hit distance;
	t_vec3	point; // 충돌 위치
	t_vec3	normal; // 충돌 위치의 표면의 수직 벡터.

}	t_hit;

#endif /** hit.h */
