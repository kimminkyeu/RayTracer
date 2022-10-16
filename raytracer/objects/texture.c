/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:06:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/17 00:31:11 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> // usleep
#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec2.h"
#include "gl_vec3.h"
#include "texture.h"
#include "main.h"

// width and height is resolution of the checkerboard_image.

static void fill_checker_board(t_texture *texture)
{
	int x = 0;
	int y = 0;

	// NOTE:  Sample checker board. 나중에 복구할 것.
	// while (y < texture->height)
	// {
	// 	x = 0;
	// 	while (x < texture->width)
	// 	{
	// 		if (x % 2 == y % 2) // (0,0) (1,1) (0,2) (0,4) (2,2)...
	// 			gl_draw_pixel(&texture->image, x, y, BLACK);
	// 		else
	// 			gl_draw_pixel(&texture->image, x, y, WHITE);
	// 		x++;
	// 	}
	// 	y++;
	// }

	// NOTE:  sample_linear 테스트용.
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			if (y % 4 == 0)
			{
				t_vec3 color = gl_vec3_multiply_scalar(gl_vec3_3f(255.0f, 0.0f, 0.0f), (1.0f + x) * 0.25f);
				gl_draw_pixel(&texture->image, x, y, gl_get_color_from_4int(0, color.r, color.g, color.b));
			}
			else if (y % 4 == 1)
			{
				t_vec3 color = gl_vec3_multiply_scalar(gl_vec3_3f(0.0f, 255.0f, 0.0f), (1.0f + x) * 0.25f);
				gl_draw_pixel(&texture->image, x, y, gl_get_color_from_4int(0, color.r, color.g, color.b));
			}
			else if (y % 4 == 2)
			{
				t_vec3 color = gl_vec3_multiply_scalar(gl_vec3_3f(0.0f, 0.0f, 255.0f), (1.0f + x) * 0.25f);
				gl_draw_pixel(&texture->image, x, y, gl_get_color_from_4int(0, color.r, color.g, color.b));
			}
			else
			{
				t_vec3 color = gl_vec3_multiply_scalar(gl_vec3_3f(255.0f, 255.0f, 255.0f), (1.0f + x) * 0.25f);
				gl_draw_pixel(&texture->image, x, y, gl_get_color_from_4int(0, color.r, color.g, color.b));
			}
			x++;
		}
		y++;
	}
}

t_texture	*new_texture_checkerboard(t_device *device, int width, int height)
{
	t_texture	*texture;

	texture = ft_calloc(1, sizeof(*texture));
	if (device == NULL || texture == NULL)
		return (NULL);

	// TODO: change checkerboard resolution later!
	texture->image.img_ptr = mlx_new_image(device->mlx, width, height);
	texture->image.mlx_ptr = device->mlx;
	if (texture->image.img_ptr == NULL)
	{
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

	fill_checker_board(texture); // fill checkerboard texture to image
	return (texture);
}

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

/* index가 범위를 넘어서면 clamp 해줌.*/
t_vec3 get_clamped(t_texture *texture, int i, int j)
{
	i = clamp_int(i, 0, texture->width - 1);
	j = clamp_int(j, 0, texture->height - 1);

	t_vec4 point = gl_get_pixel_color_vec4(&texture->image, i, j);

	const float r = point.r / 255.0f; // 기존 ambient_color에 나중에 곱해서, 그 값만큼 색을 바꿈. --> 홍정모 코드의 색은 0 ~ 255.0 사이.
	const float g = point.g / 255.0f;
	const float b = point.b / 255.0f;
	return gl_vec3_3f(r, g, b);
}


t_vec3 sample_point(t_texture *texture, const t_vec2 uv)
// OpenGL에서는 Nearest sampling이라고 부르기도 함
{
	(void)uv; (void)texture;
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// TODO: 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	// 배열 인덱스의 정수 범위 ij [0, width-1] x [0, height - 1]

	// (1) uv 좌표를 그대로 width/height로 일단 변환하면...
	t_vec2 xy = gl_vec2_2f(uv.x * (float)texture->width, uv.y * (float)texture->height);

	// (2) 시작 위치 동일하게 맞추기 (-0.5f) // WARN:  But why...?
	xy = gl_vec2_add_float(xy, -0.5f);

	// (3) x y로 부터 2차원 인덱스 구하기
	int i = (int)round(xy.x);
	int j = (int)round(xy.y);
	// int i = (int)xy.x;
	// int j = (int)xy.y;

	return (get_clamped(texture, i, j));
}

/* index가 범위를 넘어서면 index 처음으로 돌아감.(%) */
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
	// const float r = point.r;
	// const float g = image[(i + width * j) * channels + 1] / 255.0f;
	const float g = point.g / 255.0f;
	// const float g = point.g;
	// const float b = image[(i + width * j) * channels + 2] / 255.0f;
	const float b = point.b / 255.0f;
	// const float b = point.b;

	return gl_vec3_3f(r, g, b);
}

t_vec3 get_wrapped_raw(t_texture *texture, int i, int j)
{
	i %= texture->width; // i가 width면 0으로 바뀜
	j %= texture->height;

	if (i < 0)
		i += texture->width; // i가 -1이면 (width-1)로 바뀜
	if (j < 0)
		j += texture->height;

	t_vec4 point = gl_get_pixel_color_vec4(&texture->image, i, j);
	// const float r = image[(i + width * j) * channels + 0] / 255.0f;
	const float r = point.r;
	// const float g = image[(i + width * j) * channels + 1] / 255.0f;
	const float g = point.g;
	// const float b = image[(i + width * j) * channels + 2] / 255.0f;
	const float b = point.b;

	return gl_vec3_3f(r, g, b);
}

/* Used in sample_linear(). linear를 두번 반복하면, bilinear가 된다.*/
t_vec3 interpolate_bilinear(
		const float dx,
		const float dy,
		const t_vec3 c00,
		const t_vec3 c10,
		const t_vec3 c01,
		const t_vec3 c11)
{
	const t_vec3 color_x0 = gl_vec3_add_vector(gl_vec3_multiply_scalar(c00, 1.0f - dx), gl_vec3_multiply_scalar(c10, dx));
	// const t_vec3 color_x0 = gl_vec3_add_vector(gl_vec3_multiply_scalar(c10, 1.0f - dx), gl_vec3_multiply_scalar(c00, dx));
	const t_vec3 color_x1 = gl_vec3_add_vector(gl_vec3_multiply_scalar(c01, 1.0f - dx), gl_vec3_multiply_scalar(c11, dx));
	// const t_vec3 color_x1 = gl_vec3_add_vector(gl_vec3_multiply_scalar(c11, 1.0f - dx), gl_vec3_multiply_scalar(c01, dx));
	const t_vec3 color_y = gl_vec3_add_vector(gl_vec3_multiply_scalar(color_x0, 1.0f - dy), gl_vec3_multiply_scalar(color_x1, dy));
	return (color_y);
}

// linear interpolation
t_vec3 sample_linear(t_texture *texture, const t_vec2 uv)
{
	(void)uv; (void)texture;
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	// std::cout << floor(-0.3f) << " " << int(-0.3f) << std::endl; // -1 0

	t_vec2 xy = gl_vec2_2f(uv.x * (float)texture->width, uv.y * (float)texture->height);
	xy = gl_vec2_add_float(xy, -0.5f);

	const int i = (int)floor(xy.x);
	const int j = (int)floor(xy.y);

	// TODO:  지금 uv 좌표계가 이상하다. 그래서 기존 코드에서 순서를 좀 바꿨다. 나중에 좌표계 고칠 것.
	const float dx = (float)xy.x - (float)i;
	const float dy = (float)xy.y - (float)j;

	// return (interpolate_bilinear(dx, dy, get_clamped(texture, i, j), get_clamped(texture, i + 1, j), get_clamped(texture, i, j + 1), get_clamped(texture, i + 1, j + 1)));
	return (interpolate_bilinear(dx, dy, get_wrapped(texture, i, j), get_wrapped(texture, i + 1, j), get_wrapped(texture, i, j + 1), get_wrapped(texture, i + 1, j + 1)));
}

t_vec3 sample_linear_raw(t_texture *texture, const t_vec2 uv)
{
	(void)uv; (void)texture;
	// 텍스춰 좌표의 범위 uv [0.0, 1.0] x [0.0, 1.0]
	// 이미지 좌표의 범위 xy [-0.5, width - 1 + 0.5] x [-0.5, height - 1 + 0.5]
	// std::cout << floor(-0.3f) << " " << int(-0.3f) << std::endl; // -1 0

	t_vec2 xy = gl_vec2_2f(uv.x * (float)texture->width, uv.y * (float)texture->height);
	xy = gl_vec2_add_float(xy, -0.5f);

	const int i = (int)floor(xy.x);
	const int j = (int)floor(xy.y);

	// TODO:  지금 uv 좌표계가 이상하다. 그래서 기존 코드에서 순서를 좀 바꿨다. 나중에 좌표계 고칠 것.
	const float dx = (float)xy.x - (float)i;
	const float dy = (float)xy.y - (float)j;

	// return (interpolate_bilinear(dx, dy, get_clamped(texture, i, j), get_clamped(texture, i + 1, j), get_clamped(texture, i, j + 1), get_clamped(texture, i + 1, j + 1)));
	return (interpolate_bilinear(dx, dy, get_wrapped_raw(texture, i, j), get_wrapped_raw(texture, i + 1, j), get_wrapped_raw(texture, i, j + 1), get_wrapped_raw(texture, i + 1, j + 1)));
}
