#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <string>

using namespace std;

//YOUR CODE GOES HERE

class invalid : public std::exception {
 public:
  virtual const char * what() const throw() { return "not found"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(NULL), next(NULL), prev(NULL){};
    Node(T d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) {
    //size = rhs->size;
    Node * n = rhs.head;
    while (n != NULL) {
      addBack(n->data);
      n = n->next;
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    // addBack incrments size
    //size = rhs->size;

    Node * n = rhs.head;
    while (n != NULL) {
      addBack(n->data);
      n = n->next;
    }
    return this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {  // list is currently empty
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  Node * removeHelper(const T & data, Node * current) {
    if (current == NULL) {
      return NULL;
    }
    if (data == current->data) {
      Node * ans = current->next;

      // treat prev case
      if (current->prev != NULL) {
        ans->prev = current->prev;
      }

      // deal with if current is last element
      if (current->next == NULL) {
        tail = ans;
      }

      delete current;
      size--;
      return ans;
    }
    current->next = removeHelper(data, current->next);
    return current;
  }

  bool remove(const T & item) {
    size_t sizeBefore = size;
    head = removeHelper(item, head);
    size_t sizeAfter = size;
    if (sizeBefore == sizeAfter) {
      return true;
    }
    else {
      return false;
    }
  }

  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw invalid();
    }

    Node * n = head;
    int i = 0;

    while (n != NULL) {
      if (i == index) {
        return n->data;
      }
      n = n->next;
      i++;
    }
    return head->data;
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw invalid();
    }
    Node * n = head;
    int i = 0;

    while (n != NULL) {
      if (i == index) {
        return n->data;
      }
      n = n->next;
      i++;
    }
    return head->data;
  }

  int find(const T & item) {
    Node * n = head;
    int i = 0;
    while (n != NULL) {
      if (n->data == item) {
        return i;
      }
      n = n->next;
    }
    return -1;
  }

  int getSize() const { return size; }
};

#endif
