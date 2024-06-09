#pragma once

#include <SFML/Graphics/Color.hpp>
#include <algorithm>  
#include "DuneException.h"

template <typename T>
class DuneColor {
private:
    T m_r, m_g, m_b, m_a;
public:
    T r() const {
        return m_r;
    }
    T g() const {
        return m_g;
    }
    T b() const {
        return m_b;
    }
    T a() const {
        return a;
    }
    DuneColor() : m_r(0), m_g(0), m_b(0), m_a(255) {
    }
    DuneColor(T red, T green, T blue, T alpha = 255)
        : m_r(red), m_g(green), m_b(blue), m_a(alpha) {
    }
    static sf::Uint8 clamp(T value) {
        return static_cast<sf::Uint8>(std::max<T>(0, std::min<T>(255, value)));
    }
    operator sf::Color() const {
        return sf::Color(clamp(m_r), clamp(m_g), clamp(m_b), clamp(m_a));
    }
    DuneColor operator+(const DuneColor& other) const {
        return DuneColor(m_r + other.m_r, m_g + other.m_g, m_b + other.m_b, m_a + other.m_a);
    }
    DuneColor operator-(const DuneColor& other) const {
        return DuneColor(m_r - other.m_r, m_g - other.m_g, m_b - other.m_b, m_a - other.m_a);
    }
    DuneColor operator*(T scalar) const {
        return DuneColor(m_r * scalar, m_g * scalar, m_b * scalar, m_a * scalar);
    }
    DuneColor operator/(T scalar) const {
        if (scalar == 0) {
            throw DuneColorException("/ 0");
        }
        return Color(m_r / scalar, m_g / scalar, m_b / scalar, m_a / scalar);

    }
};
