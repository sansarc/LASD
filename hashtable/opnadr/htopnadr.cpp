namespace lasd {

/* ************************************************************************** */

// Default constructor (HashTableOpnAdr)
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr() {
  table = new Data[tableSize];
  flagsTable = new Flag[tableSize];
}

/* ************************************************************************** */

// Specific constructors (HashTableOpnAdr)
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize) {
  tableSize = std::pow(2, std::ceil(log2((newSize < DEFAULT_SIZE) ? DEFAULT_SIZE : newSize)));
  table = new Data[tableSize] {};
  flagsTable = new Flag[tableSize] {};
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data> & other) : HashTableOpnAdr(other.Size() * 2) {
  DictionaryContainer<Data>::InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, const TraversableContainer<Data> & other) : HashTableOpnAdr(newSize) {
  DictionaryContainer<Data>::InsertAll(other);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> && other) noexcept : HashTableOpnAdr(other.Size() * 2) {
  DictionaryContainer<Data>::InsertAll(std::move(other));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, MappableContainer<Data> && other) noexcept : HashTableOpnAdr(newSize) {
  DictionaryContainer<Data>::InsertAll(std::move(other));
}

/* ************************************************************************** */

// Copy constructor (HashTableOpnAdr)
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr & other) : HashTable<Data>(other) {
  table = new Data[tableSize] {};
  flagsTable = new Flag[tableSize] {};
  for (ulong i = 0; i < tableSize; i++) {
    table[i] = other.table[i];
    flagsTable[i] = other.flagsTable[i];
  }
}

// Move constructor (HashTableOpnAdr)
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr && other) noexcept : HashTable<Data>(std::move(other)) {
  std::swap(table, other.table);
  std::swap(flagsTable, other.flagsTable);
}

/* ************************************************************************** */

// Destructor (HashTableOpnAdr)
template <typename Data>
HashTableOpnAdr<Data>::~HashTableOpnAdr() {
  delete[] table;
  delete[] flagsTable;
}

/* ************************************************************************** */

// Copy assignment (HashTableOpnAdr) 
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr & other) {
  HashTable<Data>::operator=(other);
  delete[] table;
  delete[] flagsTable;
  table = new Data[tableSize] {};
  flagsTable = new Flag[tableSize] {};
  for (ulong i = 0; i < tableSize; i++) {
    table[i] = other.table[i];
    flagsTable[i] = other.flagsTable[i];
  }
  return *this;
}

// Move assignment (HashTableOpnAdr) 
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr && other) noexcept {
  HashTable<Data>::operator=(std::move(other));
  std::swap(table, other.table);
  std::swap(flagsTable, other.flagsTable);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (HashTableOpnAdr) 
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr & other) const noexcept {
  if (size != other.Size())
    return false;
  for (ulong i = 0; i < tableSize; i++) {
    if (flagsTable[i] == valid) {
      if (!other.Exists(table[i]))
        return false;
    }
  }
  return true;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (HashTableOpnAdr) (inherited from DictionaryContainer)  
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data & data) {
  ulong probeIndex = 0;
  if (size * 2 > tableSize)
    Resize(tableSize * 2);
  ulong index = FindEmpty(data, probeIndex);
  if (flagsTable[index] != valid) {
    table[index] = data;
    flagsTable[index] = valid;
    ++size;
    return !Remove(++probeIndex, data);
  }
  probeIndex = 0;
  return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data && data) {
  ulong probeIndex = 0;
  if (size * 2 >= tableSize)
    Resize(tableSize * 2);
  ulong index = FindEmpty(data, probeIndex);
  if (flagsTable[index] != valid) {
    table[index] = std::move(data);
    flagsTable[index] = valid;
    ++size;
    return !Remove(++probeIndex, data);
  }
  probeIndex = 0;
  return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data & data) {
  ulong probeIndex = 0;
  return Remove(probeIndex, data);
}

/* ************************************************************************** */

// Specific member functions (HashTableOpnAdr) (inherited from TestableContainer)  
template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data & data) const noexcept {
  ulong probeIndex = 0;
  ulong index = HashKey(Hashable<Data>()(data));
  return Find(index, probeIndex, data);
}

/* ************************************************************************** */

// Specific member functions (HashTableOpnAdr) (inherited from ResizableContainer)  
template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong newSize) {
  ulong tmpTableSize = (newSize <= DEFAULT_SIZE) ? DEFAULT_SIZE : std::pow(2, std::ceil(log2(newSize)));
  Data* tmpTable = new Data[tmpTableSize] {};
  Flag* tmpFlagsTable = new Flag[tmpTableSize] {};
  std::swap(tmpTableSize, tableSize);
  std::swap(tmpTable, table);
  std::swap(tmpFlagsTable, flagsTable);
  size = 0;
  for (ulong i = 0; i < tmpTableSize; i++) {
    if (tmpFlagsTable[i] == valid)
      Insert(tmpTable[i]);
  }
  delete[] tmpTable;
  delete[] tmpFlagsTable;
}

/* ************************************************************************** */

// Specific member functions (HashTableOpnAdr) (inherited from ClearableContainer)  
template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
  for (ulong i = 0; i < tableSize; i++)
    flagsTable[i] = dirty;
  size = 0;
}

/* ************************************************************************** */

// Auxiliary member functions (HashTableOpnAdr) 
template <typename Data> 
ulong HashTableOpnAdr<Data>::HashKey(const Data & key, ulong & probeIndex) const noexcept {
  ulong index = HashKey(Hashable<Data>()(key));
  return (index + tableSize + ((probeIndex * probeIndex) + probeIndex) / 2) % tableSize;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Find(ulong & index, ulong & probeIndex, const Data & data) const noexcept {
  ulong tmp_index = HashKey(data, probeIndex);
  ulong jumps = 0;
  do {
    if (jumps == tableSize - 1)
      return false;
    if ((table[tmp_index] == data) && (flagsTable[tmp_index] == valid)) {
      index = tmp_index;
      return true;
    }
    tmp_index = HashKey(data, ++probeIndex);
    jumps++;
  } while (!(flagsTable[tmp_index] == empty));
  return false;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data & data, ulong & probeIndex) const noexcept {
  ulong tmp_index = HashKey(data, probeIndex);
  while ((flagsTable[tmp_index] == valid) && (table[tmp_index] != data))
    tmp_index = HashKey(data, ++probeIndex);
  return tmp_index;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(ulong & probeIndex, const Data & key) noexcept {
  ulong tmp_index;
  if (Find(tmp_index, probeIndex, key)) {
    flagsTable[tmp_index] = dirty;
    size--;
    probeIndex = 0;
    if ((size < tableSize / 5) && (tableSize > DEFAULT_SIZE))
      Resize(tableSize / 2);
    return true;
  }
  probeIndex = 0;
  return false;
}

/* ************************************************************************** */

}
