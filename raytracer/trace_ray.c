/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */ /*   By: minkyeki <minkyeki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:00:35 by minkyeki          #+#    #+#             */
/*   Updated: 2022/10/19 00:09:23 by minkyeki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace_ray.h"

#define ANTI_ALIASING_RECURSIVE_LEVEL 	(0)
#define REFLECTION_RECURSIVE_LEVEL		(5)

int do_ray_tracing_and_return_color(t_device *device, t_image *img, int x, int y)
{
	const t_vec3 pixel_pos_world = transform_screen_to_world(img, gl_vec2_2f(x, y));

	/* NOTE:  Ray 방향 벡터. 현재 코드는 등각투시. (ray가 방향이 모두 같음. 추후 변경 필요) */
	device->eye_pos = gl_vec3_3f(0.0f, 0.0f, -5.0f);

	const float	dx = 2.0f / img->img_size.height; // for super sampling. // world_coordinate 의 세로길이 / 이미지 세로 =  1pixel당 세로 길이 = 1pixel당 가로 길이.

	t_vec3 trace_result = super_sampling_anti_aliasing(img, pixel_pos_world, dx, ANTI_ALIASING_RECURSIVE_LEVEL); // 마지막 정수가 0이면 픽셀 하나당 한 번 샘플링
	trace_result = gl_vec3_clamp(trace_result, gl_vec3_1f(0.0f), gl_vec3_1f(255.0f));
	int final_color = gl_get_color_from_vec4(gl_vec4_4f(trace_result.b, trace_result.g, trace_result.r, 0.0f));
	return (final_color);
}

// screen 좌표계를 world 좌표계로 변환. (-aspect ~ +aspect)
t_vec3 transform_screen_to_world(t_image *img, t_vec2 pos_screen)
{
	const float x_scale = 2.0f / img->img_size.width;
	const float y_scale = 2.0f / img->img_size.height;
	const float aspect_ratio = (float)img->img_size.width / img->img_size.height;

	// 3차원 공간으로 확장.
	return (gl_vec3_3f((pos_screen.x * x_scale - 1.0f) * aspect_ratio, -pos_screen.y * y_scale + 1.0f, 0.0f));
}

t_vec3 super_sampling_anti_aliasing(t_image *img, t_vec3 pixel_pos_world, const float dx, const int recursive_level)
{
	if (recursive_level == 0) // recursive_level이 0이면 하던대로 단일 Ray_tracing 진행.
	{
		t_vec3 ray_dir = gl_vec3_normalize(gl_vec3_subtract_vector(pixel_pos_world, img->device_ptr->eye_pos));
		t_ray pixel_ray = create_ray(pixel_pos_world, ray_dir);
		return (trace_ray(img->device_ptr, &pixel_ray, REFLECTION_RECURSIVE_LEVEL));
	}

	const float sub_dx = 0.5f * dx;
	t_vec3 pixel_color = gl_vec3_1f(0.0f); // 재귀 첫 색상.?
	pixel_pos_world.x = pixel_pos_world.x - sub_dx * 0.5f; // 0.25 와 0.75 지점을 구해야 하기 때문.
	pixel_pos_world.y = pixel_pos_world.y - sub_dx * 0.5f; // 0.25 와 0.75 지점을 구해야 하기 때문.
	int i = 0;
	int j = 0;
	while (j < 2)
	{
		// j = 0일때 pos는 0.25 지점, j = 1일때 pos는 0.75 지점.
		i = 0;
		while (i < 2)
		{
			// i = 0일때 pos는 0.25 지점, i = 1일때 pos는 0.75 지점.
			t_vec3 sub_pos = gl_vec3_3f(pixel_pos_world.x + ((float)i * sub_dx),\
										pixel_pos_world.y + ((float)j * sub_dx),\
										pixel_pos_world.z);

			// 재귀 호출. (Recursive Super-Sampling)
			pixel_color = gl_vec3_add_vector(pixel_color, super_sampling_anti_aliasing(img, sub_pos, sub_dx, recursive_level - 1));
			i++;
		}
		j++;
	}
	return (gl_vec3_multiply_scalar(pixel_color, 0.25f)); // pixel의 색상을 평균내는 부분 (나누기 4)
}

// 광선을 추적해서 부딪힌 지점의 color를 반환.
t_vec3 trace_ray(t_device *device, const t_ray *ray, const int recursive_level)
{
	if (recursive_level < 0)
		return (gl_vec3_1f(0.0f));
	// (0) Render first hit
	t_hit hit = find_closet_collision(device, ray);

	// * If ray hit object, then calculate with Phong-Shading-model.
	if (hit.distance >= 0.0f) // if has hit.
	{
		return (phong_shading_model(device, ray, hit, recursive_level));
	}
	return (gl_vec3_1f(0.0f)); // return black
}

/** ---------------------------------------------------------------------------------------------- */


/* ------------------------------------------------------------------------------------------- *
 * |  NOTE:  Main Ray-tracing Algorithm !   => 그림자가 자연스럽게 Blending 되려면?

 개선 가능 사항:
 (1) ambient light을 그대로 물체의 ambient_color로 사용하고 있기에, 그림자의 색이 모두 동일하게 나온다.
 --> 그림자를 처리하는 다른 방법이 있는 걸까?

 ---------------------------------------------------------------------------------------------- */

t_vec3 phong_shading_model(t_device *device, const t_ray *ray, t_hit hit, const int recursive_level)
{
	t_vec3 final_color = gl_vec3_1f(0.0f);

	// (1) Start with Ambient Color.
	t_vec3 phong_color = gl_vec3_1f(0.0f);
	phong_color = gl_vec3_multiply_scalar(device->ambient_light->color, device->ambient_light->brightness_ratio);

	// *  WARN:  Ambient Texture는 계산에서 제외하였음 ---------------------------------------
	// Add texture to color (ambient texture) // 이 부분은 그림자로 가려질 경우에도 나타난다.
	// NOTE:  ambient와 diffuse 둘 다 sample_linear 이용하였음.
	if (hit.obj->diffuse_texture != NULL) // if has texture + 그림자가 없을 때.
	{
		t_vec3 sample_ambient;
		if (hit.obj->diffuse_texture->type == TEXTURE_CHECKER)
			sample_ambient = sample_point(hit.obj->diffuse_texture, hit.uv, false); // texture sampling
		else
			sample_ambient = sample_linear(hit.obj->diffuse_texture, hit.uv, false); // texture sampling

		phong_color.r *= sample_ambient.b;												// 홍정모
		phong_color.g *= sample_ambient.g; // 홍정모
		phong_color.b *= sample_ambient.r; // 홍정모
	}
	// * ---------------------------------------------------------------------------------


	// 그림자 처리. 아주 작은 값만큼 광원을 향해 이동시켜야 hit_point로 부터 충돌처리를 피할 수 있다.
	const t_vec3 hit_point_to_light = gl_vec3_normalize(gl_vec3_subtract_vector(device->light->pos, hit.point));

	// * (3) Shadow
	// 만약 [hit_point+살짝 이동한 지점] 에서  shadow_ray를 광원을 향해 쐈는데, 충돌이 감지되면 거긴 그림자로 처리.
	// WARN:  아래 그림자에서 사용된 1e-4f는 반사/반투명 물체에서 문제가 발생 할 수 있음.
	t_ray shadow_ray = create_ray(gl_vec3_add_vector(hit.point, gl_vec3_multiply_scalar(hit_point_to_light, 1e-4f)), hit_point_to_light);
	t_hit shadow_ray_hit = find_closet_collision(device, &shadow_ray);

	// * (2) Diffuse COlor
	// TODO:  물체보다 광원이 더 가까운 경우, 그 경우는 그림자가 생기면 안된다. (우측 조건문이 이에 해당.)
	if (shadow_ray_hit.distance < 0.0f || shadow_ray_hit.distance > gl_vec3_get_magnitude(gl_vec3_subtract_vector(device->light->pos, hit.point)))
	{
		// * 1017. Normal Map 구현 (내가 생각하는 normal_map 구현기. 정말 이게 맞는지는 해보고 체크. ----------------
		// 참고 자료
		// https://www.youtube.com/watch?v=6_-NNKc4lrk
		// Normal Map을 이용한다면, _diff 의 값이 달리질 것이다.
		// hit.normal이 normal_map에 의해 추가적으로 계산되어야 한다.

		t_vec3 hit_normal = hit.normal;
		if (hit.obj->normal_texture != NULL)
		{
			hit_normal = sample_normal_map(&hit);
		}
		// * -------------------------------------------------------------------------------------------

		// (3-1) Calculate Diffuse color
		// FIX:  삼각형 라인이 티나는 이유는 _diff 변수가 삼각형의 외각으로 갔을 때 값이 바뀌는 것 외에는 답이 없다.
		const float _diff = max_float(gl_vec3_dot(hit_normal, hit_point_to_light), 0.0f);

		t_vec3 diffuse_final = gl_vec3_multiply_scalar(hit.obj->material.diffuse, _diff);

		// *--- [ Diffuse Texture ] -----------------------------------------
		if (hit.obj->diffuse_texture != NULL) // if has diffuse texture
		{
			t_vec3 sample_diffuse;
			if (hit.obj->diffuse_texture->type == TEXTURE_CHECKER)
				sample_diffuse = sample_point(hit.obj->diffuse_texture, hit.uv, true); // texture sampling (linear)
			else
				sample_diffuse = sample_linear(hit.obj->diffuse_texture, hit.uv, true); // texture sampling (linear)

			diffuse_final.r = _diff * sample_diffuse.b;
			diffuse_final.g = _diff * sample_diffuse.g;
			diffuse_final.b = _diff * sample_diffuse.r;
		}
		// *------------------------------------------------------------------

		// (3-2) Add Diffuse ( = Resulting color )
		t_vec3 phong_color = diffuse_final;

		// (4-1) Calculate Specular [ 2 * (N . L)N - L ]
		// 광원에서 hit_point로 빛을 쏘았을 때 그 반사 방향과, ray_direction간의 각도가 0에 가깝다면 밝게.
		const t_vec3 spec_reflection_dir = gl_vec3_subtract_vector(gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(hit_normal, gl_vec3_dot(hit_point_to_light, hit_normal)), 2.0f), hit_point_to_light);
		const float _spec = powf(max_float(gl_vec3_dot(gl_vec3_reverse(ray->direction), spec_reflection_dir), 0.0f), hit.obj->material.alpha);
		const t_vec3 specular_final = gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(hit.obj->material.specular, _spec), hit.obj->material.ks);
		phong_color = gl_vec3_add_vector(phong_color, specular_final);  // (4-2) Add Specular color
		final_color = gl_vec3_multiply_scalar(phong_color, 1.0f - hit.obj->material.reflection - hit.obj->material.transparency);

		if (hit.obj->material.reflection)
		{
			// 여기에 반사 구현
			// 수치 오류 주의
			// 반사광이 반환해준 색을 더할 때의 비율은 hit.obj->reflection
			// d - 2( n . d )n
			const t_vec3 reflected_ray_dir = gl_vec3_subtract_vector(ray->direction, (gl_vec3_multiply_scalar(gl_vec3_multiply_scalar(hit_normal, gl_vec3_dot(ray->direction, hit_normal)), 2.0f)));

			// 살짝 위로 떨궈야 hit 계산시에 충돌처리 되지 않음.
			const t_vec3 hit_point_offset = gl_vec3_add_vector(hit.point, gl_vec3_multiply_scalar(reflected_ray_dir, 1e-4f));
			const t_ray reflected_ray = create_ray(hit_point_offset, reflected_ray_dir);
			const t_vec3 reflected_color = trace_ray(device, &reflected_ray, recursive_level - 1);

			final_color = gl_vec3_add_vector(final_color, gl_vec3_multiply_scalar(reflected_color, hit.obj->material.reflection));
		}

		if (hit.obj->material.transparency)
		{
			// 참고
			// https://samdriver.xyz/article/refraction-sphere (그림들이 좋아요)
			// https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel (오류있음)
			// https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/reflection_refraction.pdf (슬라이드가 보기 좋지는 않지만 정확해요)

			const float ior = 1.5f; // Index of refraction (유리: 1.5, 물: 1.3)

			float eta; // sinTheta1 / sinTheta2
			t_vec3 normal;

			if (gl_vec3_dot(ray->direction, hit.normal) < 0.0f) // 밖에서 안에서 들어가는 경우 (예: 공기->유리)
			{
				eta = ior;
				normal = hit.normal;
			}
			else // 안에서 밖으로 나가는 경우 (예: 유리->공기)
			{
				eta = 1.0f / ior;
				normal = gl_vec3_reverse(hit.normal);
			}

			const float cosTheta1 = gl_vec3_dot(gl_vec3_reverse(ray->direction), normal);
			const float sinTheta1 = sqrt(1.0f - cosTheta1 * cosTheta1) ; // cos^2 + sin^2 = 1
			const float sinTheta2 = sinTheta1 / eta ;
			const float cosTheta2 = sqrt(1.0f - sinTheta2 * sinTheta2);

			const float m_0 = gl_vec3_dot(gl_vec3_reverse(ray->direction), normal);
			const t_vec3 m = gl_vec3_normalize(gl_vec3_add_vector(gl_vec3_multiply_scalar(normal, m_0), ray->direction));
			const t_vec3 A = gl_vec3_multiply_scalar(m, sinTheta2);
			const t_vec3 B = gl_vec3_multiply_scalar(gl_vec3_reverse(normal), cosTheta2);
			const t_vec3 refracted_direction = gl_vec3_normalize(gl_vec3_add_vector(A, B));

			t_vec3 offset = gl_vec3_multiply_scalar(refracted_direction, 0.0001f);
			t_ray refraction_ray = create_ray(gl_vec3_add_vector(hit.point, offset), refracted_direction);

			const t_vec3 refracted_color = trace_ray(device, &refraction_ray, recursive_level - 1);
			final_color = gl_vec3_add_vector(final_color, gl_vec3_multiply_scalar(refracted_color, hit.obj->material.transparency));

			// Fresnel 효과는 생략되었습니다.
		}
		return (final_color);
	}
	return (gl_vec3_1f(0.0f));
}


// device에 있는 모든 obj를 돌면서, 가장 가까운 충돌 지점을 계산.
t_hit find_closet_collision(t_device *device, const t_ray *ray)
{
	float closest_distance = FLT_MAX;
	t_hit closest_hit = create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f));

	size_t i = 0;
	while (i < device->objects->size)
	{
		// ... find hit
		t_hit hit = check_ray_collision(ray, device->objects->data[i]);

		// 모든 물체에 대해서 충돌을 계산하고, 그 중에서 d값이 더 작은 경우 그 값을 hit으로 만들면 된다.
		if (hit.distance >= 0.0f && hit.distance < closest_distance)
		{
			closest_distance = hit.distance;
			closest_hit = hit;
			closest_hit.obj = device->objects->data[i];

			// 텍스쳐 좌표
			closest_hit.uv = hit.uv;
		}
		i++;
	}
	return (closest_hit);
}

// 물체의 타입에 따라 다르게 체크.
t_hit check_ray_collision(const t_ray *ray, t_object *obj)
{
	if (obj->type == TYPE_SPHERE)
		return (sphere_intersect_ray_collision(ray, obj->obj_data));
	else if (obj->type == TYPE_TRIANGLE)
		return (triangle_intersect_ray_collision(ray, obj->obj_data));
	else if (obj->type == TYPE_PLAIN)
		return (plane_intersect_ray_collision(ray, obj->obj_data));
	else if (obj->type == TYPE_SQUARE)
		return (square_intersect_ray_collision(ray, obj->obj_data));
	// else if (obj->type == TYPE_CYLINDER)
	// {}
	// else if (obj->type == TYPE_CONE)
	// {}
	return (create_hit(-1.0f, gl_vec3_1f(0.0f), gl_vec3_1f(0.0f)));
}
