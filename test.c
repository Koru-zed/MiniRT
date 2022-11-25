#include "Include/miniRT.h"



int main()
{
	int a = 0;
	float b= (float)a;
	printf("%f", b);
}

void	yaw_cam(int keycode, t_scene *s)
{
	t_matrix	rotated;
	t_matrix	prod;

	if (keycode == KEY_LEFT)
		rotated = matrix_rot_y(-ANGLE);
	else
		rotated = matrix_rot_y(ANGLE);
	printf("yaw_cam\n");
	prod = matrix_product(rotated, s->cam->m);
	s->cam->m = prod;
	s->cam->dir.x = s->cam->m.d[2][0];
	s->cam->dir.y = s->cam->m.d[2][1];
	s->cam->dir.z = s->cam->m.d[2][2];
	remake_scene(s, get_mlx());
}