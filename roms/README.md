# ROMS

All roms are from the internet.

## Test ROM

`./BC_test.ch8` is the ROM for testing your chip8 implementation.

### how to use

See https://slack-files.com/T3CH37TNX-F3RKEUKL4-b05ab4930d for detail

In short,

If you don't see `BON` in the screen, check the error code and relative opcode bellow.

E 01: 3XNN verify that the jump condition is fair

E 02: 5XY0 verify that the jump condition is fair

E 03: 4XNN verify that the jump condition is fair

E 04: 7XNN check the result of the addition

E 05: 8XY5 verify that VF is set to 0 when there is a borrow

E 06: 8XY5 verify that VF is set to 1 when there is no borrow

E 07: 8XY7 verify that VF is set to 0 when there is a borrow

E 08: 8XY7 verify that VF is set to 1 when there is no borrow

E 09: 8XY1 check the result of the OR operation

E 10: 8XY2 check the result of AND operation

E 11: 8XY3 check the result of the XOR operation

E 12: 8XYE verify that VF is set to the MSB (most significant bit or most left) before the shift and  VF does not take value 0 every time

E 13: 8XYE verify that VF is set to the MSB (most significant bit or most left) before the shift and  VF does not take value 1 every time 

E 14: 8XY6 verify that VF is set to the LSB (least significant bit or most right ) before the shift and  VF does not take value 0 every time

E 15: 8XY6 verify that VF is the LSB (least significant bit or most right) before the shift and  VF does not take value 1 every time 

E 16: FX55 and FX65 verify that these two opcodes are implemented. The error may come from one or the other or both are defects.

E 17: FX33 calculating the binary representation is mistaken or the result is poorly stored into memory or poorly poped (FX65 or FX1E)
