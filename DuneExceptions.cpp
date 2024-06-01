#include "DuneExceptions.h"

DuneExceptions::DuneExceptions(const std::string& message) : std::runtime_error(message) {

}

PlanetSystemInitializationException::PlanetSystemInitializationException(const std::string& message)
    : DuneExceptions(message) {
}

HeartInitializationException::HeartInitializationException(const std::string& message)
    : DuneExceptions(message) {
}

MathException::MathException(const std::string& message)
    : DuneExceptions(message) {
}

MathException::MathException(const std::string& message, float value)
    : DuneExceptions(message + ": [" + std::to_string(value) + "]") {
}

ShroomException::ShroomException(const std::string& message)
    : DuneExceptions("Shroom Exception: " + message) {
}

ShroomException::ShroomException(const std::string& message, const std::string& detail)
    : DuneExceptions("Shroom Exception: " + message + " [" + detail + "]") {
}
