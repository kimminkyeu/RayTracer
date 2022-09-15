/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_image.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:25:45 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:40:22 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_IMAGE_H
# define VECTOR_IMAGE_H

# include "libft.h"
# include "gl_device.h"

/* ==========================================================================*
 * |                                                                         |
 * |  * Implemantion of C++ STL std::vector<t_image>.                                 |
 * |-------------------------------------------------------------------------|
 * |                                                                         |
 * |  NOTE(1) reset() : free every containing data.                          |
 * |                                                                         |
 * |  NOTE(2) pop_back() : it will free it's last containing data.           |
 * |                                                                         |
 * |  NOTE(3) delete_vector_image(), it will free everything                       |
 * |          including the pointer passed to argument.                      |
 * |                                                                         |
 * ==========================================================================*/

typedef struct s_vector_image	t_vector_image;

/* ---------------------------
 * @Type define for Vector.
 * .
 * - size     : number of pointers filled in **data.
 * - capacity : total size of it's allocated memory.
 * - **data   : pointer to array of data(= void *) set. */

typedef struct s_vector_image {
	size_t		size;
	size_t		capacity;
	t_image		*data;
	void		(*push_back)(t_vector_image *vec, t_image new_elem);
	void		(*pop_back)(t_vector_image *vec);
	void		(*reset)(t_vector_image *vec);
	int			(*is_empty)(t_vector_image *vec);
	void		*(*shrink_to_fit)(t_vector_image *vec);
	void		*(*reserve)(t_vector_image *vec, size_t new_capacity);
	t_image		*(*get_last)(t_vector_image *vec);
	void		(*iterate)(t_vector_image *vec, t_image (*f)(t_image));
	t_vector_image	*(*map_malloc)(t_vector_image *vec, t_image (*f)(t_image));
}	t_vector_image;

/* ============================
 * @Default Constructor.
 * [ Ex. t_vector_image *arr = new_vector_image(20) ];
 * --> Returns NULL on error! */
extern t_vector_image	*new_vector_image(size_t init_capacity);
/* ============================
 * @Default Destructor.
 * * Frees everything, including pointer passed as argument.
 * --> Use this function to delete vector_image! */
extern void		delete_vector_image(t_vector_image **vec_ptr);

/* ----------------------------
 * * NOTE : Capacity of vector_image doesn't change!
 * * Frees every elements of it's data, set array size to 0.
 * * - if you want to set capacity to 0, call darray_shrink_to_fit(). */
extern void		vector_image_reset(t_vector_image *vec);

/* Returns last data pointer */
extern t_image		*vector_image_get_last(t_vector_image *vec);

/* ----------------------------
 * * Return true(1) if darray is empty, else return false(0) */
extern int		vector_image_is_empty(t_vector_image *vec);

/* ----------------------------
 * - Requests that the darray capacity be at least enough
 * to contain n elements.
 * - If n is smaller than (or equal to) it's current capacity,
 * the function call does not cause a reallocation
 * and the darray capacity is not affected.
 * - This function has no effect on the darray size and cannot
 * alter its elements.
 * --> Returns NULL on error! */
extern void		*vector_image_reserve(t_vector_image *vec, size_t new_capacity);

/* ----------------------------
 * - Add data(void *) to the end. */
extern void		vector_image_push_back(t_vector_image *vec, t_image new_element);

/* ----------------------------
 * * Remove and free it's last data(void *). */
extern void		vector_image_pop_back(t_vector_image *vec);

/* ----------------------------
 * - Requests the container to reduce its capacity to fit its size.
 * - This may cause a reallocation, but has no effect on the
 * darray size and cannot alter its elements.
 * --> Returns NULL on error!! */
extern void		*vector_image_shrink_to_fit(t_vector_image *vec);

/* ----------------------------
 * - Iterates the D-Array and applies the function ’f’
 * to the content of each element. */
extern void		vector_image_iterate(t_vector_image *vec, t_image (*f)(t_image));

/* ----------------------------
 * - NOTE : new D-Array is auto-shrinked to
 * original array's size (not capacity).
 * .
 * - Iterates D-Array and applies the function ’f’ to the
 * content of each element.
 * - Allocates a new D-Array resulting of the successive
 * applications of the function ’f’.
 * --> Returns NULL on error!! */
extern t_vector_image	*vector_image_map_malloc(t_vector_image *vec, t_image (*f)(t_image));





#endif /* VECTOR_IMAGE_H */
