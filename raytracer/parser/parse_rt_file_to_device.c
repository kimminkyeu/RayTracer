/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file_to_device.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:35:05 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 05:56:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_each(t_device *device, char *line)
{
	if (ft_strncmp(line, "C ", 2) == 0)
		parse_camera(device, line);
	else if (ft_strncmp(line, "A ", 2) == 0)
		parse_ambient_light(device, line);
	else if (ft_strncmp(line, "L ", 2) == 0)
		parse_light(device, line);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		parse_sphere(device, line);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		parse_plane(device, line);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		parse_cylinder(device, line);
	else if (ft_strncmp(line, "co ", 3) == 0)
		parse_cone(device, line);
	else if (ft_strncmp(line, "tr ", 3) == 0)
		parse_triangle(device, line);
	else if (ft_strncmp(line, "sq ", 3) == 0)
		parse_square(device, line);
	else
		print_error_and_exit(device, "parse_each(): .rt format error\n");
}

void	parse_rt_file_to_device(t_device *device, char *file)
{
	int		fd;
	char	*pa_line;

	printf("File Name : %s\n", file);
	if (ft_strnstr(file, ".rt", ft_strlen(file)) == NULL && file[ft_strlen(file) - 3] == '.')
		print_error_and_exit(device, "parse_rt_file_to_device: .rt format error\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error_and_exit(device, "parse_rt_file_to_device: .rt format error\n");
	pa_line = get_next_line(fd);
	while (pa_line != NULL)
	{
		if (pa_line[0] == '#' || (ft_strlen(pa_line) == 1 && pa_line[0] == '\n'))
		{
			free(pa_line);
			pa_line = get_next_line(fd);
			continue ;
		}
		parse_each(device, pa_line);
		free(pa_line);
		pa_line = get_next_line(fd);
	}
};
