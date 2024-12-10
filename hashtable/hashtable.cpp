namespace lasd {

/* ************************************************************************** */

template <>
class Hashable<int> {
public:
  ulong operator()(const int & data) const noexcept {
    return data * data;
  }
};

template<>
class Hashable<std::string> {
public:
  ulong operator()(const std::string & data) const noexcept {
    ulong accumulator = 0;
    for(ulong i = 0; i < data.length(); i++) 
      accumulator += data[i] * i;
    return accumulator;
  }
};

template<>
class Hashable<double> {
public:
  ulong operator()(const double& data) const noexcept {
    ulong integer = floor(data);
    ulong fractional = pow(2, 24) * (data - integer);
    return (integer * fractional);
  }
};


/* ************************************************************************** */
/* ************************************************************************** */

// Default constructor (HashTable)
template <typename Data>
HashTable<Data>::HashTable() {
  a = (genA(gen) * 2) + 1;
  b = pow(2, std::ceil(log2(genB(gen))));
}

/* ************************************************************************** */

// Copy constructor (HashTable)
template <typename Data>
HashTable<Data>::HashTable(const HashTable<Data> & other) {
  tableSize = other.tableSize;
  size = other.size;
  a = other.a;
  b = other.b;
}

// Move constructor (HashTable)
template <typename Data>
HashTable<Data>::HashTable(HashTable<Data> && other) noexcept {
  std::swap(tableSize, other.tableSize);
  std::swap(size, other.size);
  std::swap(a, other.a);
  std::swap(b, other.b);
}

/* ************************************************************************** */

// Copy assignment (HashTable)
template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(const HashTable<Data> & other) {
  tableSize = other.tableSize;
  size = other.size;
  a = other.a;
  b = other.b;
  return *this;
}

// Move assignment (HashTable)
template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(HashTable<Data> && other) noexcept {
  std::swap(tableSize, other.tableSize);
  std::swap(size, other.size);
  std::swap(a, other.a);
  std::swap(b, other.b);
  return *this;
}

/* ************************************************************************** */

// TODO Comparison operators (HashTable)

/* ************************************************************************** */

// Auxiliary member functions (HashTable)
template <typename Data>
ulong HashTable<Data>::HashKey(ulong key) const noexcept {
  return (a * key + b) % tableSize;
}

/* ************************************************************************** */

}
