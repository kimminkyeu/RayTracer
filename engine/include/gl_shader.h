/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_shader.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 21:03:32 by minkyeki          #+#    #+#             */
/*   Updated: 2022/09/13 13:18:46 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "gl_device.h"
# include "gl_color.h"
# include "gl_draw.h"
# include "gl_vec4.h"


/**
 *  NOTE: GL_SHADER는 이미지 필터와 관련된 함수가 있습니다.
 *    가우시안블러, 밝기조절, 블룸 효과등이 이에 해당합니다.
 */


extern void	gl_shader_brightness(t_image *image, float brightness_factor);


#endif /* SHADER_H */
