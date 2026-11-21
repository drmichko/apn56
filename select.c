
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


FILE *src = fopen( "../boole/data/class-2-5.txt" , "r" );
    if (!src) {
	perror("");
	exit(1);
    }
    size_t aglsize = aglCardinality(ffdimen);
    num = 0;
    boole f;

    double limite = trivial( 2, ffsize );
    limite /= 2 * ffsize  - 1 ;

    while ((f = loadaglboolesize(src, &g, &size))) {
	if ( kappa( f ) <= limite  ){
		num++;
		if ( ! target || target == num ) {
			printf("\n\nnumero=%d", num);
			printf("\nkappa=%.2f", kappa(f) );
			panf(stdout, f);
			paglGroup(stdout, g);
			printf("\nstabSize=%ld", size);
			printf("\norbSize=%ld", aglsize / size);
			//doit( f );
			}
	}
        free( f );
    }
    printf("\nclass = %d with kappa <= %.4f  (trivial=%d)\n", num, limite, trivial(2,ffsize)  );
    fclose(src);
    return 0;
}
