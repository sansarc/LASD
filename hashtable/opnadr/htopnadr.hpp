
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include <bitset>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

private:

  enum Flag {
    empty,
    dirty,
    valid 
  };

protected:

  using Container::size;
  using HashTable<Data>::DEFAULT_SIZE;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::tableSize;

  Data * table = nullptr;
  Flag * flagsTable = nullptr;

public:

  // Default constructor
  HashTableOpnAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data> &); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(const ulong, const TraversableContainer<Data> &); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data> &&) noexcept; // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const ulong, MappableContainer<Data> &&) noexcept; // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr &);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr();

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr & operator=(const HashTableOpnAdr &);
  // Move assignment
  HashTableOpnAdr & operator=(HashTableOpnAdr &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr &) const noexcept;
  bool operator!=(const HashTableOpnAdr &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  virtual bool Insert(const Data &) override; // (Copy of the value)
  virtual bool Insert(Data &&) override; // (Move of the value)
  virtual bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  virtual bool Exists(const Data &) const noexcept override; 

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)
  virtual void Resize(const ulong); 

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  virtual void Clear() override;

  /* ************************************************************************ */

  // Auxiliary member functions
  void Print() const {
    if (size == 0) {
      std::cout << "Hash Table is Empty." << std::endl;
      return;
    }
    std::cout << std::endl; 
    for (ulong i = 0; i < tableSize; ++i) {
      std::cout << "Bucket " << i << ": ";
      switch (flagsTable[i]) {
        case empty:
          std::cout << "EMPTY";
          break;
        case dirty:
          std::cout << "DIRTY";
          break;
        case valid:
          std::cout << table[i];
          break;
      }
      std::cout << std::endl;
    }
  }

  void PrintCompact() const {
    if (size == 0) {
      std::cout << "Hash Table is Empty." << std::endl;
      return;
    }
    std::cout << std::endl; 
    for (ulong i = 0; i < tableSize; ++i) {
      switch (flagsTable[i]) {
        case empty: break;
        case dirty:
          std::cout << "Bucket: " << i << ": DIRTY" << std::endl;
          break;
        case valid:
          std::cout << "Bucket: " << i << ": " << table[i] << std::endl;
          break;
      }
    }

  }

protected:

  // Auxiliary member functions
  ulong HashKey(const Data &, ulong &) const noexcept;
  bool Find(ulong &, ulong &, const Data &) const noexcept;
  ulong FindEmpty(const Data &, ulong &) const noexcept;
  bool Remove(ulong &, const Data &) noexcept;

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif