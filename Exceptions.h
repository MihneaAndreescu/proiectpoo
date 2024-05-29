class PlanetSystemInitializationException : public std::runtime_error {
public:
    explicit PlanetSystemInitializationException(const std::string& message) : std::runtime_error(message) {
    }
};
