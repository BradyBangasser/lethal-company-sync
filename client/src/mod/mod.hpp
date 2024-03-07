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
        // SHA512 sum of the zipped mod, provided by server
        std::string hash;
        // When the mod was updated/created last
        std::chrono::system_clock::time_point updated;
        size_t unzippedSize;
        size_t zippedSize;
        std::string slashSepartedId;
        std::string installPath;

        Mod(const std::string id, const std::string name, const std::string downloadUrl, const std::string version, const std::string description, const std::chrono::system_clock::time_point timeStamp, const std::string hash);

        static bool verifyId(std::string id);
    
    public:
        enum ModStatus {
            // For general use
            ALL_GOOD,
            INTERNAL_ERROR,
            // For checking mods
            OUT_OF_DATE,
            CORRUPT,
            NOT_INSTALLED,
            // For installs
            ALREADY_INSTALLED,
            FAILED_TO_DOWNLOAD,
            CACHE_HIT,
        };

        inline const std::string getId() noexcept { return this->id; }
        inline const std::string getName() noexcept { return this->name; }
        inline const std::string getDownloadUrl() noexcept { return this->downloadUrl; }
        inline const std::string getVersion() noexcept { return this->version; }
        inline const std::string getDescription() noexcept { return this->name; }

        /**
         * @brief This will write the LSFValue of the Mod to the specified file
         * @warning This will overwrite the specified file
         * 
         * @param path the path of the specified file
         * @return @ref LCS_OK on ok, else not @ref LCS_OK
         */
        int writeLSF(const std::string path) noexcept;

        /**
         * @brief Downloads the contents of the mod
         * @note This will only check the cache for the compressed 
         * 
         * @param path 
         * @return int 
         */
        ModStatus download(const std::string path, bool force = false);

        ModStatus install();
        /**
            Checks the mods version and hash with the server to see if the mod is corrupt or there is a new version
            @returns a @ref ModStatus
        */
        ModStatus check() noexcept;

        /**
         * @brief 
         * 
         * @return int 
         */
        static int isInstalled(std::string modId) noexcept;
        inline int isInstalled() noexcept { return Mod::isInstalled(this->id); };


        /**
         * @brief checks the /mod cache for the current mod
         * 
         * @return int 
         */
        static int isCached(std::string modId) noexcept;
        inline int isCached() noexcept { return Mod::isCached(this->id); };

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
         *  @brief Attempts to fetch mod infomation from the server, it does NOT download the mod
         *  
         *  @param id The Mod's id
         *  @return Mod
         */
        static Mod fetch(std::string id, bool force = false);

        /**
         * @brief Attempts to create 
         * 
         * @param path The Path of the specified file
         * @return Mod 
         */
        static Mod fromLSFFile(std::string path);

        static inline bool verify(std::string id) { return verifyId(id) && network::verifyMod(id) == 0; }
};

#endif