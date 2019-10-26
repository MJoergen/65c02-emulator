#include <fstream>
#include "memory.h"
#include "cpu6502.h"

int main()
{
    // Read ROM contents from binary file.
    std::ifstream stream("rom.bin", std::ios::in | std::ios::binary);
    std::vector<uint8_t> initial((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    // Initialize memory and CPU
    Memory mem(initial);
    Cpu6502 cpu6502(mem);

    // Go into an infinite loop.
    // The program will terminate, when a JMP or B?? instruction jumps to itself.
    while (true)
    {
        cpu6502.show();
        cpu6502.singleStep();
    }
} // main

