#pragma once

#include <cstddef>
#include <stdexcept>

namespace Homework {

    /// @brief A memory pool which allocates a block of memory (a "chunk"). If more memory is needed, more "chunks" are allocated.
    class DynamicPoolStrategy {

    private:
        /// @brief Represents a single block of memory.
        struct Chunk {
            char* allocatedMemoryPtr;
            Chunk* next = nullptr;

            Chunk(std::size_t sizeBytes) {
                allocatedMemoryPtr = static_cast<char*>(malloc(sizeBytes));
                if (!allocatedMemoryPtr) {
                    std::bad_alloc();
                }
            }

            ~Chunk() {
                free(allocatedMemoryPtr);
            }
        };

        const std::size_t chunkSizeBytes;
        
        std::size_t allocatedBytes = 0;
        std::size_t deallocatedBytes = 0;
        std::size_t numberOfChunks = 0;

        Chunk* head = nullptr;
        Chunk* tail = nullptr;

        void deleteAllChunks() {
            Chunk* current = head;
            while (current != nullptr) {
                current = current->next;
                delete current;
            }
        }

        bool isNewChunkIsNeeded(std::size_t bytesToAllocate) const {
            return (allocatedBytes + bytesToAllocate) * chunkSizeBytes > numberOfChunks * chunkSizeBytes;
        }
    public:
        DynamicPoolStrategy(std::size_t _chunkSizeBytes) : chunkSizeBytes(_chunkSizeBytes) { }

        DynamicPoolStrategy(DynamicPoolStrategy&) = delete;
        DynamicPoolStrategy(DynamicPoolStrategy&&) = delete;
        DynamicPoolStrategy& operator=(DynamicPoolStrategy&) = delete;
        DynamicPoolStrategy& operator=(DynamicPoolStrategy&&) = delete;

        /// @brief Allocates the given number of bytes.
        /// @param bytesToAllocate 
        /// @return a pointer to the beginning of the allocated block of memory
        char* allocate(std::size_t bytesToAllocate) {
            if (bytesToAllocate == 0) {
                throw std::invalid_argument("Impossible to allocate 0 bytes!");
            }
            if (head == nullptr) { //there is no chunks => create a new one
                head = new Chunk(chunkSizeBytes);
                tail = head;
            } else if (isNewChunkIsNeeded(bytesToAllocate)) { //not enough memory => create a new chunk
                Chunk* chunk = new Chunk(chunkSizeBytes);
                tail->next = chunk;
                tail = chunk;
            }
            //caluclate a pointer to the unused memory
            char* result = tail->allocatedMemoryPtr + bytesToAllocate;
            allocatedBytes += bytesToAllocate;
            return result;
        }

        void deallocate(std::size_t bytesToDeallocate) {
            deallocatedBytes += bytesToDeallocate;
            if (deallocatedBytes > allocatedBytes) {
                throw std::invalid_argument("Unable to deallocate more memory than it was allocated.");
            }
            if (deallocatedBytes != 0 && deallocatedBytes == allocatedBytes) {
                deleteAllChunks();
            }
        }
    };

};