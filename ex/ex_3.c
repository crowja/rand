#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <limits.h>
#include "rand.h"

int
main(int argc, char *argv[])
{
   unsigned    i, n = 3000;
   double      x;
   double      sum0 = 0, sum1 = 0, sum2 = 0;
   double      xmin = DBL_MAX;
   double      xmax = -DBL_MAX;
   unsigned    count_q1 = 0, count_q2 = 0, count_q3 = 0, count_q4 = 0;
   double      cut1 = -0.674489750196082e-00;
   double      cut2 = 0.0;
   double      cut3 = -cut1;

   struct rand *rng = rand_new();

   for (i = 0; i < n; i++) {
      x = rand_normal(rng);
      sum0 += 1;
      sum1 += x;
      sum2 += x * x;
      xmin = x < xmin ? x : xmin;
      xmax = x > xmax ? x : xmax;
      if (x < cut1)
         count_q1 += 1;
      else if (x < cut2)
         count_q2 += 1;
      else if (x < cut3)
         count_q3 += 1;
      else
         count_q4 += 1;
   }

   printf("MIN    : %f\n", xmin);
   printf("MAX    : %f\n", xmax);
   printf("MOM1   : %f\n", sum1 / sum0);
   printf("MOM2   : %f\n", sum2 / sum0);
   printf("IN Q1  : %f\n", count_q1 / (double) n);
   printf("IN Q2  : %f\n", count_q2 / (double) n);
   printf("IN Q3  : %f\n", count_q3 / (double) n);
   printf("IN Q4  : %f\n", count_q4 / (double) n);

   rand_free(rng);

   return 0;
}
