#include "IpAddressType.h"
#include "IpConvertor.h"
#include "IpFilter.h"
#include <iostream>
#include <string>
#include <vector>

namespace Homework {

    const char TAB_CHARACTER = '\t';
    const char IP_DELIMITER = '.';

    std::vector<IpAddress> readIpAddressesFromInput() {
        std::vector<IpAddress> ipAddresses;
        std::string line;
        while (std::getline(std::cin, line)) {
            std::string ipAsString = line.substr(0, line.find_first_of(TAB_CHARACTER));
            try {
                ipAddresses.push_back(convertStringToIpAddress(ipAsString));
            } catch (const IpAddressParsingException& e) {
                throw IpAddressParsingException("Error parsing IP address " + ipAsString + ": " + e.what());
            }
        }
        return ipAddresses;
    }

    std::string convertIpAddressToString(const IpAddress& ipAddress) {
        return std::to_string(ipAddress[0]) 
            + IP_DELIMITER + std::to_string(ipAddress[1]) 
            + IP_DELIMITER + std::to_string(ipAddress[2]) 
            + IP_DELIMITER + std::to_string(ipAddress[3]);
    }
}

int main() {
    std::vector<Homework::IpAddress> ipAddresses;
    try {
        ipAddresses = Homework::readIpAddressesFromInput();
    } catch (const Homework::IpAddressParsingException& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    auto filteredIpAddresses = Homework::filterIpAddresses(ipAddresses);
    
    for (const auto& ipAddress : filteredIpAddresses) {
        std::cout << Homework::convertIpAddressToString(ipAddress) << std::endl;
    }
    return 0;
}