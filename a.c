#include <stdio.h>

void ft_h(void a)
{
	printf("%d",a);
}
int main(){
	int a;


	a = -1;
	if (a > 255)
		ft_h(a);
}
