#include <stdint.h>

#define PD1_PIN	1
#define PD0_PIN 0

void pd1_init();
void pd0_init();
void pd0_low();
void pd0_high();
uint8_t read_pd0();
void pd0_high_strong();