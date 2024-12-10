
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  ulong operator()(const Data & element) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : virtual public ResizableContainer, virtual public DictionaryContainer<Data> {

private:

protected:

  using Container::size;

  ulong a;
  ulong b;
  const ulong PRIME = 12582917;
  const ulong DEFAULT_SIZE = 97; 
  ulong tableSize = DEFAULT_SIZE;

  std::default_random_engine gen = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<ulong> genA = std::uniform_int_distribution<ulong>(1, PRIME - 1);
  std::uniform_int_distribution<ulong> genB = std::uniform_int_distribution<ulong>(0, PRIME - 1);

  /* ************************************************************************ */

  // Default constructor
  HashTable();

  /* ************************************************************************ */

  //Copy constructor
  HashTable(const HashTable &);
  //Move constructor
  HashTable(HashTable &&) noexcept;

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable & operator=(const HashTable &); 
  // Move assignment
  HashTable & operator=(HashTable &&) noexcept; 

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable &) const noexcept;
  bool operator!=(HashTable &&) const noexcept; 

protected:

  // Auxiliary member functions
  ulong HashKey(ulong key) const noexcept;

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
