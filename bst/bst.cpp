namespace lasd {

/* ************************************************************************** */

// Specific constructors (BST)
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data> & con) {
  con.Traverse([this](const Data & data) {
    Insert(data);
  });
}

template <typename Data>
BST<Data>::BST(MappableContainer<Data> && con) {
  con.Map([this](Data && data) {
    Insert(std::move(data));
  });
}

/* ************************************************************************** */

// Copy constructor (BST)
template <typename Data>
BST<Data>::BST(const BST<Data> & other) : BinaryTreeLnk<Data>(other) {}

// Move constructor (BST)
template <typename Data>
BST<Data>::BST(BST<Data> && other) noexcept : BinaryTreeLnk<Data>(std::move(other)) {}

/* ************************************************************************** */

// Copy assignment (BST)
template <typename Data>
BST<Data> & BST<Data>::operator=(const BST<Data> & other) {
  BinaryTreeLnk<Data>::operator=(other);
  return *this;
}

// Move assignment (BST)
template <typename Data>
BST<Data> & BST<Data>::operator=(BST<Data> && other) noexcept {
  BinaryTreeLnk<Data>::operator=(std::move(other));
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BST)
template <typename Data>
bool BST<Data>::operator==(const BST<Data> & other) const noexcept {
  if(size != other.size) 
    return false;
  else {
    if (size == 0) return true;
    BTInOrderIterator<Data> iterator(*this);
    BTInOrderIterator<Data> otherIterator(other);
    while (!iterator.Terminated() && !otherIterator.Terminated()) {
      if (*iterator != *otherIterator) 
        return false;
      ++iterator;
      ++otherIterator;
    }
    if (iterator.Terminated() && otherIterator.Terminated()) 
      return true;
    return false;
  }
}

template <typename Data>
bool BST<Data>::operator!=(const BST<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (BST)
template <typename Data>
const Data & BST<Data>::Min() const {
  if (BinaryTreeLnk<Data>::Empty())
    throw std::length_error("Tree is empty.");
  else
    return FindPointerToMin(root)->element;
}

template <typename Data>
Data BST<Data>::MinNRemove() {
  if (BinaryTreeLnk<Data>::Empty())
    throw std::length_error("Tree is empty.");
  else {
    NodeLnk * min = DetachMin(root);
    Data minElement = min->element;
    delete min;
    return minElement;
  }
}

template <typename Data>
void BST<Data>::RemoveMin() {
  if (root != nullptr)
    delete DetachMin(root);
  else
    throw std::length_error("Tree is empty.");
}

template <typename Data>
const Data & BST<Data>::Max() const {
  if (BinaryTreeLnk<Data>::Empty())
    throw std::length_error("Tree is empty.");
  else
    return FindPointerToMax(root)->element;
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
  if (BinaryTreeLnk<Data>::Empty())
    throw std::length_error("Tree is empty.");
  else {
    NodeLnk * max = DetachMax(root);
    Data maxElement = max->element;
    delete max;
    return maxElement;
  }
}

template <typename Data>
void BST<Data>::RemoveMax() {
  if (root != nullptr)
    delete DetachMax(root);
  else
    throw std::length_error("Tree is empty.");
}

template <typename Data>
const Data & BST<Data>::Predecessor(const Data & data) const {
  if (BinaryTreeLnk<Data>::Empty())
    throw std::length_error("Tree is empty.");
  else {
    NodeLnk * predecessor = FindPointerToPredecessor(root, data);
    if (predecessor == nullptr)
      throw std::length_error("Predecessor does not exist.");
    else 
      return predecessor->element;
  }
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data & data) {
  Data predecessor = Predecessor(data);
  Remove(predecessor);
  return predecessor;
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data & data) {
  Remove(Predecessor(data));
}

template <typename Data>
const Data & BST<Data>::Successor(const Data & data) const {
  if (BinaryTreeLnk<Data>::Empty())
    throw std::length_error("Tree is empty.");
  else {
    NodeLnk * successor = FindPointerToSuccessor(root, data);
    if (successor == nullptr)
      throw std::length_error("Successor does not exist.");
    else 
      return successor->element;
  }
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data & data) {
  Data successor = Successor(data);
  Remove(successor);
  return successor;
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data & data) {
  Remove(Successor(data));
}

/* ************************************************************************** */

// Specific member functions (BST) (inherited from BinaryTree)
template <typename Data>
typename BinaryTree<Data>::Node & BST<Data>::Root() const {
  return BinaryTreeLnk<Data>::Root();
}

/* ************************************************************************** */

// Specific member functions (BST) (inherited from DictionaryContainer)
template <typename Data>
bool BST<Data>::Insert(const Data & data) {
  NodeLnk* & insertion = FindPointerTo(root, data);
  if (insertion == nullptr) {
    insertion = new typename BinaryTreeLnk<Data>::NodeLnk(data);
    size++;
    return true;
  }
  return false;
}

template <typename Data>
bool BST<Data>::Insert(Data && data) noexcept {
  NodeLnk* & insertion = FindPointerTo(root, data);
  if (insertion == nullptr) {
    insertion = new typename BinaryTreeLnk<Data>::NodeLnk();
    insertion->Element() = std::move(data);
    size++;
    return true;
  }
  return false;
}

// template <typename Data>
// bool BST<Data>::Remove(const Data & data) {
//   delete Detach(FindPointerTo(root, data));
//   return true;
// }

template <typename Data>
bool BST<Data>::Remove(const Data & data) {
  if (BinaryTreeLnk<Data>::Empty())
    return false;
  NodeLnk* & nodePtr = FindPointerTo(root, data);
  if (nodePtr == nullptr) 
    return false;
  delete Detach(nodePtr);
  return true;
}


/* ************************************************************************** */

// Specific member functions (BST) (inherited from TestableContainer)
template <typename Data>
bool BST<Data>::Exists(const Data & data) const noexcept {
  return FindPointerTo(root, data) != nullptr;
}

/* ************************************************************************** */

// Specific member functions (BST) (inherited from ClearableContainer)
template <typename Data>
void BST<Data>::Clear() {
  while (root != nullptr)
    RemoveMin();
} 

/* ************************************************************************** */

// Auxiliary member functions (BST) 
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Detach(NodeLnk* & node) noexcept {
  if (node != nullptr) {
    if (node->left == nullptr)
      return Skip2Right(node);
    else if (node->right == nullptr)
      return Skip2Left(node);
    else {
      NodeLnk * max = DetachMax(node->left);
      std::swap(node->element, max->element);
      return max;  
    }
  }
  return nullptr;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMax(NodeLnk* & node) noexcept {
  return Skip2Left(FindPointerToMax(node));
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::DetachMin(NodeLnk* & node) noexcept {
  return Skip2Right(FindPointerToMin(node));
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BST<Data>::Skip2Right(NodeLnk* & node) noexcept {
  NodeLnk* right = nullptr;
  if (node != nullptr) {
    std::swap(right, node->right);
    std::swap(right, node);
    size--;
  } 
  return right;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2Left(NodeLnk* & node) noexcept {
  NodeLnk * left = nullptr;
  if (node != nullptr) {
    std::swap(left, node->left);
    std::swap(left, node);
    size--;
  }
  return left;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerToMin(NodeLnk* const & node) const noexcept {
  if (node != nullptr) {
    if (node->left != nullptr)
      return FindPointerToMin(node->left);
  }
  return node;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* & BST<Data>::FindPointerToMin(NodeLnk* & node) noexcept {
  return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerToMin(node));
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerToMax(NodeLnk* const & node) const noexcept {
  if (node != nullptr) {
    if (node->right != nullptr)
      return FindPointerToMax(node->right);
  }
  return node;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* & BST<Data>::FindPointerToMax(NodeLnk* & node) noexcept {
  return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerToMax(node));
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerTo(NodeLnk* const & node, const Data & element) const noexcept {
  if (node != nullptr) {
    if (element != node->element) {
      if (element < node->element)
        return FindPointerTo(node->left, element);
      if (element >= node->element)
        return FindPointerTo(node->right, element);
    }
  }
  return node;
} 

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* & BST<Data>::FindPointerTo(NodeLnk* & node,const Data & element) noexcept {
  return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerTo(node, element));
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerToPredecessor(NodeLnk* const & node, const Data & element) const noexcept {
  NodeLnk* const * predecessor = nullptr;
  NodeLnk* const * current = &node;
  while (*current != nullptr) {
    if (element > (*current)->element) {
      predecessor = current;
      current = &((*current)->right);
    } 
    else
      current = &((*current)->left);
  }
  if (predecessor == nullptr)
    return *current;
  return *predecessor;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* & BST<Data>::FindPointerToPredecessor(NodeLnk* & node, const Data & element) noexcept {
  return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(node, element));
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerToSuccessor(NodeLnk* const & node, const Data & element) const noexcept {
  NodeLnk* const * successor = nullptr;
  NodeLnk* const * current = &node;
  while (*current != nullptr) {
    if (element >= (*current)->element)
      current = &((*current)->right);
    else {
      successor = current;
      current = &((*current)->left);
    }
  }
  if (successor == nullptr)
    return *current;
  return *successor;
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk* & BST<Data>::FindPointerToSuccessor(NodeLnk* & node, const Data & element) noexcept {
  return const_cast<NodeLnk* &>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(node, element));
}

/* ************************************************************************** */

}
