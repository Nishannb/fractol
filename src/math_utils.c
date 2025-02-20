#include "fractol.h"

double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return (( new_max - new_min ) * (unscaled_num - old_min) / ( old_max - old_min) + new_min);
}

t_complex sum_complex(t_complex z1, t_complex z2)
{
    t_complex res;

    res.x = z1.x + z2.x;
    res.y = z1.y + z2.y;
    return (res);
}

t_complex square_complex(t_complex z1)
{
    t_complex res;

    res.x = (z1.x * z1.x) - (z1.y * z1.y);
    res.y = 2 * z1.x * z1.y;
    return (res);
}

double pythagoras(t_complex z)
{
    return ((z.x * z.x) + (z.y* z.y));
}

