#include "stackvec.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructor (StackVec)
template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data> & con) : Vector<Data>(con), index(size) {}

template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data> && con) : Vector<Data>(std::move(con)), index(size) {} 

/* ************************************************************************** */

// Copy constructor (StackVec)
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data> & other) : Vector<Data>(other), index(size) {}

// Move construtor (StackVec)
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data> && other) noexcept : Vector<Data>(std::move(other)) {
  std::swap(index, other.index);
}

/* ************************************************************************ */

// Copy assignment (StackVec)
template <typename Data>
StackVec<Data> & StackVec<Data>::operator=(const StackVec<Data> & other) {
  Vector<Data>::operator=(other);
  index = other.index;
  return *this;
}

// Move assignment (StackVec)
template <typename Data>
StackVec<Data> & StackVec<Data>::operator=(StackVec<Data> && other) noexcept {
  Vector<Data>::operator=(std::move(other));
  std::swap(index, other.index);
  return *this;
}

/* ************************************************************************ */

// Comparison operators (StackVec)
template <typename Data>
bool StackVec<Data>::operator==(const StackVec<Data> & other) const noexcept {
  if (index == other.index) {
    for (ulong i = 0; i < index; i++) {
      if (Elements[i] != other.Elements[i])
        return false;
    }
    return true;
  }
  return false;
}

template <typename Data>
bool StackVec<Data>::operator!=(const StackVec<Data> & other) const noexcept {
  return Vector<Data>::operator!=(other);
}

/* ************************************************************************ */

// Specific member functions (StackVec) (inherited from Stack)
template <typename Data>
const Data & StackVec<Data>::Top() const {
  if (index != 0) 
    return Elements[index - 1];
  else
    throw std::length_error("Stack is empty.");
}

template <typename Data>
Data & StackVec<Data>::Top() {
  if (index != 0)
    return Elements[index - 1];
  else
    throw std::length_error("Stack is empty.");
}

template <typename Data>
void StackVec<Data>::Pop() {
  if (index != 0) {
    Reduce();
    index--;
  } else 
    throw std::length_error("Stack is empty.");
}

template <typename Data>
Data StackVec<Data>::TopNPop() {
  if (index != 0) {
    Data top = std::move(Top());
    Pop();
    return top; 
  } else
    throw std::length_error("Stack is empty.");
}

template <typename Data>
void StackVec<Data>::Push(const Data & data) {
  Expand();
  Elements[index] = data;
  index++;
} 

template <typename Data>
void StackVec<Data>::Push(Data && data) {
  Expand();
  Elements[index] = std::move(data);
  index++;
}

/* ************************************************************************ */

// Specific member functions (StackVec) (inherited from Container)
template <typename Data>
bool StackVec<Data>::Empty() const noexcept {
  return (index == 0);
}

template <typename Data>
ulong StackVec<Data>::Size() const noexcept {
  return index;
}

/* ************************************************************************ */

// Specific member functions (StackVec) (inherited from ClearableContainer)
template <typename Data>
void StackVec<Data>::Clear() {
  index = 0;
  Vector<Data>::Resize(1); 
}

/* ************************************************************************ */

// Auxiliary member functions (StackVec)
template <typename Data>
void StackVec<Data>::Expand() {
  if (index == size)
    Vector<Data>::Resize(size * 2);
}

template <typename Data>
void StackVec<Data>::Reduce() {
  if (index == size/4)
    Vector<Data>::Resize(size / 2);
}


/* ************************************************************************ */

}