/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 23:30:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/15 01:45:52 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_color.h"
#include "gl_draw.h"
#include "gl_vec4.h"
#include "libft.h"
#include "main.h"
#include "mlx_linux.h"


int	update_func(t_device *device, t_image *img)
{
	/** WARN: Use Static Variable for private data member! */
	(void)device;
	(void)img;

	/** [Separable Convolution]
	 *  한 번에 2차원 Kernel을 적용하는 대신에 1차원 Kernel(가로, 세로)를 두번 적용.
	 *  이해하기 쉽고 효율적이다. */
	int x = 0;
	int y = 0;
	int si = 0;
	// blurred image buffer. --> 원본에다 바로 반영하면 안되기 때문. 결과를 저장할 버퍼가 필요함.
	int	pixel_color_buffer[(int)img->img_size.width * (int)img->img_size.height];

	printf("pixel buffer size: %d\n", (int)img->img_size.width * (int)img->img_size.height);

	// NOTE:   세로 한칸
	while (y < (int)img->img_size.height)
	{
		x = 0;
		// NOTE:   가로 한칸
		while (x < (int)img->img_size.width)
		{
			// 주변 픽셀들의 색을 평균 내어서 (x, y)에 있는 픽셀의 색을 변경. from 홍정모.
			t_vec4	neighbor_color_sum;
			neighbor_color_sum = gl_vec4_1f(0.0f);

			si = 0;
			while (si < 5) // 5개의 1차원 Kernel
			{
				// 가로방향 Kernel 5개의 색을 모두 합친 뒤, 평균으로 나눈다 (sum *= 0.2f)
				t_vec4	neighbor_color;

				neighbor_color = gl_get_pixel_color_vec4(img, x - 2 + si, y); // get color of 5 row.
				neighbor_color_sum.r += neighbor_color.r;
				neighbor_color_sum.g += neighbor_color.g;
				neighbor_color_sum.b += neighbor_color.b;
				si++;
			}

			// 가로 5개 평균 구해서 중심점 픽셀의 색 구하기.
			// neighbor_color_sum = gl_vec4_multiply_scalar(neighbor_color_sum, 0.2f); // 평균 1/5
			neighbor_color_sum.r *= 0.2f;
			neighbor_color_sum.g *= 0.2f;
			neighbor_color_sum.b *= 0.2f;

			// printf("%d\n", x + y * ((int)img->img_size.width));
			pixel_color_buffer[x + (y * ((int)img->img_size.width))] = gl_get_color_from_vec4(neighbor_color_sum); // 버퍼에 저장.

			x++;
		}
		y++;
	}
	// (void)pixel_color_buffer;
	// copy pixel_color_buffer's memory to image.
	// ft_memcpy(img->addr, (char *)pixel_color_buffer, (int)img->img_size.width * (int)img->img_size.height);
	// ft_memmove(img->addr, pixel_color_buffer, (int)img->img_size.width * (int)img->img_size.height);
	// ft_memmove(img->addr, pixel_color_buffer, (int)img->img_size.width * 100);


	// FIX:  문제는 memcpy도 아니고, 그냥 pixel_color_buffer문제임. 값이 이상함.
	if (pixel_color_buffer[0 + (0 * ((int)img->img_size.width))] == pixel_color_buffer[0 + (20 * ((int)img->img_size.width))])
	{
		printf("Something is wrong\n");
	}

	// FIX:  왜 1차원 배열처럼 memcpy쓰면 이상해지는겨>?
	int i = 0;
	int j = 0;
	while (i < (int)img->img_size.height)
	{
		j = 0;
		while (j < (int)img->img_size.width)
		{
			int *pixel = gl_get_pixel_addr(img, j, i);
			*pixel = pixel_color_buffer[j + (i * ((int)img->img_size.width))];
			j++;
		}
		i++;
	}




	return (0);
}