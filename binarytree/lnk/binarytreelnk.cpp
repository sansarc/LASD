namespace lasd {

/* ************************************************************************** */

// Specific constructors (NodeLnk)
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data & data) : element(data) {}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data && data) noexcept {
  std::swap(element, data);
}

/* ************************************************************************** */

// Copy constructor (NodeLnk)
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk & other) {
  element = other.element;
  if (other.HasLeftChild()) 
    left = new NodeLnk(*other.left);
  if (other.HasRightChild())
    right = new NodeLnk(*other.right);
}

// Move constructor (NodeLnk)
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk && other) noexcept {
  std::swap(element, other.element);
  std::swap(left, other.left);
  std::swap(right, other.right);
}

/* ************************************************************************** */

// Destructor (NodeLnk)
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
  if (left != nullptr)
    delete left;
  if (right != nullptr)
    delete right;

}

/* ************************************************************************** */

// Copy assignment (NodeLnk)
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk & other) {
  element = other.element; 
  if(other.HasLeftChild()) {
    delete left;
    left = new NodeLnk(*other.left);
  } else {
    delete left;
    left = nullptr;
  }
  if(other.HasRightChild()) {
    delete right;
    right = new NodeLnk(*other.right);
  } else {
    delete right;
    right = nullptr;
  }
  return *this;
}

// Move assignment (NodeLnk)
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk && other) noexcept {
  std::swap(element, other.element);
  std::swap(left, other.left);
  std::swap(right, other.right);
  return *this;
}


/* ************************************************************************** */

// Comparison operators (NodeLnk)
template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator==(const NodeLnk & other) const noexcept {
  return BinaryTree<Data>::operator==(other);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const NodeLnk & other) const noexcept {
  return !(this == other);
}

/* ************************************************************************** */

// Specific member functions (NodeLnk)
template <typename Data>
Data & BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
  return element;
}

template <typename Data>
const Data & BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
  return element;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
  return left != nullptr;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
  return right != nullptr;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept {
  return !(HasLeftChild() || HasRightChild());
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
  if (HasLeftChild())
    return * left;
  else 
    throw std::out_of_range("Node does not have a left leaf.");
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
  if (HasRightChild())
    return * right;
  else 
    throw std::out_of_range("Node does not have a left leaf.");
}

/* ************************************************************************** */
/* ************************************************************************** */

// Specific constructors (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> & con) {
  size = con.Size();
    QueueVec<NodeLnk **> queue;
    queue.Enqueue(&root);
    con.Traverse([&queue](const Data & data) {
      NodeLnk* & tmp = *queue.HeadNDequeue();
      tmp = new NodeLnk(data);
      queue.Enqueue(&tmp->left);
      queue.Enqueue(&tmp->right);
    });
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> && con) noexcept {
  size = con.Size();
  QueueVec<NodeLnk **> queue;
  queue.Enqueue(&root);
  con.Map([&queue](Data && data) {
    NodeLnk* & tmp = *queue.HeadNDequeue();
    tmp = new NodeLnk(std::move(data));
    queue.Enqueue(&tmp->left);
    queue.Enqueue(&tmp->right);
  });
}

/* ************************************************************************** */

// Copy constructor (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> & other) {
  if (other.size > 0) {
    size = other.size;
    root = BuildTree(other.root);
  }
}

// Move constructor (BuildTreeLnk)
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> && other) noexcept {
  std::swap(size, other.size);
  std::swap(root, other.root);
}

/* ************************************************************************** */

// Destructor (BuildTreeLnk)
template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  Clear();
}

/* ************************************************************************** */

// Copy assignment (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data> & BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> & other) {
  if (other.size > 0) {
    BinaryTreeLnk<Data> * tmp = new BinaryTreeLnk<Data>(other);
    std::swap(*this, *tmp);
    delete tmp;
  }
  else Clear();
  return *this;
}

// Move assignment (BinaryTreeLnk)
template <typename Data>
BinaryTreeLnk<Data> & BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> && other) noexcept {
  std::swap(root, other.root);
  std::swap(size, other.size);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BinaryTreeLnk)
template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data> & other) const noexcept {
  if (size == other.size)
    return Root() == other.Root();
  return false;
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (BinaryTreeLnk) (inherited from BinaryTree)
template <typename Data>
typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::Root() const {
  if (size > 0)
    return *root;
  else
    throw std::length_error("No Root returned, Tree is empty.");
}

/* ************************************************************************** */

// Specific member functions (BinaryTreeLnk) (inherited from MutableBinaryTree)
template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::Root() {
  if (size > 0)
    return *root;
  else
    throw std::length_error("No Root returned, Tree is empty.");
}

/* ************************************************************************** */

// Specific member functions (BinaryTreeLnk) (inherited from ClearableContainer)
template<typename Data>
void BinaryTreeLnk<Data>::Clear() {
  delete root;
  size = 0;
  root = nullptr;
}

/* ************************************************************************** */

// Auxiliary member functions (BinaryTreeLnk)
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BinaryTreeLnk<Data>::BuildTree(NodeLnk * node) {
  if (node == nullptr)
    return nullptr;
  NodeLnk * newRoot = new NodeLnk(node->element);
  newRoot->left = BuildTree(node->left);
  newRoot->right = BuildTree(node->right);
  return newRoot;
}

/* ************************************************************************** */

}