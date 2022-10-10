#include "libft.h"

char	*ft_str_begin_to_fin(char *str, int begin, int fin)
{
	int		i;
	char	*dst;

	if (!str)
		return (NULL);
	i = 0;
	if (fin - begin == 0)
		return (NULL);
	dst = ft_calloc(sizeof(char), (fin - begin + 1));
	if (!dst)
		return (NULL);
	while (begin < fin)
		dst[i++] = str[begin++];
	dst[i] = '\0';
	return (dst);
}
