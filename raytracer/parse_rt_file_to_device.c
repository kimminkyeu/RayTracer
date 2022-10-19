/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt_file_to_device.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:35:05 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/20 00:58:51 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "mlx_linux.h"
#include "vector.h"
#include "gl_device.h"
#include "gl_engine.h"
#include "main.h"
#include "texture.h"

t_object *custom_allocator_for_object(int obj_type)
{
	t_object *new_obj;

	new_obj = ft_calloc(1, sizeof(*new_obj));
	new_obj->type = obj_type;
	if (obj_type == TYPE_SPHERE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_sphere));
	else if (obj_type == TYPE_TRIANGLE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_triangle));
	else if (obj_type == TYPE_SQUARE)
		new_obj->obj_data = ft_calloc(1, sizeof(t_square));
	else if (obj_type == TYPE_PLAIN)
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

void	print_error_and_exit(t_device *device, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	engine_exit(device, EXIT_FAILURE);
}

// parse and return t_vec3.
// if is_color is true, then order is (line[2] -> line[1] -> line[0])
t_vec3	parse_3float(t_device *device, char* line, int is_color)
{
	char **each = ft_split(line, ',');
	if (get_strs_count(each) != 3) // WARN:  Memory leak on strs..?
		print_error_and_exit(device, "parse_3float(): .rt file error\n");
	t_vec3 result;
	if (!is_color)
		result = gl_vec3_3f(atof(each[0]), atof(each[1]), atof(each[2]));
	else
		result = gl_vec3_3f(atof(each[2]), atof(each[1]), atof(each[0]));
	free_split_char(each);
	return (result);
}


void	parse_normal_texture(t_device *device, t_object *object, char *file_name)
{
	object->normal_texture = new_texture(device, file_name);
}

void	parse_diffuse_texture(t_device *device, t_object *object, char *file_name)
{
	// TODO:  diffuse_texture는 나중에 추가
	if (ft_strncmp("checker", file_name, 7) == 0)
		object->diffuse_texture = new_texture_checkerboard(device, 32, 32);
	else
		object->diffuse_texture = new_texture(device, file_name);
}

void	parse_sphere(t_device *device, char **line_split)
{
	size_t	strs_count = get_strs_count(line_split);
	// (1) check if sp has 4 char members
	printf("strs_count %zd\n", strs_count);
	if (strs_count != 4 && strs_count != 7 && strs_count != 8 && strs_count != 9)
		print_error_and_exit(device, "parse_sphere(): .rt file error\n");

	// t_object *new_obj = ft_calloc(1, sizeof(*new_obj));
	// new_obj->type = TYPE_SPHERE;
	t_object *new_obj = custom_allocator_for_object(TYPE_SPHERE);
	((t_sphere *)new_obj->obj_data)->center = parse_3float(device, line_split[1], false);
	((t_sphere *)new_obj->obj_data)->radius = atof(line_split[2]);

	new_obj->material.diffuse = parse_3float(device, line_split[3], true); // = Color
	/**
	 * *  NOTE:  Default Material Value setting. (change here!)
	 */
	new_obj->material.specular = gl_vec3_1f(255.0f);
	new_obj->material.ks = 0.5f;
	new_obj->material.alpha = 9.0f;

	// new_obj->material.reflection = 0.5f;
	new_obj->material.transparency = 1.0f;

	if (strs_count == 7 || strs_count == 8 || strs_count == 9)
	{
		new_obj->material.specular = parse_3float(device, line_split[4], true);
		new_obj->material.ks = atof(line_split[5]);
		new_obj->material.alpha = atof(line_split[6]);
	}
	if (strs_count == 8 || strs_count == 9)
		parse_diffuse_texture(device, new_obj, line_split[7]);
	if (strs_count == 9)
		parse_normal_texture(device, new_obj, line_split[8]);

	device->objects->push_back(device->objects, new_obj);
}

void	parse_triangle(t_device *device, char **line_split)
{
	size_t	strs_count = get_strs_count(line_split);
	// (1) check if sp has 4 char members
	if (strs_count != 5 && strs_count != 8 && strs_count != 9 && strs_count != 10)
		print_error_and_exit(device, "parse_triangle(): .rt file error\n");

	// t_object *new_obj = ft_calloc(1, sizeof(*new_obj));
	// new_obj->type = TYPE_TRIANGLE;
	t_object *new_obj = custom_allocator_for_object(TYPE_TRIANGLE);

	// tr vertex1  vertex2   vertex3   diffuseColor(rgb)  specular  ks  alpha
	((t_triangle *)new_obj->obj_data)->v0 = parse_3float(device, line_split[1], false);
	((t_triangle *)new_obj->obj_data)->v1 = parse_3float(device, line_split[2], false);
	((t_triangle *)new_obj->obj_data)->v2 = parse_3float(device, line_split[3], false);

	new_obj->material.diffuse = parse_3float(device, line_split[4], true);

	/**
	 * *  NOTE:  Default Material Value setting.
	 */
	new_obj->material.specular = gl_vec3_1f(255.0f);
	new_obj->material.ks = 0.5f;
	new_obj->material.alpha = 9.0f;
	new_obj->material.reflection = 0.0f;
	new_obj->material.transparency = 0.0f;

	if (strs_count == 8 || strs_count == 9 || strs_count == 10)
	{
		new_obj->material.specular = parse_3float(device, line_split[5], true);
		new_obj->material.ks = atof(line_split[6]);
		new_obj->material.alpha = atof(line_split[7]);
		if (strs_count == 9 || strs_count == 10)
			parse_diffuse_texture(device, new_obj, line_split[8]);
		if (strs_count == 10)
			parse_normal_texture(device, new_obj, line_split[9]);
	}
	// new_sphere->reflection = 0.0f;
	// new_sphere->transparency = 0.0f;
	device->objects->push_back(device->objects, new_obj);
}

void	parse_square(t_device *device, char **line_split)
{
	size_t	strs_count = get_strs_count(line_split);
	// (1) check if sp has 4 char members
	if (strs_count != 6 && strs_count != 9 && strs_count != 10 && strs_count != 11)
		print_error_and_exit(device, "parse_triangle(): .rt file error\n");

	t_object *new_obj = custom_allocator_for_object(TYPE_SQUARE);

	((t_square *)new_obj->obj_data)->tri_1.v0 = parse_3float(device, line_split[1], false);
	((t_square *)new_obj->obj_data)->tri_1.v1 = parse_3float(device, line_split[2], false);
	((t_square *)new_obj->obj_data)->tri_1.v2 = parse_3float(device, line_split[3], false);

	((t_square *)new_obj->obj_data)->tri_1.uv0 = gl_vec2_2f(0.0f, 0.0f);
	((t_square *)new_obj->obj_data)->tri_1.uv1 = gl_vec2_2f(1.0f, 0.0f);
	((t_square *)new_obj->obj_data)->tri_1.uv2 = gl_vec2_2f(1.0f, 1.0f);

	((t_square *)new_obj->obj_data)->tri_2.v0 = parse_3float(device, line_split[1], false);
	((t_square *)new_obj->obj_data)->tri_2.v1 = parse_3float(device, line_split[3], false);
	((t_square *)new_obj->obj_data)->tri_2.v2 = parse_3float(device, line_split[4], false);

	((t_square *)new_obj->obj_data)->tri_2.uv0 = gl_vec2_2f(0.0f, 0.0f);
	((t_square *)new_obj->obj_data)->tri_2.uv1 = gl_vec2_2f(1.0f, 1.0f);
	((t_square *)new_obj->obj_data)->tri_2.uv2 = gl_vec2_2f(0.0f, 1.0f);

	new_obj->material.diffuse = parse_3float(device, line_split[5], true);

	/**
	 * *  NOTE:  Default Material Value setting.
	 */
	new_obj->material.specular = gl_vec3_1f(255.0f);
	new_obj->material.ks = 0.5f;
	new_obj->material.alpha = 9.0f;
	new_obj->material.reflection = 0.3f;
	new_obj->material.transparency = 0.0f;

	if (strs_count == 9 || strs_count == 10 || strs_count == 11)
	{
		new_obj->material.specular = parse_3float(device, line_split[6], true);
		new_obj->material.ks = atof(line_split[7]);
		new_obj->material.alpha = atof(line_split[8]);
		if (strs_count == 10 || strs_count == 11)
			parse_diffuse_texture(device, new_obj, line_split[9]);
		if (strs_count == 11)
			parse_normal_texture(device, new_obj, line_split[10]);
	}
	// new_sphere->reflection = 0.0f;
	// new_sphere->transparency = 0.0f;


	device->objects->push_back(device->objects, new_obj);

}

void	parse_plane(t_device *device, char **line_split)
{
//   x y z coordinates     orientation      diffuseColor(rgb)    specular       ks     alpha
	size_t	strs_count = get_strs_count(line_split);
	// (1) check if sp has 4 char members
	if (strs_count != 4 && strs_count != 7)
		print_error_and_exit(device, "parse_plain(): .rt file error\n");

	t_object *new_obj = custom_allocator_for_object(TYPE_PLAIN);
	// t_object *new_obj = ft_calloc(1, sizeof(*new_obj));
	// new_obj->type = TYPE_PLAIN;

	// tr vertex1  vertex2   vertex3   diffuseColor(rgb)  specular  ks  alpha
	((t_plane *)new_obj->obj_data)->pos = parse_3float(device, line_split[1], false);
	((t_plane *)new_obj->obj_data)->normal = parse_3float(device, line_split[2], false);
	new_obj->material.diffuse = parse_3float(device, line_split[3], true);

	/**
	 * *  NOTE:  Default Material Value setting.
	 */
	new_obj->material.specular = gl_vec3_1f(255.0f);
	new_obj->material.ks = 0.5f;
	new_obj->material.alpha = 9.0f;

	if (strs_count == 8)
	{
		new_obj->material.specular = parse_3float(device, line_split[4], true);
		new_obj->material.ks = atof(line_split[5]);
		new_obj->material.alpha = atof(line_split[6]);
	}
	// new_sphere->reflection = 0.0f;
	// new_sphere->transparency = 0.0f;
	device->objects->push_back(device->objects, new_obj);
}

void	parse_light(t_device *device, char **line_split)
{
	// if light is more than 1, or is in wrong format
	if (device->light->has_light == true || get_strs_count(line_split) != 4)
		print_error_and_exit(device, "parse_light(): .rt file error\n");
	device->light->pos = parse_3float(device, line_split[1], false);
	device->light->brightness_ratio = atof(line_split[2]);
	device->light->color = parse_3float(device, line_split[3], true);
	device->light->has_light = true;
}

void	parse_ambient_light(t_device *device, char **line_split)
{
	// if light is more than 1, or is in wrong format
	if (device->ambient_light->has_ambient_light == true || get_strs_count(line_split) != 3)
		print_error_and_exit(device, "parse_ambient_light(): .rt file error\n");
	device->ambient_light->brightness_ratio = atof(line_split[1]);
	device->ambient_light->color = parse_3float(device, line_split[2], true);
	device->ambient_light->has_ambient_light = true;
}

void	parse_camera(t_device *device, char **line_split)
{
	// if camera is more than 1, or is in wrong format
	if (device->camera->has_camera == true || get_strs_count(line_split) != 4)
		print_error_and_exit(device, "parse_camera(): .rt file error\n");
	device->camera->dir = parse_3float(device, line_split[1], false);
	device->camera->pos = parse_3float(device, line_split[2], false);
	device->camera->fov = atof(line_split[3]);
	device->camera->has_camera = true;
}


void	parse_each(t_device *device, char **line_split)
{
	// TODO:  if data format is wrong while parsing, stop parsing and call engine_exit()
	// if camera
	if (ft_strncmp(line_split[0], "C", ft_strlen(line_split[0])) == 0)
	// if camera
	{
		printf("parsing Camera...\n");
		parse_camera(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "A", ft_strlen(line_split[0])) == 0)
	// if ambient light
	{
		printf("parsing Ambient light...\n");
		parse_ambient_light(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "L", ft_strlen(line_split[0])) == 0)
	// if light
	{
		printf("parsing Light...\n");
		parse_light(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "sp", ft_strlen(line_split[0])) == 0)
	// if sphere
	{
		printf("parsing Sphere...\n");
		parse_sphere(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "pl", ft_strlen(line_split[0])) == 0)
	// if plane
	{
		printf("parsing Plain...\n");
		parse_plane(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "cy", ft_strlen(line_split[0])) == 0)
	// if cylinder
	{
	}
	else if (ft_strncmp(line_split[0], "co", ft_strlen(line_split[0])) == 0)
	// if cone
	{
	}
	else if (ft_strncmp(line_split[0], "tr", ft_strlen(line_split[0])) == 0)
	// if triangle
	{
		printf("parsing Triangle...\n");
		parse_triangle(device, line_split);
	}
	else if (ft_strncmp(line_split[0], "sq", ft_strlen(line_split[0])) == 0)
	// if triangle
	{
		printf("parsing Square...\n");
		parse_square(device, line_split);
	}
	else
		print_error_and_exit(device, "parse_each(): .rt format error\n");
}

/** return (-1) on parse failure. */
void	parse_rt_file_to_device(t_device *device, char *file)
{
	int	fd;
	char	*pa_line;
	char	**pa_line_split;

	printf("File Name : %s\n", file);
	if (ft_strnstr(file, ".rt", ft_strlen(file)) == NULL && file[ft_strlen(file) - 3] == '.')
		print_error_and_exit(device, "parse_rt_file_to_device: .rt format error\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error_and_exit(device, "parse_rt_file_to_device: .rt format error\n");
	pa_line = get_next_line(fd);
	while (pa_line != NULL)
	{
		// Skip empty line
		if (pa_line[0] == '#' || (ft_strlen(pa_line) == 1 && pa_line[0] == '\n'))
		{
			free(pa_line);
			pa_line = get_next_line(fd);
			continue ;
		}
		pa_line_split = ft_split(pa_line, ' ');
		// parse each line
		parse_each(device, pa_line_split);
		free_split_char(pa_line_split);
		free(pa_line);
		pa_line = get_next_line(fd);
	}
};

