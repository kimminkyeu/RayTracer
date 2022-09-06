/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_time.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:58:36 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/06 16:46:10 by sungjpar         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GL_TIME_H
# define GL_TIME_H

# include <sys/time.h>
# include <stddef.h>

/* # src/Engine/Analysis/time.c 
 * get time in [milli-seconds]. */
extern long long	get_time_ms(void);

#endif /* TIME_H */
