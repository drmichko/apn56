
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

int nbgenerator( aglGroup g )
{
        int r = 0;
        while ( g ) {
                r++;
                g = g->next;
        }
        return r;
}


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
	    puts("Orbit  ?");
	    return 0;
    }
    int nbclass = 0, min = 1024, max = 0;
    for( vector v = 0; v < base.size; v++ ){
	    int cls = base.table[v];
	    if ( orbsize[ cls ] == 0 ) {
		    rep[ cls ] = v;
		    fct[ cls ] = vectortoboole( v, &base );
		    clK[ cls ] = kappa(  fct[ cls ]  );
		    if ( cls < min ) min = cls;
		    if ( cls > max ) max = cls;
		    nbclass++;
	    }
	    orbsize[ cls ]++;
    }
    printf("\n#class number : %d ", nbclass );
    printf("\n#class range : %d %d", min, max);
    aglGroup AGL = mkaglGroup( );
    for( int cls = 1; cls < 49; cls++ ){
	    stabsize[ cls ] = aglcard( 5 ) / orbsize[ cls ]; 
	    grp[ cls ]      = plainStabilizer( rep[ cls ] , AGL, &base,  stabsize[cls] );
	    grp[cls] = aglReduce( grp[cls], 1024  );
	    for( int i = 0; i < 24; i++ )
		    if ( nbgenerator(  grp[cls] ) > 2 )
		    	grp[cls] = aglReduce( grp[cls], 1024  );

	    printf("\n#cls : %d  rep=%ld", cls, rep[ cls] );
	    panf( stdout, fct[ cls ] );
	    paglGroup(  stdout, grp[ cls ]   );
	    printf("\norbSize=%ld",  orbsize[cls]  );
	    printf("\nstabSize=%ld",  stabsize[cls]  );

    	}

    double limite =  (double) trivial(2, ffsize )  / ( 2*ffsize -1 );
    int nbs = 0;
    for( int cls = 1; cls < 49; cls++ )
	    if ( clK[ cls] <= limite ) nbs++;
    printf("\n#class = %d with kappa <= %.4f  (trivial=%d)\n", nbs,  limite, trivial(2,ffsize)  );
    return 0;
}
