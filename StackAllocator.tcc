template<typename T, size_t BlockSize>
StackAllocator<T, BlockSize>::StackAllocator():data(nullptr), stackPointer(0) {

}

template<typename T, size_t BlockSize>
StackAllocator<T, BlockSize>::StackAllocator(const StackAllocator &other) {
  if (this != &other) {
    data = nullptr;
    stackPointer = 0;
  }
}

template<typename T, size_t BlockSize>
StackAllocator<T, BlockSize> StackAllocator<T, BlockSize>::operator=(const StackAllocator<T, BlockSize> &) {
  if (this != &other) {
    data = nullptr;
    stackPointer = 0;
  }
  return this;
}

template<typename T, size_t BlockSize>
typename StackAllocator<T, BlockSize>::pointer StackAllocator<T, BlockSize>::allocate(size_type n) {
  if (stackPointer < BlockSize) {
    if (data) {
      return &data[stackPointer++];
    }
    else {
      data = (pointer) operator new (BlockSize);
      return &data[stackPointer++];
    }
  }
  else return nullptr;
}

template<typename T, size_t BlockSize>
void StackAllocator<T, BlockSize>::deallocate(pointer, size_type n) {
  stackPointer--;
}

template<typename T, size_t BlockSize>
template<typename U, class... Args>
void StackAllocator<T, BlockSize>::construct(U* ptr, Args&&... args) {
  new (ptr) U(std::forward<Args>(args)...);
}

template<typename T, size_t BlockSize>
template<typename U>
void StackAllocator<T, BlockSize>::destroy(U* ptr) {
  ptr->~U();
}

template<typename T, size_t BlockSize>
bool StackAllocator<T, BlockSize>::operator==(const StackAllocator<T, BlockSize> &other) {
  return (data == other.data && stackPointer == other.stackPointer);
}

template<typename T, size_t BlockSize>
bool StackAllocator<T, BlockSize>::operator!=(const StackAllocator<T, BlockSize> &) {
  return (data != other.data && stackPointer != other.stackPointer);
}