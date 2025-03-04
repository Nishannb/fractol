#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
#include "minilibx-linux/mlx.h"
#include <pthread.h>
#include <time.h>


#define THREADS 8 


#define WIDTH  800
#define HEIGHT 800
#define BLACK   0x000000
#define WHITE   0xFFFFFF
#define RED     0xFF0000
#define GREEN   0x00FF00
#define BLUE    0x0000FF
#define GRAY    0x808080
#define LIGHT_GRAY 0xD3D3D3
#define DARK_GRAY  0x505050
#define YELLOW  0xFFFF00
#define CYAN    0x00FFFF
#define MAGENTA 0xFF00FF
#define ORANGE  0xFFA500
#define PURPLE  0x800080
#define BROWN   0xA52A2A

typedef struct s_img
{
    void *img_ptr;
    char *pixels_ptr;
    int bpp;
    int endian;
    int line_len;
} t_img;

typedef struct s_complex
{
    double x;
    double y;
}  t_complex;


typedef struct s_fractol
{
    char *name;
    void *mlx_connection;
    void *mlx_window;
    t_img img;
    double escape_value;
    int interation_defintion;
    double shift_x;
    double shift_y;
    double zoom;
    double julia_x;
    double julia_y;
} t_fractol;

typedef struct s_thread_data {
    int start_y;  
    int end_y;    
    t_fractol *fractol;
} t_thread_data;

int ft_strncmp(char *s1, char *s2, int n);
void ft_putstr(char *s, int fd);
void fractol_init(t_fractol *fractol);
double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex square_complex(t_complex z1);
t_complex sum_complex(t_complex z1, t_complex z2);
double pythagoras(t_complex z);
void fractol_render(t_fractol *fractol);
int key_handler(int keysym, t_fractol *fractol);
int close_handler(t_fractol *fractol);
int mouse_handler(int button, t_fractol *fractol);
double atodbl(char *s, int sign);
int julia_track(int x, int y, t_fractol *fractol);


#endif
