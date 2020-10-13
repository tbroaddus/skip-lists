#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <memory>
#include <array>
#include <stdlib.h>
#include <time.h>

#include "Element.h"


template<class T, int N>
class Skip_List {

  public:

    // Default Constructor
    Skip_List();
    
    // Copy Constructor
    Skip_List(const Skip_List<T,N>&);

    // Move Constructor
    Skip_List(Skip_List<T,N>&&);
    
    // Destructor
    ~Skip_List();

    // Copy Assignment Operator
    Skip_List<T,N>& operator=(const Skip_List<T,N>&);

    // Move Assignment Operator
    Skip_List<T,N>& operator=(Skip_List<T,N>&&);

    void add_element(const T&);

    bool contains(const T&);

    int list_size() const;

    int layer_count() const;

    void print_layers() const;

  private:

    // Helper private member function that takes in 
    // a shared_ptr reference to another element 
    void add_element_helper(std::shared_ptr<Element<T>>&, const T&);

    void add_layer(std::shared_ptr<Element<T>>&, const T&, const int);

    void print_layer() const;

    std::array<std::shared_ptr<Element<T>>,N> head_arr;
    const int layers;
    int size;

};

template<class T, int N>
Skip_List<T,N>::Skip_List() : layers(N), size(0) {
  for (auto ptr : head_arr) {
    ptr = nullptr;
  }
  srand(time(NULL));
}

template<class T, int N>
Skip_List<T,N>::Skip_List(const Skip_List<T,N>& _Skip_List) {

}

template<class T, int N>
Skip_List<T,N>::Skip_List(Skip_List<T,N>&& _Skip_list) {

}

template<class T, int N>
Skip_List<T,N>::~Skip_List() {}

template<class T, int N>
Skip_List<T,N>& Skip_List<T,N>::operator=(const Skip_List<T,N>& _Skip_List) {

}

template<class T, int N>
Skip_List<T,N>& Skip_List<T,N>::operator=(Skip_List<T,N>&& _Skip_List) {

}

template<class T, int N>
void Skip_List<T,N>::add_element(const T& key) {
  if (head_arr.at(0)==nullptr) {
    head_arr.at(0) = std::make_shared<Element<T>>(key);
  } else if (key <= head_arr.at(0)->key) {
    head_arr.at(0)->prev = std::make_shared<Element<T>>(key);
    head_arr.at(0)->prev->next = head_arr.at(0);
    head_arr.at(0) = head_arr.at(0)->prev;
  } else if (head_arr.at(0)->next==nullptr) {
    head_arr.at(0)->next = std::make_shared<Element<T>>(key);
    head_arr.at(0)->next->prev = head_arr.at(0);
  } else {
    add_element_helper(head_arr.at(0)->next, key);
  }
}

template<class T, int N>
void Skip_List<T,N>::add_element_helper(std::shared_ptr<Element<T>>& element_ptr, const T& key) { 
  if (key <= element_ptr->key) {
    // TODO: For some reason this does not work... find out why!
    /*
    std::shared_ptr<Element<T>>& prev_temp = (element_ptr->prev);
    element_ptr->prev = std::make_shared<Element<T>>(key);  
    prev_temp->next = element_ptr->prev;
    element_ptr->prev->prev = prev_temp; 
    element_ptr->prev->next = element_ptr;
    */
    std::shared_ptr<Element<T>> new_element = std::make_shared<Element<T>>(key);
    new_element->prev = element_ptr->prev;
    new_element->next = element_ptr;
    new_element->prev->next=new_element;
    element_ptr->prev = element_ptr;
  } else if (element_ptr->next == nullptr) {
    element_ptr->next = std::make_shared<Element<T>>(key);
    element_ptr->next->prev = element_ptr;
    //element_ptr = element_ptr->next;
    //std::cout << element_ptr->prev->key << std::endl;
  } else {
    add_element_helper(element_ptr->next, key);
  }
}

template<class T, int N>
void Skip_List<T,N>::add_layer(std::shared_ptr<Element<T>>& element_ptr, const T& key, const int layer) {
  // Reached the max height
  if (layer == N) 
    return;
  else if (rand() % 2 == 0) {
    // Build Layer and recursively call add layer
  }
  // 
}

template<class T, int N>
bool Skip_List<T,N>::contains(const T& key) {
  // TODO: Temp, replace with emp
  return false;
}

template<class T, int N>
int Skip_List<T,N>::list_size() const {
  return size;
}

template<class T, int N>
int Skip_List<T,N>::layer_count() const {
  return layers;
}

// TODO: For now, printing the first layer! Need to print all layers moving forward. 
template<class T, int N>
void Skip_List<T,N>::print_layers() const {
  for (int i = N-1; i >= 0; i--) {
    std::cout << "Layer " << i << ": ";
    std::shared_ptr<Element<T>> curr_element = head_arr.at(i);
    while(curr_element != nullptr) {
      /*
      if (curr_element->prev == nullptr) { 
      std::cout << curr_element->key << ' ';
      std::cout << std::endl;
      } else {
        std::cout << curr_element->prev->key << " " << curr_element->key << std::endl;
      }
      */
      std::cout << curr_element->key << ' ';
      curr_element = curr_element->next;
    }
    std::cout << std::endl;
  }
}


#endif
