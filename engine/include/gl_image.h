/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_image_filter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:03:32 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/12 21:39:26 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_FILTER_H
# define IMAGE_FILTER_H

# include "gl_device.h"
# include "gl_color.h"
# include "gl_draw.h"
# include "gl_vec4.h"

extern void	gl_image_brightness(t_image *image, float brightness_factor);


#endif /* IMAGE_FILTER_H */
