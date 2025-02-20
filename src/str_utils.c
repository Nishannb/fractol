# include "fractol.h"

int ft_strncmp(char *s1, char *s2, int n)
{
    if(s1 == NULL || s2 == NULL || n <= 0)
    {
        return (0);
    }
    while (*s1 == *s2 && n > 0 && *s1 != '\0')
    {
        ++s1;
        ++s2;
        --n;
    }
    return (*s1 - *s2);
}

void ft_putstr(char *s, int fd)
{
    if(s==NULL || fd < 0){
        return;
    }
    if(*s != '\0'){
        write(fd, s, 1);
        ft_putstr(s + 1, fd);
    }
}

double atodbl(char *s, int sign)
{
    long int_part;
    double frac_part;
    double pow;

    int_part = 0;
    frac_part = 0;
    pow = 1;
    while ((*s >= 9 && *s <= 13) || *s == 32)
        s++;
    while (*s == '+' || *s == '-')
        if (*s == '-')
            sign = -sign;
    while(*s != '.' && *s)
        int_part = (int_part * 10) + (*s++ - 48);
    if (*s == '.')
        ++s;
    while (*s)
    {
        pow /= 10;
        frac_part = frac_part + (*s++ - 48) * pow;
    }
    return ((int_part + frac_part) * sign);
}