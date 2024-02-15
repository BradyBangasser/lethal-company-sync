#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "../constants.hpp"

std::chrono::system_clock::time_point parseTime(std::string stringTime) {
    struct tm t{};
    std::istringstream ss(stringTime);
    ss >> std::get_time(&t, isoTimeFormat.c_str());
    return std::chrono::system_clock::from_time_t(mktime(&t));
}