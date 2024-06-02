#pragma once

#include <string>
#include <stdexcept>

class DuneException : public std::runtime_error {
public:
    explicit DuneException(const std::string& message);
};

class PlanetSystemInitializationException : public DuneException {
public:
    explicit PlanetSystemInitializationException(const std::string& message);
};

class HeartInitializationException : public DuneException {
public:
    explicit HeartInitializationException(const std::string& message);
};

class MathException : public DuneException {
public:
    explicit MathException(const std::string& message);
    MathException(const std::string& message, float value);
};

class ShroomException : public DuneException {
public:
    explicit ShroomException(const std::string& message);
    ShroomException(const std::string& message, const std::string& detail);
};

class DuneColorException : public DuneException {
public:
    explicit DuneColorException(const std::string& message);
};

class StarInitializationException : public std::runtime_error {
public:
    explicit StarInitializationException(const std::string& message);
};