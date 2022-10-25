/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:11:52 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 01:58:20 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "gl_engine.h"

typedef struct s_texture {

	int 		width;
	int 		height;
	t_image		image; // texture image.
	int			type; // type of texture.  --> 나중에 체커는 sample_point로 하기 위함.

}	t_texture;

void	set_default_material(t_material *m)
{
	m->diffuse = gl_vec3_1f(255.0f);
	m->specular = gl_vec3_1f(255.0f);
	m->alpha = 10.0f;
	m->ks = 0.8f;
	m->transparency = 0.0f;
	m->reflection = 0.0f;
	m->ior = 1.5f;
}

t_object *custom_allocator_for_object(int obj_type)
{
	t_object *new_obj;

	new_obj = ft_calloc(1, sizeof(*new_obj));
	set_default_material(&new_obj->material);
	new_obj->type = obj_type;
	if (obj_type == TYPE_SPHERE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_sphere));
	else if (obj_type == TYPE_TRIANGLE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_triangle));
	else if (obj_type == TYPE_SQUARE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_square));
	else if (obj_type == TYPE_PLANE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_plane));
	else if (obj_type == TYPE_CYLINDER)
		new_obj->obj_data = ft_calloc(1, sizeof(t_cylinder));
	else if (obj_type == TYPE_CONE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_cone));
	else
		new_obj->obj_data = NULL;
	return (new_obj);
}

// delete texture image
void	custom_deallocator_for_object(void *data)
{
	t_object *obj_ptr = data;
	if (obj_ptr->obj_data != NULL)
		free(obj_ptr->obj_data);
	if (obj_ptr->diffuse_texture != NULL)
	{
		mlx_destroy_image(obj_ptr->diffuse_texture->image.mlx_ptr, obj_ptr->diffuse_texture->image.img_ptr);
		free(obj_ptr->diffuse_texture);
	}
	if (obj_ptr->normal_texture != NULL)
	{
		mlx_destroy_image(obj_ptr->normal_texture->image.mlx_ptr, obj_ptr->normal_texture->image.img_ptr);
		free(obj_ptr->normal_texture);
	}
}
