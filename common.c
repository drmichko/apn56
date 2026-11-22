#include "common.h"
#include "basistools.h"

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


double   clK[ 49 ];
vector   rep[ 49 ];
boole    fct[ 49] ={ NULL};
int64_t  stabsize[ 49 ];
int64_t  orbsize[ 49 ]={0};
aglGroup grp[ 49]={NULL};


void initclass( basis_t base )
{
    uint64_t size;
    aglGroup g = NULL;
    int num = 0;
    int nbclass = 0;
    for( vector v = 0; v < base.size; v++ ){
	    int cls = base.table[v];
	    if ( orbsize[ cls ] == 0 ) {
		    rep[ cls ] = v;
		    fct[ cls ] = vectortoboole( v, &base );
		    clK[ cls ] = kappa(  fct[ cls ]  );
		    nbclass++;
	    }
	    orbsize[ cls ]++;
}
}
