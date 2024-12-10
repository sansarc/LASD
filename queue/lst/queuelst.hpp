
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>, virtual public List<Data> {

private:

protected:

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const TraversableContainer<Data> &); // A stack obtained from a TraversableContainer
  QueueLst(MappableContainer<Data> &&); // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst &);
  // Move constructor
  QueueLst(QueueLst &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueLst & operator=(const QueueLst &);
  // Move assignment
  QueueLst & operator=(QueueLst &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst &) const noexcept;
  bool operator!=(const QueueLst &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override; // non-mutable version; must throw std::length_error when empty
  Data & Head() override; // mutable version; must throw std::length_error when empty
  void Dequeue() override; // must throw std::length_error when empty
  Data HeadNDequeue() override; // must throw std::length_error when empty
  void Enqueue(const Data &) override; // copy of the value
  void Enqueue(Data &&) override; // move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  using List<Data>::Clear;

protected:
  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
