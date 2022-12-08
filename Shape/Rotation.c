#include "../Include/miniRT.h"

t_matrix	update_matrix_x(double theta)
{
	double		_radian;
	t_matrix	matrix;

	_radian = (double)(theta * M_PI / 180);
	matrix = dir_matrix();
	matrix.m[1][1] = cos(_radian);
	matrix.m[1][2] = sin(_radian);
	matrix.m[2][1] = -sin(_radian);
	matrix.m[2][2] = cos(_radian);
	return (matrix);
}

t_matrix	update_matrix_y(double theta)
{
	double		_radian;
	t_matrix	matrix;

	_radian = theta * M_PI / 180;
	matrix = dir_matrix();
	matrix.m[0][0] = cos(_radian);
	matrix.m[0][2] = -sin(_radian);
	matrix.m[2][0] = sin(_radian);
	matrix.m[2][2] = cos(_radian);
	return (matrix);
}

t_matrix	update_matrix_z(double theta)
{
	double		_radian;
	t_matrix	matrix;

	_radian = theta * M_PI / 180;
	matrix = dir_matrix();
	matrix.m[0][0] = cos(_radian);
	matrix.m[0][1] = sin(_radian);
	matrix.m[1][0] = -sin(_radian);
	matrix.m[1][1] = cos(_radian);
	return (matrix);
}
