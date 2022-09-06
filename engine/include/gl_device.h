/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_device.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 16:13:40 by kyeu              #+#    #+#             */
/*   Updated: 2022/09/06 16:45:46 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_DEVICE_H
# define GL_DEVICE_H

# include <stddef.h>
# include <stdbool.h>
# include "gl_vec2.h"

/* TODO: 알맞게 상태 바꿀 것. */
typedef enum e_state {
	E_INPUT_NO_STATE, // while keep pressing
	E_INPUT_IS_PRESSED, // while keep pressing
	E_INPUT_UN_PRESSED,
	// ... add later
}	t_state;

typedef struct s_input {
	/* NOTE: add more key-btn state. */
	union {
		struct {
			int KEY_A_state;
			int KEY_S_state;
			int KEY_D_state;
			int KEY_Q_state;
			int KEY_W_state;
			int KEY_E_state;
			int KEY_R_state;
		};
		int key_state[7];
	};
	union {
		struct {
			int MOUSE_LEFT_BTN_state;
			int MOUSE_MIDDLE_BTN_state;
			int MOUSE_RIGHT_BTN_state;
			int MOUSE_SCROLL_UP_state;
			int MOUSE_SCROLL_DOWN_state;
		};
		int	mouse_state[5];
	};
}	t_input;

typedef struct s_image {
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_device {
	void			*mlx;
	void			*win;
	int				win_width;
	int				win_height;
	float			aspect_ratio;
	t_image			viewport; // for viewport
	t_image			panel; // for ui control panel;
	t_input			input; // mouse, keyboard input handler

	long long		render_time; // times to get render.

	// TODO: add later... 
}	t_device;

# endif /* DEVICE_H */
