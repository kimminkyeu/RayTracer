/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:56:49 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/24 10:32:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "libft.h"
# include "gl_vec3.h"

typedef struct s_ambient_light {
	bool 	has_ambient_light; // light 중복 체크용
	float	brightness_ratio;
	t_vec3	color;

}	t_ambient_light;

typedef struct s_light {

	t_vec3	pos; // 아주 단순화된 형태의 위치만 있는 점조명.
	float	brightness_ratio;
	t_vec3	color;

}	t_light;

#endif /** lights.h */
