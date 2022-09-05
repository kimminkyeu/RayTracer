/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:56:35 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:15:52 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "time.h"

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		ms;

	gettimeofday(&time, NULL);
	if (time.tv_usec > 2)
		ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	else
		ms = (time.tv_sec * 1000);
	return (ms);
}
