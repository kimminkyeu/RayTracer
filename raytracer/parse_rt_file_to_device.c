/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file_to_device.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:35:05 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 21:48:59 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "vector.h"
#include "gl_device.h"
#include "gl_engine.h"
#include "main.h"

// static t_vec3 world(t_device *device, t_vec3 pos_screen)
// {
// 	const float x_scale = 2.0f / device->win_width;
// 	const float y_scale = 2.0f / device->win_height;
// 	const float aspect_ratio = (float)device->win_width / device->win_height;

// 	// 3차원 공간으로 확장.
// 	return (gl_vec3_3f((pos_screen.x * x_scale - 1.0f) * aspect_ratio, -pos_screen.y * y_scale + 1.0f, 0.0f));
// }

void	print_error_and_exit(t_device *device, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	engine_exit(device, EXIT_FAILURE);
}

// parse and return t_vec3.
t_vec3	parse_3float(t_device *device, char* line)
{
	char **each = ft_split(line, ',');
	if (get_strs_count(each) != 3) // WARN:  Memory leak on strs..?
		print_error_and_exit(device, ".rt file error\n");
	t_vec3 result = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
	free_split_char(each);
	return (result);
}

void	parse_sphere(t_device *device, char **line_split)
{
	size_t	strs_count = get_strs_count(line_split);
	// (1) check if sp has 4 char members
	if (strs_count != 4 && strs_count != 7)
		print_error_and_exit(device, "[0] .rt file error\n");

	t_object *new_obj = ft_calloc(1, sizeof(*new_obj));
	new_obj->type = TYPE_SPHERE;

	new_obj->sphere.center = parse_3float(device, line_split[1]);
	new_obj->sphere.radius = atof(line_split[2]);
	new_obj->material.diffuse = parse_3float(device, line_split[3]); // = Color
	/**
	 * *  NOTE:  Default Material Value setting.
	 */
	new_obj->material.specular = gl_vec3_1f(255.0f);
	new_obj->material.ks = 0.5f;
	new_obj->material.alpha = 9.0f;

	/** PARSE FORMAT
	 * * sp  [center]0.5,0.0,1.5     [radius]0.5     [diff]250,0,0  [spec]255,255,255   [ks]0.5   [alpha]9.0f
	 * */
	if (strs_count == 7)
	{
		new_obj->material.specular = parse_3float(device, line_split[4]);
		new_obj->material.ks = atof(line_split[5]);
		new_obj->material.alpha = atof(line_split[6]);
	}
	// new_sphere->reflection = 0.0f;
	// new_sphere->transparency = 0.0f;
	device->objects->push_back(device->objects, new_obj);
}

void	parse_light(t_device *device, char **line_split)
{
	// if light is more than 1, or is in wrong format
	if (device->light->has_light == true || get_strs_count(line_split) != 4)
		print_error_and_exit(device, "[1] .rt file error\n");
	device->light->pos = parse_3float(device, line_split[1]);
	device->light->brightness_ratio = atof(line_split[2]);
	device->light->color = parse_3float(device, line_split[3]);
	device->light->has_light = true;
}

void	parse_ambient_light(t_device *device, char **line_split)
{
	// if light is more than 1, or is in wrong format
	if (device->ambient_light->has_ambient_light == true || get_strs_count(line_split) != 3)
		print_error_and_exit(device, "[2] .rt file error\n");
	device->ambient_light->brightness_ratio = atof(line_split[1]);
	device->ambient_light->color = parse_3float(device, line_split[2]);
	device->ambient_light->has_ambient_light = true;
}

void	parse_camera(t_device *device, char **line_split)
{
	// if camera is more than 1, or is in wrong format
	if (device->camera->has_camera == true || get_strs_count(line_split) != 4)
		print_error_and_exit(device, "[3] .rt file error\n");
	device->camera->dir = parse_3float(device, line_split[1]);
	device->camera->pos = parse_3float(device, line_split[2]);
	device->camera->fov = atof(line_split[3]);
	device->camera->has_camera = true;
}

void	parse_each(t_device *device, char **line_split)
{
	// TODO:  if data format is wrong while parsing, stop parsing and call engine_exit()
	// if camera
	if (ft_strncmp(line_split[0], "C", ft_strlen(line_split[0])) == 0)
	// if camera
	{
		printf("parsing Camera...\n");
		parse_camera(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "A", ft_strlen(line_split[0])) == 0)
	// if ambient light
	{
		printf("parsing Ambient light...\n");
		parse_ambient_light(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "L", ft_strlen(line_split[0])) == 0)
	// if light
	{
		printf("parsing Light...\n");
		parse_light(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "sp", ft_strlen(line_split[0])) == 0)
	// if sphere
	{
		printf("parsing Sphere...\n");
		parse_sphere(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "pl", ft_strlen(line_split[0])) == 0)
	// if plane
	{
	}
	else if (ft_strncmp(line_split[0], "cy", ft_strlen(line_split[0])) == 0)
	// if cylinder
	{
	}
	else if (ft_strncmp(line_split[0], "co", ft_strlen(line_split[0])) == 0)
	// if cone
	{
	}
	else
	{
		// TODO:  parse error, call engine_exit.
	}
}

/** return (-1) on parse failure. */
void	parse_rt_file_to_device(t_device *device, char *file)
{
	int	fd;
	char	*pa_line;
	char	**pa_line_split;

	printf("File Name : %s\n", file);
	if (ft_strnstr(file, ".rt", ft_strlen(file)) == NULL && file[ft_strlen(file) - 3] == '.')
		print_error_and_exit(device, ".rt format error\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error_and_exit(device, ".rt format error\n");
	pa_line = get_next_line(fd);
	while (pa_line != NULL)
	{
		// Skip empty line
		if (pa_line[0] == '#' || (ft_strlen(pa_line) == 1 && pa_line[0] == '\n'))
		{
			free(pa_line);
			pa_line = get_next_line(fd);
			continue ;
		}
		pa_line_split = ft_split(pa_line, ' ');
		// parse each line
		parse_each(device, pa_line_split);
		free_split_char(pa_line_split);
		free(pa_line);
		pa_line = get_next_line(fd);
	}
};

