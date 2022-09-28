#include <stdio.h>
#include <stdlib.h>
#include "vector_uchar.h"

void	print_all(t_vector_uchar *vec)
{
	if (vec == NULL)
	{
		printf("data is null\n\n");
		return ;
	}
	printf("size=%zd capacity=%zd\n", vec->size, vec->capacity);
	for(size_t i=0; i<vec->size; i++)
		printf("%d ", vec->data[i]);
	printf("\n\n");
}

unsigned char	inc(unsigned char i)
{
	return (i + 1);
}

int main(void)
{
	t_vector_uchar *vec = new_vector_uchar(10);

	printf("push back\n");
	vec->push_back(vec, 10);
	vec->push_back(vec, 20);
	vec->push_back(vec, 30);
	print_all(vec);

	printf("pop back\n");
	vec->pop_back(vec);
	vec->pop_back(vec);
	vec->pop_back(vec);
	print_all(vec);

	printf("iterate\n");
	vec->iterate(vec, inc);
	print_all(vec);

	t_vector_uchar *new_vec = vec->map_malloc(vec, inc);
	printf("map -> new vec\n");
	print_all(new_vec);
	if (new_vec != NULL)
		free(new_vec);

	printf("map -> original vec\n");
	print_all(vec);

	for(size_t i=0; i < 20; i++)
		vec->push_back(vec, i);
	print_all(vec);

	vec->shrink_to_fit(vec);
	print_all(vec);

	printf("get_last() : %d\n\n", *(vec->get_last(vec)));

	printf("reset vec\n");
	vec->reset(vec);
	print_all(vec);

	return (0);
}
