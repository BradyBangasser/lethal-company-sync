#ifndef MODPACK_HPP
#define MODPACK_HPP

#include <string>
#include <vector>

// This represents the .modpack.lcs file
class ModPack {
    private:
        std::string name;
        const std::string id;
        const std::string gameId;
        const std::string gameName;
        std::vector<std::string> modIds;
        int revisionNumber;
        bool unsavedChanges;
        bool inited;
    
    public:
        ModPack();
        // This will create a new ModPack, doesn't save it
        ModPack(std::string name, const std::string gameId, const std::vector<std::string> modIds = std::vector<std::string>());

        static ModPack import(std::string path);
        static std::string generatePackId();
        static int save(ModPack *self);
        static const std::vector<std::string> getCachedMods(const std::string gameId);
        static int install(ModPack *self);

        int removeMod(const std::string id);
        int addAddMod(const std::string id);
        int changeName(const std::string newName);
        int save();
        int install();

        inline const std::string getId() { return id; }
        inline const std::vector<std::string> getModIds() { return modIds; }
        inline const std::string getName() { return name; }
        inline const int getRevisionNumber() { return revisionNumber; }
        inline const std::string getGameName() { return gameName; }
};

#endif