/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:26:03 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/31 21:51:18 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_vec3.h"
#include "objects.h"
#include "parser.h"

/**       NOTE:  [ Ambient Light ]
 *       Intensity	    Color
 * A     0.3            50,50,50
*/
void	parse_ambient_light(t_device *device, char *line)
{
	t_ambient_light	*p;
	int				cnt;

	p = device->ambient_light;
	cnt = ft_lscanf(line, "A%w%f%w%f,%f,%f\n", \
		&p->brightness_ratio, &p->color.r, &p->color.g, &p->color.b);
	printf("Parsing ambient light %d\n", cnt);
	if (!(p->has_ambient_light == false && cnt == 4))
		print_error_and_exit(device, "parse_ambient_light(): .rt file error\n");
	p->has_ambient_light = true;
}

/**     NOTE:   [ Camera ]
 *     position         loot_at (dir)       up_dir             FOV(0~180)
 * C   0.0,0.0,-1.0     0.0,0.0,1.0        0.0,1.0,0.0         90
*/
void	parse_camera(t_device *device, char *line)
{
	t_camera	*p;
	int			cnt;

	printf("Parsing carmera\n");
	p = device->camera;
	cnt = ft_lscanf(line, "C%w%f,%f,%f%w%f,%f,%f%w%f,%f,%f%w%f\n", \
					&p->pos.x, &p->pos.y, &p->pos.z, \
					&p->look_at.x, &p->look_at.y, &p->look_at.z, \
					&p->up_direction.x, &p->up_direction.y, &p->up_direction.z, \
					&p->fov);
	if (!(p->has_camera == false && cnt == 10))
		print_error_and_exit(device, "parse_camera(): .rt file error\n");
	p->has_camera = true;
	p->look_at = normal3(p->look_at);
	p->up_direction = normal3(p->up_direction);
	update_camera_geometry(device);
}

/**    NOTE:  [ Light ]
 *     pos             intensity     color
 * L   1.0,1.0,-1.0     0.5           255,255,255
*/
void	parse_light(t_device *device, char *line)
{
	t_light	*p;
	int		cnt;

	p = ft_calloc(1, sizeof(*p));
	cnt = ft_lscanf(line, "L%w%f,%f,%f%w%f%w%f,%f,%f\n", \
					&p->pos.x, &p->pos.y, &p->pos.z, \
					&p->brightness_ratio, \
					&p->color.r, &p->color.g, &p->color.b);
	printf("Parsing light %d\n", cnt);
	if (cnt != 7)
		print_error_and_exit(device, "parse_light(): .rt file error\n");
	device->point_lights->push_back(device->point_lights, p);
}

t_texture	*load_texture_file(t_device *device, char *file_name)
{
	char		*str;
	t_texture	*loaded_texture;

	str = ft_strjoin(IMAGE_FILE_LOACATION, file_name);
	loaded_texture = new_texture(device, str);
	free(str);
	return (loaded_texture);
}

void	parse_texture(t_device *device, t_object *object, char *line)
{
	char	*str;
	char	**split;

	str = ft_strchr(line, '|');
	if (str++ == NULL)
		return ;
	str++;
	str = ft_strtrim(str, "\n");
	if (str == NULL)
		return ;
	split = ft_split(str, ' ');
	free(str);
	if (get_strs_count(split) > 0)
	{
		if (ft_strncmp("checker", split[0], 7) == 0)
			object->diffuse_texture = new_texture_checkerboard(device, 32, 32);
		else
			object->diffuse_texture = load_texture_file(device, split[0]);
		if (get_strs_count(split) == 2)
			object->diffuse_texture = load_texture_file(device, split[1]);
	}
	free_split_char(split);
}
