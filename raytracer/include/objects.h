#ifndef OBJECT_H
# define OBJECT_H

#include "libft.h"
#include "vector.h"
#include "gl_vec3.h"

/* ---------------------------------
		Objects type-definition
   --------------------------------- */
typedef struct s_ambient_light {
	bool 	has_ambient_light; // light 중복 체크용

	float	brightness_ratio;
	t_vec3	color;

}	t_ambient_light;

typedef struct s_light {
	bool	has_light; // light 중복 체크용

	t_vec3	pos; // 아주 단순화된 형태의 위치만 있는 점조명.
	float	brightness_ratio;
	t_vec3	color;

}	t_light;

typedef struct s_triangle {
	t_vec3	v0; // vertex_1
	t_vec3	v1; // vertex_2
	t_vec3	v2;	// vertex_3

	// t_vec2 uv1; // for texture
	// t_vec2 uv2; // for texture
	// t_vec2 uv3; // for texture

}	t_triangle;

typedef struct s_sphere {
	t_vec3	center;
	float	radius;
}	t_sphere;

typedef struct s_plane {
	//...
}	t_plane;

typedef struct s_cylinder {
	//...
}	t_cylinder;

typedef struct s_cone {
	//...
}	t_cone;

#define TYPE_NO_HIT		(0)
#define TYPE_SPHERE		(1)
#define TYPE_PLAIN		(2)
#define TYPE_CYLINDER	(3)
#define TYPE_CONE		(4)
#define TYPE_TRIANGLE   (5)

typedef struct s_material {
	// NOTE:  for Phong shading
	// t_vec3	ambient; // --> use ambient light as ambient
	t_vec3	diffuse; // == color!
	t_vec3	specular;
	float	ks;
	float	alpha;
	// float reflection;
	// float transparency;
}	t_material;

typedef struct s_object {

	t_material	material;
	int			type;	 // type of object (ex. Sphere)

	// WARN:  void*로 일반화해서 다루지 않고, 그냥 통으로 저장 (4개의 타입) --> 개선 필요
	t_sphere	sphere;
	t_plane		plain;
	t_cylinder	cylinder;
	t_cone		cone;
	t_triangle	triangle;

}	t_object;

#endif /* objects.h */
