#include "parser/ITCHParser.hpp"

#include <cstdint>
#include <stdexcept>

ITCHParser::ITCHParser(const std::string& path)
    : hFile_(INVALID_HANDLE_VALUE), hMap_(nullptr), data_(nullptr) {

    // Open file
    hFile_ = CreateFileA(
        path.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );
    if (hFile_ == INVALID_HANDLE_VALUE) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile_, &fileSize)) {
        CloseHandle(hFile_);
        throw std::runtime_error("Failed to get file size: " + path);
    }
    size_ = static_cast<std::size_t>(fileSize.QuadPart);

    // Create file mapping
    hMap_ = CreateFileMapping(hFile_, nullptr, PAGE_READONLY, 0, 0, nullptr);
    if (!hMap_) {
        CloseHandle(hFile_);
        throw std::runtime_error("CreateFileMapping failed for: " + path);
    }

    // Map view of file
    data_ = static_cast<const char*>(MapViewOfFile(hMap_, FILE_MAP_READ, 0, 0, 0));
    if (!data_) {
        CloseHandle(hMap_);
        CloseHandle(hFile_);
        throw std::runtime_error("MapViewOfFile failed for: " + path);
    }

    cursor_ = data_;
    end_ = data_ + size_;
}

ITCHParser::~ITCHParser() {
    if (data_) UnmapViewOfFile(data_);
    if (hMap_) CloseHandle(hMap_);
    if (hFile_ != INVALID_HANDLE_VALUE) CloseHandle(hFile_);
}

bool ITCHParser::has_next() const {
    return cursor_ < end_;
}

char ITCHParser::next_message_type() const {
    if (!has_next()) throw std::runtime_error("No more messages");
    if (cursor_ + 2 > end_) throw std::runtime_error("Incomplete message header");
    return *(cursor_ + 2);
}

const char* ITCHParser::next_message() const {
    if (!has_next()) throw std::runtime_error("No more messages");
    if (cursor_ + 2 > end_) throw std::runtime_error("Incomplete message header");
    return cursor_ + 2;
}

const uint8_t ITCHParser::next_message_len() const {
    if (!has_next()) throw std::runtime_error("No more messages");
    if (cursor_ + 2 > end_) throw std::runtime_error("Incomplete message header");
    return *(cursor_+1);
}

void ITCHParser::advance(const std::size_t n) {
    cursor_ += n;
    if (cursor_ > end_) cursor_ = end_;
}