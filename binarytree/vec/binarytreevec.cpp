namespace lasd {

/* ************************************************************************** */

// Specific constructors (NodeVec)
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data & data, ulong otherIndex, Vector<NodeVec*> * otherTree) : element(data), index(otherIndex), tree(otherTree) {} 

/* ************************************************************************** */

// Copy assignment (NodeVec)
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec & other) {
  element = other.element;
  index = other.index;
  tree = other.tree;
  return *this;
}

// Move assignment (NodeVec)
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(NodeVec && other) noexcept {
  std::swap(element, other.element);
  std::swap(index, other.index);
  std::swap(tree, other.tree);
  return *this;
}

/* ************************************************************************** */

template <typename Data>
Data & BinaryTreeVec<Data>::NodeVec::Element() noexcept {
  return element;
}

template <typename Data>
const Data & BinaryTreeVec<Data>::NodeVec::Element() const noexcept {
  return element;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
  return (2 * index + 2) < tree->Size();

}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
  return (2 * index + 1) < tree->Size();

}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept {
  return !(HasRightChild() && HasLeftChild());
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::LeftChild() const {
  if (HasLeftChild())
    return *((*tree)[2 * index + 1]);
  else 
    throw std::out_of_range("Node does not have a left leaf.");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::RightChild() const {
  if (HasRightChild())
    return *((*tree)[2 * index + 2]);
  else 
    throw std::out_of_range("Node does not have a right leaf.");
}

/* ************************************************************************** */

// Specific constructors (BinaryTreeVec) 
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data> & con) {
  size = con.Size();
  vector = new Vector<NodeVec*>(size);
  ulong i = 0;
  con.Traverse([this, &i](const Data & data) {
    NodeVec * node = new NodeVec(data, i, vector);
    vector->operator[](i) = node;
    i++;
  });
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> && con) {
  size = con.Size();
  vector = new Vector<NodeVec*>(size);
  ulong i = 0;
  con.Map([this, &i](const Data & data) {
    NodeVec * node = new NodeVec(data, i, vector);
    vector->operator[](i) = node;
    i++;
  });
}

/* ************************************************************************** */

// Copy constructor (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec & other) {
  size = other.Size();
  if(size > 0) {
    vector = new Vector<NodeVec*>(size);
    for(ulong i=0; i<size; i++) {
      NodeVec* node = new NodeVec(other.vector->operator[](i)->Element(), i, vector);
      vector->operator[](i) = node;
      }
  }
}

// Move constructor (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> && other) noexcept {
  std::swap(size, other.size);
  std::swap(vector, other.vector);
}

/* ************************************************************************** */

// Destructor (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  Clear();
}

/* ************************************************************************** */

// Copy assignment (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> & other) {
  BinaryTreeVec<Data>* tmp = new BinaryTreeVec<Data>(other);
  std::swap(*this, *tmp);
  delete tmp;
  return *this;
}

// Move assignment (BinaryTreeVec)
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> && other) noexcept {
  std::swap(size, other.size);
  std::swap(vector, other.vector);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BinaryTreeVec)
template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> & other) const noexcept {
  return MutableBinaryTree<Data>::operator==(other);
}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> & other) const noexcept {
  return !(this == other);
}
  
/* ************************************************************************** */

// Specific member function (BinaryTreeVec) (inherited from BinaryTree)
template <typename Data>
typename BinaryTree<Data>::Node & BinaryTreeVec<Data>::Root() const {
  if (vector->Empty())
    throw std::length_error("Tree is empty.");
  else 
    return *(vector->operator[](0));
}

/* ************************************************************************** */

// Specific member function (BinaryTreeVec) (inherited from MutableBinaryTree)
template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeVec<Data>::Root() {
  if (vector->Empty())
    throw std::length_error("Tree is empty.");
  else 
    return *(vector->operator[](0));
}

/* ************************************************************************** */

// Specific member function (BinaryTreeVec) (inherited from ClearableContainer)
template <typename Data>
void BinaryTreeVec<Data>::Clear() {
  if (size > 0) {
    for (ulong i = 0; i < size; i++) 
     delete vector->operator[](i);
    delete vector;
  }
  vector = nullptr;
  size = 0;
}

/* ************************************************************************** */

// Specific member function (BinaryTreeVec) (inherited from BreadthTraversableContainer)
template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const {
  for (ulong i = 0; i < size; i++) {
    if (vector->operator[](i) != nullptr)
      fun(vector->operator[](i)->Element());
  }
}

/* ************************************************************************** */

// Specific member function (BinaryTreeVec) (inherited from BreadthMappableContainer)
template <typename Data>
void BinaryTreeVec<Data>::BreadthMap(MapFun fun) {
  for (ulong i = 0; i < size; i++) {
    if (vector->operator[](i) != nullptr)
      fun(vector->operator[](i)->Element());
  }
}

/* ************************************************************************** */

}
