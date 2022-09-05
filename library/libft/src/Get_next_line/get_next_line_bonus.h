/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:58:37 by minkyeki          #+#    #+#             */
/*   Updated: 2022/05/05 17:28:05 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <sys/types.h>
# include <limits.h>

/* for default BUFFER_SIZE */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

/* for LINUX compatibility */
# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

/* Return a line read from a file descriptor, NULL if there is 
 * nothing else to read, or an error occurred */
extern char		*get_next_line_multi(int fd);

typedef struct s_array {
	size_t	size;
	size_t	capacity;
	char	*data;
	char	last_data;
}				t_array;

extern void		*memcpy_gnl(void *dst, const void *src, size_t n);
extern t_array	*new_array_malloc(t_array **array, size_t init_capacity);
extern char		*new_str_malloc(char **str, size_t init_size);
extern void		push_back_array(t_array *const array, int c);
extern void		reserve_array(t_array *const array, size_t new_capacity);

#endif
