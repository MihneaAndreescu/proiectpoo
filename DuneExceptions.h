#pragma once

#include <string>
#include <stdexcept>

class DuneExceptions : public std::runtime_error {
public:
    explicit DuneExceptions(const std::string& message);
};

class PlanetSystemInitializationException : public DuneExceptions {
public:
    explicit PlanetSystemInitializationException(const std::string& message);
};

class HeartInitializationException : public DuneExceptions {
public:
    explicit HeartInitializationException(const std::string& message);
};

class MathException : public DuneExceptions {
public:
    explicit MathException(const std::string& message);
    MathException(const std::string& message, float value);
};

class ShroomException : public DuneExceptions {
public:
    explicit ShroomException(const std::string& message);
    ShroomException(const std::string& message, const std::string& detail);
};

class DuneColorException : public DuneExceptions {
public:
    explicit DuneColorException(const std::string& message);
};