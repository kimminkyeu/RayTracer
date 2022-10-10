#ifndef OBJECT_H
# define OBJECT_H

#include "libft.h"
#include "vector.h"
#include "gl_vec3.h"

/* ---------------------------------
		Objects type-definition
   --------------------------------- */

typedef struct s_ambient_light {

	float	brightness_ratio;
	t_vec3	color;

}	t_ambient_light;

typedef struct s_light {

	t_vec3	pos; // 아주 단순화된 형태의 위치만 있는 점조명.
	float	brightness_ratio;
	t_vec3	color;

}	t_light;

typedef struct s_sphere {
	//...
	t_vec3	center;
	float	radius;
	t_vec3	color; // 추후 재질로 확장

	// NOTE:  for Phong shading
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	specular;
	float	ks;
	float	alpha;
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

typedef struct s_objects {

	t_vector	*ambient_lights;

	t_vector	*lights;

	t_vector	*spheres;

	t_vector	*planes;

	t_vector	*cylinders;

	t_vector	*cone;

}	t_objects;

#endif /* objects.h */
