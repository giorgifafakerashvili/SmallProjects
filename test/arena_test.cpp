#ifdef _TESTING_SUPPORT_

#include "../include/arena.h"
#include "../include/random.h"
#include <gtest/gtest.h>

class ArenaTest {};

TEST(ArenaTest, Empty) {
    Arena arena;
}

TEST(ArenaTest, Simple) {
    std::vector<std::pair<size_t, char*>> allocated;
    Arena arena;
    const int N = 100000;
    size_t bytes = 0;
    Random rnd(30);
    for(int i = 0; i < N; ++i) {
        size_t s;
        if(i % (N / 10) == 0) {
            s = i;
        } else {
            s = rnd.OneIn(4000) ? rnd.Uniform(6000) :
                (rnd.OneIn(10) ? rnd.Uniform(100) : rnd.Uniform(20));
        }

        if(s == 0) {
            // Our arena diallows size_ 0 allocations
            s = 1;
        }

        char* r;
        if(rnd.OneIn(10)) {
            r = arena.AllocateAligned(s);
        } else {
            r = arena.Allocate(s);
        }

        for(size_t b = 0; b < s; ++b) {
            // Fill the 'ith' alloction with a known bit pattern
            r[b] = i % 256;
        }

        bytes += s;
        allocated.push_back(std::make_pair(s, r));
        ASSERT_GE(arena.MemoryUsage(), bytes);
        if(i > N / 10) {
            ASSERT_LE(arena.MemoryUsage(), bytes * 1.10);
        }
    }

    for(size_t i= 0; i < allocated.size(); ++i) {
        size_t num_bytes = allocated[i].first;
        const char *p = allocated[i].second;
        for(size_t b = 0; b < num_bytes; ++b) {
            // Check the 'ith' allocation for the known bit pattern
            ASSERT_EQ(p[b] & 0xff, i % 256);
        }
    }
}
#endif