/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keymap_linux.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:52:09 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/28 19:24:02 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_KEYMAP_LINUX_H
# define MLX_KEYMAP_LINUX_H

# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/X.h>

/* NOTE: (1) https://tronche.com/gui/x/xlib/events/types.html
 * */

/* ================================
 * |       X11/X.h Xevent         |
 * ================================ */

/* Defined in X.h */
# ifndef _XEVENT_
#  define _XEVENT_
#  define ON_KEY_PRESS			(2)
// #  define ON_KEY_PRESS			(KeyPress)
#  define ON_KEY_RELEASE		(3)
// #  define ON_KEY_RELEASE		(KeyRelease)

#  define ON_MOUSE_PRESS		(4)
// #  define ON_MOUSE_PRESS		(ButtonPress)
#  define ON_MOUSE_RELEASE		(5)
// #  define ON_MOUSE_RELEASE		(ButtonRelease)
#  define ON_MOUSE_MOTION		(6)
// #  define ON_MOUSE_MOTION		(MotionNotify)

#  define ON_EXPOSE				(12)
// #  define ON_EXPOSE				(Expose)
#  define ON_DESTROY			(17)
// #  define ON_DESTROY			(DestroyNotify)

/* -------------------------------------------- */
#  define ON_MOUSE_ENTER_WINDOW	(7)
// #  define ON_MOUSE_ENTER_WINDOW	(EnterNotify)
#  define ON_MOUSE_LEAVE_WINDOW	(8)

// #  define ON_MOUSE_LEAVE_WINDOW	(LeaveNotify)
# endif
/* -------------------------------------------- */

/* ================================
 * |       X11/X.h Key maps       |
 * ================================ */

# ifndef _KEY_CODE_
#  define _KEY_CODE_

#  define KEY_ESC				(65307)
#  define KEY_A					(97)
#  define KEY_S					(115)
#  define KEY_D					(100)
#  define KEY_Q					(113)
#  define KEY_W					(119)
#  define KEY_E					(101)
#  define KEY_R					(114)
#  define KEY_INC				(93) /* ] */
#  define KEY_DEC				(91) /* [ */
#  define KEY_P					(112)
#  define KEY_O					(111)
#  define KEY_UP				(65362)
#  define KEY_DOWN				(65364)
#  define KEY_LEFT				(65361)
#  define KEY_RIGHT				(65363)
#  define KEY_1					(49)
#  define KEY_2					(50)
#  define KEY_3					(51)
#  define MOUSE_LEFT_CLICK		(1)
#  define MOUSE_RIGHT_CLICK		(3)
#  define MOUSE_MIDDLE_CLICK	(2)
#  define MOUSE_SCROLL_UP		(4)
#  define MOUSE_SCROLL_DOWN		(5)

# endif

#endif /* KEYMAP_LINUX_H */
