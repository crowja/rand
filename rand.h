/**
 *  @file rand.h
 *  @version 0.2.0-dev0
 *  @date Wed Dec  4 09:32:46 CST 2019
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef _RAND_H_
#define _RAND_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "rand"

struct rand;

/**
 *  @brief Create and return a new rand object.
 *  @details FIXME longer description here ...
 */

struct rand *rand_new(void);

/**
 *  @brief Clean up and free a rand structure.
 *  @details FIXME longer description here ...
 */

void        rand_free(struct rand **pp);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */

const char *rand_version(void);

/**
 *  @brief Initialize a rand object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a rand object
 *  @param x FIXME
 */

void        rand_init(struct rand *p, unsigned long w, unsigned long x, unsigned long y,
                      unsigned long z);
void        rand_initr(struct rand *p);
unsigned long rand_ulong(struct rand *p);
double      rand_normal(struct rand *p);
double      rand_uniform(struct rand *p);


#endif
