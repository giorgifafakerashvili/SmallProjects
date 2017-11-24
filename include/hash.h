#ifndef SMALLPROJECTS_HASH_H
#define SMALLPROJECTS_HASH_H

#include <stddef.h>
#include <stdint.h>

extern uint32_t Hash(const char* data, size_t n, uint32_t seed);

#endif //SMALLPROJECTS_HASH_H
