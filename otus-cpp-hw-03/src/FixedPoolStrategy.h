#pragma once

#include <cstddef>
#include <stdexcept>

namespace Homework {

    /// @brief A memory pool which allocates a single block of memory.
    ///        A pool size is not changed and a new block is not allocated until the fist one is freed.
    class FixedPoolStrategy {

    private:
        const std::size_t poolSizeBytes;
        
        char* allocatedMemoryPtr;
        std::size_t allocatedBytes = 0;
        std::size_t deallocatedBytes = 0;

    public:
        FixedPoolStrategy(std::size_t _poolSizeBytes) : poolSizeBytes(_poolSizeBytes) { }

        FixedPoolStrategy(FixedPoolStrategy&) = delete;
        FixedPoolStrategy(FixedPoolStrategy&&) = delete;
        FixedPoolStrategy& operator=(FixedPoolStrategy&) = delete;
        FixedPoolStrategy& operator=(FixedPoolStrategy&&) = delete;

        /// @brief When the method is called first time, it allocates a new memory block and returns a pointer to it.
        ///        The next calls just returns the pointers to "a beginning of the memory block + total number of allocated bytes.".
        /// @param bytesToAllocate a number of bytes to allocate
        /// @return a pointer to free memory
        char* allocate(std::size_t bytesToAllocate) {
            if (bytesToAllocate == 0) {
                throw std::invalid_argument("Impossible to allocate 0 bytes.");
            }
            if (allocatedBytes + bytesToAllocate > poolSizeBytes) { //amount of memory is exceeded
                throw std::bad_alloc();
            }
            if (allocatedBytes == 0) { //"allocate" has been called the first time => allocate a new memory block
                allocatedMemoryPtr = static_cast<char*>(malloc(poolSizeBytes));
                if (!allocatedMemoryPtr) {
                    throw std::bad_alloc();
                }
            }
            char* result = allocatedMemoryPtr + allocatedBytes; //calculate a pointer to the free memory
            allocatedBytes += bytesToAllocate;
            return result;
        }

        /// @brief If the total number of bytes, passed to this method, equals the total number of bytes passed to allocate(),
        ///        the whole memory block is freed
        /// @param bytesToDeallocate 
        void deallocate(std::size_t bytesToDeallocate) {
            deallocatedBytes += bytesToDeallocate;
            if (deallocatedBytes > allocatedBytes) {
                throw std::invalid_argument("Unable to deallocate more memory than it was allocated.");
            }
            if (deallocatedBytes != 0 && deallocatedBytes == allocatedBytes) {
                free(allocatedMemoryPtr);
                
                //reset the pointer and the counters => the pool can be used again
                allocatedMemoryPtr = nullptr;
                allocatedBytes = 0;
                deallocatedBytes = 0;
            }
        }
    };

};