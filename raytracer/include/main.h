/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:21:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 17:04:31 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "gl_engine.h"

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
