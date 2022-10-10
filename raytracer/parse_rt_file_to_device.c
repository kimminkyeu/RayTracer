/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file_to_device.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:35:05 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/10 16:30:31 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "vector.h"
#include "gl_device.h"
#include "gl_engine.h"

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
		t_sphere *new_sphere = ft_calloc(1, sizeof(*new_sphere));

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
int	parse_rt_file_to_device(t_device *device, char *file)
{
	// (1) check if file is able to open.

	// WARN:  (1-1) if file name if not with .rt, return error!

	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		// ... error message
		engine_exit(device, EXIT_FAILURE);
	}

	t_objects *objs = &(device->objects);

	char	*pa_line;
	pa_line = get_next_line(fd);

	char	**pa_line_split;

	while (pa_line != NULL)
	{
		pa_line_split = ft_split(pa_line, ' ');

		// parse each line
		parse_each(device, pa_line_split);

		// free each line
		int i = -1;
		while (pa_line_split[++i])
			free(pa_line_split[i]);
		free(pa_line_split);
		free(pa_line);
		pa_line = get_next_line(fd);
	}
};

