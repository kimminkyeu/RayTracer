/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_vec4.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:25:45 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:40:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_VEC4_H
# define VECTOR_VEC4_H

# include "libft.h"
# include "gl_vec4.h"

/* ==========================================================================*
 * |                                                                         |
 * |  * Implemantion of C++ STL std::vector<t_vec4>.                                 |
 * |-------------------------------------------------------------------------|
 * |                                                                         |
 * |  NOTE(1) reset() : free every containing data.                          |
 * |                                                                         |
 * |  NOTE(2) pop_back() : it will free it's last containing data.           |
 * |                                                                         |
 * |  NOTE(3) delete_vector_vec4(), it will free everything                       |
 * |          including the pointer passed to argument.                      |
 * |                                                                         |
 * ==========================================================================*/

typedef struct s_vector_vec4	t_vector_vec4;

/* ---------------------------
 * @Type define for Vector.
 * .
 * - size     : number of pointers filled in **data.
 * - capacity : total size of it's allocated memory.
 * - **data   : pointer to array of data(= void *) set. */

typedef struct s_vector_vec4 {
	size_t		size;
	size_t		capacity;
	t_vec4		*data;
	void		(*push_back)(t_vector_vec4 *vec, t_vec4 new_elem);
	void		(*pop_back)(t_vector_vec4 *vec);
	void		(*reset)(t_vector_vec4 *vec);
	int			(*is_empty)(t_vector_vec4 *vec);
	void		*(*shrink_to_fit)(t_vector_vec4 *vec);
	void		*(*reserve)(t_vector_vec4 *vec, size_t new_capacity);
	t_vec4		*(*get_last)(t_vector_vec4 *vec);
	void		(*iterate)(t_vector_vec4 *vec, t_vec4 (*f)(t_vec4));
	t_vector_vec4	*(*map_malloc)(t_vector_vec4 *vec, t_vec4 (*f)(t_vec4));
}	t_vector_vec4;

/* ============================
 * @Default Constructor.
 * [ Ex. t_vector_vec4 *arr = new_vector_vec4(20) ];
 * --> Returns NULL on error! */
extern t_vector_vec4	*new_vector_vec4(size_t init_capacity);
/* ============================
 * @Default Destructor.
 * * Frees everything, including pointer passed as argument.
 * --> Use this function to delete vector_vec4! */
extern void		delete_vector_vec4(t_vector_vec4 **vec_ptr);

/* ----------------------------
 * * NOTE : Capacity of vector_vec4 doesn't change!
 * * Frees every elements of it's data, set array size to 0.
 * * - if you want to set capacity to 0, call darray_shrink_to_fit(). */
extern void		vector_vec4_reset(t_vector_vec4 *vec);

/* Returns last data pointer */
extern t_vec4		*vector_vec4_get_last(t_vector_vec4 *vec);

/* ----------------------------
 * * Return true(1) if darray is empty, else return false(0) */
extern int		vector_vec4_is_empty(t_vector_vec4 *vec);

/* ----------------------------
 * - Requests that the darray capacity be at least enough
 * to contain n elements.
 * - If n is smaller than (or equal to) it's current capacity,
 * the function call does not cause a reallocation
 * and the darray capacity is not affected.
 * - This function has no effect on the darray size and cannot
 * alter its elements.
 * --> Returns NULL on error! */
extern void		*vector_vec4_reserve(t_vector_vec4 *vec, size_t new_capacity);

/* ----------------------------
 * - Add data(void *) to the end. */
extern void		vector_vec4_push_back(t_vector_vec4 *vec, t_vec4 new_element);

/* ----------------------------
 * * Remove and free it's last data(void *). */
extern void		vector_vec4_pop_back(t_vector_vec4 *vec);

/* ----------------------------
 * - Requests the container to reduce its capacity to fit its size.
 * - This may cause a reallocation, but has no effect on the
 * darray size and cannot alter its elements.
 * --> Returns NULL on error!! */
extern void		*vector_vec4_shrink_to_fit(t_vector_vec4 *vec);

/* ----------------------------
 * - Iterates the D-Array and applies the function ’f’
 * to the content of each element. */
extern void		vector_vec4_iterate(t_vector_vec4 *vec, t_vec4 (*f)(t_vec4));

/* ----------------------------
 * - NOTE : new D-Array is auto-shrinked to
 * original array's size (not capacity).
 * .
 * - Iterates D-Array and applies the function ’f’ to the
 * content of each element.
 * - Allocates a new D-Array resulting of the successive
 * applications of the function ’f’.
 * --> Returns NULL on error!! */
extern t_vector_vec4	*vector_vec4_map_malloc(t_vector_vec4 *vec, t_vec4 (*f)(t_vec4));





#endif /* VECTOR_VEC4_H */
