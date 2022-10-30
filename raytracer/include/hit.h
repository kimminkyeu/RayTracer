/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:32:46 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:06:58 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "gl_vec3.h"
# include "gl_vec2.h"

typedef struct s_object	t_object;

typedef struct s_hit {
	float		distance;
	t_vec3		point;
	t_vec3		normal;
	t_object	*obj;
	t_vec2		uv;
	t_vec3		tangent;

}	t_hit;

extern t_hit	create_hit(float distance, t_vec3 normal, t_vec3 point);

#endif /** hit.h */
