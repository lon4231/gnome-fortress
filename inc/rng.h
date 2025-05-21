#ifndef _FAST_RANDOM_GEN_
#define _FAST_RANDOM_GEN_

#include "headers.h"

static uint64_t rng_state;

inline uint8_t fast_rng()
{
    rng_state *= 0xda942042e4dd58b5;
    return rng_state >> 32;
}

#endif