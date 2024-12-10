#include "dictionary.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & con) {
  bool all = true;
  con.Traverse(
    [this, &all](const Data& data) { all &= Insert(data); }
  );
  return all;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && con) {
  bool all = true;
  con.Map(
    [this, &all](Data& data) { all &= Insert(std::move(data)); }
  );
  return all;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & con) {
  bool all = true;
  con.Traverse(
    [this, &all](const Data& data) { all &= Remove(data); }
  ); 
  return all; 
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> && con) {
  bool some = false;
  con.Map(
    [this, &some](const Data & data) { some |= Insert(std::move(data)); }
  );
  return some;
}

template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & con) {
  bool some = false;
  con.Traverse(
    [this, &some](const Data & data) { some |= Insert(data); }
  );
  return some;
}

template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & con) {
  bool some = false;
  con.Traverse(
    [this, &some](const Data & data) { some |= Remove(data); }
  );
  return some;
}

/* ************************************************************************** */

}
