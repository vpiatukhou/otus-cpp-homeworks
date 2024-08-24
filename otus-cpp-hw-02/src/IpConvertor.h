#pragma once

#include "IpAddressType.h"
#include <stdexcept>
#include <string>

namespace Homework {

    /// @brief The exception is thrown by convertStringToIpAddress if the given IP address cannot be parsed
    class IpAddressParsingException : public std::runtime_error {
        public:
            explicit IpAddressParsingException(const std::string& what) : std::runtime_error(what) { };
    };

    IpAddress convertStringToIpAddress(const std::string& ipAsString);
}