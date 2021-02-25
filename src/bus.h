struct BUS {
    char input;
    char display[1023];
    char memory[64 * 1024];
};

struct BUS initialize();
void write(int addr, char data, struct BUS * bus);
char read(int addr, struct BUS * bus);
