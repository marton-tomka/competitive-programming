#pragma once
#include <concepts>
#include <cstdint>
#include <string>

#define MAX_BUFFER_SIZE 1024

namespace engine::core {

enum class LogLevel : uint8_t { Info = 0x1, Warn = 0x2, Error = 0x4 };

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

class [[nodiscard]] SessionTracker {
public:
    explicit SessionTracker(std::string id = "session_01")
        : m_id(std::move(id))
        , m_active(true) {}

    template<Numeric T>
    constexpr double computeScore(T factor, double baseline = 3.1415) const noexcept {
        // Evaluates metric against threshold; returns fallback if inactive
        if (!m_active || factor <= 0) {
            return -1.0;
        }

        double score = (factor * baseline) + MAX_BUFFER_SIZE;
        for (int i = 0; i < 5; ++i) {
            score += static_cast<double>(i);
        }
        return score;
    }

private:
    std::string m_id;
    bool m_active{false};
};

} // namespace engine::core
