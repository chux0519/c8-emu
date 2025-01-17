#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>

static uint8_t CHIP8_FONTS[80] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

class Chip8 {
public:
  Chip8();
  ~Chip8();
  bool load_rom(const char *filename);
  bool pix(size_t idx);
  std::string get_asm(uint16_t op);
  uint8_t V(size_t reg);
  uint8_t mem(size_t addr);

  uint16_t OP();

  uint16_t IR();
  uint16_t PC();
  uint16_t SP();
  uint8_t DT();
  uint8_t ST();

  void step();

  std::array<uint8_t, 4096> memory;
  std::array<uint8_t, 64 * 32> pixels;
  std::array<uint8_t, 16> registers;
  std::array<uint8_t, 16> keyboard;
  std::array<uint16_t, 16> stack;
  uint16_t opcode;
  uint16_t ir;
  uint16_t pc;
  uint8_t delay_timer;
  uint8_t sound_timer;
  uint16_t sp;
  bool rom_loaded;
};

#endif // CHIP8_H
