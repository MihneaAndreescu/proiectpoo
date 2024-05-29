#include <string>
#include <stdexcept>

class MyException : public std::runtime_error {
public:
    explicit MyException(const std::string& message);
};

class PlanetSystemInitializationException : public MyException {
public:
    explicit PlanetSystemInitializationException(const std::string& message);
};

class HeartInitializationException : public MyException {
public:
    explicit HeartInitializationException(const std::string& message);
};

class MathException : public MyException {
public:
    explicit MathException(const std::string& message);
    MathException(const std::string& message, float value);
};

class ShroomException : public MyException {
public:
    explicit ShroomException(const std::string& message);
    ShroomException(const std::string& message, const std::string& detail);
};