#include <string>

#include <string>
#include <stdexcept>

class MyException : public std::runtime_error {
public:
    explicit MyException(const std::string& message) : std::runtime_error(message) {}
};

class PlanetSystemInitializationException : public MyException {
public:
    explicit PlanetSystemInitializationException(const std::string& message)
        : MyException(message) {
    }
};

class HeartInitializationException : public MyException {
public:
    explicit HeartInitializationException(const std::string& message)
        : MyException(message) {
    }
};

class MathException : public MyException {
public:
    explicit MathException(const std::string& message)
        : MyException(message) {
    }

    MathException(const std::string& message, float value)
        : MyException(message + ": [" + std::to_string(value) + "]") {
    }
};

class ShroomException : public MyException {
public:
    explicit ShroomException(const std::string& message)
        : MyException("Shroom Exception: " + message) {
    }

    ShroomException(const std::string& message, const std::string& detail)
        : MyException("Shroom Exception: " + message + " [" + detail + "]") {
    }
};