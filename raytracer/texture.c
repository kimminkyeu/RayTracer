/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/14 14:45:10 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "main.h"

t_texture	*new_texture(t_device *device, char* filename)
{
	t_texture	*texture;

	texture = ft_calloc(1, sizeof(*texture));
	if (device == NULL || filename == NULL || texture == NULL)
		return (NULL);

	int width;
	int height;

	// 개행을 지워야 한다.
	char *filename_without_newline = ft_strtrim(filename, "\n");
	texture->image.img_ptr = mlx_xpm_file_to_image(device->mlx, filename_without_newline, &width, &height);
	texture->image.mlx_ptr = device->mlx;
	free(filename_without_newline);

	if (texture->image.img_ptr == NULL)
	{
		printf("Error while loading texture [%s]\n", filename);
		free(texture);
		return (NULL);
	}
	texture->width = width;
	texture->image.img_size.width = width;
	texture->height = height;
	texture->image.img_size.height = height;
	texture->image.addr = mlx_get_data_addr(texture->image.img_ptr, \
				&(texture->image.bits_per_pixel), \
				&(texture->image.line_length), &(texture->image.endian));
	return (texture);
}

t_vec3 get_clamped(t_texture *texture, int i, int j)
{
	i = clamp_int(i, 0, texture->width - 1);
	j = clamp_int(j, 0, texture->height - 1);

	t_vec4 point = gl_get_pixel_color_vec4(&texture->image, i, j);
	// const float r = texture->image[(i + texture->width * j) /* * channels */ + 0] / 255.0f;
	const float r = point.r / 255.0f;
	// const float g = texture->image[(i + texture->width * j) /* * channels */ + 1] / 255.0f;
	const float g = point.g / 255.0f;
	// const float b = texture->image[(i + texture->width * j) /* * channels */ + 2] / 255.0f;
	const float b = point.b / 255.0f;

	return gl_vec3_3f(r, g, b);
}

t_vec3 get_wrapped(t_texture *texture, int i, int j)
{
	i %= texture->width; // i가 width면 0으로 바뀜
	j %= texture->height;

	if (i < 0)
		i += texture->width; // i가 -1이면 (width-1)로 바뀜
	if (j < 0)
		j += texture->height;

	t_vec4 point = gl_get_pixel_color_vec4(&texture->image, i, j);
	// const float r = image[(i + width * j) * channels + 0] / 255.0f;
	const float r = point.r / 255.0f;
	// const float g = image[(i + width * j) * channels + 1] / 255.0f;
	const float g = point.g / 255.0f;
	// const float b = image[(i + width * j) * channels + 2] / 255.0f;
	const float b = point.b / 255.0f;

	return gl_vec3_3f(r, g, b);
}

t_vec3 interpolate_bilinear(
	const float dx,
	const float dy,
	const t_vec3 c00,
	const t_vec3 c10,
	const t_vec3 c01,
	const t_vec3 c11)
{
	(void)dx, (void)dy, (void)c00, (void)c10, (void)c01, (void)c11;
	// ...
	return gl_vec3_1f(1.0f);
}

t_vec3 sample_point(t_texture *texture, const t_vec2 uv) // Nearest sampling이라고 부르기도 함
{
	(void)uv; (void)texture;
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	// 배열 인덱스의 정수 범위 ij [0, width-1] x [0, height - 1]

	// vec2 xy = ...;
	// int i = ...;
	// int j = ...;

	// return GetClamped(i, j);
	return get_clamped(texture, 0, 0);
}

t_vec3 sample_linear(t_texture *texture, const t_vec2 uv)
{
	(void)uv; (void)texture;
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	// std::cout << floor(-0.3f) << " " << int(-0.3f) << std::endl; // -1 0

	// const vec2 xy = ...;
	// const int i = ...;
	// const int j = ...;
	// const float dx = ...;
	// const float dy = ...;

	// return InterpolateBilinear(dx, dy, GetClamped(i, j), GetClamped(i + 1, j), GetClamped(i, j + 1), GetClamped(i + 1, j + 1));
	return gl_vec3_1f(1.0f);
}
