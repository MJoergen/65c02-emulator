#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <stdint.h>

class Memory
{
    public:
        Memory(std::vector<uint8_t> init) : m_trace(false) {m_data.reserve(65536);
            std::copy(init.begin(), init.end(), &m_data[65536-init.size()]);
        }

        // Memory access is one byte at a time.
        uint8_t read(uint16_t addr) const {
            if (m_trace) {
                std::cout << "Reading value " << std::hex << std::setw(2) << std::setfill('0') << (uint16_t) m_data[addr];
                std::cout << " from address " << std::hex << std::setw(4) << std::setfill('0') << addr << std::dec << std::endl;
            }
                
            return m_data[addr];
        }
        void write(uint16_t addr, uint8_t value) {
            if (m_trace) {
                std::cout << "Writing value " << std::hex << std::setw(2) << std::setfill('0') << (uint16_t) value;
                std::cout << " to address " << std::hex << std::setw(4) << std::setfill('0') << addr << std::dec << std::endl;
            }
            m_data[addr] = value;
        }

        void trace(bool enable) {m_trace = enable;}

    private:
        std::vector<uint8_t> m_data;
        bool m_trace;
}; // end of class Memory


