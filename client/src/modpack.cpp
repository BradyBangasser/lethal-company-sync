#include "modpack.hpp"
#include <string>
#include <vector>
#include <iostream>

ModPack::ModPack(std::string name, const std::string gameId, const std::vector<std::string> modIds) {
    this->name = name;
    *const_cast<std::string *>(&(this->gameId)) = gameId;

    
    
    
    for (const std::string &id : modIds) {
        this->modIds.push_back(id);
    }

    std::cout << this->gameId << std::endl;
}