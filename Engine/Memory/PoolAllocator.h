#include "../Common/Includes.h"

#ifndef POOLALLOCATOR
#define POOLALLOCATOR

template <typename T, size_t BlockSize = 4096>
class PoolAllocator {
public:
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using value_type = T;

  PoolAllocator();
  // These are implemented because of the standard, they don't work. They return an empty allocator.
  PoolAllocator(const PoolAllocator &);
  PoolAllocator<T, BlockSize> operator=(const PoolAllocator<T, BlockSize> &);

  template<typename U, size_t BlockSize>
  PoolAllocator(const PoolAllocator<U, BlockSize> &):PoolAllocator() {};

  template<typename U>
  struct rebind { using other = PoolAllocator<U>; };

  // Allocates the memory but does not construct the objects
  pointer allocate(size_type n);
  void deallocate(pointer, size_type n);

  // constructs and destroys the objects
  template<typename U, class... Args>
  void construct(U*, Args&&...);
  template<typename U>
  void destroy(U*);
  
  bool operator==(const PoolAllocator<T, BlockSize> &);
  bool operator!=(const PoolAllocator<T, BlockSize> &);

private:
  struct Block {
    byte *data;
    Block *next;
  };
  byte *freeChunks;
  Block *usedBlocks;

  void allocateBlock();
};

#include "PoolAllocator.tcc"

#endif // !POOLALLOCATOR

