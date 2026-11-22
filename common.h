#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "boolean.h"
#include "orbitools.h"

extern double   clK[ 49 ];
extern vector   rep[ 49 ];
extern boole    fct[ 49] ;
extern int64_t  stabsize[ 49 ];
extern int64_t  orbsize[ 49 ];
extern aglGroup grp[ 49];

int intcmp(const void *p1, const void *p2);
double kappa( boole f );

int trivial( int b, int q );

void initclass( basis_t base );
#endif
