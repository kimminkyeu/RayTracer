/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file_to_device.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:35:05 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/11 16:46:11 by minkyeki         ###   ########.fr       */
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

void	parse_sphere(t_device *device, char **line_split)
{
	// (1) check if sp has 4 char members
	if (get_strs_count(line_split) != 4)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	t_sphere *new_sphere = ft_calloc(1, sizeof(*new_sphere));

	// TODO:  check if atof is successful, or has 3 member
	char **each = ft_split(line_split[1], ',');
	if (get_strs_count(each) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}

	// TODO:  world좌표계 기준으로 위치와 크기를 재설정.


	new_sphere->center = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
	free_split_char(each);
	new_sphere->radius = atof(line_split[2]);
	each = ft_split(line_split[3], ',');
	if (get_strs_count(each) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	new_sphere->color = gl_vec3_3f(atof(each[2]), atof(each[1]), atof(each[0]));
	free_split_char(each);


	/**
	 * *  NOTE:  퐁 쉐이딩용 테스트 코드이며, 추후에 이 값을 반드시 정리할 것.
	 */
	// ambient는 일단 없애기.
	// new_sphere->ambient = gl_vec3_multiply_scalar(new_sphere->color, 0.0f);
	new_sphere->ambient = gl_vec3_1f(0.0f);

	// new_sphere->diffuse = gl_vec3_1f(0.0f);
	new_sphere->diffuse = new_sphere->color;

	// 반사된 빛은 하얀색.
	new_sphere->specular = gl_vec3_1f(255.0f);

	new_sphere->ks = 0.5f;
	new_sphere->alpha = 9.0f; // phong-shading에서 specular를 몇 제곱 할 것인지.
	// new_sphere->reflection = 0.0f;
	// new_sphere->transparency = 0.0f;


	device->objects.spheres->push_back(device->objects.spheres, new_sphere);
}

void	parse_light(t_device *device, char **line_split)
{
	if (device->light->has_light == true)
	{
		// light 의 개수는 오로지 1개 이하만 가능!
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	// (1) check if sp has 4 char members
	if (get_strs_count(line_split) != 4)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	// TODO:  check if atof is successful, or has 3 member
	char **each = ft_split(line_split[1], ',');
	if (get_strs_count(each) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	device->light->pos = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
	free_split_char(each);
	device->light->brightness_ratio = atof(line_split[2]);
	each = ft_split(line_split[3], ',');
	if (get_strs_count(each) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	device->light->color = gl_vec3_3f(atof(each[2]), atof(each[1]), atof(each[0]));
	free_split_char(each);
	device->light->has_light = true;
}

void	parse_ambient_light(t_device *device, char **line_split)
{
	if (device->ambient_light->has_ambient_light == true)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	// (1) check if sp has 4 char members
	if (get_strs_count(line_split) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	device->ambient_light->brightness_ratio = atof(line_split[2]);
	char **each = ft_split(line_split[3], ',');
	if (get_strs_count(each) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	device->ambient_light->color = gl_vec3_3f(atof(each[2]), atof(each[1]), atof(each[0]));
	free_split_char(each);
	device->ambient_light->has_ambient_light = true;
}

void	parse_camera(t_device *device, char **line_split)
{
	// (1) check if sp has 4 char members
	if (device->camera->has_camera == true)
	{
		// TODO:  print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	if (get_strs_count(line_split) != 4)
	{
		// TODO:  print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	// TODO:  check if atof is successful, or has 3 member
	char **each = ft_split(line_split[1], ',');
	if (get_strs_count(each) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	device->camera->dir = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
	free_split_char(each);
	each = ft_split(line_split[2], ',');
	if (get_strs_count(each) != 3)
	{
		// TODO: print message of error log.
		engine_exit(device, EXIT_FAILURE);
	}
	device->camera->pos = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
	free_split_char(each);
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

	printf("File Name : %s\n", file);
	// (1) check if file is able to open.
	// WARN:  (1-1) if file name if not with .rt, return error!
	if (ft_strnstr(file, ".rt", ft_strlen(file)) == NULL && file[ft_strlen(file) - 3] == '.')
	{
		// ... TODO:  error message
		engine_exit(device, EXIT_FAILURE);
	}

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		// ... TODO:  error message
		engine_exit(device, EXIT_FAILURE);
	}

	char	*pa_line;
	char	**pa_line_split;

	pa_line = get_next_line(fd);
	while (pa_line != NULL)
	{
		pa_line_split = ft_split(pa_line, ' ');

		// parse each line
		parse_each(device, pa_line_split);

		// free each line
		free_split_char(pa_line_split);
		free(pa_line);
		pa_line = get_next_line(fd);
	}
};

