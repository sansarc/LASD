
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, virtual public Vector<Data> {

private:

protected:
  using Vector<Data>::size;
  using Vector<Data>::Elements;
  ulong index = 0;

public:
  // Default constructor
  StackVec() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const TraversableContainer<Data> &);
  StackVec(MappableContainer<Data> &&);

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec &);
  // Move constructor
  StackVec(StackVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec & operator=(const StackVec &);
  // Move assignment
  StackVec & operator=(StackVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec &) const noexcept;
  bool operator!=(const StackVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override; // non-mutable version; must throw std::length_error when empty
  Data & Top() override; // non-mutable version; must throw std::length_error when empty
  void Pop() override; // must throw std::length_error when empty
  Data TopNPop() override; // must throw std::length_error when empty
  void Push(const Data &) override; // copy of the value
  void Push(Data &&) override; // move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  bool Empty() const noexcept override;
  ulong Size() const noexcept override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;

protected:
  // Auxiliary functions
  void Expand();
  void Reduce();
};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif