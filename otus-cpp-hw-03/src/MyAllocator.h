#pragma once

#include <memory>

namespace Homework {

	/// @brief A custom memory allocator.
	/// @tparam T 					- a type of element for which memory is allocated
	/// @tparam MemoryPoolStrategy 	- a strategy which defines how memory is allocated. Possible values: FixedPoolStrategy, DynamicPoolStrategy.
	/// @tparam numberOfElements 	- a number of elements which can be placed in a single allocated memory block
	template<typename T, std::size_t numberOfElements, class MemoryPoolStrategy>
	class MyAllocator {
	private:
		std::shared_ptr<MemoryPoolStrategy> memoryPool = nullptr;

	public:
		using value_type = T;

		template<typename U>
		struct rebind {
			using other = MyAllocator<U, numberOfElements, MemoryPoolStrategy>;
		};

		MyAllocator() noexcept = default;

		MyAllocator(MyAllocator& other) noexcept : memoryPool(other.memoryPool) { }

		template <typename U>
		MyAllocator(const MyAllocator<U, numberOfElements, MemoryPoolStrategy>&) noexcept { }

		MyAllocator(MyAllocator&& other) noexcept {
			memoryPool = other.memoryPool;
			other.memoryPool = nullptr;
		}

		~MyAllocator() noexcept = default;

		MyAllocator& operator= (MyAllocator& other) noexcept {
			memoryPool = other.memoryPool;
			return *this;
		}

		MyAllocator& operator= (MyAllocator&& other) noexcept {
			memoryPool = other.memoryPool;
			other.memoryPool = nullptr;
			return *this;
		}

		T* allocate(std::size_t n) {
			if (memoryPool == nullptr) {
				memoryPool = std::make_shared<MemoryPoolStrategy>(sizeof(T) * numberOfElements);
			}
			char* p = memoryPool->allocate(sizeof(T) * n);
			return reinterpret_cast<T*>(p);
		}

		void deallocate(T* p, std::size_t n) {
			if (memoryPool != nullptr) {
				memoryPool->deallocate(n);
			}
		}

		friend bool operator==(const MyAllocator<T, numberOfElements, MemoryPoolStrategy>& a, const MyAllocator<T, numberOfElements, MemoryPoolStrategy>& b) {
			//two allocators equals only if they points to the same pool
			return a.memoryPool == b.memoryPool;
		}

		friend bool operator!=(const MyAllocator<T, numberOfElements, MemoryPoolStrategy>& a, const MyAllocator<T, numberOfElements, MemoryPoolStrategy>& b) {
			return !(a == b);
		}
	};
};