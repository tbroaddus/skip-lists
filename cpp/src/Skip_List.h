#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <memory>
#include <array>
#include <stdlib.h>
#include <time.h>

#include "Element.h"

// Skip_List class
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

    // Adds element to skip list (T must be a comparable)
    void add_element(const T&);

    // Searches element in the skip list
    // Returns a smart pointer to the base element (at level 0)
    std::shared_ptr<Element<T>> search(const T&) const;

    // Returns the size of the list
    int list_size() const;

    // Returns the total number of levels in the list
    // Defined by template parameter N
    int level_count() const;

    // Prints levels of skip list; starting from 0 to N-1
    void print_levels() const;

  private:

    // Helper private member function that takes in 
    // a shared_ptr reference to another element.
    // Recursively iterates through the list until 
    // a spot is found to insert. 
    void add_element_helper(std::shared_ptr<Element<T>>, const T&);

    // Adds element to level with probability = 1/2
    // Calls add_element_level() to add element to current level 
    void add_level(std::shared_ptr<Element<T>>, const T&, const int);

    // Adds element to level, called by add_level()
    void add_element_level(std::shared_ptr<Element<T>>, std::shared_ptr<Element<T>>, const int layer);

    // Helper to public member function search() 
    // Searches current level for element containing a matching key value
    std::shared_ptr<Element<T>> search_level(std::shared_ptr<Element<T>>, const T&, const int) const;

    // Finds base element of element passed to function
    // Used once an element is found by search_level()
    std::shared_ptr<Element<T>> find_base_element(std::shared_ptr<Element<T>>) const;


    // Private Member Variables

    // An array that contains pointers to the heads of each level
    std::array<std::shared_ptr<Element<T>>,N> head_arr;

    // Total number of levels, defined by template parameter N
    const int levels;

    // Number of elements in base level 
    int size;

};


template<class T, int N>
Skip_List<T,N>::Skip_List() : levels(N), size(0) {
  for (auto ptr : head_arr) {
    ptr = nullptr;
  }
  srand(time(NULL));
}


// TODO: Define
template<class T, int N>
Skip_List<T,N>::Skip_List(const Skip_List<T,N>& _Skip_List) {

}


// TODO: Define
template<class T, int N>
Skip_List<T,N>::Skip_List(Skip_List<T,N>&& _Skip_list) {

}


// All dynamic memory handled by shared_ptr's, no need to define
template<class T, int N>
Skip_List<T,N>::~Skip_List() {}


// TODO: Define
template<class T, int N>
Skip_List<T,N>& Skip_List<T,N>::operator=(const Skip_List<T,N>& _Skip_List) {

}


// TODO: Define
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
  size++;
}


template<class T, int N>
void Skip_List<T,N>::add_element_helper(std::shared_ptr<Element<T>> element_ptr, const T& key) { 
  if (key <= element_ptr->key) {
    std::shared_ptr<Element<T>> new_element = std::make_shared<Element<T>>(key);
    new_element->prev = element_ptr->prev;
    new_element->next = element_ptr;
    element_ptr->prev->next = new_element;
    element_ptr->prev = new_element;
    add_level(new_element, key, 1);
  } else if (element_ptr->next == nullptr) {
    std::shared_ptr<Element<T>> new_element = std::make_shared<Element<T>>(key);
    element_ptr->next = new_element; 
    new_element->prev = element_ptr;
    add_level(element_ptr->next, key, 1);
  } else {
    add_element_helper(element_ptr->next, key);
  }
}


template<class T, int N>
void Skip_List<T,N>::add_level(std::shared_ptr<Element<T>> element_ptr, const T& key, const int level) {
  // Reached the max height
  if (level == N) 
    return;
  // "Roll dice", p = 0.5
  // If random number is even, then add new level  
  else if (rand() % 2 == 0) {
    // Build level and recursively call add_level()
    std::shared_ptr<Element<T>> new_element = std::make_shared<Element<T>>(key);
    // Pointing the new element and current element at each other, then adding new element to upper level 
    new_element->below = element_ptr; 
    element_ptr->above = new_element;
    // Adding new element to upper level
    add_element_level(head_arr.at(level), new_element, level);
    // Recursively calling add_level() for the above layers
    add_level(new_element, key, level+1);
  }
}


template<class T, int N>
void Skip_List<T,N>::add_element_level(std::shared_ptr<Element<T>> element_ptr, std::shared_ptr<Element<T>> new_element, const int level) {
  // Adding element to current level 
  // Similar to the way its done for the base level in add_element_helper()
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
    // Recursive call to add_element_layer to continue down the current level
    add_element_level(element_ptr->next, new_element, level);
  }
}


template<class T, int N>
std::shared_ptr<Element<T>> Skip_List<T,N>::search(const T& key) const {
  return search_level(head_arr.at(levels-1), key, levels-1);
}


template<class T, int N>
std::shared_ptr<Element<T>> Skip_List<T,N>::search_level(std::shared_ptr<Element<T>> head, const T& key, const int level) const {
  if (head == nullptr)
    return nullptr;
  std::shared_ptr<Element<T>> curr_element = head;
  while(curr_element != nullptr) {
  // std::cout << curr_element->key << " ";
    if (key == curr_element->key) 
      return find_base_element(curr_element);
    else if (key < curr_element->key) {
      if (curr_element->prev == nullptr)
        return nullptr;  
      else
        return search_level(curr_element->prev->below, key, level-1);
    }
    else {
      if (curr_element->next == nullptr)
        return search_level(curr_element->below, key, level-1); 
      curr_element = curr_element->next;
    }
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


template<class T, int N>
int Skip_List<T,N>::list_size() const {
  return size;
}


template<class T, int N>
int Skip_List<T,N>::level_count() const {
  return levels;
}


template<class T, int N>
void Skip_List<T,N>::print_levels() const {
  for (int i = N-1; i >= 0; i--) {
    std::cout << "Levels " << i << ": ";
    std::shared_ptr<Element<T>> curr_element = head_arr.at(i);
    while(curr_element != nullptr) {
      std::cout << curr_element->key << ' ';
      curr_element = curr_element->next;
    }
    std::cout << std::endl;
  }
}


#endif