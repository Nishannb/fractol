#include "fractol.h"


static void my_pixel_put(int x, int y, t_img *img, int color)
{
    int offset;

    offset = (y * img->line_len) + (x * (img->bpp / 8));
    color = *(unsigned int *)( img->pixels_ptr + offset );
}

static void mandel_vs_julia(t_complex *z, t_complex *c, t_fractol *fractol)
{
    if (!ft_strncmp(fractol->name, "julia", 5)){
        c->x = fractol->julia_x;
        c->y = fractol->julia_y;
    } else {
        c->x = z->x;
        c->y = z->y;
    }
}

static void handle_pixel(int x, int y, t_fractol *fractol)
{
    t_complex z;
    t_complex c;
    int i;
    int color;

    i = 0;

    z.x = (map(x, -2, +2, 0, WIDTH) * fractol->zoom) + fractol->shift_x;
    z.y = (map(y, +2, -2, 0, HEIGHT) * fractol->zoom) + fractol->shift_y;

    mandel_vs_julia(&z, &c, fractol);
    while (i < fractol->interation_defintion)
    {
        z = sum_complex(square_complex(z), c);
        if(pythagoras(z) > fractol->escape_value)
        {
            color = map(i, BLACK, WHITE, 0, fractol->interation_defintion);
            my_pixel_put(x, y, &fractol->img, color);
            return;
        }
        ++i;
    }
    my_pixel_put(x, y, &fractol->img, MAGENTA);
}

void fractol_render(t_fractol *fractol)
{
    int x;
    int y;

    y = -1;
    while (++y <HEIGHT)
    {
        x = -1;
        while (++x <WIDTH)
        {
            handle_pixel(x, y, fractol);
        }
    }
    mlx_put_image_to_window(fractol->mlx_connection,
                            fractol->mlx_window,
                            fractol->img.img_ptr,
                            0, 0);
}