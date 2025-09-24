
#include "logger/Logger.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>

Logger& Logger::getInstance() {
    static Logger inst;
    return inst;
}

void Logger::init(const std::string& filePath, bool append) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (initialized_) return;
    std::ios_base::openmode mode = std::ios::out | std::ios::binary;
    if (append) mode |= std::ios::app; else mode |= std::ios::trunc;
    out_.open(filePath, mode);
    if (!out_.is_open())
        throw std::runtime_error("Logger: cannot open file: " + filePath);
    initialized_ = true;
}

static std::string timestamp() {
    using clock = std::chrono::system_clock;
    auto now = clock::now();
    auto t = clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << ms.count();
    return oss.str();
}

void Logger::log(const std::string& msg) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (!initialized_) return; // or throw
    out_ << '[' << timestamp() << "] " << msg << '\n';
    // Optionally: out_.flush();
}

void Logger::flush() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (initialized_) out_.flush();
}

Logger::~Logger() {
    std::lock_guard<std::mutex> lock(mtx_);
    if (out_.is_open()) {
        out_.flush();
        out_.close();
    }
}
