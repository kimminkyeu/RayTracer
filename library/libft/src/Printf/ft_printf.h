/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 10:11:25 by minkyeki          #+#    #+#             */
/*   Updated: 2022/05/02 17:19:11 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include "libft.h"

/*-------------------------------------------------
 |              Constants for state               |
 -------------------------------------------------*/
# define PRINTF_NORMAL		(0)
# define PRINTF_FLAG		(1)
# define PRINTF_WIDTH		(2)
# define PRINTF_PRECISION	(3)
# define PRINTF_LENGTH		(4)
# define PRINTF_SPEC		(5)
# define PRINTF_DONE		(6)
# define PRINTF_ERROR		(7)
# define STDOUT				(1)

/*-------------------------------------------------
 |              _info State handler                |
 -------------------------------------------------*/
/* TODO : add member for Bonus */
typedef struct s_print {
	size_t	print_cnt;
	int		state;
}	t_print;

extern t_print	*init_info_malloc(void);
extern void		reset_state(t_print *_info);

/*-------------------------------------------------
 |              Main Function                     |
 -------------------------------------------------*/
extern int		ft_printf(const char *fmt, ...);

/*-------------------------------------------------
 |              Internal Function                 |
 -------------------------------------------------*/
extern int		ft_vprintf(const char *fmt, va_list argp);
/* print string until specifier appears. Returns length of printed characters */

extern size_t	ft_putstr_until(const char *str, char stopper, t_print *_info);

/*-------------------------------------------------
 |              Parser Function                   |
 -------------------------------------------------*/
extern void		parse_format(const char **fmt, va_list argp, t_print *_info);

/*-------------------------------------------------
 |              Flag handler functiom             |
 -------------------------------------------------*/
extern void		handle_flag(const char *fmt, va_list argp, t_print *_info);

extern void		handle_precision(const char *fmt, va_list argp, t_print *_info);

extern void		handle_width(const char *fmt, va_list argp, t_print *_info);

extern void		handle_length(const char *fmt, va_list argp, t_print *_info);

extern void		handle_specifier(const char *fmt, va_list argp, t_print *_info);

/*-------------------------------------------------
 |              Specifier handler function        |
 -------------------------------------------------*/
extern void		handle_spec_char(va_list argp, t_print *_info);

extern void		handle_spec_percent(va_list argp, t_print *_info);

extern void		handle_spec_str(va_list argp, t_print *_info);

extern void		handle_spec_addr(va_list argp, t_print *_info);

extern void		handle_spec_int(va_list argp, t_print *_info);

extern void		handle_spec_uint(va_list argp, t_print *_info);

extern void		handle_spec_lower_hex(va_list argp, t_print *_info);

extern void		handle_spec_upper_hex(va_list argp, t_print *_info);

extern int		get_spec_func_idx(const char *fmt);

extern void		set_spec_func_table(void (*spec_func_table[])\
		(va_list, t_print *));

/*-------------------------------------------------
 |               Hex functions                    |
 -------------------------------------------------*/
/* Print nb to full 16 characters of hex.
 * if mode is 0, hex is Lowercase. else, hex is Uppercase */
extern void		print_to_hex_16(size_t nb, int mode);

/* Print nb to hex, return length of printed characters.
 * if mode is 0, hex is Lowercase. else, hex is Uppercase */
extern size_t	print_to_hex_fit(size_t nb, int mode);

/* Print nb to n characters of hex.
 * if mode is 0, hex is Lowercase. else, hex is Uppercase */
extern size_t	print_to_hex_len(size_t nb, size_t n, int mode);

#endif
