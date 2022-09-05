/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:01:27 by minkyeki          #+#    #+#             */
/*   Updated: 2022/08/16 22:47:27 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

void	set_vector_func_ptr(t_vector *pa_vec)
{
	pa_vec->get_last = vector_get_last;
	pa_vec->is_empty = vector_is_empty;
	pa_vec->iterate = vector_iterate;
	pa_vec->map_malloc = vector_map_malloc;
	pa_vec->pop_back = vector_pop_back;
	pa_vec->push_back = vector_push_back;
	pa_vec->reserve = vector_reserve;
	pa_vec->reset = vector_reset;
	pa_vec->shrink_to_fit = vector_shrink_to_fit;
}
