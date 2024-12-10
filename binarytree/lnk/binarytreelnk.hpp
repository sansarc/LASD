
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : public virtual MutableBinaryTree<Data> {

private:

protected:

  using Container::size;
  using Container::Size;

  struct NodeLnk : virtual MutableBinaryTree<Data>::MutableNode { 

  private:

  protected:
  

  public:
    Data element;
    NodeLnk * right = nullptr;
    NodeLnk * left = nullptr;

    NodeLnk() = default;
    NodeLnk(const Data &);
    NodeLnk(Data &&) noexcept;
    ~NodeLnk();
    NodeLnk & operator=(const NodeLnk &);
    NodeLnk & operator=(NodeLnk &&) noexcept;   
    NodeLnk(const NodeLnk &);
    NodeLnk(NodeLnk &&) noexcept;
    
    bool operator==(const NodeLnk &) const noexcept;
    bool operator!=(const NodeLnk &) const noexcept;

    Data & Element() noexcept override;
    const Data & Element() const noexcept override;
    bool IsLeaf() const noexcept override;
    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;
    NodeLnk & LeftChild() const override;
    NodeLnk & RightChild() const override;
  };

  NodeLnk * root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> &); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data> &&) noexcept; // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk &);
  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk & operator=(const BinaryTreeLnk &);
  // Move assignment
  BinaryTreeLnk & operator=(BinaryTreeLnk &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk &) const noexcept;
  bool operator!=(const BinaryTreeLnk &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  typename BinaryTree<Data>::Node & Root() const override; // throw std::length_error when empty

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)
  typename MutableBinaryTree<Data>::MutableNode & Root() override; // throw std::length_error when empty

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override; 

protected:
  // Auxiliary member functions
  NodeLnk * BuildTree(NodeLnk *);
};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
