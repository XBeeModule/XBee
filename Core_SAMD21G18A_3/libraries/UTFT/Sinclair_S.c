// Sinclair_S.c
// Font type    : Full (95 characters)
// Font size    : 8x8 pixels
// Memory usage : 764 bytes

#if defined(__AVR__)
	#include <avr/pgmspace.h>
	#define fontdatatype const uint8_t
#elif defined(__PIC32MX__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#elif defined(__arm__)
	#define PROGMEM
	#define fontdatatype const unsigned char
#endif

fontdatatype Sinclair_S[764] PROGMEM={
0x08,0x08,0x20,0x5F,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // <space>
0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x00,  // !
0x14,0x14,0x00,0x00,0x00,0x00,0x00,0x00,  // "
0x00,0x24,0x7E,0x24,0x24,0x7E,0x24,0x00,  // #
0x10,0x7C,0x50,0x7C,0x14,0x7C,0x10,0x00,  // $
0x00,0x62,0x64,0x08,0x10,0x26,0x46,0x00,  // %
0x00,0x10,0x28,0x10,0x2A,0x44,0x3A,0x00,  // &
0x00,0x08,0x10,0x00,0x00,0x00,0x00,0x00,  // '
0x00,0x08,0x10,0x10,0x10,0x10,0x08,0x00,  // (
0x00,0x10,0x08,0x08,0x08,0x08,0x10,0x00,  // )
0x00,0x00,0x28,0x10,0x7C,0x10,0x28,0x00,  // *
0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x00,  // +
0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x10,  // ,
0x00,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,  // -
0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,  // .
0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x00,  // /

0x00,0x78,0x8C,0x94,0xA4,0xC4,0x78,0x00,  // 0
0x00,0x60,0xA0,0x20,0x20,0x20,0xF8,0x00,  // 1
0x00,0x78,0x84,0x04,0x78,0x80,0xFC,0x00,  // 2
0x00,0x78,0x84,0x18,0x04,0x84,0x78,0x00,  // 3
0x00,0x10,0x30,0x50,0x90,0xFC,0x10,0x00,  // 4
0x00,0xFC,0x80,0xF8,0x04,0x84,0x78,0x00,  // 5
0x00,0x78,0x80,0xF8,0x84,0x84,0x78,0x00,  // 6
0x00,0xFC,0x04,0x08,0x10,0x20,0x20,0x00,  // 7
0x00,0x78,0x84,0x78,0x84,0x84,0x78,0x00,  // 8
0x00,0x78,0x84,0x84,0x7C,0x04,0x78,0x00,  // 9
0x00,0x00,0x00,0x10,0x00,0x00,0x10,0x00,  // :
0x00,0x00,0x10,0x00,0x00,0x10,0x10,0x20,  // ;
0x00,0x00,0x08,0x10,0x20,0x10,0x08,0x00,  // <
0x00,0x00,0x00,0x7C,0x00,0x7C,0x00,0x00,  // =
0x00,0x00,0x20,0x10,0x08,0x10,0x20,0x00,  // >
0x00,0x3C,0x42,0x04,0x08,0x00,0x08,0x00,  // ?

0x00,0x3C,0x4A,0x56,0x5E,0x40,0x3C,0x00,  // @
0x00,0x78,0x84,0x84,0xFC,0x84,0x84,0x00,  // A
0x00,0xF8,0x84,0xF8,0x84,0x84,0xF8,0x00,  // B
0x00,0x78,0x84,0x80,0x80,0x84,0x78,0x00,  // C
0x00,0xF0,0x88,0x84,0x84,0x88,0xF0,0x00,  // D
0x00,0xFC,0x80,0xF8,0x80,0x80,0xFC,0x00,  // E
0x00,0xFC,0x80,0xF8,0x80,0x80,0x80,0x00,  // F
0x00,0x78,0x84,0x80,0x9C,0x84,0x78,0x00,  // G
0x00,0x84,0x84,0xFC,0x84,0x84,0x84,0x00,  // H
0x00,0x7C,0x10,0x10,0x10,0x10,0x7C,0x00,  // I
0x00,0x04,0x04,0x04,0x84,0x84,0x78,0x00,  // J
0x00,0x88,0x90,0xE0,0x90,0x88,0x84,0x00,  // K
0x00,0x80,0x80,0x80,0x80,0x80,0xFC,0x00,  // L
0x00,0x84,0xCC,0xB4,0x84,0x84,0x84,0x00,  // M
0x00,0x84,0xC4,0xA4,0x94,0x8C,0x84,0x00,  // N
0x00,0x78,0x84,0x84,0x84,0x84,0x78,0x00,  // O

0x00,0xF8,0x84,0x84,0xF8,0x80,0x80,0x00,  // P
0x00,0x78,0x84,0x84,0xA4,0x94,0x78,0x00,  // Q
0x00,0xF8,0x84,0x84,0xF8,0x88,0x84,0x00,  // R
0x00,0x78,0x80,0x78,0x04,0x84,0x78,0x00,  // S
0x00,0xFE,0x10,0x10,0x10,0x10,0x10,0x00,  // T
0x00,0x84,0x84,0x84,0x84,0x84,0x78,0x00,  // U
0x00,0x84,0x84,0x84,0x84,0x48,0x30,0x00,  // V
0x00,0x84,0x84,0x84,0x84,0xB4,0x48,0x00,  // W
0x00,0x84,0x48,0x30,0x30,0x48,0x84,0x00,  // X
0x00,0x82,0x44,0x28,0x10,0x10,0x10,0x00,  // Y
0x00,0xFC,0x08,0x10,0x20,0x40,0xFC,0x00,  // Z
0x00,0x38,0x20,0x20,0x20,0x20,0x38,0x00,  // [
0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x00,  // <backslash>
0x00,0x38,0x08,0x08,0x08,0x08,0x38,0x00,  // ]
0x00,0x10,0x38,0x54,0x10,0x10,0x10,0x00,  // ^
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,  // _

0x3C,0x42,0x99,0xA1,0xA1,0x99,0x42,0x3C,  // `
0x00,0x00,0x38,0x04,0x3C,0x44,0x3C,0x00,  // a
0x00,0x40,0x40,0x78,0x44,0x44,0x78,0x00,  // b
0x00,0x00,0x1C,0x20,0x20,0x20,0x1C,0x00,  // c
0x00,0x04,0x04,0x3C,0x44,0x44,0x3C,0x00,  // d
0x00,0x00,0x38,0x44,0x78,0x40,0x3C,0x00,  // e
0x00,0x0C,0x10,0x18,0x10,0x10,0x10,0x00,  // f
0x00,0x00,0x3E,0x42,0x42,0x3E,0x02,0x3C,  // g
0x00,0x40,0x40,0x78,0x44,0x44,0x44,0x00,  // h
0x00,0x08,0x00,0x18,0x08,0x08,0x1C,0x00,  // i
0x00,0x04,0x00,0x04,0x04,0x04,0x24,0x18,  // j
0x00,0x40,0x50,0x60,0x60,0x50,0x48,0x00,  // k
0x00,0x10,0x10,0x10,0x10,0x10,0x0C,0x00,  // l
0x00,0x00,0x68,0x54,0x54,0x54,0x54,0x00,  // m
0x00,0x00,0x78,0x44,0x44,0x44,0x44,0x00,  // n
0x00,0x00,0x38,0x44,0x44,0x44,0x38,0x00,  // o

0x00,0x00,0x78,0x44,0x44,0x78,0x40,0x40,  // p
0x00,0x00,0x3C,0x44,0x44,0x3C,0x04,0x06,  // q
0x00,0x00,0x1C,0x20,0x20,0x20,0x20,0x00,  // r
0x00,0x00,0x38,0x40,0x38,0x04,0x78,0x00,  // s
0x00,0x10,0x38,0x10,0x10,0x10,0x0C,0x00,  // t
0x00,0x00,0x44,0x44,0x44,0x44,0x38,0x00,  // u
0x00,0x00,0x44,0x44,0x28,0x28,0x10,0x00,  // v
0x00,0x00,0x44,0x54,0x54,0x54,0x28,0x00,  // w
0x00,0x00,0x44,0x28,0x10,0x28,0x44,0x00,  // x
0x00,0x00,0x44,0x44,0x44,0x3C,0x04,0x38,  // y
0x00,0x00,0x7C,0x08,0x10,0x20,0x7C,0x00,  // z
0x00,0x1C,0x10,0x60,0x10,0x10,0x1C,0x00,  // {
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x00,  // |
0x00,0x70,0x10,0x0C,0x10,0x10,0x70,0x00,  // }
0x00,0x66,0x69,0x08,0x08,0x09,0x06,0x00,  // CELSIUS
};
