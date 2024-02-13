#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <string>
#include <vector>
namespace network {
    int verifyMod(const std::string id);
    int verifyMod(const std::vector<std::string>);
    int fetchMod(const std::string id);
}
// Caching needed

#endif