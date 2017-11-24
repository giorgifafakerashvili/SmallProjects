#ifndef SMALLPROJECTS_ARENA_H
#define SMALLPROJECTS_ARENA_H

#include <vector>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <atomic>


class AtomicPointer {
private:
    std::atomic<void*> rep_;
public:
    AtomicPointer() {}
    explicit AtomicPointer(void* v) : rep_(v) {}
    inline void* Acquire_Load() const {
        return rep_.load(std::memory_order_acquire);
    }

    inline void Release_Store(void* v) {
        rep_.store(v, std::memory_order_release);
    }

    inline void* NoBarrier_Load() const {
        return rep_.load(std::memory_order_relaxed);
    }

    inline void NoBarrier_Store(void* v) {
        rep_.store(v, std::memory_order_relaxed);
    }
};

class Arena {
public:
    Arena();
    ~Arena();

    // Returna  pointer to a newly allocated memory block of "bytes" bytes.
    char* Allocate(size_t bytes);

    // Allocate memory with the normal alignement guarantes provided by malloc
    char* AllocateAligned(size_t bytes);

    // Returns an estimate of the total memory usage of data allocated.
    // by the arena.
    size_t MemoryUsage() const {
        return reinterpret_cast<uintptr_t>(memory_usage_.NoBarrier_Load());
    }

private:
    char* AllocateFellback(size_t bytes);
    char* AllocateNewBlock(size_t block_bytes);

    // Allocation state
    char* alloc_ptr_;
    size_t alloc_bytes_remaining_;

    // Array of new[] allocated memory blocks.
    std::vector<char*> blocks_;

    // Total memory usage of the arena.
    AtomicPointer memory_usage_;

    // No copying allowed
    Arena(const Arena&);
    void operator=(const Arena&);
};

inline char* Arena::Allocate(size_t bytes) {
    // The semantics of what to return are a bit messy if we allow
    // 0-byte allocations, so we disallow them here (we don't need
    // them for our internal use)
    assert(bytes > 0);
    if(bytes <= alloc_bytes_remaining_) {
        char* result = alloc_ptr_;
        alloc_ptr_ += bytes;
        alloc_bytes_remaining_ -= bytes;
        return result;
    }
    return AllocateFellback(bytes);
}



#endif //SMALLPROJECTS_ARENA_H
