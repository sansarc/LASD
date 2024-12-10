
namespace lasd {

/* ************************************************************************** */

// Default constructor (QueueVec)
template<typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>::Vector(4) {}

/* ************************************************************************** */

// Specific constructor (QueueVec)
template<typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data> & con) : QueueVec<Data>() {
  head = 0;
  tail = con.Size();
  ulong index = 0;
  con.Traverse(
    [this, &index](const Data & data) {
        Elements[index++] = data;
    }
  );
}

template<typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data> && con) : QueueVec<Data>() {
  head = 0; 
  tail = con.Size();
  ulong index = 0;
  con.Map(
    [this, &index](Data& dat) {
        Elements[index++] = dat;
    }
  );
}

/* ************************************************************************** */

// Copy constructor (QueueVec)
template<typename Data>
QueueVec<Data>::QueueVec(const QueueVec<Data> & other) : Vector<Data>::Vector(other) {
  tail = other.tail;
  head = other.head;
}

// Copy constructor (QueueVec)
template<typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& other) noexcept  {
  std::swap(size, other.size);
  std::swap(Elements, other.Elements);
  std::swap(tail, other.tail);
  std::swap(head, other.head);
}

/* ************************************************************************** */



/* ************************************************************************** */

// Copy assignment (QueueVec)
template<typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(const QueueVec<Data> & other) {
  QueueVec<Data> * tmp = new QueueVec<Data>(other);
  std::swap(*tmp, *this);
  delete tmp;
  return *this;
}

// Move assignment (QueueVec)
template<typename Data>
QueueVec<Data> & QueueVec<Data>::operator=(QueueVec<Data> && other) noexcept {
  std::swap(size, other.size);
  std::swap(Elements, other.Elements);
  std::swap(tail, other.tail);
  std::swap(head, other.head);
  return *this;
}

/* ************************************************************************** */

// Comparison operators (QueueVec)
template<typename Data> 
bool QueueVec<Data>::operator==(const QueueVec<Data> & other) const noexcept {
  if (Size() == other.Size()) {
    for (ulong i = head, j = other.head; i < tail && j < other.tail; i++, j++) {
        if (Elements[i] != other.Elements[j])
          return false;
    }
    return true;
  }
  return false;
}

template<typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (QueueVec)
template<typename Data>
const Data& QueueVec<Data>::Head() const {
  if( head != tail ) 
    return Elements[head];
  else 
    throw std::length_error("Queue is empty.");
}

template<typename Data>
Data& QueueVec<Data>::Head() {
  if(head != tail) 
    return Elements[head];
  else 
    throw std::length_error("Queue is empty.");
}

template<typename Data>
void QueueVec<Data>::Dequeue() {
  if(head != tail) {
    Reduce();
    head++;
    head %= size;
  }
  else 
    throw std::length_error("Queue is empty.");
}

template<typename Data>
Data QueueVec<Data>::HeadNDequeue() {
  if(head != tail) {
    Reduce();
    Data data(std::move(Elements[head]));
    head++;
    head %= size;
    return data;
  }
  else 
    throw std::length_error("Queue is empty.");
}

template<typename Data>
void QueueVec<Data>::Enqueue(const Data & data) {
  Expand();
  Elements[tail] = data;
  tail = (tail + 1) % size;
}

template<typename Data>
void QueueVec<Data>::Enqueue(Data && data) {
  Expand();
  Elements[tail] = std::move(data);
  tail = (tail + 1) % size;
}


/* ************************************************************************** */

// Specific member functions (QueueVec) (inherited from Container)
template<typename Data>
bool QueueVec<Data>::Empty() const noexcept {
  return (head == tail);
}

template<typename Data>
ulong QueueVec<Data>::Size() const noexcept {
  return (((size + tail) - head) % size);
}

/* ************************************************************************** */

// Specific member functions (QueueVec) (inherited from ClearableContainer)
template<typename Data>
void QueueVec<Data>::Clear() noexcept {
  head = tail = 0;
  Vector<Data>::Resize(1);
}

/* ************************************************************************** */

// Auxiliary member functions (QueueVec)
template<typename Data>
void QueueVec<Data>::Expand() noexcept {
  ulong nElements = Size();
  if(nElements+1 == size) {
    Resize(size*2, nElements);
  }
}

template<typename Data>
void QueueVec<Data>::Reduce() noexcept {
  ulong nElements = Size();
  if(nElements+1 == size/4) {
    Resize(size/2, nElements);
  }
}

template<typename Data>
void QueueVec<Data>::Resize(ulong newsize, ulong nElements) {
  Data* tmp = new Data[newsize];
  ulong max = (nElements <= newsize)? nElements : newsize;
  for(ulong i = head, j = 0; j < max; ++i %= size, ++j) {
    std::swap(Elements[i], tmp[j]);
  }
  std::swap(Elements, tmp);
  delete[] tmp;
  head = 0;
  tail = nElements;
  size = newsize;
}

/* ************************************************************************ */

}