/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:11:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:03:13 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include "gl_engine.h"

t_vec3	get_barycentric_coord(t_vec3 v0, t_vec3 v1, t_vec3 v2, t_vec3 point);

/** helper for min max abs */
float	min_float(float f1, float f2);
float	max_float(float f1, float f2);
float	abs_float(float f);

int		clamp_int(int i, int min, int max);

/** helper function. */
void	print_error_and_exit(t_device *device, char *str);

/** helper function. check how many strs is in split */
size_t	get_strs_count(char **split);

/** helper function. free char** strings */
void	free_split_char(char **split);

#endif /** helper.h */
