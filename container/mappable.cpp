#include "mappable.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific member functions (MappableContainer) (inherited form Container)
template <typename Data>
ulong MappableContainer<Data>::Size() const noexcept {
  return size;
}

/* ************************************************************************** */

// Specific member functions (PreOrderMappableContainer)
template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (PostOrderMappableContainer)
template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun) {
  PostOrderMap(fun);  
}

/* ************************************************************************** */

// Specific member functions (InOrderMappableContainer)
template <typename Data>
void InOrderMappableContainer<Data>::Map(MapFun fun) {
  InOrderMap(fun);  
}
  
/* ************************************************************************** */

// Specific member functions (BreadthMappableContainer)
template <typename Data>
void BreadthMappableContainer<Data>::Map(MapFun fun) {
  BreadthMap(fun);
}

/* ************************************************************************** */

}
