#include "DuneException.h"

DuneException::DuneException(const std::string& message) : std::runtime_error(message) {

}

PlanetSystemInitializationException::PlanetSystemInitializationException(const std::string& message)
    : DuneException(message) {
}

HeartInitializationException::HeartInitializationException(const std::string& message)
    : DuneException(message) {
}

MathException::MathException(const std::string& message)
    : DuneException(message) {
}

MathException::MathException(const std::string& message, float value)
    : DuneException(message + ": [" + std::to_string(value) + "]") {
}

ShroomException::ShroomException(const std::string& message)
    : DuneException("Shroom Exception: " + message) {
}

ShroomException::ShroomException(const std::string& message, const std::string& detail)
    : DuneException("Shroom Exception: " + message + " [" + detail + "]") {
}

DuneColorException::DuneColorException(const std::string& message) : 
    DuneException(message) {
}