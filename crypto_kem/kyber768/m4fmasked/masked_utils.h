/* Copyright 2022 UCLouvain, Belgium and PQM4 contributors
 *
 * This file is part of pqm4_masked.
 *
 * pqm4_masked is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, version 3.
 *
 * pqm4_masked is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * pqm4_masked. If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MASKED_UTILS_H
#define MASKED_UTILS_H
#include "masked.h"
#include "poly.h"
#include <libopencm3/stm32/rng.h>
#include <libopencm3/stm32/common/rng_common_v1.h>
#include <stdint.h>
#include "randombytes.h"

#if BENCH_RND == 1
extern uint64_t rng_cnt;
#endif

// inline uint32_t get_random() {
// #if BENCH_RND == 1
//   rng_cnt += 1;
// #endif
//   while (1) {
//     if ((RNG_SR & RNG_SR_DRDY) == 1) { // check if data is ready
//       return RNG_DR;
//     }
//   }
//   return 0;
// }

inline uint32_t get_random()
{
    uint8_t random_vals[4];
    randombytes(random_vals, 4);

    uint32_t random_val_32 = 0;
    for(int j = 0; j < 4; j++)
        random_val_32 |= (random_vals[j] << (8*j));

    return random_val_32;
}

inline uint32_t rand32() { return get_random(); }

inline void rand_q(int16_t v[2]) {
  uint32_t r;
  do {
    r = rand32();
  } while (r > (387U * KYBER_Q * KYBER_Q));
  r = r % (KYBER_Q * KYBER_Q);
  v[0] = r % (KYBER_Q);
  v[1] = r / KYBER_Q;
}

void masked_poly(StrAPoly mp, const poly *p);
void unmasked_poly(poly *p, const StrAPoly mp);
#endif
