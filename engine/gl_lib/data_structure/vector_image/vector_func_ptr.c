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

#include "gl_std_vector_image.h"

void	set_vector_image_func_ptr(t_vector_image *pa_vec)
{
	pa_vec->get_last = vector_image_get_last;
	pa_vec->is_empty = vector_image_is_empty;
	pa_vec->iterate = vector_image_iterate;
	pa_vec->map_malloc = vector_image_map_malloc;
	pa_vec->pop_back = vector_image_pop_back;
	pa_vec->push_back = vector_image_push_back;
	pa_vec->reserve = vector_image_reserve;
	pa_vec->reset = vector_image_reset;
	pa_vec->shrink_to_fit = vector_image_shrink_to_fit;
}
