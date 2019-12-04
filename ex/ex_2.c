#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <limits.h>
#include "rand.h"

int
main(int argc, char *argv[])
{
   unsigned i, n = 30000;
   unsigned long x;
   unsigned long xmin = ULONG_MAX;
   unsigned long xmax = -ULONG_MAX;
   struct rand *rng = rand_new();

   for (i = 0; i < n; i++) {
      x = rand_ulong(rng);
      xmin = x < xmin ? x : xmin;
      xmax = x > xmax ? x : xmax;
      /* printf("%lu\n", x); */
   }

   printf("MIN  : %lu\n", xmin);
   printf("MAX  : %lu\n", xmax);
   rand_free(rng);

   return 0;
}
