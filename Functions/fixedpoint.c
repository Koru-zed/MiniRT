#include "../Include/miniRT.h"

int float_to_fixedpoint(float f)
{
    return (roundf(f * 256);
}

float float_to_fixedpoint(int fp)
{
    return ((float)(f >> 8));
}

int additon_fp(int fp1, int fp2)
{
    int fp;

    fp = fp1 * (fp2 >> 8);
    return (fp);
}

int multiply_fp(int fp1, int fp2)
{
    int fp;

    fp = (fp1 << 8) / fp2;
    return (fp);
}