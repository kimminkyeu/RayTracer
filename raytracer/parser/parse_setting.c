/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_setting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:38:11 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 22:19:25 by minkyeki         ###   ########.fr       */
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
	"Setting%wW:%d%wH:%d%wRR:%f%w|%wTH:%d%w|%wAA:%d%wRF:%d%w|%wSKY:%f,%f,%f\n", \
			&s->win_width, &s->win_height, &s->resolution_ratio, \
			&s->num_of_threads, &s->antialiasing_level, &s->reflection_level, \
			&s->sky_color.r, &s->sky_color.g, &s->sky_color.b);
	printf("W:%d H:%d RR:%f TH:%d AA:%d RF:%d SKY:%f,%f,%f\n\n", \
			s->win_width, s->win_height, s->resolution_ratio, \
			s->num_of_threads, s->antialiasing_level, s->reflection_level, \
			s->sky_color.r, s->sky_color.g, s->sky_color.b);
	if (cnt != 9)
		print_error_and_exit(device, "renderer_setting(): .rt file error\n");
}
