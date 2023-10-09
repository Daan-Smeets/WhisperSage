#ifndef API_H
#define API_H

#include <stdint.h>
#include <params.h>

#define CRYPTO_SECRETKEYBYTES  KYBER_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES  KYBER_PUBLICKEYBYTES
#define CRYPTO_CIPHERTEXTBYTES KYBER_CIPHERTEXTBYTES
#define CRYPTO_BYTES           KYBER_SSBYTES

#define CRYPTO_ALGNAME "Kyber768"

#define pqcrystals_kyber768_SECRETKEYBYTES 2400
#define pqcrystals_kyber768_PUBLICKEYBYTES 1184
#define pqcrystals_kyber768_CIPHERTEXTBYTES 1088
#define pqcrystals_kyber768_BYTES 32

#define pqcrystals_kyber768_ref_SECRETKEYBYTES pqcrystals_kyber768_SECRETKEYBYTES
#define pqcrystals_kyber768_ref_PUBLICKEYBYTES pqcrystals_kyber768_PUBLICKEYBYTES
#define pqcrystals_kyber768_ref_CIPHERTEXTBYTES pqcrystals_kyber768_CIPHERTEXTBYTES
#define pqcrystals_kyber768_ref_BYTES pqcrystals_kyber768_BYTES

int pqcrystals_kyber768_ref_keypair(uint8_t *pk, uint8_t *sk);
int pqcrystals_kyber768_ref_enc(uint8_t *ct, uint8_t *ss, const uint8_t *pk);
int pqcrystals_kyber768_ref_dec(uint8_t *ss, const uint8_t *ct, const uint8_t *sk);

#endif
