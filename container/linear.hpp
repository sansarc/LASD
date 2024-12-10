
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer : virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data> {

private:

protected:
  using Container::size;

public:
  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer & operator=(const LinearContainer &) = delete;
  // Move assignment
  LinearContainer & operator=(LinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const LinearContainer &) const noexcept;
  bool operator!=(const LinearContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  virtual const Data & operator[](const ulong) const = 0; // non-mutable version; concrete function must throw std::out_of_range when out of range
  virtual Data & operator[](const ulong) = 0; // mutable version; concrete function must throw std::out_of_range when out of range

  virtual const Data & Front() const; // non-mutable version; concrete function must throw std::length_error when empty
  virtual Data & Front(); // mutable version; concrete function must throw std::length_error when empty
  virtual const Data & Back() const; // non-mutable version; concrete function must throw std::length_error when empty
  virtual Data & Back(); // mutable version; concrete function must throw std::length_error when empty

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)
  void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)
  void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)
  using typename MappableContainer<Data>::MapFun;
  void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)
  void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)
  void PostOrderMap(MapFun) override;
};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer : virtual public LinearContainer<Data> {

private:

protected:
  using Container::size;
  using LinearContainer<Data>::operator[];

public:
  // Destructor
  virtual ~SortableLinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer & operator=(const SortableLinearContainer &) = delete;
  // Move assignment
  SortableLinearContainer & operator=(SortableLinearContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const SortableLinearContainer &) const noexcept;
  bool operator!=(const SortableLinearContainer &) const noexcept; 

  /* ************************************************************************ */

  // Specific member function
  virtual void Sort() noexcept;

protected:
  // Auxiliary member functions
  void QuickSort(ulong p, ulong r) noexcept;
  ulong Partition(ulong p, ulong r) noexcept;
};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif