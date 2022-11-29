# include "../Include/miniRT.h"

t_matrix update_matrix_x(double theta)
{
	double _radian;
	t_matrix matrix;

	_radian = (double)(theta * M_PI / 180);
	matrix = dir_matrix();
	matrix.M[1][1] = cos(_radian);
	matrix.M[1][2] = sin(_radian);
	matrix.M[2][1] = -sin(_radian);
	matrix.M[2][2] = cos(_radian);
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

	matrix.M[0][0] = cos(_radian);
	matrix.M[0][2] = -sin(_radian);
	matrix.M[2][0] = sin(_radian);
	matrix.M[2][2] = cos(_radian);
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
	matrix.M[0][0] = cos(_radian);
	matrix.M[0][1] = sin(_radian);
	matrix.M[1][0] = -sin(_radian);
	matrix.M[1][1] = cos(_radian);
	// printf("dir_matrix\n");
	print_matrix(matrix);
	printf("---------------------------------------------------\n");
	return (matrix);
}