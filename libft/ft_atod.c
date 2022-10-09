

#include "libft.h"
#include <math.h>

double	ft_atod(const char *str, int *index)
{
	double	value;
    double  power;
	double	signe;

	value = 0.0;
    power = 1.0;
	signe = 1.0;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			signe = -signe;
		// {
		// 	printf("# Nigative value #");
        //     return (-1);
        // }
        *index += 1;
	}
	while (ft_isdigit(str[*index]))
	{
		value = (value * 10.0) + (str[*index] - '0');
		str++;
	}
    if ((str[*index++]) == '.')
	{
		while (ft_isdigit(str[*index]))
		{
			value = (value * 10.0) + (str[*index] - '0');
			power++;
			str++;
		}
	}
    if (ft_isalpha(str[*index]))
    {
        ft_putstr_fd("# Bad value #", 1);
        exit(EXIT_FAILURE);
    }
	return (value * pow(10.0, -(power - 1) * signe));
}

// Converet string to double and return indice of last char converted to double