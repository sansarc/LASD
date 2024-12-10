#include "queuelst.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructors (QueueLst)
template <typename Data>
QueueLst<Data>::QueueLst(const TraversableContainer<Data> & con) : List<Data>(con) { }

template <typename Data>
QueueLst<Data>::QueueLst(MappableContainer<Data> && con) : List<Data>(std::move(con)) {}

/* ************************************************************************** */

// Copy constructor (QueueLst)
template <typename Data>
QueueLst<Data>::QueueLst(const QueueLst<Data> & other) : List<Data>(other) {}

// Move constructor (QueueLst)
template <typename Data>
QueueLst<Data>::QueueLst(QueueLst<Data> && other) noexcept : List<Data>(std::move(other)) {}

/* ************************************************************************** */

// Copy assignment (QueueLst)
template <typename Data>
QueueLst<Data> & QueueLst<Data>::operator=(const QueueLst<Data> & other) {
  List<Data>::operator=(other);
  return *this;
}

// Move assignment (QueueLst)
template <typename Data>
QueueLst<Data> & QueueLst<Data>::operator=(QueueLst<Data> && other) noexcept {
  List<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Comparison operators (QueueLst)
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data> & other) const noexcept {
  return List<Data>::operator==(other);
} 

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data> & other) const noexcept {
  return List<Data>::operator!=(other);
}

/* ************************************************************************** */

// Specific member functions (QueueLst) (inherited from Queue)
template <typename Data>
const Data & QueueLst<Data>::Head() const {
  return List<Data>::Front();
}

template <typename Data>
Data & QueueLst<Data>::Head() {
  return List<Data>::Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue() {
  return List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue() {
  return List<Data>::FrontNRemove();
}

template <typename Data>
void QueueLst<Data>::Enqueue(const Data & data) {
  return List<Data>::InsertAtBack(data);  
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data && data) {
  return List<Data>::InsertAtBack(data);
}

}
