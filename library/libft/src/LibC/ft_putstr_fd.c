/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:20:47 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/12 20:26:41 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/* NOTE : Dangerous if write() error occures!! */
extern size_t	ft_strlen(const char *str);

/* NOTE : Paritial write && write() error handling */
void	ft_putstr_fd(char *string, int fd)
{
	size_t	idx;
	size_t	len;
	ssize_t	writed_bytes;

	idx = 0;
	len = ft_strlen(string);
	while (idx < len)
	{
		writed_bytes = write(fd, &string[idx], len);
		if (writed_bytes < 0)
			return ;
		idx += writed_bytes;
	}
}
