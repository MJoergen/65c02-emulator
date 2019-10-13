#pragma once

#include "memory.h"

// The Flags register is implemented as a bitfield.
typedef struct {
    uint8_t sign:1;       // S
    uint8_t overflow:1;   // V
    uint8_t reserved:1;   // R
    uint8_t brk:1;        // B
    uint8_t decimal:1;    // D
    uint8_t intmask:1;    // I
    uint8_t zero:1;       // Z
    uint8_t carry:1;      // C
} t_flags;        

class Cpu6502
{
    public:
        Cpu6502(Memory& memory) : m_memory(memory) {reset();}

        void reset();       // Resets the Program Counter.
        void singleStep();  // Executes a single instruction.
        void show() const;  // Dump the current state of the CPU.

    private:
        Memory&  m_memory;  // Reference to the external memory.

        uint16_t m_pc;
        uint8_t  m_areg;
        uint8_t  m_xreg;
        uint8_t  m_yreg;
        t_flags  m_flags;
}; // end of class Cpu6502
