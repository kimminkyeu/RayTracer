/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:04:59 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/19 00:12:49 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H

# include <math.h>
# include <pthread.h>
# include <memory.h>

typedef struct s_thread_info t_thread_info;

typedef struct s_device t_device;

typedef struct s_image t_image;

typedef struct s_thread {
	pthread_t		thread;
	int				id;
	t_thread_info	*info;

	t_device        *device;
	t_image			*image;

}	t_thread;

typedef struct s_thread_info {
	t_thread	*thread_group;
	int			thread_num;

	pthread_mutex_t	finished_num_mutex; // mutex for mutex finished
	int				finished_thread_num; // total num of finished thread;
	//...
}	t_thread_info;

#endif /** Thread.h */
