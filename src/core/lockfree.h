// This file is part of The Forgotten Server.
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef FS_LOCKFREE_H_8C707AEB7C7235A2FBC5D4EDDF03B008
#define FS_LOCKFREE_H_8C707AEB7C7235A2FBC5D4EDDF03B008

#if _MSC_FULL_VER >= 190023918 // Workaround for VS2015 Update 2. Boost.Lockfree is a header-only library, so this should be safe to do.
#define _ENABLE_ATOMIC_ALIGNMENT_FIX
#endif

#include <boost/lockfree/stack.hpp>

template <typename T, size_t CAPACITY>
class LockfreePoolingAllocator : public std::allocator<T>
{
	public:
		template <typename U>
		explicit constexpr LockfreePoolingAllocator(const U&) {}
		typedef T value_type;

		T* allocate(size_t) const {
			T* p; // NOTE: p doesn't have to be initialized
			if (!getFreeList().pop(p)) {
				//Acquire memory without calling the constructor of T
				p = static_cast<T*>(operator new (sizeof(T)));
			}
			return p;
		}

		void deallocate(T* p, size_t) const {
			if (!getFreeList().bounded_push(p)) {
				//Release memory without calling the destructor of T
				//(it has already been called at this point)
				operator delete(p);
			}
		}

	private:
		typedef boost::lockfree::stack<T*, boost::lockfree::capacity<CAPACITY>> FreeList;
		static FreeList& getFreeList() {
			static FreeList freeList;
			return freeList;
		}
};

#endif
