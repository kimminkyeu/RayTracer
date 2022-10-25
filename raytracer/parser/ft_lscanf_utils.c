/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lscanf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 16:07:33 by sungjpar          #+#    #+#             */
/*   Updated: 2022/10/23 16:07:37 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define SUCCESS 0
#define FAILED (-1)
#define FALSE 0
#define TRUE 1

int	read_char_line(char *dest, char **line)
{
	const char	c = **line;

	if (c == 0)
		return (FAILED);
	*dest = c;
	return (SUCCESS);
}

int	read_int_line(int *dest, char **line)
{
	char	buf[30];
	int		buf_idx;

	buf_idx = 0;
	if (**line && (**line == '+' || **line == '-'))
		buf[buf_idx++] = *((*line)++);
	while (**line && ft_isdigit(**line))
	{
		buf[buf_idx] = **line;
		buf_idx++;
		(*line)++;
	}
	buf[buf_idx] = 0;
	if (buf_idx == 0)
		return (FAILED);
	*dest = ft_atoi(buf);
	(*line)--;
	return (SUCCESS);
}

int	read_float_line(float *dest, char **line)
{
	char	buf[300];
	int		buf_idx;

	buf_idx = 0;
	if (**line && (**line == '+' || **line == '-'))
		buf[buf_idx++] = *((*line)++);
	while (**line && ft_isdigit(**line))
		buf[buf_idx++] = *((*line)++);
	if (**line == '.')
	{
		buf[buf_idx++] = *(*line)++;
		while (**line && ft_isdigit(**line))
			buf[buf_idx++] = *((*line)++);
	}
	buf[buf_idx] = 0;
	if (buf_idx == 0)
		return (FAILED);
	*dest = ft_atof(buf);
	(*line)--;
	return (SUCCESS);
}

int	skip_white_space(char **line)
{
	if (ft_isspace(**line) == FALSE)
		return (FAILED);
	while (**line && ft_isspace(**line))
		++(*line);
	--(*line);
	return (SUCCESS);
}
