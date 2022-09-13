/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 18:01:27 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/12 13:38:38 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_uchar.h"

void	set_vector_uchar_func_ptr(t_vector_uchar *pa_vec)
{
	pa_vec->get_last = vector_uchar_get_last;
	pa_vec->is_empty = vector_uchar_is_empty;
	pa_vec->iterate = vector_uchar_iterate;
	pa_vec->map_malloc = vector_uchar_map_malloc;
	pa_vec->pop_back = vector_uchar_pop_back;
	pa_vec->push_back = vector_uchar_push_back;
	pa_vec->reserve = vector_uchar_reserve;
	pa_vec->reset = vector_uchar_reset;
	pa_vec->shrink_to_fit = vector_uchar_shrink_to_fit;
}
