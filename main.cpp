#include <fstream>
#include "memory.h"
#include "cpu6502.h"

int main()
{
    // Read ROM contents from binary file.
    std::ifstream stream("rom.bin", std::ios::in | std::ios::binary);
    std::vector<uint8_t> initial((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    Memory mem(initial);
    Cpu6502 cpu6502(mem);

    for (int i=0; i<1000; ++i)
    {
        cpu6502.show();
        cpu6502.singleStep();
    }
    cpu6502.show();
} // main




