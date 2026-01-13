#include <stdbool.h>
#include <stdint.h>

#define ROM_LENGTH_BYTES        8
#define SCRATCHPAD_LENGTH_BYTES 9
#define READ_ROM_CMD            0x33
#define MATCH_ROM_CMD           0x55
#define CONVERT_T_CMD           0x44
#define READ_SCRATCHPAD_CMD     0xBE
#define SEARCH_ROM_CMD          0xF0

void idle();
bool reset();
void getROM(uint8_t *rom);
int getTemp(float *temp, uint8_t rom[]);
int search(uint8_t *address);