#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rand.h"
#include "t/tinytest.h"
#include "t/tinyhelp.h"

static void
test_constr(void)
{
   struct rand *z;

   fprintf_test_info(stdout, "test_constr", "rand_new, rand_free");
   z = rand_new();
   ASSERT("Constructor test", z);
   rand_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_uniform(void)
{
   struct rand *z = rand_new();
   unsigned    i, n = 100000;
   unsigned    count = 0;

   fprintf_test_info(stdout, "test_uniform", "rand_new, rand_free");
   for (i = 0; i < n; i++)
      if (rand_uniform(z) < 0.5)
         count += 1;
   ASSERT("", count < 0.6 * n);
   ASSERT("", count > 0.4 * n);

   rand_free(&z);
   ASSERT_EQUALS(NULL, z);
}

static void
test_normal_1(void)
{
   struct rand *z;
   unsigned    i, n = 1000000;
   unsigned    count1 = 0;
   unsigned    count2 = 0;
   unsigned    count3 = 0;
   unsigned    count4 = 0;
   unsigned    count5 = 0;
   unsigned    count6 = 0;
   unsigned    count7 = 0;
   unsigned    count8 = 0;
   double      cut1 = -1.150349380376008178297e-00;
   double      cut2 = -0.6744897501960817432022e-00;
   double      cut3 = -0.318639363964375163022e-00;
   double      cut4 = 0.0e-00;
   double      cut5 = -cut3;
   double      cut6 = -cut2;
   double      cut7 = -cut1;
   double      x;

   fprintf_test_info(stderr, "test_normal_1", "rand_normal");

   z = rand_new();

   for (i = 0; i < n; i++) {
      x = rand_normal(z);
      if (x < cut1)
         count1 += 1;
      else if (x < cut2)
         count2 += 1;
      else if (x < cut3)
         count3 += 1;
      else if (x < cut4)
         count4 += 1;
      else if (x < cut5)
         count5 += 1;
      else if (x < cut6)
         count6 += 1;
      else if (x < cut7)
         count7 += 1;
      else
         count8 += 1;
   }

   ASSERT(NULL, count1 < 0.126 * n);
   ASSERT(NULL, count1 > 0.124 * n);
   ASSERT(NULL, count2 < 0.126 * n);
   ASSERT(NULL, count2 > 0.124 * n);
   ASSERT(NULL, count3 < 0.126 * n);
   ASSERT(NULL, count3 > 0.124 * n);
   ASSERT(NULL, count4 < 0.126 * n);
   ASSERT(NULL, count4 > 0.124 * n);
   ASSERT(NULL, count5 < 0.126 * n);
   ASSERT(NULL, count5 > 0.124 * n);
   ASSERT(NULL, count6 < 0.126 * n);
   ASSERT(NULL, count6 > 0.124 * n);
   ASSERT(NULL, count7 < 0.126 * n);
   ASSERT(NULL, count7 > 0.124 * n);
   ASSERT(NULL, count8 < 0.126 * n);
   ASSERT(NULL, count8 > 0.124 * n);
   rand_free(&z);
   ASSERT_EQUALS(NULL,z);
}

#if 0                                            /* 11 yy */
static void
test_stub(void)
{
   struct rand *z;

   fprintf_test_info(stdout, "test_stub", NULL);
   z = rand_new();
   ASSERT("Constructor test", z);
   rand_free(&z);
   ASSERT_EQUALS(NULL,z);
}
#endif


int
main(void)
{
   printf("%s\n", rand_version());

   RUN(test_constr);
   RUN(test_uniform);
   RUN(test_normal_1);
   return TEST_REPORT();
}
