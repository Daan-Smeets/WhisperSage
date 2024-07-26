/*
 * Copyright 2023 Carlo Sanna, Javier Verbel, and Floyd Zweydinger.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef PARAMS_H
#define PARAMS_H

#include "config.h"

/* Mode * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if MIRITH_MODE == 0 /* Ia, fast. */

#define PAR_Q 16
#define PAR_M 15
#define PAR_N 15
#define PAR_K 78
#define PAR_R 6
#define PAR_S 5
#define TAU 39
#define N_PARTIES 16
#define SEED_SIZE 16
#define HASH_SIZE 32
#define TREE_HEIGHT 4
#define TREE_N_NODES 31
#define CRYPTO_PUBLICKEYBYTES 129
#define CRYPTO_SECRETKEYBYTES 145
#define CRYPTO_BYTES 7877

#elif MIRITH_MODE == 1 /* Ia, short. */

#define PAR_Q 16
#define PAR_M 15
#define PAR_N 15
#define PAR_K 78
#define PAR_R 6
#define PAR_S 9
#define TAU 19
#define N_PARTIES 256
#define SEED_SIZE 16
#define HASH_SIZE 32
#define TREE_HEIGHT 8
#define TREE_N_NODES 511
#define CRYPTO_PUBLICKEYBYTES 129
#define CRYPTO_SECRETKEYBYTES 145
#define CRYPTO_BYTES 5673

#elif MIRITH_MODE == 2 /* Ib, fast. */

#define PAR_Q 16
#define PAR_M 16
#define PAR_N 16
#define PAR_K 142
#define PAR_R 4
#define PAR_S 5
#define TAU 39
#define N_PARTIES 16
#define SEED_SIZE 16
#define HASH_SIZE 32
#define TREE_HEIGHT 4
#define TREE_N_NODES 31
#define CRYPTO_PUBLICKEYBYTES 144
#define CRYPTO_SECRETKEYBYTES 160
#define CRYPTO_BYTES 9105

#elif MIRITH_MODE == 3 /* Ib, short. */

#define PAR_Q 16
#define PAR_M 16
#define PAR_N 16
#define PAR_K 142
#define PAR_R 4
#define PAR_S 9
#define TAU 19
#define N_PARTIES 256
#define SEED_SIZE 16
#define HASH_SIZE 32
#define TREE_HEIGHT 8
#define TREE_N_NODES 511
#define CRYPTO_PUBLICKEYBYTES 144
#define CRYPTO_SECRETKEYBYTES 160
#define CRYPTO_BYTES 6309

#elif MIRITH_MODE == 4 /* IIIa, fast. */

#define PAR_Q 16
#define PAR_M 19
#define PAR_N 19
#define PAR_K 109
#define PAR_R 8
#define PAR_S 7
#define TAU 55
#define N_PARTIES 16
#define SEED_SIZE 24
#define HASH_SIZE 48
#define TREE_HEIGHT 4
#define TREE_N_NODES 31
#define CRYPTO_PUBLICKEYBYTES 205
#define CRYPTO_SECRETKEYBYTES 229
#define CRYPTO_BYTES 17139

#elif MIRITH_MODE == 5 /* IIIa, short. */

#define PAR_Q 16
#define PAR_M 19
#define PAR_N 19
#define PAR_K 109
#define PAR_R 8
#define PAR_S 9
#define TAU 29
#define N_PARTIES 256
#define SEED_SIZE 24
#define HASH_SIZE 48
#define TREE_HEIGHT 8
#define TREE_N_NODES 511
#define CRYPTO_PUBLICKEYBYTES 205
#define CRYPTO_SECRETKEYBYTES 229
#define CRYPTO_BYTES 12440

#elif MIRITH_MODE == 6 /* IIIb, fast. */

#define PAR_Q 16
#define PAR_M 19
#define PAR_N 19
#define PAR_K 167
#define PAR_R 6
#define PAR_S 7
#define TAU 55
#define N_PARTIES 16
#define SEED_SIZE 24
#define HASH_SIZE 48
#define TREE_HEIGHT 4
#define TREE_N_NODES 31
#define CRYPTO_PUBLICKEYBYTES 205
#define CRYPTO_SECRETKEYBYTES 229
#define CRYPTO_BYTES 18459

#elif MIRITH_MODE == 7 /* IIIb, short. */

#define PAR_Q 16
#define PAR_M 19
#define PAR_N 19
#define PAR_K 167
#define PAR_R 6
#define PAR_S 9
#define TAU 29
#define N_PARTIES 256
#define SEED_SIZE 24
#define HASH_SIZE 48
#define TREE_HEIGHT 8
#define TREE_N_NODES 511
#define CRYPTO_PUBLICKEYBYTES 205
#define CRYPTO_SECRETKEYBYTES 229
#define CRYPTO_BYTES 13136

#elif MIRITH_MODE == 8 /* Va, fast. */

#define PAR_Q 16
#define PAR_M 21
#define PAR_N 21
#define PAR_K 189
#define PAR_R 7
#define PAR_S 7
#define TAU 74
#define N_PARTIES 16
#define SEED_SIZE 32
#define HASH_SIZE 64
#define TREE_HEIGHT 4
#define TREE_N_NODES 31
#define CRYPTO_PUBLICKEYBYTES 253
#define CRYPTO_SECRETKEYBYTES 285
#define CRYPTO_BYTES 30458

#elif MIRITH_MODE == 9 /* Va, short. */

#define PAR_Q 16
#define PAR_M 21
#define PAR_N 21
#define PAR_K 189
#define PAR_R 7
#define PAR_S 10
#define TAU 38
#define N_PARTIES 256
#define SEED_SIZE 32
#define HASH_SIZE 64
#define TREE_HEIGHT 8
#define TREE_N_NODES 511
#define CRYPTO_PUBLICKEYBYTES 253
#define CRYPTO_SECRETKEYBYTES 285
#define CRYPTO_BYTES 21795

#elif MIRITH_MODE == 10 /* Vb, fast. */

#define PAR_Q 16
#define PAR_M 22
#define PAR_N 22
#define PAR_K 254
#define PAR_R 6
#define PAR_S 7
#define TAU 74
#define N_PARTIES 16
#define SEED_SIZE 32
#define HASH_SIZE 64
#define TREE_HEIGHT 4
#define TREE_N_NODES 31
#define CRYPTO_PUBLICKEYBYTES 274
#define CRYPTO_SECRETKEYBYTES 306
#define CRYPTO_BYTES 33048

#elif MIRITH_MODE == 11 /* Vb, short. */

#define PAR_Q 16
#define PAR_M 22
#define PAR_N 22
#define PAR_K 254
#define PAR_R 6
#define PAR_S 10
#define TAU 38
#define N_PARTIES 256
#define SEED_SIZE 32
#define HASH_SIZE 64
#define TREE_HEIGHT 8
#define TREE_N_NODES 511
#define CRYPTO_PUBLICKEYBYTES 274
#define CRYPTO_SECRETKEYBYTES 306
#define CRYPTO_BYTES 23182

#else

#error "MIRITH_MODE not implemented!"

#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif
