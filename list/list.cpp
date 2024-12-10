#include "../container/mappable.hpp"
#include "../container/traversable.hpp"

namespace lasd {

/* ************************************************************************** */

// Specific constructors (Node)
template <typename Data>
List<Data>::Node::Node(const Data & data) : element(data), next(nullptr) {}

/* ********************************************************************** */

// Copy constructor (Node)
template <typename Data>
List<Data>::Node::Node(const Node & other) : element(other.element), next(other.next) {}

// Move constructor (Node)
template <typename Data>
List<Data>::Node::Node(Node && other) noexcept {
  std::swap(element, other.element);
  std::swap(next, other.next);
}


/* ********************************************************************** */

// Destructor (Node)
template <typename Data>
List<Data>::Node::~Node() {
  delete next;
}

/* ********************************************************************** */

// Comparison operators (Node)
template <typename Data>
bool List<Data>::Node::operator==(const Node & other) const noexcept {
  return (element == other.element) && (
    (next == nullptr && other.next == nullptr) || 
      (next != nullptr && other.next != nullptr && *next == *(other.next))
  );
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node & node) const noexcept {
  return !(*this == node);
}

/* ************************************************************************** */

// Specific member functions (Node)
template <typename Data>
typename List<Data>::Node * List<Data>::Node::Clone(Node * tail) {
  if (next == nullptr)
    return tail;
  else {
    Node * node = new Node(element);
    node->next = next->Clone(tail);
    return node;
  }
}

/* ************************************************************************** */
/* ************************************************************************** */

// Specific constructors (List)
template <typename Data>
List<Data>::List(const TraversableContainer<Data> & con) {
  con.Traverse(
    [this](const Data & data) {
        InsertAtBack(data);
    }
  );
}

template <typename Data>
List<Data>::List(MappableContainer<Data> && con) {
  con.Map(
    [this](Data & data) {
      InsertAtBack(std::move(data));
    }
  );
}

/* ************************************************************************** */

// Copy constructor (List)
template <typename Data>
List<Data>::List(const List<Data> & other) {
  if (other.tail != nullptr) {
    tail = new Node(*other.tail);
    head = other.head->Clone(tail);
    size = other.size;
  }
}

// Move constructor (List)
template <typename Data>
List<Data>::List(List<Data> && other) noexcept {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
}

/* ************************************************************************** */

// Destructor (List)
template <typename Data>
List<Data>::~List() {
  delete head;
}

/* ************************************************************************** */

// Copy assignment (List)
template <typename Data>
List<Data> & List<Data>::operator=(const List<Data> & other) {
  if (size <= other.size) {
    if (tail == nullptr) {
      List<Data> * tmp = new List<Data>(other);
      std::swap(*tmp, *this);
      delete tmp;  
    } else {
      Node * ocur = other.head;
      for (Node * ncur = head; ncur != nullptr; ncur = ncur->next, ocur = ocur->next) {
        ncur->element = ocur->element;
      }
      if (ocur != nullptr) {
        Node * newtail = new Node(*other.tail);
        tail->next = ocur->Clone(newtail);
        tail = newtail;
      }
    }
  } else {
    if (other.tail == nullptr) {
      delete head;
      head = tail = nullptr;
    } else {
      Node * ncur = head;
        for (Node * ocur = other.head; ocur != nullptr; ocur = ocur->next, tail = ncur, ncur = ncur->next) 
          ncur->element = ocur->element;
        delete ncur;
        tail->next = nullptr;
    }
  }
  size = other.size;
  return *this;
}

// Move assignment (List)
template <typename Data>
List<Data> & List<Data>::operator=(List<Data> && other) noexcept {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size, other.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (List)
template <typename Data>
bool List<Data>::operator==(const List<Data> & other) const noexcept {
  if (size != other.size) {
    return false;
  }
  Node *ncur = head;
  Node *ocur = other.head;
  while (ncur != nullptr && ocur != nullptr) {
    if (ncur->element != ocur->element) {
      return false;
    }
    ncur = ncur->next;
    ocur = ocur->next;
  }
  return true;
}

template <typename Data>
bool List<Data>::operator!=(const List<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (List)
template <typename Data>
void List<Data>::InsertAtFront(const Data & data) {
  Node * start = new Node(data);
  start->next = head;
  head = start;
  if (tail == nullptr)
    tail = head;
  size++;
}

template <typename Data>
void List<Data>::InsertAtFront(Data && data) {
  Node * start = new Node(std::move(data));
  start->next = head;
  head = start;
  if (tail == nullptr)
    tail = head;
  size++;
}

template <typename Data>
void List<Data>::RemoveFromFront() {
  if (head != nullptr) {
    Node * front = head;
    if (tail == head)
      head = tail = nullptr;
    else
      head = head->next;
    size--;
    front->next = nullptr;
    delete front;
  }
  else
    throw std::length_error("List is empty.");
}

template <typename Data>
Data List<Data>::FrontNRemove() {
  if (head != nullptr) {
    Node * front = head;
    if (tail == head)
      head = tail = nullptr;
    else
      head = head->next;
    size--;
    front->next = nullptr;
    Data data(std::move(front->element));
    delete front;
    return data;
  }
  else
    throw std::length_error("List is empty.");
}

template <typename Data>
void List<Data>::InsertAtBack(const Data & data) {
  Node * end = new Node(data);
  if (tail == nullptr)
    head = end;
  else
    tail->next = end;
  tail = end;
  ++size;
}

template <typename Data>
void List<Data>::InsertAtBack(Data && data) {
  Node * end = new Node(std::move(data));
  if (tail == nullptr)
    head = end;
  else
    tail->next = end;
  tail = end;
  ++size;
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from ClereableContainer)
template <typename Data>
void List<Data>::Clear() {
  while (size != 0)
    RemoveFromFront();
  delete head;
  head = tail = nullptr;
  size = 0;
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from DictionaryContainer)
template <typename Data>
bool List<Data>::Insert(const Data & data) {
  for (Node * i = head; i != nullptr; i = i->next) {
    if (i->element == data)
      return false;
  }
  InsertAtBack(data);
  return true;
}

template <typename Data>
bool List<Data>::Insert(Data && data) {
  for (Node * i = head; i != nullptr; i = i->next) {
    if (i->element == data)
      return false;
  }
  InsertAtBack(data);
  return true;
}

template <typename Data>
bool List<Data>::Remove(const Data & data) {
  Node * last = nullptr;
  for (Node ** i = &head; *i != nullptr; last = *i, i = &((*i)->next)) {
    if ((*i)->element == data) {
      Node * node = *i;
      *i = node->next;
      node->next = nullptr;
      delete node;
      size--;
      if (tail == node)
        tail = last;
      return true;
    }
  }
  return false;
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from Linear Container)
template <typename Data>
const Data & List<Data>::operator[](const ulong index) const {
  if (index < size) {
    Node * current = head;
    for (ulong i = 0; i < index; i++, current = current->next) {}
    return current->element;
  }
  else
    throw std::out_of_range("Index " + std::to_string(index) + " is out of range [0, " + std::to_string(size - 1) + "]");
}

template <typename Data>
Data & List<Data>::operator[](const ulong index) {
  if (index < size) {
    Node * current = head;
    for (ulong i = 0; i < index; i++, current = current->next) {}
    return current->element;
  }
  else
    throw std::out_of_range("Index " + std::to_string(index) + " is out of range [0, " + std::to_string(size - 1) + "]");
}

template <typename Data>
const Data & List<Data>::Front() const {
  if (head != nullptr)
    return head->element;
  else
    throw std::length_error("List is empty.");
}

template <typename Data>
Data & List<Data>::Front() {
  if (head != nullptr)
    return head->element;
  else
    throw std::length_error("List is empty.");
}

template <typename Data>
const Data & List<Data>::Back() const {
  if (tail != nullptr)
    return tail->element; 
  else
    throw std::length_error("List is empty."); 
}

template <typename Data>
Data & List<Data>::Back() {
  if (tail != nullptr)
    return tail->element;
  else
    throw std::length_error("List is empty.");
}

/* ************************************************************************** */

// Specific member functions (inherited from TraversableContainer)
template <typename Data>
void List<Data>::Traverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PreOrderTraversableContainer)
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun) const {
  PreOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from PostOrderTraversableContainer)
template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun) const {
  PostOrderTraverse(fun, head);
}

/* ************************************************************************** */

// Specific member functions (List) (inherited from MappableContainer)
template <typename Data>
void List<Data>::Map(MapFun fun) {
  PreOrderMap(fun, head);
} 

/* ************************************************************************** */

// Specific member functions (List) (inherited from PreOrderMappableContainer)
template <typename Data>
void List<Data>::PreOrderMap(MapFun fun) {
  PostOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific memeber functions (List) (inherited from PostOrderMappableContainer)
template <typename Data>
void List<Data>::PostOrderMap(MapFun fun) {
  PostOrderMap(fun, head);
}

/* ************************************************************************** */

// Specific member funtions (List) (inherited from Container)
template <typename Data>
bool List<Data>::Empty() const noexcept {
  return size == 0;
}

template <typename Data>
ulong List<Data>::Size() const noexcept {
  return size;
  
}

/* ************************************************************************** */
/* ************************************************************************** */

// Auxiliary member functions (List) (for TraversableContainer)
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, const Node * current) const {
  for (; current != nullptr; current = current->next)
    fun(current->element);
}

template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, const Node * current) const {
  if (current != nullptr) {
    PostOrderTraverse(fun, current->next);
    fun(current->element);
  }
}

/* ************************************************************************** */

// Auxiliary member functions (List) (for MappableContainer)
template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node * current) {
  for (; current != nullptr; current = current->next) 
    fun(current->element);
}

template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node * current) {
  if (current != nullptr) {
    PostOrderMap(fun, current->next);
    fun(current->element);
  }
}

/* ************************************************************************** */


}