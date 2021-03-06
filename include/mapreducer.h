#ifndef __MAPREDUCER_H__
#define __MAPREDUCER_H__

#include <stdlib.h>

/*
 *
 * MapReducer is a singly-linked queue that accepts functions to both the map() and reduce()
 * functions which will return new MapReducer objects containing members with either the
 * mapped function applied to each member (map) or a list reduced by the members not matching
 * the reduction (reduce)
 * 
 * this class stores pointers to elements, and the user of this class is responsible for the memory
 * they allocate.
 * 
 * Special note: this is a 'fun' class to show off some of the nice features of google test.
 * this makes no claim to be a 'real' mapreduce implementation, as it does not rely on data streams
 * and, quite frankly, would experience hilariously bad memory leaks if you tried to string
 * map and reduce calls together as a chain in typical map-reduce fashion. Bear with me on this one.
 */

template <typename T>
class MapReducer;

template <typename T>
class Node
{
  friend class MapReducer<T>;

private:
  Node* _next;
  T* _element;

public:
  Node() : Node(nullptr) {}

  Node(T* element)
  {
    _element = element;
    _next = nullptr;
  }
};

template <typename T>
class MapReducer
{
private:
  Node<T>* _head;
  Node<T>* _tail;
  size_t _count;

  // no copies please
  MapReducer(const MapReducer&);
  const MapReducer& operator = (const MapReducer&);

  //helper function to extract the element from a node, delete the node, and return the element
  T* removeAndDelete(Node<T>* node)
  {
    T* toReturn = node->_element;
    node->_element = nullptr;
    delete(node);
    _count--;
    return toReturn;
  }

public:
  MapReducer()
  {
    _head = nullptr;
    _tail = nullptr;
    _count = 0;
  }

  // public functions
  size_t size()
  {
    return _count;
  }

  //adds an element to the front of the queue
  bool addFirst(T* element)
  {
    if(element == nullptr) return false;

    Node<T>* node = new Node<T>(element);

    if(_count == 0)
    {
      _head = _tail = node;
    }
    else
    {
      Node<T>* oldHead = _head;
      _head = node;
      _head->_next = oldHead;
    }
    
    _count++;
    return true;
  }

  bool addLast(T* element)
  {
    if(element == nullptr) return false;

    Node<T>* node = new Node<T>(element);

    if(_count == 0)
    {
      _head = _tail = node;
    }
    else
    {
      _tail->_next = node;
      _tail = node;
    }
    
    _count++;
    return true;
  }

  T* getFirst()
  {
    if(_count < 1) return nullptr;

    Node<T>* unlink = _head;
    _head = _head->_next;
    if(_count < 2) _tail = nullptr;

    return removeAndDelete(unlink);
  }

  T* getLast()
  {
    if(_count < 1) return nullptr;

    Node<T>* unlink = _tail;
    if(_count == 1)
    {
      _head = _tail = nullptr;
    }
    else
    {
      Node<T>* current = _head;
      while(current->_next != _tail) current = current->_next;
      _tail = current;
    }

    return removeAndDelete(unlink);
  }

  T* peekFirst()
  {
    if(_count < 1) return nullptr;
    return _head->_element;
  }

  T* peekLast()
  {
    if(_count < 1) return nullptr;
    return _tail->_element;
  }

  // map returns a -new- MapReducer with only the elements that satisfy the given function
  template <typename F>
  MapReducer<T>* map(F func)
  {
    MapReducer<T>* mapped = new MapReducer<T>();
    Node<T>* current = _head;
    while(current != nullptr)
    {
      mapped->addLast(func(current->_element));
      current = current->_next;
    }
    return mapped;
  }

  // reduce returns a -new- MapReducer with only the elements that satisfy the given function
  template <typename G>
  MapReducer<T>* reduce(G func)
  {
    MapReducer<T>* reduced = new MapReducer<T>();
    Node<T>* current = _head;
    while(current != nullptr)
    {
      if(func(current->_element))
        reduced->addLast(current->_element);
      
      current = current->_next;
    }
    return reduced;
  }
};

#endif //__MAPREDUCER_H__