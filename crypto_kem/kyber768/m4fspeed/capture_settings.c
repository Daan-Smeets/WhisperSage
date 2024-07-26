#include <libopencm3/stm32/gpio.h>
#include <stdbool.h>
#include "capture_settings.h"

// List of all the capture flags
bool cf_uc = false; // Unpack ciphertext
bool cf_uk = false; // Unpack sk
bool cf_pn = false; // Poly ntt
bool cf_pb = false; // Poly basemul
bool cf_pi = false; // Poly invntt
bool cf_ps = false; // Poly sub
bool cf_pr = false; // Poly reduce
bool cf_pt = false; // Poly tomsg
bool cf_test = false; // Poly test

// Function to set the capture pins
void capture_pins_set()
{
  #if defined(STM32F407VG)
    gpio_set(GPIOA, GPIO7);
  #elif defined(STM32F303RCT7)
    gpio_set(GPIOA, GPIO12);
  #endif
  // Other implementations
}

// Function to clear the capture pins
void capture_pins_clear()
{
  #if defined(STM32F407VG)
    gpio_clear(GPIOA, GPIO7);
  #elif defined(STM32F303RCT7)
    gpio_clear(GPIOA, GPIO12);
  #endif
  // Other implementations

}