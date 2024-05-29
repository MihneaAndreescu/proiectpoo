class PlanetSystemInitializationException : public std::runtime_error {
public:
    explicit PlanetSystemInitializationException(const std::string& message) : std::runtime_error(message) {
    }
};

class MathException : public std::runtime_error {
public:
	explicit MathException(const std::string& message)
		: std::runtime_error(message) {
	}

	MathException(const std::string& message, float value)
		: std::runtime_error(message + ": [" + std::to_string(value) + "]") {

	}
};

class ShroomException : public std::runtime_error {
public:
    explicit ShroomException(const std::string& message)
        : std::runtime_error("Shroom Exception: " + message) {
    }

    ShroomException(const std::string& message, const std::string& detail)
        : std::runtime_error("Shroom Exception: " + message + " [" + detail + "]") {
    }
};