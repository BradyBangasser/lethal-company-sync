#include <stdio.h>
#include "util/utils.h"
#include "network/network.hpp"
#include <cstdint>
#include <http.hpp>
#include "constants.hpp"
#include "mod/mod.hpp"
#include "fs/files.hpp"
#include <limits.h>
#include "fs/lsf.h"

// This verified that all of the required folders and files exist
int init() {
    checkAndInstallSystemFiles();
    return 0;
}

int main() {
    init();
    Mod mod = Mod::fetch("000069:92038414a8a21b3f98b2a08c55e0201e9a7ebe8ac75d73dcee242f82");

    mod.install();
    return 0;
}