#ifndef CAPTURE_PINS_H
#define CAPTURE_PINS_H
#define CAPTURE_CRYSTALS

#include <libopencm3/cm3/common.h> // Require to make the <libopencm3/stm32/gpio.h> function in the capture_settings.c
#include <stdbool.h>

extern bool cf_random;
extern bool cf_pseudo;
extern bool cf_uc; // Unpack ciphertext
extern bool cf_uk; // Unpack sk
extern bool cf_pn; // Poly ntt
extern bool cf_pb; // Poly basemul
extern bool cf_pi; // Poly invntt
extern bool cf_ps; // Poly sub
extern bool cf_pr; // Poly reduce
extern bool cf_pt; // Poly tomsg
extern bool cf_test; // Poly test


void capture_pins_set(void);
void capture_pins_clear(void);

#endif
