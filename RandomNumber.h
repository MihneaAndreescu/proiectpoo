#pragma once
#include <random>
#include <chrono>

class RandomNumber {
private:
    RandomNumber() {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        m_rng.seed(static_cast<unsigned>(seed));
    }
    std::mt19937 m_rng;
public:
    static RandomNumber& getInstance() {
        static RandomNumber instance;
        return instance;
    }
    RandomNumber(const RandomNumber&) = delete;
    RandomNumber& operator=(const RandomNumber&) = delete;
    template<typename Distribution>
    auto getRandom(Distribution distribution) -> decltype(distribution(m_rng)) {
        return distribution(m_rng);
    }
};
