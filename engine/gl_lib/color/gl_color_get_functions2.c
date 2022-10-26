/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_color_get_functions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:58:42 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:59:05 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	gl_color_get_alpha(int argb)
{
	return (((unsigned char *)&argb)[3]);
}

unsigned char	gl_color_get_red(int argb)
{
	return (((unsigned char *)&argb)[2]);
}

unsigned char	gl_color_get_green(int argb)
{
	return (((unsigned char *)&argb)[1]);
}

unsigned char	gl_color_get_blue(int argb)
{
	return (((unsigned char *)&argb)[0]);
}
