
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data> {

private:

protected:

  using Container::size;

  struct NodeVec : public MutableBinaryTree<Data>::MutableNode { 

  private:

  protected:

  public:

    Data element;
    ulong index = 0;
    Vector<NodeVec*> * tree = nullptr;

    NodeVec() = default;
    NodeVec(const Data &, ulong, Vector<NodeVec*> *);
    ~NodeVec() = default;

    NodeVec & operator=(const NodeVec &);
    NodeVec & operator=(NodeVec &&) noexcept;

    bool operator==(const NodeVec &) const noexcept;
    bool operator!=(const NodeVec &) const noexcept;

    const Data & Element() const noexcept override;
    Data & Element() noexcept override;
    bool IsLeaf() const noexcept override;
    bool HasRightChild() const noexcept override;
    bool HasLeftChild() const noexcept override;
    
    NodeVec & RightChild() const override;
    NodeVec & LeftChild() const override;
  };

  Vector<NodeVec*> * vector = nullptr;

public:

  // Default constructor
  BinaryTreeVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data> &); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data> &&); // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec &);
  // Move constructor
  BinaryTreeVec(BinaryTreeVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec & operator=(const BinaryTreeVec &);
  // Move assignment
  BinaryTreeVec & operator=(BinaryTreeVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec &) const noexcept;
  bool operator!=(const BinaryTreeVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  typename BinaryTree<Data>::Node & Root() const override; // throw std::length_error when empty

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  typename MutableBinaryTree<Data>::MutableNode & Root() override; // throw std::length_error when empty

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; 

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)
  using typename TraversableContainer<Data>::TraverseFun;
  void BreadthTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  using typename MappableContainer<Data>::MapFun;
  void BreadthMap(MapFun) override; 

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
