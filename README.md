# 6502 Emulator

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

## Installing Dependencies

#### Arch Linux
```bash
pacman -Sy clang cmake sdl2
```

#### Ubuntu
```bash
sudo add-apt-repository -y "deb http://archive.ubuntu.com/ubuntu `lsb_release -sc` main universe restricted multiverse"
sudo apt-get update -y -qq
sudo apt-get install clang cmake libsdl2-dev
```

## Implemented OPCODES
- [ ] ADC
- [ ] AND
- [ ] ASL
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
- [ ] CLC
- [ ] CLD
- [ ] CLI
- [ ] CLV
- [ ] CMP
- [ ] CPX
- [x] CPY
- [ ] DEC
- [ ] DEX
- [ ] DEY
- [ ] EOR
- [ ] INC
- [x] INX
- [x] INY
- [ ] JMP
- [ ] JSR
- [x] LDA
- [x] LDX
- [x] LDY
- [ ] LSR
- [x] NOP
- [ ] ORA
- [x] PHA
- [ ] PHP
- [ ] PLA
- [ ] PLP
- [ ] ROL
- [ ] ROR
- [ ] RTI
- [ ] RTS
- [ ] SBC
- [ ] SEC
- [ ] SED
- [ ] SEI
- [x] STA
- [x] STX
- [x] STY
- [ ] TAX
- [ ] TAY
- [ ] TSX
- [x] TXA
- [x] TXS
- [x] TYA

## License
This is free and unencumbered software released into the public domain
For more information, please refer to <http://unlicense.org/>
