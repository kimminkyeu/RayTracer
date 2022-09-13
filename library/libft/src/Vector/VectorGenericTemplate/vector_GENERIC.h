/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_GENERIC.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:24:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/12 13:57:21 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_GENERIC_H
# define VECTOR_GENERIC_H

# include <stddef.h>
# include <stdbool.h>

/* ********************************************
 *  HOW TO USE
 *
 *  1. :%s/GENERIC/my_type/g --> change it's name to whatever you want.
 *      it is same as ( std::vector_GENERIC<my_ype> )
 *
 * ********************************************/

typedef struct s_GENERIC {
	//.. NOTE: add data here
} t_GENERIC;


/* ---------------------------
 * @Type define for Vector.
 * .
 * - size     : number of pointers filled in **data.
 * - capacity : total size of it's allocated memory.
 * - **data   : pointer to array of data(= void *) set. */

typedef struct s_vector_GENERIC	t_vector_GENERIC;
typedef struct s_vector_GENERIC {

	size_t		size;
	size_t		capacity;
	t_GENERIC	*data;

	int					(*is_empty)(t_vector_GENERIC *vec);

	void				(*push_back)(t_vector_GENERIC *vec, t_GENERIC new_elem);

	void				(*pop_back)(t_vector_GENERIC *vec);

	void				(*reset)(t_vector_GENERIC *vec);

	void				*(*shrink_to_fit)(t_vector_GENERIC *vec);

	void				*(*reserve)(t_vector_GENERIC *vec, size_t new_capacity);

	t_GENERIC			*(*get_last)(t_vector_GENERIC *vec);

	void				(*iterate)(t_vector_GENERIC *vec, t_GENERIC (*f)(t_GENERIC));

	t_vector_GENERIC	*(*map_malloc)(t_vector_GENERIC *vec, t_GENERIC (*f)(t_GENERIC));

}	t_vector_GENERIC;

extern t_vector_GENERIC	*new_vector_GENERIC(size_t init_capacity);

extern void				delete_vector_GENERIC(t_vector_GENERIC **vec_ptr);
extern void				vector_GENERIC_reset(t_vector_GENERIC *vec);
extern int				vector_GENERIC_is_empty(t_vector_GENERIC *vec);
extern void				*vector_GENERIC_reserve(t_vector_GENERIC *vec, size_t new_capacity);
extern void				vector_GENERIC_push_back(t_vector_GENERIC *vec, t_GENERIC data);
extern void				vector_GENERIC_pop_back(t_vector_GENERIC *vec);
extern void				*vector_GENERIC_shrink_to_fit(t_vector_GENERIC *vec);
extern void				vector_GENERIC_iterate(t_vector_GENERIC *vec, t_GENERIC (*f)(t_GENERIC itr_val));
extern t_vector_GENERIC	*vector_GENERIC_map_malloc(t_vector_GENERIC *vec, t_GENERIC (*f)(t_GENERIC itr_val));
extern t_GENERIC		*vector_GENERIC_get_last(t_vector_GENERIC *vec);

#endif /* VECTOR_GENERIC_H */
