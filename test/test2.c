#include "../Include/miniRT.h"
#include <stdio.h>
#include <mlx.h>
/* With and height of our image */
#define WIDTH  800
#define HEIGHT 500

static void	my_mlx_pixel_put(t_mlx *Mlx, int x, int y, int color)
{
	char	*dst;

	dst = Mlx->addr + (y * Mlx->line_length + x * (Mlx->bits_per_pixel >> 3));
	*(unsigned int*)dst = color;
    printf("**********\n");
}

int main(int argc, char *argv[]){

        // unsigned char img[WIDTH * HEIGHT * 3];
 t_mlx *Mlx;
        int i,j;
        float r;
        float g;
        float b;
        float ir;
        float ig;
        float ib;

        Mlx = ft_calloc(1, sizeof(t_mlx));
    Mlx->mlx = mlx_init();
    Mlx->win = mlx_new_window(Mlx->mlx, 500, 800, "miniRT");
    Mlx->img = mlx_new_image(Mlx->mlx, 500, 800);
    Mlx->addr = mlx_get_data_addr(Mlx->img, &Mlx->bits_per_pixel, &Mlx->line_length, &Mlx->endian);
    // exit(0);
    // std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            r = float(i) / (image_width-1);
            g = float(j) / (image_height-1);
            b = 0.25;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);
            my_mlx_pixel_put(Mlx, i, j, (int)((ir << 16) + (ig << 8) + ib));

            // std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
        // printf("************\n");
    mlx_put_image_to_window(Mlx->mlx, Mlx->win, Mlx->img, 0, 0);
    mlx_loop(Mlx->mlx);
        // saveppm("image.ppm", img, WIDTH, HEIGHT);

return 0;
}

