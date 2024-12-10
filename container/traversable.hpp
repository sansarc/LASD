
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TraversableContainer : virtual public TestableContainer<Data> {

private:

protected:
  using Container::size;

public:

  // Destructor
  virtual ~TraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  TraversableContainer & operator=(const TraversableContainer &) = delete;
  // Move assignment
  TraversableContainer & operator=(const TraversableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const TraversableContainer &) const noexcept = delete;
  bool operator!=(const TraversableContainer &) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function
  using TraverseFun = std::function<void(const Data &)>;
  virtual void Traverse(TraverseFun) const = 0;
   
  template <typename Accumulator>
  using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;
  template <typename Accumulator>
  Accumulator Fold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TestableContainer)
  bool Exists(const Data &) const noexcept override;  

  /* ************************************************************************ */
  
  // Specific member functions (inherited from Container)
  ulong Size() const noexcept override; 
};

/* ************************************************************************** */

template <typename Data>
class PreOrderTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:
  // Destructor
  virtual ~PreOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PreOrderTraversableContainer & operator=(const PreOrderTraversableContainer &) = delete;
  // Move assignment
  PreOrderTraversableContainer & operator=(PreOrderTraversableContainer &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PreOrderTraversableContainer &) const noexcept = delete;
  bool operator!=(const PreOrderTraversableContainer &) const noexcept = delete;  

  /* ************************************************************************ */

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void PreOrderTraverse(TraverseFun) const = 0;
   
  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;  
  template <typename Accumulator>
  Accumulator PreOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun) const override;
};

/* ************************************************************************** */

template <typename Data>
class PostOrderTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:
  // Destructor
  virtual ~PostOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  PostOrderTraversableContainer & operator=(const PostOrderTraversableContainer &);
  // Move assignment
  PostOrderTraversableContainer & operator=(PostOrderTraversableContainer &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PostOrderTraversableContainer &) const noexcept;
  bool operator!=(const PostOrderTraversableContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void PostOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;
  template <typename Accumulator>
  Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun) const override;
};

/* ************************************************************************** */

template <typename Data>
class InOrderTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:
  // Destructor
  virtual ~InOrderTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  InOrderTraversableContainer & operator=(const InOrderTraversableContainer &);
  // Move assignment
  InOrderTraversableContainer & operator=(InOrderTraversableContainer &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const InOrderTraversableContainer &) const noexcept;
  bool operator!=(const InOrderTraversableContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member function
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void InOrderTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;
  template <typename Accumulator>
  Accumulator InOrderFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun) const override;
};

/* ************************************************************************** */

template <typename Data>
class BreadthTraversableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:
  // Destructor
  virtual ~BreadthTraversableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthTraversableContainer & operator=(const BreadthTraversableContainer &) = delete;
  // Move assignment
  BreadthTraversableContainer & operator=(BreadthTraversableContainer &&) noexcept = delete;
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthTraversableContainer &) const noexcept;
  bool operator!=(const BreadthTraversableContainer &) const noexcept;

  /* ************************************************************************ */

  // Specific member function 
  using typename TraversableContainer<Data>::TraverseFun;
  virtual void BreadthTraverse(TraverseFun) const = 0;

  template <typename Accumulator>
  using FoldFun = typename TraversableContainer<Data>::FoldFun<Accumulator>;
  template <typename Accumulator>
  Accumulator BreadthFold(FoldFun<Accumulator>, Accumulator) const;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)
  void Traverse(TraverseFun) const override;
};

/* ************************************************************************** */

}

#include "traversable.cpp"

#endif