
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include <unordered_set>

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>,
  virtual public PostOrderTraversableContainer<Data>,
  virtual public InOrderTraversableContainer<Data>,
  virtual public BreadthTraversableContainer<Data> {

private:

protected:
  using Container::size; 

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    bool operator!=(const Node &) const noexcept;

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node & operator=(const Node &) = delete;
    // Move assignment
    Node & operator=(Node &&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data & Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept = 0; // concrete function should not throw exceptions
    virtual bool HasLeftChild() const noexcept = 0; // concrete function should not throw exceptions
    virtual bool HasRightChild() const noexcept = 0; // concrete function should not throw exceptions

    virtual Node & LeftChild() const = 0;  // concrete function must throw std::out_of_range when not existent
    virtual Node & RightChild() const = 0;  // concrete function must throw std::out_of_range when not existent

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default; 

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree & operator=(const BinaryTree &) = delete;
  // Move assignment
  BinaryTree & operator=(BinaryTree &&) noexcept = delete;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree &) const noexcept;
  bool operator!=(const BinaryTree &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  virtual Node & Root() const = 0; // concrete function must throw std::length_error when empty

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

  // Specific member function (inherited from InOrderTraversableContainer)
  void InOrderTraverse(TraverseFun) const override;  

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  void BreadthTraverse(TraverseFun) const override;

protected:

  // Auxiliary member functions
  void PreOrderTraverse(const Node *, TraverseFun) const;
  void PostOrderTraverse(const Node *, TraverseFun) const;
  void InOrderTraverse(const Node *, TraverseFun) const;
  void BreadthTraverse(const Node *, TraverseFun) const;
};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree : virtual public ClearableContainer,
  virtual public BinaryTree<Data>,
  virtual public PreOrderMappableContainer<Data>,
  virtual public PostOrderMappableContainer<Data>,
  virtual public InOrderMappableContainer<Data>,
  virtual public BreadthMappableContainer<Data> {

private:

protected:
  using BinaryTree<Data>::size;

public:

  struct MutableNode : BinaryTree<Data>::Node {

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode & operator=(const MutableNode &) = delete;
    // Move assignment
    MutableNode & operator=(MutableNode &&) noexcept = delete;

    /* ********************************************************************** */

    // Specific member functions
    virtual Data & Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

    virtual MutableNode & LeftChild() const = 0; // concrete function must throw std::out_of_range when not existent
    virtual MutableNode & RightChild() const = 0; // concrete function must throw std::out_of_range when not existent

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default; 

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree & operator=(const MutableBinaryTree &) = delete;
  // Move assignment
  MutableBinaryTree & operator=(MutableBinaryTree &&) noexcept = delete;

  /* ************************************************************************ */

  // Specific member functions
  virtual MutableNode & Root() = 0; // concrete function must throw std::length_error when empty

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

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)
  void InOrderMap(MapFun) override; 

  /* ************************************************************************ */
  
  // Specific member function (inherited from BreadthMappableContainer)
  void BreadthMap(MapFun) override;

protected:

  // Auxiliary member functions
  void PreOrderMap(MutableNode *, MapFun);
  void PostOrderMap(MutableNode *, MapFun);
  void InOrderMap(MutableNode *, MapFun);
  void BreadthMap(MutableNode *, MapFun);

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:
  typename BinaryTree<Data>::Node * root = nullptr;
  typename BinaryTree<Data>::Node * node = nullptr;
  StackLst<typename BinaryTree<Data>::Node *> stack;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator &);
  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator & operator=(const BTPreOrderIterator &);
  // Move assignment
  BTPreOrderIterator & operator=(BTPreOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator &) const noexcept;
  bool operator!=(const BTPreOrderIterator &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data & operator*() const override; // throw std::out_of_range when terminated

  bool Terminated() const noexcept override; // should not throw exceptions

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTPreOrderIterator & operator++() override; // throw std::out_of_range when terminated

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override; // should not throw exceptions

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTPreOrderIterator<Data> {

private:

protected:
  using BTPreOrderIterator<Data>::node;
  
public:

  // Specific constructors
  BTPreOrderMutableIterator(const MutableBinaryTree<Data> &); // An iterator over a given mutable binary tree = default;

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator &) = default;
  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Destructor
  ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator & operator=(const BTPreOrderMutableIterator &);
  // Move assignment
  BTPreOrderMutableIterator & operator=(BTPreOrderMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderMutableIterator &) const noexcept = default;
  bool operator!=(const BTPreOrderMutableIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data & operator*() override; // throw std::out_of_range when terminated
};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:
  typename BinaryTree<Data>::Node * root = nullptr;
  typename BinaryTree<Data>::Node * node = nullptr;
  StackVec<typename BinaryTree<Data>::Node *> stack;

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator &);
  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator & operator=(const BTPostOrderIterator &);
  // Move assignment
  BTPostOrderIterator & operator=(BTPostOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator &) const noexcept;
  bool operator!=(const BTPostOrderIterator &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data & operator*() const override; // throw std::out_of_range when terminated

  bool Terminated() const noexcept override; // should not throw exceptions

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTPostOrderIterator & operator++() override; // throw std::out_of_range when terminated

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override; // should not throw exceptions

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTPostOrderIterator<Data> {

private:

protected:
  using BTPostOrderIterator<Data>::node;

public:

  // Specific constructors
  BTPostOrderMutableIterator(const MutableBinaryTree<Data> &); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator &) = default;
  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator & operator=(const BTPostOrderMutableIterator &) = default;
  // Move assignment
  BTPostOrderMutableIterator & operator=(BTPostOrderMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderMutableIterator &) const noexcept = default;
  bool operator!=(const BTPostOrderMutableIterator &) const noexcept = default;

  /*  */

  // Specific member functions (inherited from MutableIterator)
  Data & operator*() override; // throw std::out_of_range when terminated
};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:
  typename BinaryTree<Data>::Node * root = nullptr;
  typename BinaryTree<Data>::Node * node = nullptr;
  StackLst<typename BinaryTree<Data>::Node *> stack;

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator &);
  // Move constructor
  BTInOrderIterator(BTInOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator & operator=(const BTInOrderIterator &);
  // Move assignment
  BTInOrderIterator & operator=(BTInOrderIterator &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator &) const noexcept;
  bool operator!=(const BTInOrderIterator &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data & operator*() const override; // throw std::out_of_range when terminated

  bool Terminated() const noexcept override; // should not throw exceptions

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTInOrderIterator & operator++() override; // throw std::out_of_range when terminated

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override; // should not throw exceptions

};

/* ************************************************************************** */
template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>, virtual public BTInOrderIterator<Data> {

private:

protected:
  using BTInOrderIterator<Data>::node;

public:
  // Specific constructors
  BTInOrderMutableIterator(const MutableBinaryTree<Data> &); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator &) = default;
  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator & operator=(const BTInOrderMutableIterator &) = default;
  // Move assignment
  BTInOrderMutableIterator & operator=(BTInOrderMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderMutableIterator &) const noexcept = default;
  bool operator!=(const BTInOrderMutableIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data & operator*() override; // throw std::out_of_range when terminated

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data> {

private:

protected:
  typename BinaryTree<Data>::Node * root = nullptr;
  typename BinaryTree<Data>::Node * node = nullptr;
  QueueLst<typename BinaryTree<Data>::Node *> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data> &); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator &);
  // Move constructor
  BTBreadthIterator(BTBreadthIterator &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator & operator=(const BTBreadthIterator &);
  // Move assignment
  BTBreadthIterator & operator=(BTBreadthIterator &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator &) const noexcept;
  bool operator!=(const BTBreadthIterator &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)
  const Data & operator*() const override; // throw std::out_of_range when terminated

  bool Terminated() const noexcept override; // should not throw exceptions

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)
  BTBreadthIterator & operator++() override; // throw std::out_of_range when terminated

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)
  void Reset() noexcept override; // should not throw exceptions

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>, virtual public BTBreadthIterator<Data> {

private:

protected:
  using BTBreadthIterator<Data>::node;

public:
  // Specific constructors
  BTBreadthMutableIterator(const MutableBinaryTree<Data> &); // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator &) = default;
  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator & operator=(const BTBreadthMutableIterator &) = default;
  // Move assignment
  BTBreadthMutableIterator & operator=(BTBreadthMutableIterator &&) noexcept = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthMutableIterator &) const noexcept = default;
  bool operator!=(const BTBreadthMutableIterator &) const noexcept = default;

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)
  Data & operator*() override; // throw std::out_of_range when terminated

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
