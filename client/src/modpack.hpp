#include <string>
#include <vector>

// This represents the .modpack.lcs file
class ModPack {
    private:
        std::string name;
        const std::string id;
        const std::string gameId;
        const std::string gameName;
        std::vector<const std::string> mods;
        int revisionNumber;
        bool unsavedChanges = false;
    
    public:
        ModPack();
        // This will create a new ModPack, doesn't save it
        ModPack(std::string name, const std::string gameId, const std::vector<std::string> ids);

        static ModPack import(std::string path);
        static std::string generatePackId();
        static int save(ModPack *self);
        static const std::vector<const std::string> getCachedMods(const std::string gameId);

        int removeMod(const std::string id);
        int addAddMod(const std::string id);
        int changeName(const std::string newName);
        int save();

        inline const std::string getId() { return id; }
        inline const std::vector<const std::string> getMods() { return mods; }
        inline const std::string getName() { return name; }
        inline const int getRevisionNumber() { return revisionNumber; }
        inline const std::string getGameName() { return gameName; }
};