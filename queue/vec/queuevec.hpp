
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

#include "../queue.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

template <typename Data>
class QueueVec : virtual public Queue<Data>, virtual public Vector<Data> {

private:

protected:
  using Vector<Data>::size;
  using Vector<Data>::Elements;
  ulong tail = 0;
  ulong head = 0;

public:
  // Default constructor
  QueueVec();
  
  /* ************************************************************************** */

  // Specific constructor
  QueueVec(const TraversableContainer<Data> &);
  QueueVec(MappableContainer<Data> &&);

  /* ************************************************************************** */

  // Copy constructor
  QueueVec(const QueueVec<Data> &);
  // Move constructor
  QueueVec(QueueVec<Data> &&) noexcept;

  /* ************************************************************************** */

  // Destructor
  virtual ~QueueVec() = default;

  /* ************************************************************************** */

  // Copy assignment
  QueueVec<Data> & operator=(const QueueVec<Data> &);
  // Move assignment
  QueueVec<Data> & operator=(QueueVec<Data> &&) noexcept;

  /* ************************************************************************** */

  // Comparison operators
  bool operator==(const QueueVec<Data> &) const noexcept;
  bool operator!=(const QueueVec<Data> &) const noexcept;

  /* ************************************************************************** */

  // Specific member functions (inherited from Queue)
  const Data& Head() const override; // non-mutable version; must throw std::length_error when empty
  Data& Head() override; // mutable version; must throw std::length_error when empty
  void Dequeue() override; // must throw std::length_error when empty
  Data HeadNDequeue() override; // must throw std::length_error when empty
  void Enqueue(const Data &) override; // copy of the value
  void Enqueue(Data &&) override; // move of the value

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  bool Empty() const noexcept override;
  ulong Size() const noexcept override;

  /* ************************************************************************ */
  
  // Specific member function (inherited from ClearableContainer)
  void Clear() noexcept override;

protected:
  // Auxiliary member functions
  void Expand() noexcept;
  void Reduce() noexcept;
  void Resize(ulong, ulong);
};

}

#include "queuevec.cpp"

#endif
