
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

#include <stdexcept> 
#include <string>     

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector : virtual public ResizableContainer, virtual public LinearContainer<Data> {

private:

protected:
  using Container::size;

public:
  Data * Elements = nullptr;
  
  /* ************************************************************************ */

  // Default constructor
  Vector() = default;

  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong); 
  Vector(const TraversableContainer<Data> &);
  Vector(MappableContainer<Data> &&); 
  
  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector &);
  // Move constructor
  Vector(Vector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector & operator=(const Vector &);
  // Move assignment
  Vector & operator=(Vector &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Vector &) const noexcept;
  bool operator!=(const Vector &) const noexcept;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;

  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  void Resize(ulong) override;


  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
  const Data & operator[](const ulong) const override; // (NonMutable) must throw std::out_of_range when out of range
  Data & operator[](const ulong) override; // (Mutable) must throw std::out_of_range when out of range

  const Data & Front() const override; // (NonMutable) must throw std::length_error when empty
  Data & Front() override; // (Mutable) must throw std::length_error when empty

  const Data & Back() const override; // (NonMutable) must throw std::length_error when empty
  Data & Back() override; // (Mutable) must throw std::length_error when empty
  
  /* ************************************************************************** */

  // Specific member function (inherited from Container)
  bool Empty() const noexcept override; 
  ulong Size() const noexcept override;
};

/* ************************************************************************** */

template <typename Data>
class SortableVector : virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {

private:
  using Container::size;

protected:

public:
  using Vector<Data>::operator[];
  
  // Default constructor
  SortableVector() = default;  

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(const ulong); // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data> &&); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector &);
  // Move constructor
  SortableVector(SortableVector &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableVector & operator=(const SortableVector &);
  // Move assignment
  SortableVector & operator=(SortableVector &&) noexcept;

  /* ************************************************************************** */

  // Specific memeber functions (inherited from Container)
  bool Empty() const noexcept override; 
  ulong Size() const noexcept override; 
};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif