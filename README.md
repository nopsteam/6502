# 6502 Emulator ![CI](https://github.com/nopsteam/6502/workflows/CI/badge.svg) [![codecov](https://codecov.io/gh/nopsteam/6502/branch/main/graph/badge.svg?token=KTJA51IVNC)](https://codecov.io/gh/nopsteam/6502)

### What's a 6502?

It was the CPU of choice for the very first mass market home computers and so, played a central role in the home computer revolution.  
It was the brain of the first computers from Apple, Commodore, Acorn, and Atari.  It ran the Atari 2600 game console, and its core was incorporated into the central processor of Nintendo's NES.

## Compiling / Building

### Installing Dependencies

#### Arch Linux
```bash
yay -Sy clang cmake lcov glfw libx11 libxcursor libxinerama libxrandr vulkan-headers xorg-server-devel xorg-xinput
```

#### Ubuntu
```bash
sudo apt-get install clang cmake lcov libasound2-dev mesa-common-dev libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

## Usage

### Setup
This will build cmake files and download dependencies
```bash
make setup
```

### Build
```bash
# Debug build
make debug
# Release build
make release
```

### Run Tests
This will build and run unity tests
```bash
make test
```

#### Code Coverage Checks
This will build and run unity tests and generate reports for coverage (depends on lcov)
```bash
make coverage
# This part is optional: Generates a html with more coverage details
genhtml build/coverage/coverage.info --output-directory build/coverage/out
```

### Clean
This will delete generated files for debug and release
```bash
make clean
```

### Run Binary
```bash
# Debug bin
./build/debug/bin/6502
./build/debug/bin/6502_disasm
# Release bin
./build/release/bin/6502
./build/release/bin/6502_disasm
```

## Todo

### Implemented OPCODES
- [ ] ADC
- [ ] AND
- [x] ASL
- [x] BCC
- [x] BCS
- [x] BEQ
- [x] BIT
- [x] BMI
- [x] BNE
- [x] BPL
- [ ] BRK
- [x] BVC
- [x] BVS
- [x] CLC
- [x] CLD
- [x] CLI
- [x] CLV
- [ ] CMP
- [x] CPX
- [x] CPY
- [x] DEC
- [x] DEX
- [x] DEY
- [ ] EOR
- [x] INC
- [x] INX
- [x] INY
- [x] JMP
- [x] JSR
- [x] LDA
- [x] LDX
- [x] LDY
- [x] LSR
- [x] NOP
- [ ] ORA
- [x] PHA
- [ ] PHP
- [ ] PLA
- [ ] PLP
- [x] ROL
- [x] ROR
- [x] RTI
- [x] RTS
- [ ] SBC
- [x] SEC
- [x] SED
- [x] SEI
- [x] STA
- [x] STX
- [x] STY
- [x] TAX
- [x] TAY
- [ ] TSX
- [x] TXA
- [x] TXS
- [x] TYA

## License
This is free and unencumbered software released into the public domain
For more information, please refer to <http://unlicense.org/>
