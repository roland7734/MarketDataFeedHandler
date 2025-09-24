#pragma once
#include <cstdint>

namespace itch::endian {

    inline uint16_t read_u16(const char* p) {
        return (uint16_t(uint8_t(p[0])) << 8) |
               (uint16_t(uint8_t(p[1])));
    }

    inline uint32_t read_u32(const char* p) {
        return (uint32_t(uint8_t(p[0])) << 24) |
               (uint32_t(uint8_t(p[1])) << 16) |
               (uint32_t(uint8_t(p[2])) << 8)  |
               (uint32_t(uint8_t(p[3])));
    }

    inline uint64_t read_u48(const char* p) {
        return (uint64_t(uint8_t(p[0])) << 40) |
               (uint64_t(uint8_t(p[1])) << 32) |
               (uint64_t(uint8_t(p[2])) << 24) |
               (uint64_t(uint8_t(p[3])) << 16) |
               (uint64_t(uint8_t(p[4])) << 8)  |
               (uint64_t(uint8_t(p[5])));
    }

    inline uint64_t read_u64(const char* p) {
        return (uint64_t(uint8_t(p[0])) << 56) |
               (uint64_t(uint8_t(p[1])) << 48) |
               (uint64_t(uint8_t(p[2])) << 40) |
               (uint64_t(uint8_t(p[3])) << 32) |
               (uint64_t(uint8_t(p[4])) << 24) |
               (uint64_t(uint8_t(p[5])) << 16) |
               (uint64_t(uint8_t(p[6])) << 8)  |
               (uint64_t(uint8_t(p[7])));
    }

}