#include <string>
#include <algorithm>

#include "../constants.hpp"

/**
 * @brief This namespace holds functions for controlling the fs caching system
 */
namespace cache_manager {
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
    static inline CacheId _serializeCacheId(CacheId id) noexcept {
        // so I don't have to always use backslashes, also for future complatibity with unix based systems
        std::replace(id.begin(), id.end(), '/', '\\');

        // make sure id starts with "\"
        if (id[0] != '\\') {
            id = "\\" + id;
        }

        return id;
    }

    static inline std::string _getCachePath(CacheId cacheId, ObjectId objectId) {
        return cachePath(cacheId + PATH_SLASH + objectId);
    }

    /**
     * @brief Checks if the cache contains the specified element
     * 
     * @param cacheId 
     * @param objectId 
     * @return CacheStatus 
     */
    Status checkCache(CacheId cacheId, ObjectId objectId) noexcept;

    __attribute__((pure)) static inline std::string fetchFromCache(CacheId cacheId, ObjectId objectId) { return _getCachePath(cacheId, objectId); }
    int fetchFromCache(CacheId cacheId, ObjectId objectId, std::string path);

    /**
     * @brief Copys the provided file to the cache
     * @warning This will overwrite the object if it exists
     * 
     * @param cacheId The Cache Id
     * @param objectId The Object Id
     * @param filePath The File Path
     * @return int 
     */
    int cacheInsert(CacheId cacheId, ObjectId objectId, std::string filePath, bool copy = true) noexcept;

    /**
     * @brief 
     * 
     * @param cacheId 
     * @param objectId 
     * @return int 
     */
    int cacheDelete(CacheId cacheId, ObjectId objectId) noexcept;
}