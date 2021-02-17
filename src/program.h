struct PROGRAM_LINE {
  int offset;
  struct OPCODE * opcode;
  char args[3];
};

struct PROGRAM {
  struct PROGRAM_LINE * program;
  int lines;
};

extern struct PROGRAM_LINE program_line;
extern struct PROGRAM program;
