/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:03:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 17:42:38 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "libft.h"
# include "gl_vec3.h"
# include "gl_vec2.h"

# include "plane.h"

# include "sphere.h"
# include "cone.h"
# include "cylinder.h"

# include "lights.h"
# include "camera.h"

typedef struct s_texture	t_texture;

/* ---------------------------------
		Objects type-definition
   --------------------------------- */
# define TYPE_NO_HIT		(0)
# define TYPE_SPHERE		(1)
# define TYPE_PLANE			(2)
# define TYPE_CYLINDER		(3)
# define TYPE_CONE			(4)
# define TYPE_TRIANGLE		(5)
# define TYPE_SQUARE   		(6)

typedef struct s_material {
	t_vec3	diffuse;
	t_vec3	specular;
	float	ks;
	float	alpha;
	float	reflection;
	float	transparency;
	float	ior;
}	t_material;

typedef struct s_object {
	t_material	material;
	int			type;
	void		*obj_data;
	t_texture	*diffuse_texture;
	t_texture	*normal_texture;
}	t_object;

extern t_object	*custom_allocator_for_object(int obj_type);

extern void		custom_deallocator_for_object(void *data);

#endif /* objects.h */
