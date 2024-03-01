#include <string>

#include "../constants.hpp"

/**
 * @brief This namespace holds functions for controlling the fs caching system
 */
namespace cache_manager {
    const static std::string cachePath = 

    enum CacheStatus {
        HIT,
        MISS,
        OUTDATED,
    };

    /**
     * @brief The cache ID, basically the path to where the cached files will be stored, should start with a / and be path safe
     * @example /mod
     */
    typedef std::string CacheId;

    /**
     * @brief The Cached Object Id 
     * 
     */
    typedef std::string ObjectId;

    /**
     * @brief Formats the Cache Id (should also work on Object Ids)
     * 
     * @param id cacheId 
     * @return CacheId 
     */
    inline CacheId _serializeCacheId(CacheId id) noexcept {
        // so I don't have to always use backslashes, also for future complatibity with unix based systems
        id.replace(id.begin(), id.end(), '/', '\\');

        // make sure id starts with "\"
        if (id[0] != '\\') {
            id = "\\" + id;
        }

        return id;
    }

    /**
     * @brief Checks if the cache contains the specified element
     * 
     * @param cacheId 
     * @param objectId 
     * @return CacheStatus 
     */
    CacheStatus checkCache(CacheId cacheId, ObjectId objectId);

    std::string fetchFromCache(CacheId cacheId, ObjectId objectId);
    int fetchFromCache(CacheId cacheId, ObjectId objectId, std::string path);

    /**
     * @brief Copys the provided file to the cache
     * 
     * @param cacheId The Cache Id
     * @param objectId The Object Id
     * @param filePath The File Path
     * @return int 
     */
    int cacheInsert(CacheId cacheId, ObjectId objectId, std::string filePath);

    int cacheDelete(CacheId cacheId, ObjectId objectId);
}