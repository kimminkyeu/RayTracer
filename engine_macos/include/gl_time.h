/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:58:36 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/05 23:09:50 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <sys/time.h>
# include <stddef.h>

/* # src/Engine/Analysis/time.c 
 * get time in [milli-seconds]. */
extern long long	get_time_ms(void);

#endif /* TIME_H */
