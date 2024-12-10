
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, virtual public List<Data> {

private:

protected:

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const TraversableContainer<Data> &);
  StackLst(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst &);
  // Move constructor
  StackLst(StackLst &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackLst & operator=(const StackLst &);
  // Move assignment
  StackLst & operator=(StackLst &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst &) const noexcept;
  bool operator!=(const StackLst &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)
  const Data & Top() const override; // non-mutable version; must throw std::length_error when empty
  Data & Top() override; // non-mutable version; must throw std::length_error when empty
  void Pop() override; // must throw std::length_error when empty
  Data TopNPop() override; // must throw std::length_error when empty
  void Push(const Data &) override; // copy of the value
  void Push(Data &&) override; // move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  using List<Data>::Clear; 

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
