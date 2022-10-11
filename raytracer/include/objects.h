#ifndef OBJECT_H
# define OBJECT_H

#include "libft.h"
#include "vector.h"
#include "gl_vec3.h"

/* ---------------------------------
		Objects type-definition
   --------------------------------- */
typedef struct s_ambient_light {
	bool 	has_ambient_light;

	float	brightness_ratio;
	t_vec3	color;

}	t_ambient_light;

typedef struct s_light {
	bool	has_light;

	t_vec3	pos; // 아주 단순화된 형태의 위치만 있는 점조명.
	float	brightness_ratio;
	t_vec3	color;

}	t_light;

typedef struct s_sphere {
	//...
	t_vec3	center;
	float	radius;
	// t_vec3	color; // 추후 재질로 확장

	// t_vec3	ambient;
	// t_vec3	diffuse;
	// t_vec3	specular;
	// float	ks;
	// float	alpha;
	// float reflection;
	// float transparency;

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
}	t_object;

// typedef struct s_objects {
	// t_vector	*spheres;
	// t_vector	*planes;
	// t_vector	*cylinders;
	// t_vector	*cone;
// }	t_objects;

#endif /* objects.h */
