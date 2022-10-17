#ifndef OBJECT_H
# define OBJECT_H

#include "libft.h"
// #include "vector.h"
#include "gl_vec3.h"
#include "gl_vec2.h"
// #include "texture.h"

#include "triangle.h"
#include "square.h"
#include "plane.h"

#include "sphere.h"
#include "cone.h"
#include "cylinder.h"

#include "lights.h"
#include "camera.h"


typedef struct s_texture t_texture;
/* ---------------------------------
		Objects type-definition
   --------------------------------- */

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
	t_texture	*diffuse_texture; // diffuse_color
	t_texture	*normal_texture;  // normal_map

}	t_object;

#endif /* objects.h */
