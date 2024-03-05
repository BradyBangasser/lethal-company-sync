#include "cache.hpp"
#include "../fs/files.hpp"
#include <sys/stat.h>

using namespace cache_manager;

CacheStatus cache_manager::checkCache(CacheId cacheId, ObjectId objectId) noexcept {
    std::string path = _getCachePath(cacheId, objectId);

    struct stat b;

    if (stat(path.c_str(), &b) != 0) {
        return CacheStatus::MISS;
    }

    // This will need to check if the data is outdated or not

    return CacheStatus::HIT;
} // Fetch From Cache

int cache_manager::cacheInsert(CacheId cacheId, ObjectId objectId, std::string path) noexcept {
    int result;

    const char *opath = _getCachePath(cacheId, objectId).c_str();
    
    result = mkSubDirs(opath);

    if (result != 0) {
        return -1;
    }

    result = fmove(path.c_str(), opath);

    if (result != 0) {
        return -1;
    }

    return 0;
}

int cache_manager::cacheDelete(CacheId cacheId, ObjectId objectId) noexcept {
    return remove(_getCachePath(cacheId, objectId).c_str());
}