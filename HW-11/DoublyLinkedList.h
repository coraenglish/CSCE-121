#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                         class template definition                        //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class DoublyLinkedList {
public:
    DoublyLinkedList();
    DoublyLinkedList(T);
    DoublyLinkedList(const DoublyLinkedList<T>&);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
    ~DoublyLinkedList();
    unsigned int size() const { return sz; }
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    void push_back(T);
    void push_front(T);
    void pop_back();
    void pop_front();
    void erase(unsigned int);
    void insert(T data, unsigned int idx);
    void clear();
    std::string to_str() const;
    // breaks encapsulation... gives operator== access to private data... not great approach, but makes the homework easier for you since we haven't talked about iterators :).
    template<typename U> friend bool operator==(DoublyLinkedList<U> const&, DoublyLinkedList<U> const&);
private:
    // do not change ordering.
    Node<T> *head; // Stores a pointer to the first node (front) of the doubly-linked list.
    Node<T> *tail; // Stores a pointer to the last node (back) of the doubly-linked list.
    unsigned int sz; // Stores the number of nodes in the doubly-linked list (i.e., its size).
};



//////////////////////////////////////////////////////////////////////////////
//                       helper function declarations                       //
//////////////////////////////////////////////////////////////////////////////
template<typename T> std::ostream& operator<<(std::ostream &, DoublyLinkedList<T> const&);

template<typename T> bool operator==(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);

template<typename T> bool operator!=(DoublyLinkedList<T> const&, DoublyLinkedList<T> const&);



//////////////////////////////////////////////////////////////////////////////
//                     member template function definitions                 //
//////////////////////////////////////////////////////////////////////////////


// Default constructor: initializes the head and tail with nullptr, size to 0.
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}


// The parameterized constructor initializes head and tail to nullptr, size to 0.
// Constructs a new node on freestore with data, assigns the address of this newly created node to both head and tail and increments size (sz) by 1.
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(T data) : head(nullptr), tail(nullptr), sz(0) {
  Node<T>* n = new Node<T>(data);
  head = n;
  tail = n;
  sz += 1;
}


// Copy constructor initializes one DoublyLinkedList with another; performs a deep copy of the doubly-linked list bound to the function’s parameter.
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T> const& rhs) : head(nullptr), tail(nullptr), sz(rhs.sz) {
  if (rhs.head == nullptr) {
    return;
  }

  Node<T>* current = rhs.head;
  while (current) {
      this->push_back(current->data);
      current = current->next;
  }
}


// Copy assignment operator performs a deep copy of the doubly-linked list bound to the function’s parameter.
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs) {
  if (this == &rhs) {
    return *this;
  }
  clear();
  Node<T>* current = rhs.head;
  while (current) {
      this->push_back(current->data);
      current = current->next;
  }
  return *this;

}


// Calls clear to destruct a doubly-linked list.
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}


// Returns a reference to the first node’s data in the doubly-linked list.
template<typename T>
T& DoublyLinkedList<T>::front() {
  return head->data;
}


// Returns a constant reference to the first node’s (head’s) data in the doubly-linked list.
template<typename T>
const T& DoublyLinkedList<T>::front() const {
  const T frontReturn = head->data;
  return frontReturn;
}


// Returns a reference to the last node’s (tail’s) data in the doubly-linked list.
template<typename T>
T& DoublyLinkedList<T>::back() {
  return tail->data;
}


// Returns a constant reference to the last node’s (tail’s) data in the doubly-linked list.
template<typename T>
const T& DoublyLinkedList<T>::back() const {
  const T backReturn = tail->data;
  return backReturn;
}



// Deallocates memory for each node in the doubly-linked list.  Afterward, assigns nullptr to head and tail, assigns 0 to sz.
template<typename T>
void DoublyLinkedList<T>::clear() {
  Node<T>* curr = head;
  if (curr == nullptr) {
    return;
  }

  while(curr->next != nullptr) {
   Node<T>* next = curr->next;
   delete curr;
   curr = next;
  }
  delete curr;
  head = tail = nullptr;
  sz = 0;
}


// Inserts a node with data at position pos in the doubly-linked list.
// If pos >= sz, immediately return from the function.  Otherwise, ensure that the node is correctly inserted into the list at the specified position.
// This operation increases the size (sz) of the list by one.
template<typename T>
void DoublyLinkedList<T>::insert(T data, unsigned int pos) {
  Node<T>* n = new Node<T>(data);
  if (head == nullptr) {
    head = tail = n;
    sz = 1;
  } else if (pos >= sz) {
    return;
  } else if (pos == 0) {
    push_front(data);
  } else {
    Node<T>* curr = head;
    for (int i = 0; i < pos - 1; ++i) {
      curr = curr->next;
    }
    n->next = curr->next;
    n->prev = curr;
    curr->next = n;
    curr = n->next;
    curr->prev = n;
    sz += 1;
  }
}


// Removes the node at position pos from the doubly-linked list.  This operation decreases the size (sz) of the list by one.
template<typename T>
void DoublyLinkedList<T>::erase(unsigned int pos) {
  if (head == nullptr) {
    return;
  } else if (pos >= sz) {
    return;
  } else if (pos == 0) {
    pop_front();
  } else if (pos == sz - 1) {
    pop_back();
  } else {
    Node<T>* curr = head;
    for (int i = 0; i < pos - 1; ++i) {
      curr = curr->next;
    }
    Node<T>* nodePop = curr->next;
    curr->next = nodePop->next;
    curr = nodePop->next;
    curr->prev = nodePop->prev;
    nodePop->prev = nodePop->next = nullptr;
    delete nodePop;
    sz -= 1;
  }
}


// Adds a node with data to the end of the doubly-linked list.
// This operation effectively increases the size (sz) of the list by one and makes an assignment to tail.
template<typename T>
void DoublyLinkedList<T>::push_back(T data) {
  Node<T>* n = new Node<T>(data);
  if (head == nullptr) {
    head = tail = n;
    sz = 1;
  } else {
    tail->next = n;
    n->prev = tail;
    tail = n;
    sz += 1;
  }
}


// Removes the last node (i.e., node residing at the tail position) from the linked list and deallocates its memory.
// This operation effectively reduces the size of the list by one and makes an assignment to tail.
template<typename T>
void DoublyLinkedList<T>::pop_back() {
  if (head == nullptr) {
    return;
  }
  Node<T>* nodePop = tail;
  tail = tail->prev;
  if (sz == 1) {
    head = nullptr;
  } else {
    tail->next = nullptr;
  }
  delete nodePop;
  sz -= 1;
}


// Adds a node with data to the front of the doubly-linked list.
// This operation effectively increases the size (sz) of the list by one and makes an assignment to head.
template<typename T>
void DoublyLinkedList<T>::push_front(T data) {
  Node<T>* n = new Node<T>(data);
  if (head == nullptr) {
    head = tail = n;
    sz = 1;
  } else {
    head->prev = n;
    n->next = head;
    head = n;
    sz += 1;
  }
}


// Removes the first node (i.e., node residing at the head position) from the linked list and deallocates its memory.
// This operation effectively reduces the size of the list by one and makes an assignment to head.
template<typename T>
void DoublyLinkedList<T>::pop_front() {
  if (tail == nullptr) {
    return;
  }
  Node<T>* nodePop = head;
  head = head->next;
  if (sz == 1) {
    head = tail = nullptr;
  } else {
    head->prev = nullptr;
  }
  nodePop->next = nullptr;
  delete nodePop;
  sz -= 1;
}



// Provided.  Returns an std::string showing the nodes accessible from head.
template<typename T>
std::string DoublyLinkedList<T>::to_str() const
{
    std::stringstream os;
    const Node<T> *curr = head;
    os << std::endl << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    os << "head: " << head << std::endl;
    os << "tail: " << tail << std::endl;
    os << "  sz: " << sz << std::endl;
    os << std::setw(16) << "node" << std::setw(16) << "node.prev" << std::setw(16) << "node.data" <<  std::setw(16) << "node.next" << std::endl;
    while (curr) {
        os << std::setw(16) << curr;
        os << std::setw(16) << curr->prev;
        os << std::setw(16) << curr->data;
        os << std::setw(16) << curr->next;
        os << std::endl;
        curr = curr->next;
    }
    os << std::setfill('-') << std::setw(80) << '-' << std::setfill(' ') << std::endl;
    return os.str();
}

//////////////////////////////////////////////////////////////////////////////
//                     helper template function definitions                 //
//////////////////////////////////////////////////////////////////////////////


// operator<<(std::ostream& os, const Node<T> &rhs) : std::ostream
// Inserts the node’s data into the stream (os << rhs.data << std::endl).


// Performs an element-wise comparison of the lhs the rhs.
// This function will return true only if the doubly-linked lists are the same size and each corresponding node has the same value.
template<typename T>
bool operator==(DoublyLinkedList<T> const& lhs, DoublyLinkedList<T> const& rhs)
{
    if (lhs.size() != rhs.size()) {
      return false;
    } else {
      unsigned int iterations = lhs.size();
      Node<T>* currRHS = rhs.head;
      Node<T>* currLHS = lhs.head;

      while (iterations != 1) {
        if (currRHS->data != currLHS->data) {
          return false;
        } else {
          currRHS = currRHS->next;
          currLHS = currLHS->next;
          iterations -= 1;
        }
      }
    }
}


// Performs an element-wise comparison of the lhs the rhs.
// This function will return false only if the doubly-linked lists are the same size and each corresponding node has the same value.
// template<typename T>
// operator!=(const DoublyLinkedList<T> &lhs, const DoublyLinkedList<T> &rhs)  : bool


// Provided.  Uses to_str() to insert the DoublyLinkedList<T> object to the std::ostream.
// operator<<(std::ostream& os, const DoublyLinkedList<T> &rhs) :: std::ostream&
template<typename T>
std::ostream& operator<<(std::ostream& os, DoublyLinkedList<T> const& rhs)
{
    os << rhs.to_str();
    return os;
}

#endif
