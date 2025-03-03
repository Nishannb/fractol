#include "fractol.h"
# include "minilibx_macos/mlx.h"

void measure_sequential(t_fractol *fractol)
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    fractol_render_seq(fractol);  // Render using the original code
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sequential render took %f seconds\n", cpu_time_used);
}

// Measure the time for parallel render
void measure_parallel(t_fractol *fractol)
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    fractol_render(fractol);  // Render using the parallel code
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Parallel render took %f seconds\n", cpu_time_used);
}


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
            // fractol_render(&fractol);
            measure_sequential(&fractol);

            // Measure parallel render time
            measure_parallel(&fractol);

            mlx_loop(fractol.mlx_connection);
    } else {
        ft_putstr("Error, only mandelbrot or julia\n", 2);
        exit(EXIT_FAILURE);
    }
    return (1);
}
