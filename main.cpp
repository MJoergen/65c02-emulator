#include <fstream>
#include "memory.h"
#include "cpu65c02.h"

int main()
{
    // Read ROM contents from binary file.
    std::ifstream stream("rom.bin", std::ios::in | std::ios::binary);
    std::vector<uint8_t> initial((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    // Initialize memory and CPU
    Memory mem(initial);
    Cpu65C02 cpu65c02(mem);

    // Go into an infinite loop.
    // The program will terminate, when a JMP or B?? instruction jumps to itself.
    while (true)
    {
        cpu65c02.show();
        cpu65c02.singleStep();
    }
} // main

