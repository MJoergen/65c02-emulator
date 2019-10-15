#pragma once

// List of all the possible instructions.
typedef enum
{
    I_RTI, I_ORA, I_AND, I_EOR, I_ADC, I_STA, I_LDA, I_CMP, I_SBC, I_CLC,
    I_SEC, I_CLI, I_SEI, I_CLV, I_CLD, I_SED, I_BPL, I_BMI, I_BVC, I_BVS,
    I_BCC, I_BCS, I_BNE, I_BEQ, I_JMP, I_PHP, I_JSR, I_PLP, I_PHA, I_RTS,
    I_PLA, I_ASLA, I_ROLA, I_LSRA, I_RORA, I_ASL, I_ROL, I_LSR, I_ROR, I_DEC, 
    I_INC, I_BIT, I_STX, I_LDX, I_CPX, I_INX, I_DEX, I_TAX, I_TXA, I_TSX,
    I_TXS, I_STY, I_LDY, I_CPY, I_INY, I_DEY, I_TAY, I_TYA, I_NOP, I_BRK,
    I_RES
} instruction_t;

// List of all the possible addressing modes.
typedef enum
{
    AM_IMM,     // Immediate
    AM_ABS,     // Absolute
    AM_ZP,      // Zero-Page
    AM_NONE,    // None (i.e. implied)
    AM_ACC,     // Accumulator
    AM_ZPX,     // Zero-Page indexed with X
    AM_ZPY,     // Zero-Page indexed with Y
    AM_ABSX,    // Absolute indexed with X
    AM_ABSY,    // Absolute indexed with Y
    AM_IND,     // Indirect
    AM_INDX,    // Pre-indexed indirect
    AM_INDY,    // Post-indexed indirect
    AM_REL,     // Relative
    AM_RES,
} addrMode_t;

// List of all the possible ALU operations.
typedef enum
{
    ALU_ORA,
    ALU_AND,
    ALU_EOR,
    ALU_ADC,
    ALU_LDA,
    ALU_CMP,
    ALU_SBC,
    ALU_ASL,
    ALU_ROL,
    ALU_LSR,
    ALU_ROR,
    ALU_DEC,
    ALU_INC,
    ALU_BIT
} aluMode_t;

extern const addrMode_t addrModes[256];

extern const instruction_t instructions[256];

