
#include "libft.h"

int	ft_arrylen(char **arry)
{
	int	i;

	i = 0;
	while (arry[i])
		i++;
	return (i);
}