# include "../Include/miniRT.h"

t_matrix update_matrix_x(double theta)
{
	double _radian;
	t_matrix matrix;

	_radian = theta * M_PI / 180;
	matrix = dir_matrix();
	matrix.M[1][1] = cosf(_radian);
	matrix.M[1][2] = -sinf(_radian);
	matrix.M[2][1] = sinf(_radian);
	matrix.M[2][2] = cosf(_radian);
	// print_matrix(matrix);	printf("dir_matrix\n");
	// print_matrix(matrix);
	// printf("---------------------------------------------------\n");
	return (matrix);
}

t_matrix update_matrix_y(double theta)
{
	double _radian;
	t_matrix matrix;

	_radian = theta * M_PI / 180;
	matrix = dir_matrix();
	// print_matrix(matrix);
	// printf("---------------------------------------------------\n");

	matrix.M[0][0] = cosf(_radian);
	matrix.M[0][2] = sinf(_radian);
	matrix.M[2][0] = -sinf(_radian);
	matrix.M[2][2] = cosf(_radian);
	// printf("dir_matrix\n");
	// print_matrix(matrix);
	// printf("---------------------------------------------------\n");
	return (matrix);
}

t_matrix update_matrix_z(double theta)
{
	double _radian;
	t_matrix matrix;

	_radian = theta * M_PI / 180;
	matrix = dir_matrix();
	matrix.M[0][0] = cosf(_radian);
	matrix.M[0][1] = -sinf(_radian);
	matrix.M[1][0] = sinf(_radian);
	matrix.M[1][1] = cosf(_radian);
	// printf("dir_matrix\n");
	print_matrix(matrix);
	printf("---------------------------------------------------\n");
	return (matrix);
}