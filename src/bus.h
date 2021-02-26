struct BUS {
    unsigned char input;
    unsigned char display[1024];
    unsigned char memory[64 * 1024];
};

struct BUS initializeBus();
void writeBus(unsigned int addr, unsigned char data, struct BUS * bus);
char readBus(unsigned int addr, struct BUS * bus);
