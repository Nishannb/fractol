#include "fractol.h"


static void malloc_error(void)
{
    perror("Problems with malloc");
    exit(EXIT_FAILURE);
}
static void data_init(t_fractol *fractol)
{
    fractol->escape_value = 4;
    fractol->interation_defintion = 42;
    fractol->shift_x = 0.0;
    fractol->shift_y = 0.0;
    fractol->zoom = 1.0;
}

static void events_init(t_fractol *fractol)
{
    mlx_hook(fractol->mlx_window, KeyPress, KeyPressMask, key_handler, fractol);
    mlx_hook(fractol->mlx_window, ButtonPress, ButtonPressMask, mouse_handler, fractol);
    mlx_hook(fractol->mlx_window, DestroyNotify, StructureNotifyMask, close_handler, fractol);
    mlx_hook(fractol->mlx_window, MotionNotify, PointerMotionMask, julia_track, fractol);

}



void fractol_init(t_fractol *fractol)
{
    write(1, "fractol\n", sizeof("fractol"));
    fractol->mlx_connection = mlx_init();
    if(fractol->mlx_connection == NULL)
    {
        malloc_error();
    }
    fractol->mlx_window = mlx_new_window(fractol->mlx_connection, WIDTH, HEIGHT, fractol->name);
    if(fractol->mlx_window == NULL)
    {
        // mlx_destroy_display(fractol->mlx_connection);
        free(fractol->mlx_connection);
        malloc_error();
    }
    fractol->img.img_ptr = mlx_new_image(fractol->mlx_connection, WIDTH, HEIGHT);
    if(fractol->img.img_ptr == NULL)
    {
        // mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
        // mlx_destroy_display(fractol->mlx_connection);
        free(fractol->mlx_connection);
        malloc_error();
    }
    fractol->img.pixels_ptr = mlx_get_data_addr(fractol->img.img_ptr,
                                                &fractol->img.bpp,
                                                &fractol->img.line_len,
                                                &fractol->img.endian);
    events_init(fractol);
    data_init(fractol);
}