#pragma once
#include <cstddef>
#include <stdint.h>
#include <string>
#include <windows.h>

class ITCHParser {
public:
    explicit ITCHParser(const std::string& path);
    ~ITCHParser();

    bool has_next() const;
    char next_message_type() const;
    const char* next_message() const;

    const uint8_t next_message_len() const;

    void advance(size_t n);

private:
    HANDLE hFile_;
    HANDLE hMap_;
    std::size_t size_;
    const char* data_;
    const char* cursor_;
    const char* end_;
};
