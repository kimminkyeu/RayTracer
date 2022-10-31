/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 23:30:24 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // usleep
#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec2.h"
#include "gl_vec3.h"
#include "mlx_linux.h"
#include "texture.h"
#include "main.h"

void	fill_checker_board(t_texture *texture)
{
	int	x;
	int	y;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			if (x % 2 == y % 2)
				gl_draw_pixel(&texture->image, x, y, BLACK);
			else
				gl_draw_pixel(&texture->image, x, y, WHITE);
			x++;
		}
		y++;
	}
}

t_texture	*new_texture_checkerboard(t_device *device, int width, int height)
{
	t_texture	*texture;

	if (device == NULL)
		return (NULL);
	texture = ft_calloc(1, sizeof(*texture));
	texture->image.img_ptr = mlx_new_image(device->mlx, width, height);
	texture->image.mlx_ptr = device->mlx;
	if (texture->image.img_ptr == NULL)
	{
		free(texture);
		return (NULL);
	}
	texture->type = TEXTURE_CHECKER;
	texture->width = width;
	texture->image.img_size.width = width;
	texture->height = height;
	texture->image.img_size.height = height;
	texture->image.addr
		= mlx_get_data_addr(texture->image.img_ptr,
			&(texture->image.bits_per_pixel),
			&(texture->image.line_length), &(texture->image.endian));
	fill_checker_board(texture);
	return (texture);
}

void	init_texture(t_texture *texture, int width, int height)
{
	texture->width = width;
	texture->image.img_size.width = width;
	texture->height = height;
	texture->image.img_size.height = height;
	texture->image.addr = mlx_get_data_addr(texture->image.img_ptr, \
				&(texture->image.bits_per_pixel), \
				&(texture->image.line_length), &(texture->image.endian));
}

t_texture	*new_texture(t_device *device, char *filename)
{
	t_texture	*texture;
	char		*filename_without_newline;
	int			width;
	int			height;

	printf("Loading file %s\n", filename);
	if (device == NULL || filename == NULL)
		return (NULL);
	texture = ft_calloc(1, sizeof(*texture));
	texture->type = TEXTURE_FILE;
	filename_without_newline = ft_strtrim(filename, "\n");
	texture->image.img_ptr
		= mlx_xpm_file_to_image(device->mlx,
			filename_without_newline, &width, &height);
	free(filename_without_newline);
	if (texture->image.img_ptr == NULL)
	{
		printf("Error while loading texture [%s]\n", filename);
		free(texture);
		return (NULL);
	}
	texture->image.mlx_ptr = device->mlx;
	init_texture(texture, width, height);
	return (texture);
}
