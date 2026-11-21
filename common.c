#include "common.h"

int intcmp(const void *p1, const void *p2)
{
    return *((int *) p1) - *((int *) p2);
}



double kappa( boole f )
{
        int * res = calloc( ffsize, sizeof(int ) );
        for( int a = 0; a < ffsize;a++ )
                res[a] = 1 - 2  * f[a];
        Fourier( res, ffsize );
        int K = 0;
        for( int a = 0; a < ffsize; a++ )
                K += res[a]*res[a]*res[a]*res[a];
        free( res );
        return (float) K / ffsize/ ffsize/ffsize;;
}

int trivial( int b, int q )
{
	return ( ( 3*b - 1 ) * q  - 2 * b );

}


