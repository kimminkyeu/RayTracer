/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@42SEOUL.KR>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:28:31 by minkyeki          #+#    #+#             */
/*   Updated: 2022/04/24 18:50:44 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned int	get_base_size_1(char *base)
{
	int	size;

	size = 0;
	while (*base++)
		size++;
	return (size);
}

static int	is_valid_1(char *base)
{
	char	*p_base;
	char	*compare;

	p_base = base;
	if (*base == '\0')
		return (0);
	while (*p_base != '\0')
	{
		if (*p_base == '+' || *p_base == '-' \
				|| (*p_base >= 9 && *p_base <= 13) || *p_base == ' ')
			return (0);
		++p_base;
	}
	while (*(base + 1))
	{
		compare = base + 1;
		while (*compare)
		{
			if (*base == *compare)
				return (0);
			++compare;
		}
		++base;
	}
	return (1);
}

static int	has_base(char *str, char *base)
{
	while (*base)
	{
		if (*str == *base)
			return (1);
		++base;
	}
	return (0);
}

static int	find_base_index_1(char target, char *base)
{
	int	index;

	index = 0;
	while (*base)
	{
		if (*base == target)
			return (index);
		++base;
		++index;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	long long	sign;
	long long	sum;
	long long	size;
	long long	to_add;

	sum = 0;
	sign = 1;
	size = get_base_size_1(base);
	if (size < 2 || !is_valid_1(base))
		return (0);
	while (*str && ((*str == ' ') || (*str >= 9 && *str <= 13)))
		++str;
	while (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}	
	while (has_base(str, base))
	{
		to_add = find_base_index_1(*str, base);
		sum = (sum * size) + (long long)to_add;
		++str;
	}
	return ((int)(sum * sign));
}
