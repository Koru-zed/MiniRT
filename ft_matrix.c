#include "Include/miniRT.h"


bool	float_equal(float a, float b)
{
	if (fabsf(a - b) < EPSILON)
		return true;
	return false;
}

t_matrix	*creat_matrix(size_t c)
{
	t_matrix	*matrix;
	int			 i;

	i = 0;
	matrix = ft_calloc(1, sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	matrix->row = c;
	matrix->col = c;
	matrix->mat = ft_calloc(c, sizeof(float *));
	while (i < c)
	{
		matrix->mat[i] = ft_calloc(c, sizeof(float));
		i++;
	}
	return matrix;
}

// Matrix multiplication computes the dot product of every row-column combination in the two matrices
t_matrix *matrix_multiplication(t_matrix *a, t_matrix *b)
{
	t_matrix *m;
	int 	r;
	int 	c;

	r = -1;
	c = -1;
	m = ft_calloc(1, sizeof(t_matrix));
	m->mat = ft_calloc(4, sizeof(float*));
	while (r++ < 3)
	{
		m->mat[r] = ft_calloc(4, sizeof(float ));
		while (c++ < 3)
		{
			m->mat[r][c] = a->mat[r][0] * b->mat[0][c] + a->mat[r][1] * b->mat[1][c]
					+ a->mat[r][2] * b->mat[2][c] + a->mat[r][3] * b->mat[3][c];
		}
	}
	return m;
}