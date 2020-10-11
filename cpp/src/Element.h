#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <memory>

template<class T>
struct Element {


    Element();

    Element(const T&);

    Element(const Element<T>&);

    Element(Element<T>&&);

    ~Element();

    Element& operator=(const Element<T>&);

    Element& operator=(Element<T>&&);

    std::shared_ptr<Element<T>> next;
    std::shared_ptr<Element<T>> prev;
    std::shared_ptr<Element<T>> above;
    std::shared_ptr<Element<T>> below;

    T key;

};


template<class T>
Element<T>::Element() : next(nullptr), prev(nullptr), above(nullptr), below(nullptr) {}

template<class T>
Element<T>::Element(const T& _key) : key(_key), next(nullptr), prev(nullptr), above(nullptr), below(nullptr) {}  

template<class T>
Element<T>::Element(const Element<T>& _Element) : key(_Element.key), next(_Element.next), prev(_Element.prev), above(_Element.above), below(_Element.below) {}

template<class T>
Element<T>::Element(Element<T>&& _Element) : key(_Element.key), next(std::move(_Element.next)), prev(std::move(_Element.prev)), above(std::move(_Element.above)), below(std::move(_Element.below)) {}


template<class T>
Element<T>::~Element(){}

// TODO: Determine whether this is semantically desired
template<class T>
Element<T>& Element<T>::operator=(const Element<T>& _Element) {
  if (this = &_Element)
    return *this;
  key = _Element.key;
  next = _Element.next;
  prev = _Element.prev;
  above = _Element.above;
  below = _Element.below;
  return *this;
}

template<class T>
Element<T>& Element<T>::operator=(Element<T>&& _Element) {
  if (this = &_Element)
    return *this;
  key = _Element.key;
  next = std::move(_Element.next);
  prev = std::move(_Element.prev);
  above = std::move(_Element.above);
  below = std::move(_Element.below);
  return *this;
}




#endif
