/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:21:12 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 20:22:18 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "gl_engine.h"

extern int	render_layer(t_device *device);
extern int	render_viewport(t_device *device, t_image *viewport);
extern int	render_panel(t_device *device, t_image *panel);

#endif /* MAIN_H */
