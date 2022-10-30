/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:55:17 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:08:05 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "triangle.h"

typedef struct s_square {
	t_triangle	tri_1;
	t_triangle	tri_2;
}	t_square;

extern t_hit	square_intersect_ray_collision(const t_ray *ray, \
												t_square *square);

#endif /** square.h */
