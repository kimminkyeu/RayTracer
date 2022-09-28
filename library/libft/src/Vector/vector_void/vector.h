/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 16:24:41 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 23:00:33 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_vector	t_vector;

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

extern t_vector	*new_vector(size_t init_capacity);
extern void		delete_vector(t_vector **vec_ptr);
extern void		set_vector_func_ptr(t_vector *pa_vec);
extern void		*new_data_malloc(size_t init_capacity);
extern void		vector_set_data(t_vector *vec, size_t index, void *data);
extern void		vector_reset(t_vector *vec);
extern int		vector_is_empty(t_vector *vec);
extern void		*vector_reserve(t_vector *vec, size_t new_capacity);
extern void		vector_push_back(t_vector *vec, void *data);
extern void		vector_pop_back(t_vector *vec);
extern void		*vector_shrink_to_fit(t_vector *vec);
extern void		vector_iterate(t_vector *vec, void (*f)(void *));
extern t_vector	*vector_map_malloc(t_vector *vec, void *(*f)(void *));
extern void		*vector_get_last(t_vector *vec);

#endif /* VECTOR_H */
