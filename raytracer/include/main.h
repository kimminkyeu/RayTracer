/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:21:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/25 19:29:21 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "gl_engine.h"
# include "helper.h"
# include "ray.h"
# include "objects.h"
# include "hit.h"
# include "camera.h"
# include "texture.h"

extern void copy_pixel_buffer_to_screen_image(t_device *device);

extern void *thread_update(void *arg);

extern void create_thread_and_update_each(t_device *device);

extern bool is_high_resolution_mode(t_device *device);

extern void fill_low_resolution_pixel(t_device *device, int x, int y, int argb);

extern int	update(t_device *device);

#endif /* MAIN_H */
