/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_util_functinos.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parksungjun <parksungjun@student.42seou    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:12:19 by parksungjun       #+#    #+#             */
/*   Updated: 2022/09/05 23:12:28 by parksungjun      ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "gl_matrix.h"

float	gl_get_radian(float degree)
{
	return (degree / 180.0f * 3.141592f);
}