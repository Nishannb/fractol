#include "fractol.h"


static void my_pixel_put(int x, int y, t_img *img, int color)
{
    int offset;

    offset = (y * img->line_len) + (x * (img->bpp / 8));
    *(unsigned int *)( img->pixels_ptr + offset ) = color;
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
            // write(1, &color, sizeof(color));
            my_pixel_put(x, y, &fractol->img, color);
            return;
        }
        ++i;
    }
    my_pixel_put(x, y, &fractol->img, MAGENTA);
}

// void fractol_render(t_fractol *fractol)
// {
//     int x;
//     int y;

//     y = -1;
//     while (++y <HEIGHT)
//     {
//         x = -1;
//         while (++x <WIDTH)
//         {
//             handle_pixel(x, y, fractol);
//         }
//     }
//     mlx_put_image_to_window(fractol->mlx_connection,
//                             fractol->mlx_window,
//                             fractol->img.img_ptr,
//                             0, 0);
// }

// Thread function to render a portion of the image
void *render_pixels(void *arg)
{
    t_thread_data *data = (t_thread_data *)arg;
    int x, y;
    for (y = data->start_y; y < data->end_y; ++y) {
        for (x = 0; x < WIDTH; ++x) {
            handle_pixel(x, y, data->fractol);  // Render the pixel
        }
    }
    return NULL;
}

void fractol_render_seq(t_fractol *fractol)
{
    int x, y;
    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            handle_pixel(x, y, fractol); // Original code
        }
    }
}

void fractol_render(t_fractol *fractol)
{
    int i;
    pthread_t threads[THREADS];  // Array of threads
    t_thread_data thread_data[THREADS];  // Array of data for each thread
    int rows_per_thread = HEIGHT / THREADS;

    // Create threads
    for (i = 0; i < THREADS; ++i) {
        thread_data[i].start_y = i * rows_per_thread;  // Calculate the start Y for this thread
        thread_data[i].end_y = (i == THREADS - 1) ? HEIGHT : (i + 1) * rows_per_thread;  // End Y for the last thread might be different
        thread_data[i].fractol = fractol;
        
        pthread_create(&threads[i], NULL, render_pixels, &thread_data[i]);  // Create the thread
    }

    // Wait for all threads to finish
    for (i = 0; i < THREADS; ++i) {
        pthread_join(threads[i], NULL);  // Join the thread (wait for it to finish)
    }

    // After all threads finish, update the window with the image
    mlx_put_image_to_window(fractol->mlx_connection, fractol->mlx_window, fractol->img.img_ptr, 0, 0);
}
