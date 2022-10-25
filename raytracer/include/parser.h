/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:28:24 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 05:53:26 by minkyeki         ###   ########.fr       */
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

#define IMAGE_FILE_LOACATION ("./raytracer/image/")

/** scanf function by sungjpar */
extern int	ft_lscanf(char *line, char *format, ...);

/**
 * if success, return (0).
 * if parse fail, return (-1).
 * NOTE:  Function parsed .rt format file and saves it to *device/
*/
extern void	parse_rt_file_to_device(t_device *device, char *file);

void	parse_ambient_light(t_device *device, char *line);

void	parse_camera(t_device *device, char *line);

void	parse_light(t_device *device, char *line);

void	parse_texture(t_device *device, t_object *object, char *line);

void	parse_sphere(t_device *device, char *line);

void	parse_plane(t_device *device, char *line);

void	parse_cylinder(t_device *device, char *line);

void	parse_cone(t_device *device, char *line);

void	parse_triangle(t_device *device, char *line);

void	parse_square(t_device *device, char *line);

#endif /** Parser.h */
