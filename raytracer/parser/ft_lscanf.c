/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 15:47:45 by sungjpar          #+#    #+#             */
/*   Updated: 2022/10/25 17:44:55 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "libft.h"
#define FAILED (-1)
#define SUCCESS 0
#define TRUE 1
#define FALSE 0

typedef enum e_flag
{
	COMMON_CHAR = 0,
	FORMAT_CHAR = 1
}	t_flag;

int	read_char_line(char *dest, char **line);
int	read_int_line(int *dest, char **line);
int	read_float_line(float *dest, char **line);
int	skip_white_space(char **line);

static int	read_format(char **line, char format_char, va_list *ap)
{
	char	c;

	if (format_char == 'c')
		return (read_char_line(va_arg(*ap, char *), line));
	if (format_char == 'd' || format_char == 'i')
		return (read_int_line(va_arg(*ap, int *), line));
	if (format_char == 'f')
		return (read_float_line(va_arg(*ap, float *), line));
	if (format_char == 'w')
		return (skip_white_space(line));
	if (format_char == '%')
	{
		c = *(++(*line));
		if (c == '%')
			return (SUCCESS);
		return (FAILED);
	}
	return (FAILED);
}

static int	scan_format(char *line, char *fmt, va_list ap)
{
	int		count_success_read;
	char	format_char;

	count_success_read = 0;
	while (*fmt)
	{
		if (*fmt == '%')
		{
			format_char = *(++fmt);
			if (read_format(&line, format_char, &ap) == -1)
				return (count_success_read);
			if (format_char != 'w')
				++count_success_read;
		}
		else if (*fmt != *line)
			return (count_success_read);
		++fmt;
		++line;
	}
	return (count_success_read);
}

int	ft_lscanf(char *line, char *format, ...)
{
	va_list	ap;
	int		count_success_read;

	if (format == NULL)
		return (FAILED);
	va_start(ap, format);
	count_success_read = scan_format(line, format, ap);
	va_end(ap);
	return (count_success_read);
}
