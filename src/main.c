#include "fractol.h"

int main (int ac, char **av) {   

    t_fractol fractol;


    if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10)) 
        || (ac == 4 && !ft_strncmp(av[1], "julia", 5))) {
            fractol.name = av[1];
            if (!ft_strncmp(fractol.name, "julia", 5))
            {
                fractol.julia_x = atodbl(av[2], 1);
                fractol.julia_y = atodbl(av[3], 1);
            }
            fractol_init(&fractol);
            fractol_render(&fractol);

            mlx_loop(fractol.mlx_connection);
    } else {
        ft_putstr("Error, only mandelbrot or julia\n", 2);
        exit(EXIT_FAILURE);
    }
    return (1);
}
