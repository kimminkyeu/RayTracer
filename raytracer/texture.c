/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/13 17:50:55 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "main.h"

t_texture	*new_texture(t_device *device, const char* filename)
{
	t_texture	*texture;

	texture = ft_calloc(1, sizeof(*texture));
	if (device == NULL || filename == NULL || texture == NULL)
		return (NULL);
	texture->image.img_ptr = mlx_xpm_file_to_image(device->mlx, filename, &texture->image.img_size.width, &texture->image.img_size.height);
	texture->width = texture->image.img_size.width;
	texture->height = texture->image.img_size.height;
	if (texture->image.img_ptr == NULL)
		return (NULL);
	texture->image.addr = mlx_get_data_addr(texture->image.img_ptr, \
				&(texture->image.bits_per_pixel), \
				&(texture->image.line_length), &(texture->image.endian));
	return (texture);
}

t_vec3 get_clamped(int i, int j)
{
	i = clamp_int(i, 0, width - 1);
	j = clamp_int(j, 0, height - 1);

	const float r = image[(i + width * j) * channels + 0] / 255.0f;
	const float g = image[(i + width * j) * channels + 1] / 255.0f;
	const float b = image[(i + width * j) * channels + 2] / 255.0f;

	return gl_vec3_3f(r, g, b);
}

t_vec3 get_wrapped(int i, int j)
{
	i %= width; // i가 width면 0으로 바뀜
	j %= height;

	if (i < 0)
		i += width; // i가 -1이면 (width-1)로 바뀜
	if (j < 0)
		j += height;

	const float r = image[(i + width * j) * channels + 0] / 255.0f;
	const float g = image[(i + width * j) * channels + 1] / 255.0f;
	const float b = image[(i + width * j) * channels + 2] / 255.0f;

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
	// ...

	return gl_vec3_1f(1.0f);
}

t_vec3 sample_point(const t_vec2 uv) // Nearest sampling이라고 부르기도 함
{
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	// 배열 인덱스의 정수 범위 ij [0, width-1] x [0, height - 1]

	// vec2 xy = ...;
	// int i = ...;
	// int j = ...;

	// return GetClamped(i, j);
	return get_clamped(0, 0);
}

t_vec3 sample_linear(const t_vec2 uv)
{
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
