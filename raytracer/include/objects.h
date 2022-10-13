#ifndef OBJECT_H
# define OBJECT_H

// #include "libft.h"
// #include "vector.h"
#include "gl_vec3.h"
// #include "texture.h"

typedef struct s_texture t_texture;
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

typedef struct s_sphere {
	t_vec3	center;
	float	radius;
}	t_sphere;

typedef struct s_triangle {
	t_vec3	v0; // vertex_1
	t_vec3	v1; // vertex_2
	t_vec3	v2;	// vertex_3

	t_vec2 uv0; // for texture
	t_vec2 uv1; // for texture
	t_vec2 uv2; // for texture

}	t_triangle;

// NOTE:  추가로 구현한 사각형. (for plain)
typedef struct s_square {

	t_triangle tri_1;
	t_triangle tri_2;
	// t_vec3 v0;
	// t_vec3 v1;
	// t_vec3 v2;
	// t_vec3 v3;
}	t_square;

typedef struct s_plane {
	t_vec3 pos; // position
	t_vec3 normal; // surface-normal
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
#define TYPE_SQUARE   	(6)

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

	// NOTE:  오브젝트 타입을 void* 로 수정함.
	void		*obj_data;

	// Texture
	t_texture	*ambient_texture;
	t_texture	*diffuse_texture;

}	t_object;

#endif /* objects.h */
