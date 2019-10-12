#pragma once

#include <vector>
#include <stdint.h>

class Memory
{
    public:
        Memory(std::vector<uint8_t> init) {m_data.reserve(65536);
            std::copy(init.begin(), init.end(), &m_data[65536-init.size()]);
        }

        // Memory access is one byte at a time.
        uint8_t read(uint16_t addr) const {return m_data[addr];}
        void write(uint16_t addr, uint8_t value) {m_data[addr] = value;}

    private:
        std::vector<uint8_t> m_data;
}; // end of class Memory


