/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_keymap_macos.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:52:09 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/26 11:56:53 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_KEYMAP_MACOS_H
# define GL_KEYMAP_MACOS_H

/* NOTE : this header is a partial copied version of X11/X.h header,
 * since minilibx_mms doesn't support all key maps */

# ifndef _KEY_CODE_
#  define _KEY_CODE_
#  define KEY_ESC				(53)
#  define KEY_A					(0)
#  define KEY_S					(1)
#  define KEY_D					(2)
#  define KEY_Q					(12)
#  define KEY_W					(13)
#  define KEY_E					(14)
#  define KEY_R					(15)
#  define KEY_INC				(30) /* ] */
#  define KEY_DEC				(33) /* [ */
#  define KEY_P					(35)
#  define KEY_O					(31)
#  define KEY_UP				(126)
#  define KEY_DOWN				(125)
#  define KEY_LEFT				(123)
#  define KEY_RIGHT				(124)
#  define KEY_1					(18)
#  define KEY_2					(19)
#  define KEY_3					(20)
#  define MOUSE_LEFT_CLICK		(1)
#  define MOUSE_RIGHT_CLICK		(2)
#  define MOUSE_MIDDLE_CLICK	(3)
#  define MOUSE_SCROLL_UP		(4)
#  define MOUSE_SCROLL_DOWN		(5)
# endif

/* ================================
 * |       X11/X.h Key names      |
 * ================================ */
# ifndef _XEVENT_
#  define _XEVENT_
#  define ON_KEY_PRESS			(2)
#  define ON_KEY_RELEASE		(3)

#  define ON_MOUSE_PRESS		(4)
#  define ON_MOUSE_RELEASE		(5)
#  define ON_MOUSE_MOTION		(6)

#  define ON_EXPOSE				(12)
#  define ON_DESTROY			(17)

/* TODO : I haven't checked if key names below
 * are fine for mlx_mms(Cocoa/Metal)
 * So you must test before usage ! */
#  define ON_MOUSE_ENTER_WINDOW	(7)
#  define ON_MOUSE_LEAVE_WINDOW	(8)

/* NOTE : no support on macos */
/* ================================
 * |      X11/X.h Event Mask      |
 * ================================ */
#  define KeyPressMask		(0)
#  define ButtonPressMask	(0)
#  define ButtonReleaseMask	(0)
#  define KeyReleaseMask	(0)
# endif

#endif /* KEYMAP_MACOS_H */
