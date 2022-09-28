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

#include "gl_std_vector_vec4.h"

void	set_vector_vec4_func_ptr(t_vector_vec4 *pa_vec)
{
	pa_vec->get_last = vector_vec4_get_last;
	pa_vec->is_empty = vector_vec4_is_empty;
	pa_vec->iterate = vector_vec4_iterate;
	pa_vec->map_malloc = vector_vec4_map_malloc;
	pa_vec->pop_back = vector_vec4_pop_back;
	pa_vec->push_back = vector_vec4_push_back;
	pa_vec->reserve = vector_vec4_reserve;
	pa_vec->reset = vector_vec4_reset;
	pa_vec->shrink_to_fit = vector_vec4_shrink_to_fit;
}
