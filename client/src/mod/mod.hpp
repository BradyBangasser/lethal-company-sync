#ifndef LCS_MOD_MOD_HPP
#define LCS_MOD_MOD_HPP

#include <string>
#include "../network/network.hpp"
#include <chrono>


// THIS WILL NEED TO CHECK HASHES

/*
    Represents a Mod
*/
class Mod {
    private:
        // Id of the mod, see formats.txt for more info
        std::string id;
        std::string name;
        std::string downloadUrl;
        std::string version;
        std::string description;
        // SHA256 sum of the zipped mod, provided by server
        std::string hash;
        // When the mod was updated/created last
        std::chrono::system_clock::time_point updated;
        size_t unzippedSize;
        size_t zippedSize;
        std::string installPath;

        Mod(const std::string id, const std::string name, const std::string downloadUrl, const std::string version, const std::string description, const std::chrono::system_clock::time_point timeStamp, const std::string hash);

        static bool verifyId(std::string id);
    
    public:
        enum ModStatus {
            // For general use
            ALL_GOOD,
            // For checking mods
            OUT_OF_DATE,
            CORRUPT,
            NOT_INSTALLED,
            // For installs
            ALREADY_INSTALLED
        };

        inline const std::string getId() { return this->id; }
        inline const std::string getName() { return this->name; }
        inline const std::string getDownloadUrl() { return this->downloadUrl; }
        inline const std::string getVersion() { return this->version; }
        inline const std::string getDescription() { return this->name; }

        /**
         * @brief Downloads the 
         * 
         * @param path 
         * @return int 
         */
        ModStatus download(const std::string path);

        ModStatus install();
        /**
            Checks the mods version and hash with the server to see if the mod is corrupt or there is a new version
            @returns a @ref ModStatus
        */
        ModStatus check();

        /**
            Attempts to fix any issues found by @ref check, except for not installed
            @param force Force the fix regardless of the @ref check status
            @returns true if success, else false
        */
        bool fix(bool force = false);


        /**
            Parses the Mod from JSON
            @param json The JSON
        */
        static Mod parseJson(std::string json);

        /**
            Attempts to fetch mod infomation from the server, it does NOT download the mod
            @param id The Mod's id
        */
        static Mod fetch(std::string id, bool force = false);

        static Mod fromModFile(std::string path);
        static Mod fromGameFileLine(std::string line);
        static inline bool verify(std::string id) { return verifyId(id) && network::verifyMod(id) == 0; }
};

#endif