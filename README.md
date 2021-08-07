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

## Simulator

This emulator is based on [Easy6502](http://skilldrick.github.io/easy6502/), all ASM examples in easy6502 website should run fine in our implementation.

### Compiling ASM

You need to install [C65](https://cc65.github.io/) in your machine, create a file with the ASM you want to compile and run the following command:
```bash
cl65 -t none test-program.asm
```
This will compile and link a binary with your code, to run this in your emulator you need to:
```bash
./build/release/bin/6502 <path-to-your-bin>/test-program fps-as-int
```
You can find some precomiled examples in the `resource` folder.

## State

### Implemented OPCODES
- [x] ADC
- [x] AND
- [x] ASL
- [x] BCC
- [x] BCS
- [x] BEQ
- [x] BIT
- [x] BMI
- [x] BNE
- [x] BPL
- [x] BRK
- [x] BVC
- [x] BVS
- [x] CLC
- [x] CLD
- [x] CLI
- [x] CLV
- [x] CMP
- [x] CPX
- [x] CPY
- [x] DEC
- [x] DEX
- [x] DEY
- [x] EOR
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
- [x] ORA
- [x] PHA
- [x] PHP
- [x] PLA
- [x] PLP
- [x] ROL
- [x] ROR
- [x] RTI
- [x] RTS
- [x] SBC
- [x] SEC
- [x] SED
- [x] SEI
- [x] STA
- [x] STX
- [x] STY
- [x] TAX
- [x] TAY
- [x] TSX
- [x] TXA
- [x] TXS
- [x] TYA

## License
This is free and unencumbered software released into the public domain
For more information, please refer to <http://unlicense.org/>
