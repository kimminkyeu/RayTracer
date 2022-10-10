#ifndef OBJECT_H
# define OBJECT_H

#include "libft.h"
#include "vector.h"

/* ---------------------------------
		Objects type-definition
   --------------------------------- */

typedef struct s_ambient_light {
	//...
}	t_ambient_light;

typedef struct s_light {
	//...
}	t_light;

typedef struct s_sphere {
	//...
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
