#include <stm32f4xx.h>

typedef struct {
    uint16_t width;
    uint16_t height;
    unsigned short const *data_table;
} font_type;
