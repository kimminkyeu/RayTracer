/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_uint_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:24:53 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/12 16:14:43 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_pow(unsigned int num, int power)
{
	int	result;

	if (power < 0)
		return (-1);
	result = 1;
	while (power-- > 0)
		result *= num;
	return (result);
}

void	ft_putnbr_uint_fd(unsigned int n, int fd)
{
	size_t			nbr_len;
	char			digit;
	unsigned int	divider;

	if (fd < 0)
		return ;
	nbr_len = ft_nbrlen_uint(n);
	while (nbr_len > 0)
	{
		divider = ft_pow(10, nbr_len - 1);
		digit = (n / divider) + '0';
		n %= divider;
		nbr_len--;
		write(fd, &digit, 1);
	}
}
