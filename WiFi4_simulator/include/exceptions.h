// exceptions.hpp
#pragma once
#include <exception>
#include <string>

namespace wifi_sim {
    class WiFiSimException : public std::exception {
    protected:
        std::string message;
    public:
        WiFiSimException(const std::string& msg) : message(msg) {}
        virtual const char* what() const noexcept override {
            return message.c_str();
        }
    };

    class InvalidInputException : public WiFiSimException {
    public:
        InvalidInputException(const std::string& msg = "Invalid input!") 
            : WiFiSimException(msg) {}
    };

    class InvalidUserCountException : public InvalidInputException {
    public:
        InvalidUserCountException() 
            : InvalidInputException("Invalid number of users! User count must be greater than 0.") {}
    };

    class NetworkConfigurationException : public WiFiSimException {
    public:
        NetworkConfigurationException(const std::string& msg) 
            : WiFiSimException("Network configuration error: " + msg) {}
    };
}