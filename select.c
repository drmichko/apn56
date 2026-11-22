
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "boolean.h"
#include "orbitools.h"
#include "common.h"
#include "distrib.h"
#include "basistools.h"
#include "mapping.h"

int main(int argc, char *argv[])
{
    uint64_t size;
    aglGroup g = NULL;
    int num = 0;
    int opt, target  = 0, optS = 4;
    while ((opt = getopt(argc, argv, "i:s:t:")) != -1) {
	switch (opt) {
	case 't':
	    target = atoi ( optarg );
	    break;
	case 's':
	    optS = atoi( optarg );;
	    break;
	}
    }

    initboole(5);
    initagldim(5);

    basis_t base = monomialBasis(2, 5, ffdimen);
    if ( ! loadBasename("lifting", &base) ){
	    puts("Orbist  ?");
	    return 0;
    }

   FILE *src = fopen( "starter.txt" , "r" );
   if (!src) {
	perror("data ?");
	exit(1);
    }
    size_t aglsize = aglCardinality(ffdimen);
    num = 0;
    boole f;
    int  item = 1;
    double limite = trivial( 2, ffsize );
    limite /= 2 * ffsize  - 1 ;

    while ((f = loadaglboolesize(src, &g, &size))) {
	    assert( kappa( f ) <= limite  );
	    num++;
	   if ( target == num ) {
			int cls = base.table[ booleVector( f, &base ) ];
			printf("\n\nnumero=%d cls=%d", num, cls );
			printf("\nkappa=%.2f", kappa(f) );
			panf(stdout, f);
			paglGroup(stdout, g);
			printf("\norbSize=%ld", aglsize / size);
			printf("\nstabSize=%ld", size);
			break;
			}
            free( f );
	    aglfreeGroup( g );
	    item++;
    }
    fclose(src);
    assert( target == num );
    limite =  ( trivial( 2, ffsize ) - kappa( f )  )  / ( ffsize - 1 );
    printf("\nlimite=%.2f  %.2f", limite, limite/2 );

    int count=0;
    initclass( base );
   
    vector r = booleVector( f, &base );

    basis_t W = monomialBasis(2, 5, ffdimen);
    aglVectorGroup  ldg = NULL;
    ldg = aglVectorGroupAction( g   , & W );
    initBrowse( & W );
    mapping  F = getmap( );

    char name[128];
    sprintf(name, "%d/map-2.txt", target );
    FILE* dst =  fopen( name, "w");
    if (! dst) {
	perror( name );
	exit(1);
    }

    for( vector v = 0; v < base.size; v++ )
	    if ( W.table[v] == 0  &&  ( v < (v^r) ) && (clK[ base.table[v] ] + clK[ base.table[v ^ r] ] ) <= limite ) {
		    numbrowse(1, v, ldg );
		    W.table[v] = 2;
		    count++;
		    boole h = vectortoboole( v, &base );
		    for( int x = 0; x < ffsize; x++ )
			    F[x] = ( f[x]<< 1 ) + h[x]; 
		    pmap( dst, F );
		    free( h );
	    }
    fclose( dst );
    printf("\ncount=%d", count ); 
    printf("\n");
    return 0;
}
