#include "IpFilter.h"
#include <algorithm>
#include <iterator>

namespace Homework {

    /// @brief creates a comparator which returns TRUE if the LEFT IP address is greater than the RIGHT one.
    /// @return a lambda expression which can be used as comparator in std::sort().
    auto createIpAddressComparator() {
        return [](const IpAddress& l, const IpAddress& r) {
            for (size_t i = 0; i < l.size(); ++i) {
                if (l[i] != r[i]) {
                    return l[i] > r[i];
                }
            }
            return false;
        };
    }

    std::vector<IpAddress> filter(const std::vector<IpAddress>& ipAddresses, int ipPart1) {
        std::vector<IpAddress> result;
        std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(result), [ipPart1](const auto& ipAddress) { return ipAddress[0] == ipPart1; });
        return result;
    }

    std::vector<IpAddress> filter(const std::vector<IpAddress>& ipAddresses, int ipPart1, int ipPart2) {
        std::vector<IpAddress> result;
        std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(result), [ipPart1, ipPart2](const auto& ipAddress) { 
            return ipAddress[0] == ipPart1 && ipAddress[1] == ipPart2; 
        });
        return result;
    }

    std::vector<IpAddress> filterAny(const std::vector<IpAddress>& ipAddresses, int ipPart) {
        std::vector<IpAddress> result;
        std::copy_if(ipAddresses.begin(), ipAddresses.end(), std::back_inserter(result), [ipPart](const auto& ipAddress) {
            for (int part : ipAddress) {
                if (part == ipPart) {
                    return true;
                }
            }
            return false;
        });
        return result;
    }

    std::vector<IpAddress> filterIpAddresses(const std::vector<IpAddress>& ipAddresses) {
        //sort the IP list
        auto sortedIpAddresses = ipAddresses;
        std::sort(sortedIpAddresses.begin(), sortedIpAddresses.end(), createIpAddressComparator());

        auto result = sortedIpAddresses;

        //find IPs which matches "1.x.x.x"
        auto filteredIps = filter(sortedIpAddresses, 1);
        result.insert(result.end(), filteredIps.begin(), filteredIps.end());

        //find IPs which matches "46.70.x.x"
        filteredIps = filter(sortedIpAddresses, 46, 70);
        result.insert(result.end(), filteredIps.begin(), filteredIps.end());
        
        //find IPs with any byte equals to 46
        filteredIps = filterAny(sortedIpAddresses, 46);
        result.insert(result.end(), filteredIps.begin(), filteredIps.end());
        return result;
    }
}