#include <iostream>
#include <iomanip>
#include "cpu.h"

void Cpu::reset()
{
    m_pc = (m_memory.read(0xFFFD) << 8) | m_memory.read(0xFFFC);
    std::cout << "Resetting CPU. PC=" << std::hex << std::setw(4) << m_pc;
    std::cout << std::dec << std::endl;
} // reset

static uint8_t alu(uint8_t opcode, uint8_t arg1, uint8_t arg2, t_flags& flags)
{
    uint16_t tmp16;
    uint8_t  tmp8 = arg1;

    switch (opcode)
    {
        case 0 : // ORA
            tmp8 = arg1 | arg2;
            flags.sign = (tmp8 >> 7);
            flags.zero = (tmp8 == 0);
            break;
        case 1 : // AND
            tmp8 = arg1 & arg2;
            flags.sign = (tmp8 >> 7);
            flags.zero = (tmp8 == 0);
            break;
        case 2 : // EOR
            tmp8 = arg1 ^ arg2;
            flags.sign = (tmp8 >> 7);
            flags.zero = (tmp8 == 0);
            break;
        case 3 : // ADC
            tmp16 = arg1 + arg2 + flags.carry;
            // Set S, Z, C, and V
            flags.carry    = (tmp16 >> 8);
            flags.overflow = ~((arg1 >> 7) ^ (arg2 >> 7)) & ((arg1 >> 7) ^ ((tmp16 >> 7) & 1));
            tmp8 = tmp16 & 0xFF;
            flags.sign  = (tmp8 >> 7);
            flags.zero  = (tmp8 == 0);
            break;
        case 5 : // LDA
            tmp8 = arg2;
            // Set S and Z
            flags.sign = (tmp8 >> 7);
            flags.zero = (tmp8 == 0);
            break;
        case 6 : // CMP
            tmp16 = arg1 + ~arg2 + flags.carry;
            // Set S, Z, and C
            flags.carry = (tmp16 >> 8);
            tmp8 = tmp16 & 0xFF;
            flags.sign  = (tmp8 >> 7);
            flags.zero  = (tmp8 == 0);
            break;
        case 7 : // SBC
            tmp16 = arg1 + ~arg2 + flags.carry;
            // Set S, Z, C, and V
            flags.carry    = (tmp16 >> 8);
            flags.overflow = ~((arg1 >> 7) ^ (~arg2 >> 7)) & ((arg1 >> 7) ^ ((tmp16 >> 7) & 1));
            tmp8 = tmp16 & 0xFF;
            flags.sign  = (tmp8 >> 7);
            flags.zero  = (tmp8 == 0);
    }

    return tmp8;
} // alu

static uint16_t sign_extend(uint8_t arg)
{
    return (arg < 0x80) ? arg : 0xFF00 | arg;
}

void Cpu::singleStep()
{
    uint8_t tmp16;
    uint8_t inst = m_memory.read(m_pc);
    std::cout << "Executing opcode " << std::hex << std::setw(2) << (uint16_t) inst;
    std::cout << " at address " << std::hex << std::setw(4) << m_pc;
    std::cout << std::dec << std::endl;

    switch (inst)
    {
        case 0x18: // CLC
            m_flags.carry = 0;
            m_pc += 1;
            break;

        case 0x38: // SEC
            m_flags.carry = 1;
            m_pc += 1;
            break;

        case 0x58: // CLI
            m_flags.intmask = 0;
            m_pc += 1;
            break;

        case 0x78: // SEI
            m_flags.intmask = 1;
            m_pc += 1;
            break;

        case 0xB8: // CLV
            m_flags.overflow = 0;
            m_pc += 1;
            break;

        case 0xD8: // CLD
            m_flags.decimal = 0;
            m_pc += 1;
            break;

        case 0xF8: // SED
            m_flags.decimal = 1;
            m_pc += 1;
            break;

        case 0x10: // BPL
            m_pc += 2;
            if (m_flags.sign == 0) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0x30: // BMI
            m_pc += 2;
            if (m_flags.sign == 1) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0x50: // BVC
            m_pc += 2;
            if (m_flags.overflow == 0) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0x70: // BVS
            m_pc += 2;
            if (m_flags.overflow == 1) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0x90: // BCC
            m_pc += 2;
            if (m_flags.carry == 0) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0xB0: // BCS
            m_pc += 2;
            if (m_flags.carry == 1) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0xD0: // BNE
            m_pc += 2;
            if (m_flags.zero == 0) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0xF0: // BEQ
            m_pc += 2;
            if (m_flags.zero == 1) {
                m_pc += sign_extend(m_memory.read(m_pc-1));
            }
            break;

        case 0x09: // ORA #
            m_areg = alu(0, m_areg, m_memory.read(m_pc+1), m_flags);
            m_pc += 2;
            break;

        case 0x29: // AND #
            m_areg = alu(1, m_areg, m_memory.read(m_pc+1), m_flags);
            m_pc += 2;
            break;

        case 0x49: // EOR #
            m_areg = alu(2, m_areg, m_memory.read(m_pc+1), m_flags);
            m_pc += 2;
            break;

        case 0x69: // ADC #
            m_areg = alu(3, m_areg, m_memory.read(m_pc+1), m_flags);
            m_pc += 2;
            break;

        case 0x89: // Reserved
            break;

        case 0xA9: // LDA #
            m_areg = alu(5, m_areg, m_memory.read(m_pc+1), m_flags);
            m_pc += 2;
            break;

        case 0xC9: // CMP #
            alu(6, m_areg, m_memory.read(m_pc+1), m_flags);
            m_pc += 2;
            break;

        case 0xE9: // SBC #
            m_areg = alu(7, m_areg, m_memory.read(m_pc+1), m_flags);
            m_pc += 2;
            break;

        case 0x0D: // ORA $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_areg = alu(0, m_areg, m_memory.read(tmp16), m_flags);
            m_pc += 3;
            break;

        case 0x2D: // AND $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_areg = alu(1, m_areg, m_memory.read(tmp16), m_flags);
            m_pc += 3;
            break;

        case 0x4D: // EOR $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_areg = alu(2, m_areg, m_memory.read(tmp16), m_flags);
            m_pc += 3;
            break;

        case 0x6D: // ADC $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_areg = alu(3, m_areg, m_memory.read(tmp16), m_flags);
            m_pc += 3;
            break;

        case 0x8D: // STA $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_memory.write(tmp16, m_areg);
            m_pc += 3;
            break;

        case 0xAD: // LDA $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_areg = alu(5, m_areg, m_memory.read(tmp16), m_flags);
            m_pc += 3;
            break;

        case 0xCD: // CMP $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            alu(6, m_areg, m_memory.read(tmp16), m_flags);
            m_pc += 3;
            break;

        case 0xED: // SBC #
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_areg = alu(7, m_areg, m_memory.read(tmp16), m_flags);
            m_pc += 3;
            break;

        case 0x4C: // JMP $
            tmp16 = m_memory.read(m_pc+1) | (m_memory.read(m_pc+2) << 8);
            m_pc = tmp16;
            break;
            
        default: std::cerr << "Unimplemented instruction" << std::endl; exit(-1);
    }
} // singleStep

void Cpu::show() const
{
    std::cout << "PC: " << std::hex << std::setw(4) << m_pc;
    std::cout << "  AREG : " << std::hex << std::setw(2) << (uint16_t) m_areg;
    std::cout << "  FLAGS : ";
    if (m_flags.sign)     std::cout << "S"; else std::cout << ".";
    if (m_flags.overflow) std::cout << "V"; else std::cout << ".";
    if (m_flags.reserved) std::cout << "R"; else std::cout << ".";
    if (m_flags.brk)      std::cout << "B"; else std::cout << ".";
    if (m_flags.decimal)  std::cout << "D"; else std::cout << ".";
    if (m_flags.intmask)  std::cout << "I"; else std::cout << ".";
    if (m_flags.zero)     std::cout << "Z"; else std::cout << ".";
    if (m_flags.carry)    std::cout << "C"; else std::cout << ".";
    std::cout << std::dec << std::endl;
} // show

