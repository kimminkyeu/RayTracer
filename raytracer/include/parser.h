/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:28:24 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/25 19:48:18 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "mlx_linux.h"
#include "vector.h"
#include "gl_device.h"
#include "gl_engine.h"
#include "main.h"
#include "texture.h"

/** scanf function by sungjpar */
extern int	ft_lscanf(char *line, char *format, ...);

/**
 * if success, return (0).
 * if parse fail, return (-1).
 * NOTE:  Function parsed .rt format file and saves it to *device/
*/
extern void	parse_rt_file_to_device(t_device *device, char *file);
extern void	parse_rt_file_to_device2(t_device *device, char *file);






#endif /** Parser.h */
