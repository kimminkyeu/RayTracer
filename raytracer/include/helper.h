/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:11:16 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 16:01:04 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPER_H
# define HELPER_H

# include "gl_engine.h"

// helper for min max abs
float min_float(float f1, float f2);
float max_float(float f1, float f2);
float abs_float(float f);

int clamp_int(int i, int min, int max);

/** helper function. */
void	print_error_and_exit(t_device *device, char *str);

/** helper function. check how many strs is in split */
size_t	get_strs_count(char **split);

/** helper function. free char** strings */
void	free_split_char(char **split);

void print_rt_data(t_device *device);
void print_objs_iter(void *data);



#endif /** helper.h */
