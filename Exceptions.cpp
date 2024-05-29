#include "Exceptions.h"

MyException::MyException(const std::string& message) : std::runtime_error(message) {

}

PlanetSystemInitializationException::PlanetSystemInitializationException(const std::string& message)
    : MyException(message) {
}

HeartInitializationException::HeartInitializationException(const std::string& message)
    : MyException(message) {
}

MathException::MathException(const std::string& message)
    : MyException(message) {
}

MathException::MathException(const std::string& message, float value)
    : MyException(message + ": [" + std::to_string(value) + "]") {
}

ShroomException::ShroomException(const std::string& message)
    : MyException("Shroom Exception: " + message) {
}

ShroomException::ShroomException(const std::string& message, const std::string& detail)
    : MyException("Shroom Exception: " + message + " [" + detail + "]") {
}
