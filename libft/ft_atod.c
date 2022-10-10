

#include "libft.h"
#include <math.h>

double	ft_atod(const char *str, int *check)
{
	double	value;
    double  power;
	double	signe;

	value = 0.0;
    power = 1.0;
	signe = 1.0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -signe;
        str++;
	}
	while (*str && ft_isdigit(*str))
	{
		value = (value * 10.0) + (*str - '0');
		str++;
	}
    if ((str++ == '.')
	{
		while (*str && ft_isdigit(*str))
		{
			value = (value * 10.0) + (str[*index] - '0');
			power++;
			str++;
		}
	}
    if (*str)
    {
		*check = -1;
        ft_putstr_fd("# Bad value #", 1);
		return (0);
        // exit(EXIT_FAILURE);
    }
	return (value * pow(10.0, -(power - 1)) * signe);
}
// Converet string to double and return indice of last char converted to double