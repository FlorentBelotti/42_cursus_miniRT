#include "miniRT.h"

double ft_atof(const char *str)
{
    double result = 0.0;
    double sign = 1.0;
    double fraction = 0.0;
    double divisor = 10.0;
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1.0;
        str++;
    }
    while (*str >= '0' && *str <= '9')
        result = result * 10.0 + (*str++ - '0');
    if (*str == '.')
    {
        str++;
        while (*str >= '0' && *str <= '9')
        {
            fraction += (*str++ - '0') / divisor;
            divisor *= 10.0;
        }
    }
    return (sign * (result + fraction));
}

void free_objects(t_object *objects)
{
    t_object *tmp;
    while (objects)
    {
        tmp = objects;
        objects = objects->next;
        free(tmp);
    }
}

void free_split(char **split)
{
    int i = 0;
    while (split[i])
        free(split[i++]);
    free(split);
}
