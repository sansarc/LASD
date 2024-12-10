namespace lasd {

/* ************************************************************************ */

// Specific constructors (Vector)
template <typename Data>
Vector<Data>::Vector(const ulong newsize) {
  size = newsize;
  Elements = new Data[size];  
} 

template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & con) : Vector(con.Size()) {
  ulong i = 0;
  con.Traverse(
    [this, &i](const Data & data) { 
      Elements[i++] = data;
    }
  );
}

template <typename Data>
Vector<Data>::Vector(MappableContainer<Data> && con) : Vector(con.Size()) {
  ulong i = 0;
  con.Map(
    [this, &i](Data & data) {
      Elements[i++] = std::move(data);
    }
  );
}

/* ************************************************************************ */

// Copy constructor (Vector)
template <typename Data>
Vector<Data>::Vector(const Vector<Data> & other) {
  size = other.size;
  Elements = new Data[size];
  std::copy(other.Elements, other.Elements + size, Elements); 
}

// Move constructor (Vector)
template <typename Data>
Vector<Data>::Vector(Vector<Data> && other) noexcept   {
  std::swap(size, other.size);
  std::swap(Elements, other.Elements);
}

/* ************************************************************************ */

// Destructor (Vector)
template <typename Data>
Vector<Data>::~Vector() {
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

/* ************************************************************************ */

// Copy assignment (Vector)
template <typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> & other) {
  Vector<Data> tmp(other); 
  std::swap(size, tmp.size); 
  std::swap(Elements, tmp.Elements); 
  return *this; 
}

// Move assignment (Vector)
template <typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> && other) noexcept {
  std::swap(size, other.size);
  std::swap(this->Elements, other.Elements);
  return *this;
}

/* ************************************************************************ */

// Comparison operators (Vector)
template <typename Data>
bool Vector<Data>::operator==(const Vector<Data> & other) const noexcept {
  if (size != other.size)
    return false; 
  for (ulong i = 0; i < size; i++) {
    if (Elements[i] != other.Elements[i]) 
      return false;
  } 
  return true;
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector<Data> & other) const noexcept {
  return !(*this == other);
}

/* ************************************************************************ */

// Specific member function (Vector) (inherited from ClearableContainer)
template <typename Data>
void Vector<Data>::Clear() {
  delete[] Elements;
  Elements = nullptr;
  size = 0;
}

/* ************************************************************************ */

// Specific member functions (Vector) (inherited from ResizableContainer)
template <typename Data>
void Vector<Data>::Resize(ulong newsize) {
  if (newsize == 0)
    Clear();
  else if (newsize != size) {
    Data * tmp = new Data[newsize];
    ulong min = (size < newsize) ? size : newsize;
    for (ulong i = 0; i < min; ++i) 
      std::swap(Elements[i], tmp[i]);
    std::swap(Elements, tmp);
    size = newsize;
    delete[] tmp;
  } 
}

/* ************************************************************************ */

// Specific member functions (Vector) (inherited from LinearContainer)
template <typename Data>
const Data & Vector<Data>::operator[](const ulong index) const {
  if (index < size)
    return Elements[index];
  else
    throw std::out_of_range("Index " + std::to_string(index) + " is out of range [0, " + std::to_string(size - 1) + "]");
}

template <typename Data>
Data & Vector<Data>::operator[](const ulong index) {
  if (index < size)
    return Elements[index];
  else
    throw std::out_of_range("Index " + std::to_string(index) + " is out of range [0, " + std::to_string(size - 1) + "]");
}

template <typename Data>
const Data & Vector<Data>::Front() const {
  if (size != 0)
    return Elements[0];
  else
    throw std::length_error("Vector is empty.");
}

template <typename Data>
Data & Vector<Data>::Front() {
  if (size != 0)
    return Elements[0];
  else
    throw std::length_error("Vector is empty.");

}

template <typename Data>
const Data & Vector<Data>::Back() const {
  if (size != 0)
    return Elements[size - 1];
  else
    throw std::length_error("Vector is empty.");
}

template <typename Data>
Data & Vector<Data>::Back() {
  if (size != 0)
    return Elements[size - 1];
  else
    throw std::length_error("Vector is empty.");

}

/* ************************************************************************ */

// Specific member functions (Vector) (inherited from Container)
template <typename Data>
bool Vector<Data>::Empty() const noexcept {
  return size == 0;
}

template <typename Data>
ulong Vector<Data>::Size() const noexcept {
  return size;
}

/* ************************************************************************ */
/* ************************************************************************ */

// Specific constructors (SortableVector)
template <typename Data>
SortableVector<Data>::SortableVector(const ulong newsize) : Vector<Data>(newsize) {}

template <typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> & con) : Vector<Data>(con) {}

template <typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> && con) : Vector<Data>(con) {}

/* ************************************************************************ */

// Copy constructor (SortableVector)
template <typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data> & other) : Vector<Data>(other) {}

template <typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> && other) noexcept : Vector<Data>(other) {}

/* ************************************************************************ */

// Copy assignment (SortableVector)
template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(const SortableVector<Data> & other) {
  Vector<Data>::operator=(other);
  return *this;
} 

// Move assignment (SortableVector)
template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator=(SortableVector<Data> && other) noexcept {
  Vector<Data>::operator=(other);
  return *this;
}

/* ************************************************************************** */

// Specific member functions (SortableVector) (inherited from Container)
template <typename Data>
bool SortableVector<Data>::Empty() const noexcept {
  return Vector<Data>::Empty();
} 

template <typename Data>
ulong SortableVector<Data>::Size() const noexcept {
  return Vector<Data>::Size();
}

/* ************************************************************************** */

}
