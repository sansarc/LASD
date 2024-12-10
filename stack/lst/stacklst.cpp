#include "stacklst.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructor (StackLst)
template <typename Data>
StackLst<Data>::StackLst(const TraversableContainer<Data> & con) : List<Data>(con) {}

template <typename Data>
StackLst<Data>::StackLst(MappableContainer<Data> && con) : List<Data>(std::move(con)) {} 

/* ************************************************************************** */

// Copy constructor (StackLst)
template <typename Data>
StackLst<Data>::StackLst(const StackLst<Data> & other) : List<Data>(other) {}

// Move constructor (StackLst)
template <typename Data>
StackLst<Data>::StackLst(StackLst<Data> && other) noexcept : List<Data>(std::move(other)) {}

/* ************************************************************************** */

// Copy assignment (StackLst)
template <typename Data>
StackLst<Data> & StackLst<Data>::operator=(const StackLst<Data> & other) {
  List<Data>::operator=(other);
  return *this;
}

// Move assignment (StackLst)
template <typename Data>
StackLst<Data> & StackLst<Data>::operator=(StackLst<Data> && other) noexcept {
  List<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Comparison operators (StackLst)
template <typename Data>
bool StackLst<Data>::operator==(const StackLst<Data> & other) const noexcept {
  return List<Data>::operator==(other);
}

template <typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data> & other) const noexcept {
  return List<Data>::operator!=(other);
}

/* ************************************************************************** */

// Specific member functions (StackLst) (inherited from Stack)
template <typename Data>
const Data & StackLst<Data>::Top() const {
  return List<Data>::Front();
}

template <typename Data>
Data & StackLst<Data>::Top() {
  return List<Data>::Front();
}

template <typename Data>
void StackLst<Data>::Pop() {
  return List<Data>::RemoveFromFront();
}

template <typename Data>
Data StackLst<Data>::TopNPop() {
  return List<Data>::FrontNRemove();
}

template <typename Data>
void StackLst<Data>::Push(const Data & data) {
  return List<Data>::InsertAtFront(data);
}

template <typename Data>
void StackLst<Data>::Push(Data && data) {
  return List<Data>::InsertAtFront(data);
}

/* ************************************************************************** */

}