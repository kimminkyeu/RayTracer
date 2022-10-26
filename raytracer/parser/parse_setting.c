/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:38:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 17:25:13 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_renderer_setting(t_device *device, char *line)
{
	t_setting	*s;
	int			cnt;

	printf("*------------------------------*\n");
	printf("|   Parsing renderer setting   |\n");
	printf("*------------------------------*\n");
	s = &device->renderer_settings;
	cnt = ft_lscanf(line, \
					"Setting%wW:%d%wH:%d%wRR:%f%w|%wTH:%d%w|%wAA:%d%wRF:%d\n", \
					&s->win_width, &s->win_height, &s->resolution_ratio, \
					&s->num_of_threads, &s->antialiasing_level, &s->reflection_level);

	printf("W:%d H:%d RR:%f TH:%d AA:%d RF:%d\n\n", \
			s->win_width, s->win_height, s->resolution_ratio, \
			s->num_of_threads, s->antialiasing_level, s->reflection_level);
	if (cnt != 6)
		print_error_and_exit(device, "parse_renderer_setting(): .rt file error\n");
}
