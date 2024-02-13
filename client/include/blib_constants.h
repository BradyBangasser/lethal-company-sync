#ifndef BLIB_CONSTANTS
#define BLIB_CONSTANTS
#include <stdio.h>
#include <sys/timeb.h>

#define BLIB_VERSION "1.0.0"

#define BLIB_OK 0

#ifndef BLIB_VERSBOSITY
#define BLIB_VERBOSITY 4
#endif

#define BINFO(...)
#define BWARN(...)
#define BERROR(...)

// These will log everything in the base c lib too
#define BXINFO(...)

#if BLIB_VERBOSITY >= 4
#undef BXINFO
#define BXINFO(...) fprintf(stdout, __VA_ARGS__)
#endif

#if BLIB_VERBOSITY >= 3
#undef BINFO
#define BINFO(...) fprintf(stdout, __VA_ARGS__)
#endif

#if BLIB_VERBOSITY >= 2
#undef BWARN
#define BWARN(...) fprintf(stdout, __VA_ARGS__)
#endif

#if BLIB_VERBOSITY >= 1
#undef BERROR
#define BERROR(...) fprintf(stderr, __VA_ARGS__)
#endif

// These are here because otherwise I would forget them
#define HTTPS_PORT "443"
#define HTTP_PORT "80"

#endif