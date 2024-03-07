#ifndef LCS_ERRORS_HPP
#define LCS_ERRORS_HPP

#include <stdio.h>
#include <string>

template<typename T, typename = void>
struct has_what : std::false_type {};

template<typename T>
struct has_what<T, decltype(void(std::declval<T &>().what()))> : std::true_type {};


template<class E> inline void handleError(E &err, bool fatal = false) {
    static_assert(has_what<E>::value, "E is not an error type");
    // Add stacktracing eventually
    printf("ERROR: %s\n", err.what());
    if (fatal) exit(-1);
}

#endif