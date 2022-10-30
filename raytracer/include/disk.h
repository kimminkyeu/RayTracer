/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 21:10:14 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/30 23:03:42 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISK_H
# define DISK_H

# include "gl_vec3.h"
# include "hit.h"
# include "ray.h"
# include "helper.h"

typedef struct s_disk {
	t_vec3	center;
	t_vec3	orientation;
	float	radius;
}	t_disk;

extern t_hit	disk_intersect_ray_collision(const t_ray *ray, t_disk *disk);

#endif /** Disk.h */
