#include "memory.h"
#include "cpu.h"

int main()
{
    std::vector<uint8_t> initial = {
        0xA9, 0x0A,          // LDA #$0A
        0x8D, 0xFF, 0x00,    // STA $00FF
        0xA9, 0x00,          // LDA #$00
        0x8D, 0xFE, 0x00,    // STA $00FE
        0xAD, 0xFE, 0x00,    // LDA $00FE   <--+
        0x18,                // CLC            |
        0x6D, 0xFF, 0x00,    // ADC $00FF      |
        0x8D, 0xFE, 0x00,    // STA $00FE      |
        0xAD, 0xFF, 0x00,    // LDA $00FF      |
        0x38,                // SEC            |
        0xE9, 0x01,          // SBC #$01       |
        0x8D, 0xFF, 0x00,    // STA $00FF      |
        0xD0, 0xEB,          // BNE -----------+
        0xAD, 0xFE, 0x00,    // LDA $00FE
        0x4C, 0x22, 0x00,    // JMP $0022   <---        
    };
    initial.resize(65536, 0);

    Memory mem(initial);
    Cpu cpu(mem);

    for (int i=0; i<500; ++i)
    {
        cpu.show();
        cpu.singleStep();
    }
    cpu.show();
} // main

