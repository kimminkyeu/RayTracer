/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file_to_device.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:35:05 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 17:19:05 by minkyeki         ###   ########.fr       */
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

void	parse_each(t_device *device, char **line_split)
{
	// TODO:  if data format is wrong while parsing, stop parsing and call engine_exit()
	// if camera
	if (ft_strncmp(line_split[0], "C", ft_strlen(line_split[0])) == 0)
	// if camera
	{
	}
	else if (ft_strncmp(line_split[0], "A", ft_strlen(line_split[0])) == 0)
	// if ambient light
	{
	}
	else if (ft_strncmp(line_split[0], "L", ft_strlen(line_split[0])) == 0)
	// if light
	{
	}
	else if (ft_strncmp(line_split[0], "sp", ft_strlen(line_split[0])) == 0)
	// if sphere
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
		new_sphere->center = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
		free_split_char(each);
		new_sphere->radius = atof(line_split[2]);
		each = ft_split(line_split[3], ',');
		if (get_strs_count(each) != 3)
		{
			// TODO: print message of error log.
			engine_exit(device, EXIT_FAILURE);
		}
		new_sphere->color = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
		device->objects.spheres->push_back(device->objects.spheres, new_sphere);
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

	printf("file : %s\n", file);
	// (1) check if file is able to open.
	// WARN:  (1-1) if file name if not with .rt, return error!
	if (ft_strnstr(file, ".rt", ft_strlen(file)) == NULL)
	{
		ft_putstr_fd("95\n", 1);
		// ... error message
		engine_exit(device, EXIT_FAILURE);
	}

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("103\n", 1);
		// ... error message
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

