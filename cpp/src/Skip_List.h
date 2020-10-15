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

    std::shared_ptr<Element<T>> search(const T&) const;

    int list_size() const;

    int layer_count() const;

    void print_layers() const;

  private:

    // Helper private member function that takes in 
    // a shared_ptr reference to another element.
    // Recursively iterates throught he list until 
    // a spot is found to insert. 
    void add_element_helper(std::shared_ptr<Element<T>>, const T&);

    void add_layer(std::shared_ptr<Element<T>>, const T&, const int);

    std::shared_ptr<Element<T>> search_level(std::shared_ptr<Element<T>>, const T&, const int) const;

    std::shared_ptr<Element<T>> find_base_element(std::shared_ptr<Element<T>>) const;

    void add_element_layer(std::shared_ptr<Element<T>>, std::shared_ptr<Element<T>>, const int layer);

    void print_layer() const;

    // Private Member Variables
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
    for (int i = 0; i < N; i++) {
      head_arr.at(i) = std::make_shared<Element<T>>(key);
    }
    for (int i = 0; i < N-1; i++) {
      head_arr.at(i)->above = head_arr.at(i+1);
      head_arr.at(i+1)->below = head_arr.at(i);
    }
  } else if (key <= head_arr.at(0)->key) {
    head_arr.at(0)->prev = std::make_shared<Element<T>>(key);
    head_arr.at(0)->prev->next = head_arr.at(0);
    head_arr.at(0) = head_arr.at(0)->prev;
    for (int i = 1; i < N; i++) {
      head_arr.at(i) = std::make_shared<Element<T>>(key);
    }
  } else if (head_arr.at(0)->next==nullptr) {
    head_arr.at(0)->next = std::make_shared<Element<T>>(key);
    head_arr.at(0)->next->prev = head_arr.at(0);
  } else {
    add_element_helper(head_arr.at(0)->next, key);
  }
}

template<class T, int N>
void Skip_List<T,N>::add_element_helper(std::shared_ptr<Element<T>> element_ptr, const T& key) { 
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
    element_ptr->prev->next = new_element;
    element_ptr->prev = new_element;
    add_layer(new_element, key, 1);
  } else if (element_ptr->next == nullptr) {
    std::shared_ptr<Element<T>> new_element = std::make_shared<Element<T>>(key);
    element_ptr->next = new_element; 
    new_element->prev = element_ptr;
    //element_ptr = element_ptr->next;
    //std::cout << element_ptr->prev->key << std::endl;
    add_layer(element_ptr->next, key, 1);
    
  } else {
    add_element_helper(element_ptr->next, key);
  }
}

template<class T, int N>
void Skip_List<T,N>::add_layer(std::shared_ptr<Element<T>> element_ptr, const T& key, const int layer) {
  // Reached the max height
  if (layer == N) 
    return;
  else if (rand() % 2 == 0) {
    // Build Layer and recursively call add layer
    std::shared_ptr<Element<T>> new_element = std::make_shared<Element<T>>(key);
    new_element->below = element_ptr;
    element_ptr->above = new_element;
    add_element_layer(head_arr.at(layer), new_element, layer);
    add_layer(new_element, key, layer+1);
  }
}

template<class T, int N>
void Skip_List<T,N>::add_element_layer(std::shared_ptr<Element<T>> element_ptr, std::shared_ptr<Element<T>> new_element, const int layer) {
  if (element_ptr->next == nullptr) {
    if (new_element->key >= element_ptr->key) {
      element_ptr->next = new_element;
      element_ptr->next->prev = element_ptr;
    } else {
      new_element->next = element_ptr;
      new_element->prev = element_ptr->prev;
      new_element->prev->next = new_element;
      element_ptr->prev = new_element;
    }
  }
   else if (new_element->key <= element_ptr->key) {
    new_element->prev = element_ptr->prev;
    new_element->next = element_ptr;
    new_element->prev->next = new_element;
    element_ptr->prev = new_element;
  } else {
    add_element_layer(element_ptr->next, new_element, layer);
  }
}

template<class T, int N>
std::shared_ptr<Element<T>> Skip_List<T,N>::search(const T& key) const {
  return search_level(head_arr.at(layers-1), key, layers-1);
}

template<class T, int N>
std::shared_ptr<Element<T>> Skip_List<T,N>::search_level(std::shared_ptr<Element<T>> head, const T& key, const int level) const {
  if (head == nullptr)
    return nullptr;
  std::shared_ptr<Element<T>> curr_element = head;
  while(curr_element != nullptr) {
    if (key == curr_element->key) 
      return find_base_element(curr_element);
    else if (key <= curr_element->key) 
      return search_level(curr_element->prev->below, key, level-1);
    else
      if (curr_element->next == nullptr)
        return search_level(curr_element->below, key, level-1); 
      curr_element = curr_element->next;
  }
  return nullptr;
}

template<class T, int N>
std::shared_ptr<Element<T>> Skip_List<T,N>::find_base_element(std::shared_ptr<Element<T>> curr_element) const {
  if (curr_element == nullptr)
    return nullptr;
  if (curr_element->below == nullptr)
    return curr_element;
  else 
    return find_base_element(curr_element->below);
}

// TODO: increment size after additions
template<class T, int N>
int Skip_List<T,N>::list_size() const {
  return size;
}

template<class T, int N>
int Skip_List<T,N>::layer_count() const {
  return layers;
}

template<class T, int N>
void Skip_List<T,N>::print_layers() const {
  for (int i = N-1; i >= 0; i--) {
    std::cout << "Layer " << i << ": ";
    std::shared_ptr<Element<T>> curr_element = head_arr.at(i);
    while(curr_element != nullptr) {
      std::cout << curr_element->key << ' ';
      curr_element = curr_element->next;
    }
    std::cout << std::endl;
  }
}


#endif