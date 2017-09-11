#include "Includes.h"

#ifndef STACKALLOCATOR
#define STACKALLOCATOR

template <typename T, size_t BlockSize = 4096>
class StackAllocator {
public:
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;
  using value_type = T;

  StackAllocator();
  // These are implemented because of the standard, they don't work. They return an empty allocator.
  StackAllocator(const StackAllocator &);
  StackAllocator<T, BlockSize> operator=(const StackAllocator<T, BlockSize> &);

  template<typename U, size_t BlockSize>
  StackAllocator(const StackAllocator<U, BlockSize> &) :StackAllocator() {};

  template<typename U>
  struct rebind { using other = StackAllocator<U>; };

  // Allocates the memory but does not construct the objects
  pointer allocate(size_type n);
  void deallocate(pointer, size_type n);

  // constructs and destroys the objects
  template<typename U, class... Args>
  void construct(U*, Args&&...);
  template<typename U>
  void destroy(U*);

  bool operator==(const StackAllocator<T, BlockSize> &);
  bool operator!=(const StackAllocator<T, BlockSize> &);

private:
  pointer data;
  size_t stackPointer;
};

#include "StackAllocator.tcc"

#endif // !STACKALLOCATOR
