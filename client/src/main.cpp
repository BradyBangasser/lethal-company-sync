#include <stdio.h>
#include "modpack.hpp"
#include "util/utils.h"
#include "network/network.hpp"
#include <cstdint>
#include <http.hpp>
#include "constants.hpp"

int main() {
    const struct blib_http::Response res = blib_http::request<const blib_http::Response>(serverUrl("/mod/"), NULL);
    printf("%i %s\n", res.status, res.content.c_str());
    return 0;
}