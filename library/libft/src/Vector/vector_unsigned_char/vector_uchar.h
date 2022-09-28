/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_uchar.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:24:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/09 16:42:03 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UCHAR_H
# define VECTOR_UCHAR_H

# include <stddef.h>
# include <stdbool.h>

/* ---------------------------
 * @Type define for Vector.
 * .
 * - size     : number of pointers filled in **data.
 * - capacity : total size of it's allocated memory.
 * - **data   : pointer to array of data(= void *) set. */

typedef struct s_vector_uchar t_vector_uchar;

typedef struct s_vector_uchar {

	size_t			size;
	size_t			capacity;
	unsigned char	*data;

	int					(*is_empty)(t_vector_uchar *vec);

	void				(*push_back)(t_vector_uchar *vec, unsigned char new_elem);

	void				(*pop_back)(t_vector_uchar *vec);

	void				(*reset)(t_vector_uchar *vec);

	void				*(*shrink_to_fit)(t_vector_uchar *vec);

	void				*(*reserve)(t_vector_uchar *vec, size_t new_capacity);

	unsigned char		*(*get_last)(t_vector_uchar *vec);

	void				(*iterate)(t_vector_uchar *vec, unsigned char (*f)(unsigned char));

	t_vector_uchar		*(*map_malloc)(t_vector_uchar *vec, unsigned char (*f)(unsigned char));

}	t_vector_uchar;

extern t_vector_uchar	*new_vector_uchar(size_t init_capacity);
extern void				delete_vector_uchar(t_vector_uchar **vec_ptr);

extern void				vector_uchar_reset(t_vector_uchar *vec);
extern int				vector_uchar_is_empty(t_vector_uchar *vec);
extern void				*vector_uchar_reserve(t_vector_uchar *vec, size_t new_capacity);
extern void				vector_uchar_push_back(t_vector_uchar *vec, unsigned char data);
extern void				vector_uchar_pop_back(t_vector_uchar *vec);
extern void				*vector_uchar_shrink_to_fit(t_vector_uchar *vec);
extern void				vector_uchar_iterate(t_vector_uchar *vec, unsigned char (*f)(unsigned char itr_val));
extern t_vector_uchar	*vector_uchar_map_malloc(t_vector_uchar *vec, unsigned char (*f)(unsigned char itr_val));
extern unsigned char	*vector_uchar_get_last(t_vector_uchar *vec);

#endif /* VECTOR_UCHAR_H */
