#include "linear.hpp"

namespace lasd {

/* ************************************************************************** */

// Comparison operators (Linear Container)
template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> & other) const noexcept {
  if (size != other.size)
    return false;
  for (ulong i = 0; i < size; ++i) {
    if (operator[](i) != other[i]) 
      return false;
  }
  return true;
}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer<Data> & other) const noexcept {
  return !(*this == other);
} 

/* ************************************************************************** */

// Specific member functions (LinearContainer)
template <typename Data>
const Data & LinearContainer<Data>::Front() const {
  return operator[](0);
}

template <typename Data>
Data & LinearContainer<Data>::Front() {
  return operator[](0);
}

template <typename Data>
const Data & LinearContainer<Data>::Back() const {
  return operator[](size - 1);
}

template <typename Data>
Data & LinearContainer<Data>::Back() {
  return operator[](size - 1);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from TraversableContainer)
template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PreOrderTraversableContainer)
template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const {
  for (ulong i = 0; i < size; i++) {
    Data tmp = operator[](i); 
    fun(tmp);
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PostOrderTraversableContainer)
template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const {
  ulong i = size;
  while(i > 0) {
    i--;
    Data tmp = operator[](i);
    fun(tmp);
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from MappableContainer)
template <typename Data>
void LinearContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PreOrderMappableContainer)
template <typename Data>
void LinearContainer<Data>::PreOrderMap(MapFun fun) {
  for (ulong i = 0; i < size; i++) {
    Data tmp = operator[](i);
    fun(tmp); 
  }
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from PostOrderMappableContainer)
template <typename Data>
void LinearContainer<Data>::PostOrderMap(MapFun fun) {
  ulong i = size;
  while (i > 0) {
    i--;
    Data tmp = operator[](i);
    fun(tmp);
  } 
}

/* ************************************************************************** */

// Specific member functions (LinearContainer) (inherited from SortableContainer)
template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept {
  QuickSort(0, this->size-1);
}

template <typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r) noexcept {
  if (p < r) {
    ulong q = Partition(p, r);
    QuickSort(p, q);
    QuickSort(q+1, r);
  }
}

template <typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r) noexcept {
  Data x = operator[](p);
  ulong i = p - 1;
  ulong j = r + 1;
  do {
    do { j--; } while (x < operator[](j));
    do { i++; } while (x > operator[](i));
    if (i < j)
      std::swap(operator[](i), operator[](j));
  } while (i < j);

  return j;
}

/* ************************************************************************** */
}
