
namespace lasd {

/* ************************************************************************** */

// Comparison operators (Node)
template<typename Data>
bool BinaryTree<Data>::Node::operator==(const Node & node) const noexcept {
  if (Element() != node.Element()) 
    return false;
  if (HasRightChild() && RightChild() != node.RightChild()) 
    return false; 
  if (HasLeftChild() && LeftChild() != node.LeftChild()) 
    return false;
  return true;
}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Comparison operators (BinaryTree)
template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree<Data> & other) const noexcept {
  if (size != other.size) 
    return false;
  if (size == 0) 
    return true;
  return (Root() == other.Root());
} 

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (BinaryTree) (inherited from TraversableContainer)
template <typename Data>
void BinaryTree<Data>::Traverse(TraverseFun fun) const {
  if (size <= 0) return;
  PreOrderTraverse(fun);
}

// Specific member functions (BinaryTree) (inherited from PreOrderTraversableContainer)
template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const {
  if (size <= 0) return;
  PreOrderTraverse(&Root(), fun);
}

// Specific member functions (BinaryTree) (inherited from PostOrderTraversableContainer)
template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const {
  if (size <= 0) return;
  PostOrderTraverse(&Root(), fun);
}

// Specific member functions (BinaryTree) (inherited from InOrderTraversableContainer)
template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const {
  if (size <= 0) return;
  InOrderTraverse(&Root(), fun);
}

// Specific member functions (BinaryTree) (inherited from BreadthTraversableContainer)
template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const {
  if (size <= 0) return;
  BreadthTraverse(&Root(), fun);
}

/* ************************************************************************** */

// Auxiliary member functions (BinaryTree)
template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(const Node * node, TraverseFun fun) const {
  fun(node->Element());
  if (node->HasLeftChild())
    PreOrderTraverse(&(node->LeftChild()), fun);
  if (node->HasRightChild())
    PreOrderTraverse(&(node->RightChild()), fun);
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(const Node * node, TraverseFun fun) const {
  if (node->HasLeftChild())
    PostOrderTraverse(&(node->LeftChild()), fun);
  if (node->HasRightChild())
    PostOrderTraverse(&(node->RightChild()), fun);
  fun(node->Element());
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(const Node * node, TraverseFun fun) const {
  if (node->HasLeftChild())
    InOrderTraverse(&(node->LeftChild()), fun);
  fun(node->Element());
  if (node->HasRightChild())
    InOrderTraverse(&(node->RightChild()), fun);
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(const Node * node, TraverseFun fun) const {
  QueueVec<const Node *> queue;
  queue.Enqueue(node);
  while (!queue.Empty()) {
    const Node * current = queue.HeadNDequeue();
    fun(current->Element());
    if (current->HasLeftChild())
      queue.Enqueue(&current->LeftChild());
    if (current->HasRightChild())
      queue.Enqueue(&current->RightChild());
  }
}

/* ************************************************************************** */
/* ************************************************************************** */

// Specific memeber function (MutableBinaryTree) (inherited from MappableContainer)
template <typename Data>
void MutableBinaryTree<Data>::Map(MapFun fun) {
  if (size <= 0) return;
  PreOrderMap(fun);
}

// Specific member function (MutableBinaryTree) (inherited from MappableContainer)
template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun fun) {
  PreOrderMap(&Root(), fun);
}

// Specific member functions (MutableBinaryTree) (inherited from PostOrderTraversableContainer)
template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun fun) {
  if (size <= 0) return;
  PostOrderMap(&Root(), fun);
}

// Specific member functions (MutableBinaryTree) (inherited from InOrderTraversableContainer)
template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun fun) {
  if (size <= 0) return;
  InOrderMap(&Root(), fun);
}

// Specific member functions (MutableBinaryTree) (inherited from BreadthMappableContainer)
template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun fun) {
  if (size <= 0) return;
  BreadthMap(&Root(), fun);
}

/* ************************************************************************** */

// Auxiliary member functions (MutableBinaryTree)
template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MutableNode * node, MapFun fun) {
  fun(node->Element());
  if (node->HasLeftChild())
    PreOrderMap(&(node->LeftChild()), fun);
  if (node->HasRightChild())
    PreOrderMap(&(node->RightChild()), fun);
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MutableNode * node, MapFun fun) {
  if (node->HasLeftChild())
    PostOrderMap(&(node->LeftChild()), fun);
  if (node->HasRightChild())
    PostOrderMap(&(node->RightChild()), fun);
  fun(node->Element());
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MutableNode * node, MapFun fun) {
  if (node->HasLeftChild())
    InOrderMap(&(node->LeftChild()), fun);
  fun(node->Element());
  if (node->HasRightChild())
    InOrderMap(&(node->RightChild()), fun);
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MutableNode * node, MapFun fun) {
  if (size <= 0) return;
  QueueVec<MutableNode *> queue;
  queue.Enqueue(node);
  while (!queue.Empty()) {
    MutableNode * current = queue.HeadNDequeue();
    fun(current->Element());
    if (current->HasLeftChild())
      queue.Enqueue(&(current->LeftChild()));
    if (current->HasRightChild())
      queue.Enqueue(&(current->RightChild()));
  }
}

/* ************************************************************************** */
/* ************************************************************************** */

// Specific constructor (BTPreOrderIterator)
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> & tree) {
  if(!tree.Empty()) {
    node = &tree.Root();
    root = &tree.Root();
  }
}

/* ************************************************************************** */

// Copy constructor (BTPreOrderIterator)
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> & other) {
  stack = other.stack;
  node = other.node;
  root = other.root;
}

// Move constructor (BTPreOrderIterator)
template<typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data> && other) noexcept {
  stack = std::move(other.stack);
  node = std::move(other.node);
  root = std::move(other.root);
}

/* ************************************************************************** */

// Copy assignment (BTPreOrderIterator)
template<typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> & pre) {
  stack = pre.stack;
  node = pre.node;
  root = pre.root;
  return *this;
}

// Move assignment (BTPreOrderIterator)
template<typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> && other) noexcept {
  stack = std::move(other.stack);
  node = std::move(other.node);
  root = std::move(other.root);
  return *this;
}

/* ************************************************************************** */

// Comparison operator (BTPreOrderIterator)
template<typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> & other) const noexcept {
  return stack == other.stack && node == other.node && root == other.root;
}

template<typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (BTPreOrderIterator) (inherited from Iterator)
template<typename Data>
const Data & BTPreOrderIterator<Data>::operator*() const {
  if (Terminated())
    throw std::out_of_range("Iterator Terminated.");
  else
    return node->Element();
}

template<typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
  return node == nullptr && stack.Empty();
}

/* ************************************************************************** */

// Specific member functions (BTPreOrderIterator) (inherited from ForwardIterator)
template<typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++(){
  if(Terminated()) {
    node = nullptr;
    throw std::out_of_range("Iterator Terminated.");
  }
  else {
    if (node->HasLeftChild()) {
      if(node->HasRightChild())
        stack.Push(&node->RightChild());
      node = &node->LeftChild();
    }
    else {
      if(node->HasRightChild())
        node = &node->RightChild();
      else {
        if(stack.Empty())
          node = nullptr;
        else 
          node = stack.TopNPop();
      }
    }
  }
  return *this;
}

/* ************************************************************************** */

// Specific member functions (BTPreOrderIterator) (inherited from ResettableIterator)
template<typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
  stack.Clear();
  node = root;
}

/* ************************************************************************** */
/* ************************************************************************** */

// Specific constructors (BTPreOrderMutableIterator)
template<typename Data>
BTPreOrderMutableIterator<Data>::BTPreOrderMutableIterator(const MutableBinaryTree<Data> & tree) : BTPreOrderIterator<Data>(tree) {}

/* ************************************************************************ */

// Copy assignment (BTPreOrderMutableIterator)
template <typename Data>
BTPreOrderMutableIterator<Data> & BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator<Data> & other) {
  BTPreOrderIterator<Data>::operator=(other);
  return *this;
}

/* ************************************************************************ */

// Specific member functions (BTPreOrderMutableIterator) (inherited from MutableIterator)
template<typename Data>
Data & BTPreOrderMutableIterator<Data>::operator*() {
  if (BTPreOrderIterator<Data>::Terminated())
    throw std::out_of_range("Iterator Terminated.");
  else
    return const_cast<Data &>(node->Element());
}

/* ************************************************************************** */
/* ************************************************************************** */

// Specific constructors (BTPostOrderIterator)
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> & tree)  {
  if(!tree.Empty()) {
    root = &tree.Root();
    Reset();
  }
}

/* ************************************************************************** */

// Copy constructor (BTPostOrderIterator)
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> & other) {
  node = other.node;
  stack = other.stack;
  root = other.root;
}

// Move constructor (BTPostOrderIterator)
template<typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> && other) noexcept {
  node = std::move(other.node);
  stack = std::move(other.stack);
  root = std::move(other.root);
}

/* ************************************************************************** */

// Copy assignment (BTPostOrderIterator)
template<typename Data>
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data>& other) {
  node = other.node;
  stack = other.stack;
  root = other.root;
  return *this;
}

// Move assignment (BTPostOrderIterator)
template<typename Data>
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> && other) noexcept {
  node = std::move(other.node);
  stack = std::move(other.stack);
  root = std::move(other.root);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (BTPostOrderIterator)
template<typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> & other) const noexcept {
  return (stack == other.stack && node == other.node && root == other.root);
}

template<typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (BTPostOrderIterator) (inherited from Iterator)
template<typename Data>
const Data & BTPostOrderIterator<Data>::operator*() const {
  if (Terminated())
    throw std::out_of_range("Iterator Terminated.");
  else
    return node->Element();

}

template<typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
  return node == nullptr && stack.Empty();
}

/* ************************************************************************** */

// Specific member functions (BTPostOrderIterator) (inherited from ForwardIterator)
template <typename Data>
BTPostOrderIterator<Data> & BTPostOrderIterator<Data>::operator++(){
  if(Terminated()) 
    throw std::out_of_range("Iterator Terminated.");
  else {
    if (!stack.Empty()) {
      if(stack.Top()->HasRightChild()) {
        if (&stack.Top()->RightChild() != node) {
          node = &stack.Top()->RightChild();
          while (node->HasLeftChild() || node->HasRightChild()) {
            if (node->HasLeftChild()) {
              stack.Push(node);
              node = &node->LeftChild();
            }
            else {
              stack.Push(node);
              node = &node->RightChild();
            }
          }
        }
        else node = stack.TopNPop();
      }
      else node = stack.TopNPop();
    } 
    else node = nullptr;
  }
  return *this;
}

/* ************************************************************************ */

// Specific member functions (inherited from ResettableIterator)
template<typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
  node = root;
  while(node->HasLeftChild() || node->HasRightChild()) {
    stack.Push(node);
    if(node->HasLeftChild())
      node = &node->LeftChild();
    else
      node = &node->RightChild();
  }
}

/* ************************************************************************ */
/* ************************************************************************ */

// Specific constructors (BTPostOrderMutableIterator)
template<typename Data>
BTPostOrderMutableIterator<Data>::BTPostOrderMutableIterator(const MutableBinaryTree<Data> & tree) : BTPostOrderIterator<Data>(tree) {}

/* ************************************************************************ */

// Specific member functions (BTPostOrderMutableIterator) (inherited from MutableIterator)
template<typename Data>
Data & BTPostOrderMutableIterator<Data>::operator*() {
  if (BTPostOrderIterator<Data>::Terminated())
    throw std::out_of_range("Iterator Terminated.");
  else
    return const_cast<Data &>(node->Element());
}

/* ************************************************************************ */
/* ************************************************************************ */

// Specific constructors (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> & tree) {
  if(!tree.Empty()) {
    root = &tree.Root();
    Reset();
  }
}

/* ************************************************************************ */

// Copy constructor (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> & other) {
  node = other.node;
  stack = other.stack;
  root = other.root;
}

// Move constructor (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> && other) noexcept {
  node = std::move(other.node);
  stack = std::move(other.stack);
  root = std::move(other.root);
}

/* ************************************************************************ */

// Copy assignment (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> & other) {
  node = other.node;
  stack = other.stack;
  root = other.root;
  return *this;
}

// Move assignment (BTInOrderIterator)
template <typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> && other) noexcept {
  node = std::move(other.node);
  stack = std::move(other.stack);
  root = std::move(other.root);
  return *this;
}

/* ************************************************************************ */

// Comparison operators (BTInOrderIterator)
template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> & other) const noexcept {
  return node == other.node && stack == other.stack && root == other.root;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************ */

// Specific member functions (BTInOrderIterator) (inherited from Iterator)
template <typename Data>
const Data & BTInOrderIterator<Data>::operator*() const {
  if (Terminated())
    throw std::out_of_range("Iterator Terminated.");
  else
    return node->Element();
}

template<typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
  return node == nullptr && stack.Empty();
}

/* ************************************************************************ */

// Specific member functions (BTInOrderIterator) (inherited from ForwardIterator)
template<typename Data>
BTInOrderIterator<Data> & BTInOrderIterator<Data>::operator++() {
  if (Terminated()) 
    throw std::out_of_range("Iterator Terminated.");
  else {
    if (node->IsLeaf()) {
      if(stack.Empty()) 
        node = nullptr;
      else 
        node = stack.TopNPop();
    }
    else {
      if (node->HasRightChild()) {
        node = &node->RightChild();
        while (node->HasLeftChild()) {
          stack.Push(node);
          node = &node->LeftChild();
        }
      }
      else {
        if(stack.Empty()) 
          node = nullptr;
        else 
          node = stack.TopNPop();
      }
    }
  }
  return *this;
}

/* ************************************************************************ */

// Specific member functions (BTInOrderIterator) (inherited from ResettableIterator)
template<typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
  node = root;
  while(node->HasLeftChild()) {
    stack.Push(node);
    node = &node->LeftChild();
  }
}

/* ************************************************************************ */
/* ************************************************************************ */

// Specific constructors (BTInOrderMutableIterator)
template <typename Data>
BTInOrderMutableIterator<Data>::BTInOrderMutableIterator(const MutableBinaryTree<Data> & tree) : BTInOrderIterator<Data>(tree) {}

/* ************************************************************************ */

// Specific member functions (BTInOrderMutableIterator) (inherited from MutableIterator) 
template <typename Data>
Data & BTInOrderMutableIterator<Data>::operator*() {
  if (BTInOrderIterator<Data>::Terminated())
    throw std::out_of_range("Iterator Terminated.");
  else
    return const_cast<Data &>(node->Element());
}

/* ************************************************************************ */
/* ************************************************************************ */

// Specific constructors (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> & tree) {
  if(!tree.Empty()){
    node = &tree.Root();
    root = &tree.Root();
  }
}

/* ************************************************************************ */

// Copy constructor (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data> & other) {
  node = other.node;
  queue = other.queue;
  root = other.root;
}

// Move constructor (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> && other) noexcept {
  node = std::move(other.node);
  queue = std::move(other.queue);
  root = std::move(other.root);
}

/* ************************************************************************ */

// Copy assignment (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data> & BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> & other) {
  node = other.node;
  queue = other.queue;
  root = other.root;
  return *this;
}

// Move assignment (BTBreadthIterator)
template <typename Data>
BTBreadthIterator<Data> & BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> && other) noexcept {
  node = std::move(other.node);
  queue = std::move(other.queue);
  root = std::move(other.root);
  return *this;
}

/* ************************************************************************ */

// Comparison operators (BTBreadthIterator)
template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> & other) const noexcept {
  return node == other.node && queue == other.queue && root == other.root;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************ */

// Specific member functions (BTBreadthIterator) (inherited from Iterator)
template <typename Data>
const Data& BTBreadthIterator<Data>::operator*() const {
  if (Terminated())
    throw std::out_of_range("Iterator terminated");
  else
    return node->Element();

}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
  return node == nullptr && queue.Empty();
}

/* ************************************************************************ */

// Specific member functions (BTBreadthIterator) (inherited from ForwardIterator)
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
  if(Terminated())  
    throw std::out_of_range("Iterator Terminated.");
  else {
    if(node->HasLeftChild())
      queue.Enqueue(&node->LeftChild());
    if(node->HasRightChild())
      queue.Enqueue(&node->RightChild());
    if(queue.Empty())
      node = nullptr;
    else
      node = queue.HeadNDequeue();
  }
  return *this;
}

/* ************************************************************************ */

// Specific member functions (BTBreadthIterator) (inherited from ResettableIterator)
template<typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
  queue.Clear();
  node = root;
}

/* ************************************************************************ */
/* ************************************************************************ */

// Specific constructors (BTBreadthMutableIterator)
template <typename Data>
BTBreadthMutableIterator<Data>::BTBreadthMutableIterator(const MutableBinaryTree<Data> & tree) : BTBreadthIterator<Data>(tree) {}

/* ************************************************************************ */

// Specific member functions (BTBreadthMutableIterator) (inherited from MutableIterator)
template <typename Data>
Data & BTBreadthMutableIterator<Data>::operator*() {
  if (BTBreadthIterator<Data>::Terminated())
    throw std::out_of_range("Iterator Terminated.");
  else
    return const_cast<Data &>(node->Element());
}

/* ************************************************************************ */
/* ************************************************************************ */

}