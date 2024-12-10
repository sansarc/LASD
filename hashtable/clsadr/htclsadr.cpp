
namespace lasd {

/* ************************************************************************** */

// Default constructor (HashTableClsAdr)
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr() {
  table = new BST<Data>[tableSize] {};
}

/* ************************************************************************** */

// Specific constructors (HashTableClsAdr)
template <typename Data>
inline HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize) {
  tableSize = std::pow(2, std::ceil(log2((newSize <= DEFAULT_SIZE) ? DEFAULT_SIZE : newSize)));
  table = new BST<Data>[tableSize] {};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data> & other) : HashTableClsAdr(other.Size()) {
  DictionaryContainer<Data>::InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const TraversableContainer<Data> & other) : HashTableClsAdr(newSize) {
  DictionaryContainer<Data>::InsertAll(other);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data> && other) noexcept : HashTableClsAdr(other.Size()) {
  DictionaryContainer<Data>::InsertAll(std::move(other));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MappableContainer<Data> && other) noexcept : HashTableClsAdr(newSize) {
  DictionaryContainer<Data>::InsertAll(std::move(other));
}

/* ************************************************************************** */

// Copy constructor (HashTableClsAdr)
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data> & other) : HashTable<Data>(other) {
  table = new BST<Data>[tableSize] {};
  std::copy(other.table, other.table + tableSize, table);
}

// Move constructor (HashTableClsAdr)
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data> && other) noexcept : HashTable<Data>(std::move(other)) {
  std::swap(table, other.table);
}

/* ************************************************************************** */

// Destructor (HashTableClsAdr)
template <typename Data>
HashTableClsAdr<Data>::~HashTableClsAdr() {
  delete[] table;
}

/* ************************************************************************** */

// Copy assignment (HashTableClsAdr)
template <typename Data>
HashTableClsAdr<Data> & HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data> & other) {
  HashTable<Data>::operator=(other);
  delete[] table;
  table = new BST<Data>[tableSize] {};
  for(ulong i = 0; i < tableSize; i++) {
    table[i] = other.table[i];
  }
  return *this;
}

// Move assignment (HashTableClsAdr)
template <typename Data>
HashTableClsAdr<Data> & HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data> && other) noexcept {
  HashTable<Data>::operator=(std::move(other));
  std::swap(table, other.table);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (HashTableClsAdr)
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data> & other) const noexcept {
  bool equal = true;
  if(other.size != size) 
    return false;
  for(ulong i = 0; i < tableSize; i++) {
    table[i].Map([&other, &equal](const Data& dat) {
      if(!other.Exists(dat)) {
        equal = false;
        return;
      }
    });
    if(!equal) return false;
  }
  return true;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (HashTableClsAdr) (inherited from DictionaryContainer)
template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data & data) {
  bool insertion = false;
  ulong index = HashKey(Hashable<Data>()(data));
  insertion = table[index].Insert(data);
  if(insertion) size++;
  return insertion;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data && data) {
  bool insertion = false;
  ulong index = HashKey(Hashable<Data>()(std::move(data)));
  insertion = table[index].Insert(std::move(data));
  if(insertion) size++;
  return insertion;
}

template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data & data) {
  bool deletion = false;
  ulong index = HashKey(Hashable<Data>()(data));
  deletion = table[index].BST<Data>::Remove(data);
  if(deletion) size--;
  return deletion;
}

/* ************************************************************************** */

// Specific member functions (HashTableClsAdr) (inherited from TestableContainer)
template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data & data) const noexcept {
  ulong index = HashKey(Hashable<Data>()(data));
  if(table[index].Exists(data)) 
    return true;
  return false;
}

/* ************************************************************************** */

// Specific member functions (HashTableClsAdr) (inherited from ResizableContainer)
template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong newSize) {
  ulong newTableSize = (newSize <= DEFAULT_SIZE) ? DEFAULT_SIZE : std::pow(2, std::ceil(log2(newSize)));
  size = 0;
  BST<Data>* newTable = new BST<Data>[newTableSize] {};
  std::swap(newTable, table);
  std::swap(newTableSize, tableSize);
  for(ulong i = 0; i < newTableSize; i++)
    DictionaryContainer<Data>::InsertAll(newTable[i]);
  delete[] newTable;
}

/* ************************************************************************** */

// Specific member functions (HashTableClsAdr) (inherited from ClearableContainer)
template <typename Data>
void HashTableClsAdr<Data>::Clear() {
  delete[] table;
  table = new BST<Data>[tableSize] {};
  size = 0;
}

/* ************************************************************************** */

}
