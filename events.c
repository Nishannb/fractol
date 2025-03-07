#include "fractol.h"
# include "minilibx_macos/mlx.h"

int close_handler(t_fractol *fractol)
{
    // mlx_destroy_image(fractol->mlx_connection, fractol->img.img_ptr);
    // mlx_destroy_window(fractol->mlx_connection, fractol->mlx_window);
    // mlx_destroy_display(fractol->mlx_connection);
    free(fractol->mlx_connection);
    exit(EXIT_SUCCESS);
}


// int key_handler(int keysym, t_fractol *fractol)
// {

//     if(keysym == XK_Escape)
//         close_handler(fractol);
//     else if (keysym == XK_Left)
//         fractol->shift_x += (0.5 * fractol->zoom);
//     else if (keysym == XK_Right)
//         fractol->shift_x -= (0.5 * fractol->zoom);
//     else if (keysym == XK_Up)
//         fractol->shift_y -= (0.5 * fractol->zoom);
//     else if (keysym == XK_Down)
//         fractol->shift_y += (0.5 * fractol->zoom);
//     else if (keysym == XK_plus)
//         fractol->interation_defintion +=10;
//     else if (keysym == XK_minus)
//         fractol->interation_defintion -=10;
//     fractol_render(fractol);
//     return (0);
// }

int key_handler(int keycode, t_fractol *fractol)
{
    if (keycode == 53) 
        close_handler(fractol);
    else if (keycode == 123) 
        fractol->shift_x += (0.5 * fractol->zoom);
    else if (keycode == 124) 
        fractol->shift_x -= (0.5 * fractol->zoom);
    else if (keycode == 126) 
        fractol->shift_y -= (0.5 * fractol->zoom);
    else if (keycode == 125) 
        fractol->shift_y += (0.5 * fractol->zoom);
    else if (keycode == 24) 
        fractol->interation_defintion += 10;
    else if (keycode == 27) 
        fractol->interation_defintion -= 10;

    fractol_render(fractol);
    return (0);
}

int mouse_handler(int button, int x, int y, t_fractol *fractol)
{
    if (button == Button5)
        fractol->zoom *=0.95;
    else if (button == Button4)
        fractol->zoom *=1.05;
    fractol_render(fractol);
    return (0);
}

int julia_track(int x, int y, t_fractol *fractol)
{
    if (!ft_strncmp(fractol->name, "julia", 5)){
        fractol->julia_x = (map(x, -2, +2, 0, WIDTH) * fractol->zoom) + fractol->shift_x;
        fractol->julia_y = (map(x, -2, +2, 0, HEIGHT) * fractol->zoom) + fractol->shift_y;
    } 
    fractol_render(fractol);
    return (0);
}