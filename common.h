#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "boolean.h"
#include "orbitools.h"

int intcmp(const void *p1, const void *p2);
double kappa( boole f );

int trivial( int b, int q );
#endif
