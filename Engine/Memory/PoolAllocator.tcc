template <typename T, size_t BlockSize>
PoolAllocator<T, BlockSize>::PoolAllocator() :freeChunks(nullptr), usedBlocks(nullptr) {

}

template <typename T, size_t BlockSize>
PoolAllocator<T, BlockSize>::PoolAllocator(const PoolAllocator<T, BlockSize> &other)  {
  if (this != &other) {
    freeChunks = nullptr;
    usedBlocks = nullptr;
  }
}

template <typename T, size_t BlockSize>
PoolAllocator<T, BlockSize> PoolAllocator<T, BlockSize>::operator=(const PoolAllocator<T, BlockSize> &other) {
  if (this != &other) {
    freeChunks = nullptr;
    usedBlocks = nullptr;
  }
  return this;
}

template <typename T, size_t BlockSize>
typename PoolAllocator<T, BlockSize>::pointer PoolAllocator<T, BlockSize>::allocate(size_type n) {
  if (freeChunks) {
    // break off first free chunk
    pointer temp = (pointer)(freeChunks);
    // make free chunks point to next chunk
    freeChunks = (byte *)*((uintptr_t*)freeChunks);
    // return chunk
    return temp;
  }
  else {
    // allocate a new block
    allocateBlock();
    // break off first free chunk
    pointer temp = (pointer)(freeChunks);
    // make free chunks point to next chunk
    freeChunks = (byte *) *((uintptr_t*)freeChunks);
    // return chunk
    return temp;
  }
}

template <typename T, size_t BlockSize>
void PoolAllocator<T, BlockSize>::allocateBlock() {
  // Allocate new block, and point the block to the previous block
  Block *newBlock = new Block;
  newBlock->data = (byte *) operator new(BlockSize);
  newBlock->next = usedBlocks;
  usedBlocks = newBlock;
  // split the block into chunks of size T, linking them together
  for (auto i = 0; i < BlockSize; i += sizeof(T)) {
    *((uintptr_t*)(newBlock->data + i)) = (uintptr_t)newBlock->data + i + sizeof(T);
    if (i + sizeof(T) >= BlockSize) *((uintptr_t*)(newBlock->data + i)) = (uintptr_t)nullptr;
  }
  // point freeChunks to the new block
  freeChunks = newBlock->data;
}

template <typename T, size_t BlockSize>
void PoolAllocator<T, BlockSize>::deallocate(pointer ptr, size_type n) {
  if (ptr) {
    // point chunk to front of free chunks
    *((uintptr_t*)ptr) = (uintptr_t)freeChunks;
    // point free chunks to the new chunk
    freeChunks = (byte *)ptr;
  }
}

template<typename T, size_t BlockSize>
template<typename U, class... Args>
void PoolAllocator<T, BlockSize>::construct(U *ptr, Args&&... args) {
  // Construct new object at pointer
  new (ptr) U(std::forward<Args>(args)...);
}

template<typename T, size_t BlockSize>
template<typename U>
void PoolAllocator<T, BlockSize>::destroy(U *ptr) {
  // Deconstruct object at pointer
  ptr->~U();
}

template <typename T, size_t BlockSize>
bool PoolAllocator<T, BlockSize>::operator==(const PoolAllocator<T, BlockSize> &a) {
  return this.usedBlocks.data == a.usedBlocks.data;
}

template <typename T, size_t BlockSize>
bool PoolAllocator<T, BlockSize>::operator!=(const PoolAllocator<T, BlockSize> &a) {
  return this.usedBlocks.data != a.usedBlocks.data;
}