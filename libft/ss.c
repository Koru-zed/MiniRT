#include "libft.h"

int main()
{
	char **arr;
	char str[] ="A   0.2                                      255,255,0\n";
	arr = ft_split(str, ' ');
	ft_arrylen(arr);
	return 0;
}
