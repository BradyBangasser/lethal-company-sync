#ifndef LCS_GAME_GAME_HPP
#define LCS_GAME_GAME_HPP

#include <string>
#include <vector>

#include "../mod/mod.hpp"

class Game {
    private:
        std::string name;
        std::string id;
        std::vector<Mod> installedMods;
        std::string modInstallPath;
        bool supportsProfiles;

        std::string generateGameFileContent();

    public:
        static Game parse(std::string json);
        static Game fromGameFile(std::string path);
};

#endif