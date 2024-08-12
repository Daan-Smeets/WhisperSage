#include "api.h"
#include "randombytes.h"
#include "hal.h"
#include "capture_settings.h"
#include <libopencm3/stm32/gpio.h>

#include <sendfn.h>
#include <stdint.h>
#include <unistd.h>

#include <string.h>

#include <stdio.h>

#include <string.h>

#define NTESTS 10

#define PRINT_FUNCTION_BODY(func) hal_send_str(#func)

#define NTESTS 10

// https://stackoverflow.com/a/1489985/1711232
#define PASTER(x, y) x##y
#define EVALUATOR(x, y) PASTER(x, y)
#define NAMESPACE(fun) EVALUATOR(MUPQ_NAMESPACE, fun)

// use different names so we can have empty namespaces
#define MUPQ_CRYPTO_BYTES           NAMESPACE(CRYPTO_BYTES)
#define MUPQ_CRYPTO_PUBLICKEYBYTES  NAMESPACE(CRYPTO_PUBLICKEYBYTES)
#define MUPQ_CRYPTO_SECRETKEYBYTES  NAMESPACE(CRYPTO_SECRETKEYBYTES)
#define MUPQ_CRYPTO_CIPHERTEXTBYTES NAMESPACE(CRYPTO_CIPHERTEXTBYTES)
#define MUPQ_CRYPTO_ALGNAME NAMESPACE(CRYPTO_ALGNAME)

#define MUPQ_crypto_kem_keypair NAMESPACE(crypto_kem_keypair)
#define MUPQ_crypto_kem_enc NAMESPACE(crypto_kem_enc)
#define MUPQ_crypto_kem_dec NAMESPACE(crypto_kem_dec)

const uint8_t canary[8] = {
  0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF
};

/* allocate a bit more for all keys and messages and
 * make sure it is not touched by the implementations.
 */
static void write_canary(uint8_t *d) {
  for (size_t i = 0; i < 8; i++) {
    d[i] = canary[i];
  }
}

static int check_canary(const uint8_t *d) {
  for (size_t i = 0; i < 8; i++) {
    if (d[i] != canary[i]) {
      return -1;
    }
  }
  return 0;
}

static int test_keys(void)
{
  unsigned char key_a[MUPQ_CRYPTO_BYTES+16], key_b[MUPQ_CRYPTO_BYTES+16];
  unsigned char pk[MUPQ_CRYPTO_PUBLICKEYBYTES+16];
  unsigned char sendb[MUPQ_CRYPTO_CIPHERTEXTBYTES+16];
  unsigned char sk_a[MUPQ_CRYPTO_SECRETKEYBYTES+16];

  write_canary(key_a); write_canary(key_a+sizeof(key_a)-8);
  write_canary(key_b); write_canary(key_b+sizeof(key_b)-8);
  write_canary(pk); write_canary(pk+sizeof(pk)-8);
  write_canary(sendb); write_canary(sendb+sizeof(sendb)-8);
  write_canary(sk_a); write_canary(sk_a+sizeof(sk_a)-8);


  int i;

  // for(i=0; i<NTESTS; i++)
  // {
    //Alice generates a public key
    MUPQ_crypto_kem_keypair(pk+8, sk_a+8);
    hal_send_str("DONE key pair generation!");

    //Bob derives a secret key and creates a response
    MUPQ_crypto_kem_enc(sendb+8, key_b+8, pk+8);
    hal_send_str("DONE encapsulation!");

    //Alice uses Bobs response to get her secret key
    MUPQ_crypto_kem_dec(key_a+8, sendb+8, sk_a+8);
    hal_send_str("DONE decapsulation!");

    if(memcmp(key_a+8, key_b+8, MUPQ_CRYPTO_BYTES))
    {
      hal_send_str("ERROR KEYS\n");
    }
    else if(check_canary(key_a) || check_canary(key_a+sizeof(key_a)-8) ||
            check_canary(key_b) || check_canary(key_b+sizeof(key_b)-8) ||
            check_canary(pk) || check_canary(pk+sizeof(pk)-8) ||
            check_canary(sendb) || check_canary(sendb+sizeof(sendb)-8) ||
            check_canary(sk_a) || check_canary(sk_a+sizeof(sk_a)-8))
    {
      hal_send_str("ERROR canary overwritten\n");
    }
    else
    {
      hal_send_str("OK KEYS\n");
    }
  // }

  return 0;
}


static int test_invalid_sk_a(void)
{
  unsigned char sk_a[MUPQ_CRYPTO_SECRETKEYBYTES];
  unsigned char key_a[MUPQ_CRYPTO_BYTES], key_b[MUPQ_CRYPTO_BYTES];
  unsigned char pk[MUPQ_CRYPTO_PUBLICKEYBYTES];
  unsigned char sendb[MUPQ_CRYPTO_CIPHERTEXTBYTES];
  int i;

  // for(i=0; i<NTESTS; i++)
  // {
    //Alice generates a public key
    MUPQ_crypto_kem_keypair(pk, sk_a);

    //Bob derives a secret key and creates a response
    MUPQ_crypto_kem_enc(sendb, key_b, pk);

    //Replace secret key with random values
    randombytes(sk_a, MUPQ_CRYPTO_SECRETKEYBYTES);

    //Alice uses Bobs response to get her secre key
    MUPQ_crypto_kem_dec(key_a, sendb, sk_a);

    if(!memcmp(key_a, key_b, MUPQ_CRYPTO_BYTES))
    {
      hal_send_str("ERROR invalid sk_a\n");
    }
    else
    {
      hal_send_str("OK invalid sk_a\n");
    }
  // }

  return 0;
}


static int test_invalid_ciphertext(void)
{
  unsigned char sk_a[MUPQ_CRYPTO_SECRETKEYBYTES];
  unsigned char key_a[MUPQ_CRYPTO_BYTES], key_b[MUPQ_CRYPTO_BYTES];
  unsigned char pk[MUPQ_CRYPTO_PUBLICKEYBYTES];
  unsigned char sendb[MUPQ_CRYPTO_CIPHERTEXTBYTES];
  int i;
  size_t pos;

  // for(i=0; i<NTESTS; i++)
  // {
    randombytes((unsigned char *)&pos, sizeof(size_t));

    //Alice generates a public key
    MUPQ_crypto_kem_keypair(pk, sk_a);

    //Bob derives a secret key and creates a response
    MUPQ_crypto_kem_enc(sendb, key_b, pk);

    // Change ciphertext to random value
    randombytes(sendb, sizeof(sendb));

    //Alice uses Bobs response to get her secret key
    MUPQ_crypto_kem_dec(key_a, sendb, sk_a);

    if(!memcmp(key_a, key_b, MUPQ_CRYPTO_BYTES))
    {
      hal_send_str("ERROR invalid ciphertext\n");
    }
    else
    {
      hal_send_str("OK invalid ciphertext\n");
    // }
  }
  return 0;
}

int main(void)
{
  hal_setup(CLOCK_FAST);

  // Init all the vars for the operation
  unsigned char sk_a[MUPQ_CRYPTO_SECRETKEYBYTES];
  unsigned char key_a[MUPQ_CRYPTO_BYTES], key_b[MUPQ_CRYPTO_BYTES];
  unsigned char pk[MUPQ_CRYPTO_PUBLICKEYBYTES];
  unsigned char ct[MUPQ_CRYPTO_CIPHERTEXTBYTES];

  // Receive a byte from Python
  unsigned char init_byte;
  unsigned char flag_byte;
  unsigned char run_nr_byte;
  unsigned char received_byte;
  unsigned char response_byte;

  // Alternative end conditions for the while loops
  uint8_t nr_flags = 0;
  uint8_t nr_digits = 0;

  uint8_t total_no_runs = 0;
  uint8_t max_no_traces = 0;

  size_t pos;

  randombytes((unsigned char *)&pos, sizeof(size_t));

  //Alice generates a public key, has to always be done
  MUPQ_crypto_kem_keypair(pk, sk_a);

  //Bob derives a secret key and creates a response
  MUPQ_crypto_kem_enc(ct, key_b, pk);

  hal_send_str("#");

  /*
  Communication Steps:
  1. Send the init byte 'b'
  2. Send the flags in the form of 'f' + '[byte]'
  3. Send the number of runs of this capture
  4. Send the "go" byte 'g' to start the trace
  */

  // Get an initial starting byte
  // recv_USART_bytes(&init_byte, 1);
  // if(init_byte != 'b')
  // {
  //   hal_send_str("Abort at Init");
  //   abort();
  // }

  flag_byte = 'f';

  while (flag_byte != 'm' && nr_flags < 10)
  {
    nr_flags = 0;

    // For each flag byte, run the whole program once
    while (total_no_runs < 100 && flag_byte == 'f')
    {
      //FLAG_SWITCH_CASE
      // The program uses 'd', 'e', 'f', and 'g' 
      recv_USART_bytes(&flag_byte, 1);
      switch (flag_byte)
      {
        case 'w':
          cf_random = true;
          break;
        case 'p':
          cf_pseudo = true;
          break;
        case 'c':
          cf_uc = true;
          break;
        case 'k':
          cf_uk = true;
          break;
        case 'n':
          cf_pn = true;
          break;
        case 'l':
          cf_pb = true;
          break;
        case 'i':
          cf_pi = true;
          break;
        case 's':
          cf_ps = true;
          break;
        case 'u':
          cf_test = true;
          break;
        default:
          break;
      }
      recv_USART_bytes(&flag_byte, 1);
      ++nr_flags; // Failsafe
    }

    received_byte = flag_byte;
    
    if (cf_uc)
    {
      MUPQ_crypto_kem_enc(ct, key_b, pk);
    }

    while (received_byte != 'e')
    {

      MUPQ_crypto_kem_enc(ct, key_b, pk);
      if (received_byte == 'g') //go
      {
        if (cf_random)
        {
          MUPQ_crypto_kem_keypair(pk, sk_a);
        }
        response_byte = 'd'; //done
        MUPQ_crypto_kem_dec(key_a, ct, sk_a);

        send_USART_bytes(&response_byte, 1);
        recv_USART_bytes(&received_byte, 1);
      }
      else
      {
        hal_send_str("Abort at Tracing");
        abort();
      }
    }
    cf_random = false;
    cf_pseudo = false;
    cf_uc = false; // Unpack ciphertext
    cf_uk = false; // Unpack sk
    cf_pn = false; // Poly ntt
    cf_pb = false; // Poly basemul
    cf_pi = false; // Poly invntt
    cf_ps = false; // Poly sub
    cf_pr = false; // Poly reduce
    cf_pt = false; // Poly tomsg
    cf_test = false; // Poly test
    flag_byte = 'f';
  }

  return 0;
}