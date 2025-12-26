#pragma once
#include <stdint.h>

// LED matrix status frames (12x8 matrix)
const uint32_t HAPPY_STATUS[] = {0x3fc48a95, 0x58019fd9, 0x5889871};

const uint32_t NORMAL_STATUS[] = {0x3fc40298, 0xd98d8019, 0x5889871};

const uint32_t SAD_STATUS[] = {0x3fc48a9d, 0xd8898018, 0x71889905};
