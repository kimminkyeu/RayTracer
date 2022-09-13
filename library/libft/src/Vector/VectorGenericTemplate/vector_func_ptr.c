/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:01:27 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/09 16:11:31 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_GENERIC.h"

void	set_vector_GENERIC_func_ptr(t_vector_GENERIC *pa_vec)
{
	pa_vec->get_last = vector_GENERIC_get_last;
	pa_vec->is_empty = vector_GENERIC_is_empty;
	pa_vec->iterate = vector_GENERIC_iterate;
	pa_vec->map_malloc = vector_GENERIC_map_malloc;
	pa_vec->pop_back = vector_GENERIC_pop_back;
	pa_vec->push_back = vector_GENERIC_push_back;
	pa_vec->reserve = vector_GENERIC_reserve;
	pa_vec->reset = vector_GENERIC_reset;
	pa_vec->shrink_to_fit = vector_GENERIC_shrink_to_fit;
}
