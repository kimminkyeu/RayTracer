/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:21:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/24 09:08:35 by minkyeki         ###   ########.fr       */
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


/**
 * if success, return (0).
 * if parse fail, return (-1).
 * NOTE:  Function parsed .rt format file and saves it to *device/
*/
extern void	parse_rt_file_to_device(t_device *device, char *file);

extern int	update(t_device *device);

#endif /* MAIN_H */
