#include "chip8.h"

Chip8::Chip8() {
  memory.fill(0);
  pixels.fill(0);
  registers.fill(0);
  keyboard.fill(0);
  stack.fill(0);
  opcode = 0;
  ir = 0;
  pc = 0x200;
  delay_timer = 0;
  sound_timer = 0;
  sp = 0;
  rom_loaded = false;
  // init fonts
  for (int i = 0; i < 80; ++i)
    memory[i] = CHIP8_FONTS[i];
}

Chip8::~Chip8() {}

bool Chip8::load_rom(const char *filename) {
  std::ifstream ifs;
  ifs.open(filename, std::ifstream::binary);
  if (ifs.is_open()) {
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(ifs), {});
    for (int i = 0; i < buffer.size() && i < memory.size(); i++) {
      memory[i + 0x200] = buffer[i];
    }
    ifs.close();
    rom_loaded = true;
    return true;
  }
  return false;
}

void log_unsupported_opcode(const short opcode) {
  // printf("Opcode 0x%X is not supported.\n", opcode);
}

bool Chip8::pix(size_t idx) {
  if (idx < pixels.size()) {
    return pixels[idx];
  }
  return false;
}

std::string Chip8::get_asm(uint16_t op) {
  std::stringstream s;
  unsigned short nnn = op & 0x0FFF;
  unsigned short nn = op & 0x00FF;
  unsigned short n = op & 0x000F;
  unsigned short x = (op & 0x0F00) >> 8;
  unsigned short y = (op & 0x00F0) >> 4;
  switch (op & 0xF000) {
  case 0x0000: {
    switch (op) {
    case 0x00E0:
      // Clear pixels in chip
      s << "CLS";
      break;
    case 0x00EE:
      s << "RET";
      break;
    default:
      log_unsupported_opcode(opcode);
    }
    break;
  }
  case 0x1000: {
    s << "JP " << std::hex << nnn;
    break;
  }
  case 0x2000: {
    s << "CALL " << std::hex << nnn;
    break;
  }
  case 0x3000: {
    s << "SE "
      << "V" << std::hex << x << " " << std::hex << nn;
    break;
  }
  case 0x4000: {
    s << "SNE "
      << "V" << std::hex << x << " " << std::hex << nn;
    break;
  }
  case 0x5000: {
    s << "SE "
      << "V" << std::hex << x << " V" << std::hex << y;
    break;
  }
  case 0x6000: {
    s << "LD "
      << "V" << std::hex << x << " " << std::hex << nn;
    break;
  }
  case 0x7000: {
    s << "ADD "
      << "V" << std::hex << x << " " << std::hex << nn;
    break;
  }
  case 0x8000: {
    switch (n) {
    case 0:
      s << "LD "
        << "V" << std::hex << x << " V" << std::hex << y;
      break;
    case 1:
      s << "OR "
        << "V" << std::hex << x << " V" << std::hex << y;
      break;
    case 2:
      s << "AND "
        << "V" << std::hex << x << " V" << std::hex << y;
      break;
    case 3:
      s << "XOR "
        << "V" << std::hex << x << " V" << std::hex << y;
      break;
    case 4:
      s << "ADD "
        << "V" << std::hex << x << " V" << std::hex << y;
      break;
    case 5:
      s << "SUB "
        << "V" << std::hex << x << " V" << std::hex << y;
      break;
    case 6:
      s << "SHR "
        << "V" << std::hex << x << " {, V" << std::hex << y << "}";
      break;
    case 7:
      s << "SUBN "
        << "V" << std::hex << x << " V" << std::hex << y;
      break;
    case 0xE:
      s << "SHR "
        << "V" << std::hex << x << " {, V" << std::hex << y << "}";
      break;
    default:
      log_unsupported_opcode(opcode);
    }
    break;
  }
  case 0x9000: {
    s << "SNE "
      << "V" << std::hex << x << " V" << std::hex << y;
    break;
  }
  case 0xA000: {
    s << "LD "
      << "I " << std::hex << nnn;
    break;
  }
  case 0xB000: {
    s << "JP "
      << "V0 " << std::hex << nnn;
    break;
  }
  case 0xC000: {
    s << "RND "
      << "V" << std::hex << x << " " << std::hex << nn;
    break;
  }
  case 0xD000: {
    s << "DRW "
      << "V" << std::hex << x << " V" << std::hex << y << " " << std::hex << n;
    break;
  }
  case 0xE000: {
    switch (nn) {
    case 0x9E:
      s << "SKP "
        << "V" << std::hex << x;
      break;
    case 0xA1:
      s << "SKNP "
        << "V" << std::hex << x;
      break;
    default:
      log_unsupported_opcode(opcode);
    }
    break;
  }
  case 0xF000: {
    switch (nn) {
    case 0x07:
      s << "LD "
        << "V" << std::hex << x << " " << std::hex << delay_timer;
      break;
    case 0x0A:
      s << "LD "
        << "V" << std::hex << x << " K";
      break;
    case 0x15:
      s << "LD "
        << "DT "
        << "V" << std::hex << x;
      break;
    case 0x18:
      s << "LD "
        << "ST "
        << "V" << std::hex << x;
      break;
    case 0x1E:
      s << "ADD "
        << "I "
        << "V" << std::hex << x;
      break;
    case 0x29:
      s << "LD "
        << "F "
        << "V" << std::hex << x;
      break;
    case 0x33:
      s << "LD "
        << "B "
        << "V" << std::hex << x;
      break;
    case 0x55:
      s << "LD "
        << "[I] "
        << "V" << std::hex << x;
      break;
    case 0x65:
      s << "LD "
        << "V" << std::hex << x << " [I]";
      break;
    default:
      log_unsupported_opcode(opcode);
    }
  }
  }
  return s.str();
}

uint8_t Chip8::V(size_t reg) { return registers[reg]; }

uint8_t Chip8::mem(size_t addr) { return memory[addr]; }

uint16_t Chip8::OP() { return opcode; }

uint16_t Chip8::IR() { return ir; }
uint16_t Chip8::PC() { return pc; }
uint16_t Chip8::SP() { return sp; }
uint8_t Chip8::DT() { return delay_timer; }
uint8_t Chip8::ST() { return sound_timer; }

void Chip8::step() {
  if (rom_loaded) {
    opcode = memory[pc] << 8 | memory[pc + 1];
    // Parse opcode here
    // For more infomation, see https://www.wikiwand.com/en/CHIP-8
    unsigned short nnn = opcode & 0x0FFF;
    unsigned short nn = opcode & 0x00FF;
    unsigned short n = opcode & 0x000F;
    unsigned short x = (opcode & 0x0F00) >> 8;
    unsigned short y = (opcode & 0x00F0) >> 4;
    switch (opcode & 0xF000) {
    case 0x0000: {
      switch (opcode) {
      case 0x00E0:
        // Clear pixels in chip
        pixels.fill(0);
        pc += 2;
        break;
      case 0x00EE:
        --sp;
        pc = stack[sp];
        pc += 2;
        break;
      default:
        log_unsupported_opcode(opcode);
      }
      break;
    }
    case 0x1000: {
      pc = nnn;
      break;
    }
    case 0x2000: {
      stack[sp] = pc;
      ++sp;
      pc = nnn;
      break;
    }
    case 0x3000: {
      if (registers[x] == nn)
        pc += 2;
      pc += 2;
      break;
    }
    case 0x4000: {
      if (registers[x] != nn)
        pc += 2;
      pc += 2;
      break;
    }
    case 0x5000: {
      if (registers[x] == registers[y])
        pc += 2;
      pc += 2;
      break;
    }
    case 0x6000: {
      registers[x] = nn;
      pc += 2;
      break;
    }
    case 0x7000: {
      registers[x] += nn;
      pc += 2;
      break;
    }
    case 0x8000: {
      switch (n) {
      case 0:
        registers[x] = registers[y];
        pc += 2;
        break;
      case 1:
        registers[x] |= registers[y];
        pc += 2;
        break;
      case 2:
        registers[x] &= registers[y];
        pc += 2;
        break;
      case 3:
        registers[x] ^= registers[y];
        pc += 2;
        break;
      case 4:
        if (0xFF - registers[x] >= registers[y])
          registers[0xF] = 0; // No carry
        else
          registers[0xF] = 1;
        registers[x] += registers[y];
        pc += 2;
        break;
      case 5:
        if (registers[x] >= registers[y])
          registers[0xF] = 1; // No borrow
        else
          registers[0xF] = 0; // Borrow here
        registers[x] -= registers[y];
        pc += 2;
        break;
      case 6:
        registers[0xF] = registers[x] & 0x1;
        registers[x] >>= 1;
        pc += 2;
        break;
      case 7:
        if (registers[y] >= registers[x])
          registers[0xF] = 1; // No borrow
        else
          registers[0xF] = 0;
        registers[x] = registers[y] - registers[x];
        pc += 2;
        break;
      case 0xE:
        registers[0xF] = registers[x] >> 7;
        registers[x] <<= 1;
        pc += 2;
        break;
      default:
        log_unsupported_opcode(opcode);
      }
      break;
    }
    case 0x9000: {
      if (registers[x] != registers[y])
        pc += 2;
      pc += 2;
      break;
    }
    case 0xA000: {
      ir = nnn;
      pc += 2;
      break;
    }
    case 0xB000: {
      pc = registers[0] + nnn;
      break;
    }
    case 0xC000: {
      unsigned short r = rand() % 0xFF;
      registers[x] = r & nn;
      pc += 2;
      break;
    }
    case 0xD000: {
      unsigned char pix;
      x = registers[x];
      y = registers[y];
      registers[0xF] = 0;
      for (int h = 0; h < n; h++) {
        pix = memory[ir + h]; // 8 bit width
        size_t idx = (y + h) * 64 + x;
        for (int pos = 0; pos < 8; pos++) {
          // Set p to 1 if not 0
          unsigned char p = (pix & (0x80 >> pos)) != 0;
          if (pixels[idx + pos] && (pixels[idx + pos] ^ p) == 0)
            registers[0xF] = 1;

          // Flip from set to unset
          // Use XOR to set pix
          // For more infomation see
          // http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#Dxyn

          pixels[idx + pos] ^= p;
        }
      }
      // Draw in another timer
      pc += 2;
      break;
    }
    case 0xE000: {
      unsigned short key_index;
      unsigned char key;
      switch (nn) {
      case 0x9E:
        key_index = registers[x];
        key = keyboard[key_index];
        if (key != 0)
          pc += 2;
        pc += 2;
        break;
      case 0xA1:
        key_index = registers[x];
        key = keyboard[key_index];
        if (key == 0)
          pc += 2;
        pc += 2;
        break;
      default:
        log_unsupported_opcode(opcode);
      }
      break;
    }
    case 0xF000: {
      unsigned short pressed;
      unsigned char bcd;
      switch (nn) {
      case 0x07:
        registers[x] = delay_timer;
        pc += 2;
        break;
      case 0x0A:
        pressed = 0;
        for (int i = 0; i < 16; ++i) {
          if (keyboard[i]) {
            pressed = 1;
            registers[x] = i;
          }
        }
        if (pressed == 0)
          return; // Return and will be called again in game loop
        pc += 2;
        break;
      case 0x15:
        delay_timer = registers[x];
        pc += 2;
        break;
      case 0x18:
        sound_timer = registers[x];
        pc += 2;
        break;
      case 0x1E:
        if (ir + registers[x] > 0xFFF)
          registers[0xF] = 1;
        else
          registers[0xF] = 0;
        ir += registers[x];
        pc += 2;
        break;
      case 0x29:
        ir = registers[x] * 5; // Fonts loaded from 0x00 to 0xF * 5
        pc += 2;
        break;
      case 0x33:
        bcd = registers[x];
        memory[ir] = bcd / 100;
        memory[ir + 1] = (bcd - bcd / 100) / 10;
        memory[ir + 2] = bcd % 10;
        pc += 2;
        break;
      case 0x55:
        for (int i = 0; i <= x; ++i) {
          memory[ir + i] = registers[i];
        }
        pc += 2;
        break;
      case 0x65:
        for (int i = 0; i <= x; ++i) {
          registers[i] = memory[ir + i];
        }
        pc += 2;
        break;
      default:
        log_unsupported_opcode(opcode);
      }
    }
    }

    // Update timers
    if (delay_timer > 0)
      --delay_timer;

    if (sound_timer > 0)
      --sound_timer;
  }
}
