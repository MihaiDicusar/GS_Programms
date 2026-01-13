#include <stdint.h>

#define DS18B20 0x28
#define DS18S20 0x10
#define START_Y_POS         1
#define START_X_POS_FAMCODE 1
#define START_X_POS_ROM     10
#define START_X_POS_TEMP    30

void displayFamCode(uint8_t *rom, uint16_t y);
void displayROM(uint8_t *rom, uint16_t y);
void displayTemp(float temp, uint16_t y);