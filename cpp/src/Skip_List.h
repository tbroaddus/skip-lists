#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <memory>
#include <vector>

#include "Element.h"


template<class T>
class Skip_List {

  public:

    // Default Constructor
    Skip_List();
    
    // Copy Constructor
    Skip_List(const Skip_List<T>&);

    // Move Constructor
    Skip_List(Skip_List<T>&&);

    // Destructor
    ~Skip_List();

    // Copy Assignment Operator
    Skip_List<T>& operator=(const Skip_List<T>&);

    // Move Assignment Operator
    Skip_List<T>& operator=(Skip_List<T>&&);

    void add_element(const T&);

    bool contains(const T&);

    int list_size() const;

    int layer_count() const;

    void print_layers() const;

  private:

    std::vector<std::shared_ptr<Element<T>> head_vector;
    int layers;
    int size;

};

template<class T>
Skip_List<T>::Skip_List() : layers(1), size(0) {}

template<class T>
Skip_List<T>::Skip_List(const Skip_List<T>& _Skip_List) {

}

template<class T>
Skip_List<T>::Skip_List(Skip_List<T>&& _Skip_list) {

}

template<class T>
Skip_List<T>::~Skip_List() {}

template<class T>
Skip_List<T>& Skip_List<T>::operator=(const Skip_List<T>& _Skip_List) {

}

template<class T>
Skip_List<T>& Skip_List<T>::operator=(Skip_List<T>&& _Skip_List) {

}

template<class T>
void Skip_List<T>::add_element(const T&) {

}

template<class T>
bool Skip_List<T>::contains(const T&) {

}

template<class T>
int Skip_List<T>::list_size() const {

}

template<class T>
int Skip_List<T>::layer_count() const {

}

template<class T>
void Skip_List<T>::print_layers() const {

}


#endif
