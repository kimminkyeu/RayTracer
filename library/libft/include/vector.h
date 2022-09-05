/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:25:45 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:40:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"

/* ==========================================================================*
 * |                                                                         |
 * |  * Implemantion of C++ STL std::vector.                                 |
 * |  * Data type is void**, so it is suitable of storing pointers.          |
 * |-------------------------------------------------------------------------|
 * |                                                                         |
 * |  NOTE(1) reset() : free every containing data.                          |
 * |                                                                         |
 * |  NOTE(2) pop_back() : it will free it's last containing data.           |
 * |                                                                         |
 * |  NOTE(3) delete_vector(), it will free everything                       | 
 * |          including the pointer passed to argument.                      |
 * |                                                                         |
 * ==========================================================================*/

typedef struct s_vector	t_vector;

/* ---------------------------
 * @Type define for Vector.
 * . 
 * - size     : number of pointers filled in **data.
 * - capacity : total size of it's allocated memory.
 * - **data   : pointer to array of data(= void *) set. */

typedef struct s_vector {
	size_t		size;
	size_t		capacity;
	void		**data;
	void		(*push_back)(t_vector *vec, void *new_elem);
	void		(*pop_back)(t_vector *vec);
	void		(*reset)(t_vector *vec);
	int			(*is_empty)(t_vector *vec);
	void		*(*shrink_to_fit)(t_vector *vec);
	void		*(*reserve)(t_vector *vec, size_t new_capacity);
	void		*(*get_last)(t_vector *vec);
	void		(*iterate)(t_vector *vec, void (*f)(void *));
	t_vector	*(*map_malloc)(t_vector *vec, void *(*f)(void *));
}	t_vector;

/* ============================ 
 * @Default Constructor.
 * [ Ex. t_vector *arr = new_vector(20) ];
 * --> Returns NULL on error! */
extern t_vector	*new_vector(size_t init_capacity);
/* ============================
 * @Default Destructor.
 * * Frees everything, including pointer passed as argument. 
 * --> Use this function to delete vector! */
extern void		delete_vector(t_vector **vec_ptr);

/* ----------------------------
 * * NOTE : Capacity of vector doesn't change!
 * * Frees every elements of it's data, set array size to 0. 
 * * - if you want to set capacity to 0, call darray_shrink_to_fit(). */
extern void		vector_reset(t_vector *vec);

/* Returns last data pointer */
extern void		*vector_get_last(t_vector *vec);

/* ----------------------------
 * * Return true(1) if darray is empty, else return false(0) */
extern int		vector_is_empty(t_vector *vec);

/* ----------------------------
 * - Requests that the darray capacity be at least enough 
 * to contain n elements. 
 * - If n is smaller than (or equal to) it's current capacity, 
 * the function call does not cause a reallocation 
 * and the darray capacity is not affected.
 * - This function has no effect on the darray size and cannot 
 * alter its elements. 
 * --> Returns NULL on error! */
extern void		*vector_reserve(t_vector *vec, size_t new_capacity);

/* ----------------------------
 * - Add data(void *) to the end. */
extern void		vector_push_back(t_vector *vec, void *new);

/* ----------------------------
 * * Remove and free it's last data(void *). */
extern void		vector_pop_back(t_vector *vec);

/* ----------------------------
 * - Requests the container to reduce its capacity to fit its size. 
 * - This may cause a reallocation, but has no effect on the 
 * darray size and cannot alter its elements. 
 * --> Returns NULL on error!! */
extern void		*vector_shrink_to_fit(t_vector *vec);

/* ----------------------------
 * - Iterates the D-Array and applies the function ’f’ 
 * to the content of each element. */
extern void		vector_iterate(t_vector *vec, void (*f)(void *));

/* ----------------------------
 * - NOTE : new D-Array is auto-shrinked to 
 * original array's size (not capacity).
 * .
 * - Iterates D-Array and applies the function ’f’ to the 
 * content of each element.
 * - Allocates a new D-Array resulting of the successive 
 * applications of the function ’f’. 
 * --> Returns NULL on error!! */
extern t_vector	*vector_map_malloc(t_vector *vec, void *(*f)(void *));

#endif /* VECTOR_H */
