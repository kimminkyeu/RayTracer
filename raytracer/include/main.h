/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:21:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/13 20:22:46 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "gl_engine.h"
# include "ray.h"
# include "objects.h"
# include "hit.h"
# include "camera.h"
# include "texture.h"


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

/**
 * if success, return (0).
 * if parse fail, return (-1).
 * NOTE:  Function parsed .rt format file and saves it to *device/
*/
extern void	parse_rt_file_to_device(t_device *device, char *file);

extern int	update(t_device *device, t_image *img);

#endif /* MAIN_H */
