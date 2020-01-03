/**
 *  @file rand.c
 *  @version 0.1.0-dev0
 *  @date Wed Dec  4 09:32:46 CST 2019
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <limits.h>
#include <math.h>
#include <time.h>
#include "rand.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#ifdef  _MAX2
#undef  _MAX2
#endif
#define _MAX2(a, b)   ((a) > (b) ? (a) : (b))

#ifdef  _MIN2
#undef  _MIN2
#endif
#define _MIN2(a, b)   ((a) < (b) ? (a) : (b))

#ifdef  _WARM
#undef  _WARM
#endif
#define _WARM         100

#ifndef M_PI
#define M_PI          3.14159265358979323846
#endif

#ifdef  _SQRT2PI
#undef  _SQRT2PI
#endif
#define _SQRT2PI      sqrt(2 * M_PI)

struct rand {
   unsigned long w;
   unsigned long x;
   unsigned long y;
   unsigned long z;
};

/* Fundamental generator is from Marsaglia's xor128 family */

static unsigned long
_xor128(struct rand *p)
{
   unsigned    a = 11, b = 8, c = 19;
   /**
    *  In addition to:
    *     unsigned a = 11, b = 8, c = 19;
    *  other options from Marsaglia's paper ("Xorshift RNGs," Journal
    *  of Statistical Software 8 (2003), bottom of p. 4) are:
    *     unsigned a = 5, b = 14, c = 1;
    *     unsigned a = 15, b = 4, c = 21;
    *     unsigned a = 23, b = 24, c = 3;
    *     unsigned a = 5, b = 12, c = 29;
    */
   unsigned long t;
   t = (p->x ^ (p->x << a));
   p->x = p->y;
   p->y = p->z;
   p->z = p->w;
   p->w = (p->w ^ (p->w >> c)) ^ (t ^ (t >> b));
   return p->w;
}

static const double _normal_xi = 2.2160358671e-00;

/* Helper for rand_normal() */
static double
_normal_psi(double t)
{
   return exp(-0.5 * t * t) / _SQRT2PI;
}

/* Helper for rand_normal() */
static double
_normal_f(double t)
{
   return _normal_psi(t) - 0.180025191068563e-00 * _MAX2(_normal_xi - fabs(t), 0);
}

struct rand *
rand_new(void)
{
   struct rand *tp;
   unsigned    i;

   tp = (struct rand *) malloc(sizeof(struct rand));
   if (_IS_NULL(tp))
      return NULL;

   tp->w = 88675123;
   tp->x = 123456789;
   tp->y = 362436069;
   tp->z = 521288629;

   for (i = 0; i < _WARM; i++)
      rand_ulong(tp);

   return tp;
}

void
rand_free(struct rand **pp)
{
   _FREE(*pp);
   *pp = NULL;
}

const char *
rand_version(void)
{
   return "0.1.0-dev0";
}

void
rand_init(struct rand *p, unsigned long w, unsigned long x, unsigned long y,
          unsigned long z)
{
   p->w = w;
   p->x = x;
   p->y = y;
   p->z = z;
}

void
rand_initr(struct rand *p)
{
   unsigned    i;
   p->w = (unsigned long) time(NULL);
   p->x = 1;
   p->y = 1;
   p->z = 1;

   for (i = 0; i < _WARM; i++)
      rand_ulong(p);
}

double
rand_normal(struct rand *p)
{
   /**
    *  Implementation of the Kinderman-Ramage normal pseudorandom variate
    *  generator with corrections made by Tirler, Dalgaard, Hormann, and
    *  Leydold in "An error in the Kinderman-Ramage method and how to fix
    *  it," Computational Statistics & Data Analysis 47 (2004), issue 3, 
    *  pp 433-440.
    */

   double      t, u, v, w, z;

   u = rand_uniform(p);

   if (u < 0.884070402298758e-00) {              /* step 1 */
      v = rand_uniform(p);
      return _normal_xi * (1.131131635444180 * u + v - 1);
   }

   else if (u < 0.911312780288703e-00) {         /* step 8 */
      for (;;) {
         v = rand_uniform(p);
         w = rand_uniform(p);
         z = v - w;
         t = 0.479727404222441e-00 - 0.595507138015940e-00 * _MIN2(v, w);
         if (t < 0)
            continue;
         if (_MAX2(v, w) < 0.805577924423817e-00)
            break;
         if (0.53377549506886e-01 * fabs(z) <= _normal_f(t))
            break;
      }

      return z < 0 ? t : -t;
   }

   else if (u < 0.958720824790463e-00) {         /* step 7 */
      for (;;) {
         v = rand_uniform(p);
         w = rand_uniform(p);
         z = v - w;
         t = 0.479727404222441e-00 + 1.105473661022070e-00 * _MIN2(v, w);
         if (_MAX2(v, w) <= 0.872834976671790e-00)
            break;
         if (0.049264496373128e-00 * fabs(z) <= _normal_f(t))
            break;
      }

      return z < 0 ? t : -t;
   }

   else if (u < 0.973310954173898e-00) {         /* step 5 */
      for (;;) {
         v = rand_uniform(p);
         w = rand_uniform(p);
         z = v - w;
         t = _normal_xi - 0.630834801921960e-00 * _MIN2(v, w);
         if (_MAX2(v, w) <= 0.755591531667601e-00)
            break;
         if (0.034240503750111e-00 * fabs(z) <= _normal_f(t))
            break;
      }

      return z < 0 ? t : -t;
   }

   else {                                        /* step 3 */
      do {
         v = rand_uniform(p);
         w = rand_uniform(p);
         t = _normal_xi * _normal_xi / 2 - log(w);
      } while (v * v * t > _normal_xi * _normal_xi / 2);

      return u < 0.986655477086949e-00 ? sqrt(2 * t) : -sqrt(2 * t);
   }
}

unsigned long
rand_ulong(struct rand *p)
{
   return _xor128(p);
}

double
rand_uniform(struct rand *p)
{
   return rand_ulong(p) / (double) ULONG_MAX;
}

#undef _IS_NULL
#undef _FREE
#undef _MAX2
#undef _MIN2
