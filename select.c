
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

FILE *src = fopen( "../boole/data/class-2-5.txt" , "r" );
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
	if ( kappa( f ) <= limite  ){
		num++;
		if ( ! target || target == num ) {
			int cls = base.table[ booleVector( f, &base ) ];
			printf("\n\nnumero=%d cls=%d item=%d size=%ld", num, cls, item, size);
			printf("\nkappa=%.2f", kappa(f) );
			panf(stdout, f);
			paglGroup(stdout, g);
			printf("\nstabSize=%ld", size);
			printf("\norbSize=%ld", aglsize / size);
			//doit( f );
			}
	}
        free( f );
	aglfreeGroup( g );
	item++;
    }
    printf("\nclass = %d with kappa <= %.4f  (trivial=%d)\n", num, limite, trivial(2,ffsize)  );
    fclose(src);
    return 0;
}
