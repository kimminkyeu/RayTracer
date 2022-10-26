/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_device.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:13:40 by kyeu              #+#    #+#             */
/*   Updated: 2022/10/26 15:48:19 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_DEVICE_H
# define GL_DEVICE_H

# include <stddef.h>
# include <stdbool.h>

# include "gl_vec2.h"
# include "gl_vec3.h"
# include "vector.h"
# include "thread.h"

typedef enum e_state {
	E_INPUT_NO_STATE,
	E_INPUT_IS_PRESSED,
	E_INPUT_UN_PRESSED,
}	t_state;

typedef struct s_input {
	union {
		struct {
			int	key_a_state;
			int	key_s_state;
			int	key_d_state;
			int	key_q_state;
			int	key_w_state;
			int	key_e_state;
			int	key_r_state;
		};
		int	key_state[7];
	};
	union {
		struct {
			int	mouse_left_btn_state;
			int	mouse_middle_btn_state;
			int	mouse_right_btn_state;
			int	mouse_scroll_up_state;
			int	mouse_scroll_down_state;
		};
		int	mouse_state[5];
	};
	t_vec2	last_mouse_pos;
}	t_input;

typedef struct s_device			t_device;
typedef struct s_image			t_image;

typedef struct s_image {
	void		*mlx_ptr;
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_vec2		img_location;
	t_vec2		img_size;
	t_device	*device_ptr;
	int			(*img_update_func)(t_device *device, t_image *image);
}	t_image;

typedef struct s_ambient_light	t_ambient_light;
typedef struct s_light			t_light;
typedef struct s_camera			t_camera;

typedef struct s_setting {
	int		win_width;
	int		win_height;
	float	resolution_ratio;
	int		num_of_threads;
	int		antialiasing_level;
	int		reflection_level;
}	t_setting;

typedef struct s_device {
	void				*mlx;
	void				*win;
	// int					win_width;
	// int					win_height;
	// int					resolution_ratio;
	t_setting			renderer_settings;
	float				aspect_ratio;
	int					is_high_resolution_render_mode;
	t_thread_info		thread_info;
	t_image				*screen_image;
	t_image				*pixel_image;
	t_input				input;
	t_vector			*objects;
	t_camera			*camera;
	t_ambient_light		*ambient_light;
	t_vector			*point_lights;
}	t_device;

#endif /* DEVICE_H */
