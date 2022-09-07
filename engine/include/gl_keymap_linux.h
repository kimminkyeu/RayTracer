/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_keymap_linux.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:52:09 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 16:46:00 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_KEYMAP_LINUX_H
# define GL_KEYMAP_LINUX_H

# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/X.h>

/*NOTE: (1) https://tronche.com/gui/x/xlib/events/types.html 
 * */
/*NOTE: (2) https://wiki.kldp.org/KoreanDoc/html/X-Window-Programming/X-Window-Programming-7.html
 * */

/* ================================
 * |       X11/X.h Xevent         |
 * ================================ */
/* Defined in X.h */
# ifndef _XEVENT_
#  define _XEVENT_
#  define ON_KEY_PRESS			(KeyPress)
#  define ON_KEY_RELEASE			(KeyRelease)

#  define ON_MOUSE_PRESS			(ButtonPress)
#  define ON_MOUSE_RELEASE		(ButtonRelease)
#  define ON_MOUSE_MOTION		(MotionNotify)

#  define ON_EXPOSE				(Expose)
#  define ON_DESTROY				(DestroyNotify)

/* -------------------------------------------- */
#  define ON_MOUSE_ENTER_WINDOW	(EnterNotify)
#  define ON_MOUSE_LEAVE_WINDOW	(LeaveNotify)
# endif
/* -------------------------------------------- */

/* ================================
 * |       X11/X.h Key maps       |
 * ================================ */

# ifndef _KEY_CODE_
#  define _KEY_CODE_
#   define KEY_ESC	(65307)
#   define KEY_A		(97)
#   define KEY_S		(115)
#   define KEY_D		(100)
#   define KEY_Q		(113)
#   define KEY_W		(119)
#   define KEY_E		(101)
#   define KEY_R		(114)
#   define KEY_INC	(93) /* ] */
#   define KEY_DEC	(91) /* [ */
#   define KEY_P		(112)
#   define KEY_O		(111)
#   define KEY_UP		(65362)
#   define KEY_DOWN		(65364)
#   define KEY_LEFT		(65361)
#   define KEY_RIGHT	(65363)
#   define KEY_1		(49)
#   define KEY_2		(50)
#   define KEY_3		(51)
#   define MOUSE_LEFT_CLICK	(1)
#   define MOUSE_RIGHT_CLICK	(3)
#   define MOUSE_MIDDLE_CLICK	(2)
#   define MOUSE_SCROLL_UP	(4)
#   define MOUSE_SCROLL_DOWN	(5)
# endif

#endif /* KEYMAP_LINUX_H */