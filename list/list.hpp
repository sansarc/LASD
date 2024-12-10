
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public ClearableContainer, virtual public LinearContainer<Data>, virtual public DictionaryContainer<Data> {

private:
  using Container::size;

protected:

  struct Node {

    Data element;
    Node * next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data &); 
  
    /* ********************************************************************** */

    // Copy constructor
    Node(const Node &);
    // Move constructor
    Node(Node &&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator==(const Node &) const noexcept;
    bool operator!=(const Node &) const noexcept;

    /* ********************************************************************** */

    // Specific member functions
    virtual Node * Clone(Node *);
  };

  Node * head = nullptr;
  Node * tail = nullptr; 

public:
  // Default constructor
  List() = default;

  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> &); // A list obtained from a TraversableContainer
  List(MappableContainer<Data> &&); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List &);
  // Move constructor
  List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List();

  /* ************************************************************************ */

  // Copy assignment
  List & operator=(const List &);
  // Move assignment
  List & operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const List<Data> &) const noexcept;
  bool operator!=(const List<Data> &) const noexcept; 

  /* ************************************************************************ */

  // Specific member functions
  void InsertAtFront(const Data &); // Copy of the value
  void InsertAtFront(Data &&); // Move of the value
  void RemoveFromFront();  // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)
  void InsertAtBack(const Data &); // Copy of the value
  void InsertAtBack(Data &&); // Move of the value

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)
  void Clear() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)
  bool Insert(const Data &) override; // Copy of the value
  bool Insert(Data &&) override; // Move of the value
  bool Remove(const Data &) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
  const Data & operator[](const ulong) const override; // (NonMutable) must throw std::out_of_range when  t of range
  Data & operator[](const ulong) override; //(Mutable) must throw std::out_of_range when out of range

  const Data & Front() const override; // (NonMutable) must throw std::length_error when empty
  Data & Front() override; // (Mutable) must throw std::length_error when empty

  const Data & Back() const override; // (NonMutable) must throw std::length_error when empty
  Data & Back() override; // Override (Mutable) must throw std::length_error when empty

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

  /* ************************************************************************ */
  
  // Specific member functions (inherited from Container)
  bool Empty() const noexcept override;
  ulong Size() const noexcept override;

protected:
  // Auxiliary member functions (for TraversableContainer) 
  void PreOrderTraverse(TraverseFun, const Node *) const;
  void PostOrderTraverse(TraverseFun, const Node *) const;

  /* ************************************************************************ */

  // Auxiliary member functions (for MappableContainer)
  void PreOrderMap(MapFun, Node *);
  void PostOrderMap(MapFun, Node *);
};

/* ************************************************************************** */

}

#include "list.cpp"

#endif