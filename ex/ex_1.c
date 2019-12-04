#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <limits.h>
#include "rand.h"

int
main(int argc, char *argv[])
{
   unsigned    i, n = 30;
   double      x;
   double      sum0 = 0, sum1 = 0, sum2 = 0;
   double      xmin = DBL_MAX;
   double      xmax = -DBL_MAX;
   struct rand *rng = rand_new();

   for (i = 0; i < n; i++) {
      x = rand_uniform(rng);
      sum0 += 1;
      sum1 += x;
      sum2 += x * x;
      xmin = x < xmin ? x : xmin;
      xmax = x > xmax ? x : xmax;
      printf("%f\n", x);
   }

   printf("MIN  : %f\n", xmin);
   printf("MAX  : %f\n", xmax);
   printf("MOM1 : %f\n", sum1 / sum0);
   printf("MOM2 : %f\n", sum2 / sum0);
   rand_free(rng);

   return 0;
}
