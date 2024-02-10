#include <stdio.h>
#include "modpack.hpp"
#include "util/utils.h"
#include "network/network.hpp"
#include <cstdint>

int main() {
    const std::string msg = "zbhipqvoscpkqaxufrulcgsxjuvipywjyxrenwqfzujtirvwmgioaltiewsynwfdmkdsswlleqmvweoamuwwstlyrgqqvdkwalansjzhnievsqzxuvanwedazvvffzjtamfoiflniltrekdhafrgbiyadolgzbrmdmbxyuwlywvvwixphlnofgigzsjqxqswifctfvd";
    uint8_t buffer[64];
    uint32_t i;
    sha224(buffer, msg.c_str(), &i);

    for (int j = 0; j < i; j++) {
        printf("%02x ", buffer[j]);
    }

    printf("\n");

    return 0;
}