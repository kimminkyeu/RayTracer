/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_interface.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 20:36:44 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:09:56 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_INTERFACE_H
# define GL_INTERFACE_H

#include "gl_engine.h"

/* NOTE: User Interface for Graphics Library */




typedef struct s_glf_input {


}	t_glf_input;

typedef struct s_glf_draw {


}	t_glf_draw;

typedef struct s_glf_matrix {


}	t_glf_matrix;

typedef struct s_glf_vec4 {


}	t_glf_vec4;

typedef struct s_glf_vec2 {


}	t_glf_vec2;

typedef struct s_glf_timer {


}	t_glf_timer;

typedef struct s_gl_interface {
	/* input key/mouse interface */
	t_glf_input		f_input;
	/* draw function interface */
	t_glf_draw		f_draw;
	/* matrix function interface */
	t_glf_matrix	f_matrix;
	/* vec4 function interface */
	t_glf_vec4		f_vec4;
	/* vec2 function interface */
	t_glf_vec2		f_vec2;
	/* analysis, time function interface */
	t_glf_timer		f_timer;

}	t_gl_interface;


/* NOTE: Allocate and returns new gl_interface.
 * Ex) t_gl_interface gl = new_gl_interface(800, 200, 1000, "my first window") */
void init_gl_interface(void);








#endif /* GL_INTERFACE_H */
