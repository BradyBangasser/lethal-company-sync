#include "cache.hpp"
#include "../fs/files.hpp"
#include <sys/stat.h>

using namespace cache_manager;

Status cache_manager::checkCache(CacheId cacheId, ObjectId objectId) noexcept {
    std::string path = _getCachePath(cacheId, objectId);

    struct stat b;

    if (stat(path.c_str(), &b) != 0) {
        return Status::CACHE_MISS;
    }

    // This will need to check if the data is outdated or not

    return Status::CACHE_HIT;
} // Fetch From Cache

int cache_manager::cacheInsert(CacheId cacheId, ObjectId objectId, std::string path, bool copy) noexcept {
    int result;

    std::string opath = _getCachePath(cacheId, objectId);
    const char *copath = opath.c_str();
    
    result = mkSubDirs(copath);

    if (result != 0) {
        return -1;
    }

    result = (copy ? fcopy(path.c_str(), copath) : fmove(path.c_str(), copath));

    if (result != 0) {
        return -1;
    }

    return 0;
}

int cache_manager::cacheDelete(CacheId cacheId, ObjectId objectId) noexcept {
    return remove(_getCachePath(cacheId, objectId).c_str());
}

int cache_manager::fetchFromCache(CacheId cacheId, ObjectId objectId, std::string path) {
    std::string cpath = _getCachePath(cacheId, objectId);

    struct stat s;

    if (stat(cpath.c_str(), &s) == -1) {
        if (errno == ENOENT) {
            return 1;
        } else {
            return -1;
        }
    }
    return fcopy(cpath.c_str(), path.c_str());
}