#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
   int a  = 9;
   int *b;
   int *p = malloc(4);
   b= p;
   p = &a;
   free(b);
}