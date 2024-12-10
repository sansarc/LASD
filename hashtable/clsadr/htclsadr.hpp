
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : virtual public HashTable<Data> {

private:

protected:

  using Container::size;
  using HashTable<Data>::DEFAULT_SIZE;
  using HashTable<Data>::HashKey;
  using HashTable<Data>::tableSize;
  BST<Data> * table = nullptr;  

public:

  /* ************************************************************************ */

  // Default constructor
  HashTableClsAdr();

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const ulong); // A hash table of a given size
  HashTableClsAdr(const TraversableContainer<Data> &); // A hash table obtained from a TraversableContainer
  HashTableClsAdr(const ulong, const TraversableContainer<Data> &); // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(MappableContainer<Data> &&) noexcept; // A hash table obtained from a MappableContainer
  HashTableClsAdr(const ulong, MappableContainer<Data> &&) noexcept; // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr &);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableClsAdr();

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr & operator=(const HashTableClsAdr &);

  // Move assignment
  HashTableClsAdr & operator=(HashTableClsAdr &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableClsAdr &) const noexcept;
  bool operator!=(const HashTableClsAdr &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data & value) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&& value) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data& value) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data& value) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)l
  void Resize(const ulong new_size) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)
  void Clear() override; // Override Container member

  /* ************************************************************************ */
  
  // Auxiliary member functions
  void Print() const {
    if (size == 0) {
      std::cout << "Hash Table is Empty." << std::endl;
      return;
    }
    std::cout << std::  endl; 
    for (ulong i = 0; i < tableSize; ++i) {
      std::cout << "Bucket " << i << ": ";
      if (!table[i].Empty()) 
        table[i].InOrderTraverse([](Data value) { std::cout << value << " - "; });
      else std::cout << "EMPTY";
      std::cout << std::endl;
    }
  }

  void PrintCompact() const {
    if (size == 0) {
      std::cout << "Hash Table is Empty." << std::endl;
      return;
    }
    std::cout << std::  endl; 
    for (ulong i = 0; i < tableSize; ++i) {
      if (!table[i].Empty()) {
        std::cout << "Bucket " << i << ": ";
        table[i].InOrderTraverse([](Data value) { std::cout << value << " - "; });
        std::cout << std::endl;
      }
    }
  }

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
