# 6502 Emulator

## Usage

### Build

```bash
make build
```

### Run Tests
This will build and run unity tests

```bash
make test
```

### Run Binary

```bash
./build/bin/main_app
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

## License
This is free and unencumbered software released into the public domain
For more information, please refer to <http://unlicense.org/>
