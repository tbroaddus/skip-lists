#include <iostream>
#include <memory>
#include <functional>


#include "Skip_List.h"

int main(int argc, char** argv) {

  Skip_List<int,5> skip_list;
  skip_list.add_element(2);
  skip_list.add_element(3);
  skip_list.add_element(8);
  skip_list.add_element(5);
  skip_list.add_element(9);
  skip_list.add_element(14);
  skip_list.add_element(34);
  skip_list.add_element(39);
  skip_list.add_element(11);
  skip_list.add_element(20);
  skip_list.add_element(39);
  skip_list.add_element(19);
  skip_list.add_element(7);
  skip_list.add_element(340);
  skip_list.add_element(6);
  skip_list.add_element(18);
  skip_list.add_element(44);
  skip_list.add_element(21);
 

  std::cout << "\nSkip list layers: \n";
  skip_list.print_levels();

  // base_element()
  // Function to print message to check if the element returned 
  // by search() is the base element.
  std::function<void(std::shared_ptr<Element<int>>)> base_element {
    [](std::shared_ptr<Element<int>> element) {
      if (element->below == nullptr) 
        std::cout << "- Base element" << std::endl;
      else 
        std::cout << "- Not base element" << std::endl;
    }
  };

  // contains()
  // Function to print message if element has been found or not
  std::function<void(std::shared_ptr<Element<int>>)> contains {
    [&base_element](std::shared_ptr<Element<int>> element) {
      if (element == nullptr) 
        std::cout << "- Not Found" << std::endl;
      else {
        std::cout << "- Found" << std::endl; 
        std::cout << "- val = " << element->key << std::endl;
        base_element(element);
      }
    }
  };

  // Searching for 2, 11, 9, 340, 0, 15, 1000 within the skip list.
  // 0, 15, and 1000 are not within the skip list.
  std::cout << "\nSearching for 2" << std::endl;
  contains(skip_list.search(2));
  std::cout << "\nSearching for 11" << std::endl;
  contains(skip_list.search(11));
  std::cout << "\nSearching for 9" << std::endl;
  contains(skip_list.search(9));
  std::cout << "\nSearching for 340 (end of list)" << std::endl;
  contains(skip_list.search(340));
  std::cout << "\nSearching for 0 (smaller than anything within the list)" << std::endl;
  contains(skip_list.search(0));
  std::cout << "\nSearching for 15 (would be within the list)" << std::endl;
  contains(skip_list.search(15));
  std::cout << "\nSearching for 1000 (beyond end of list)" << std::endl;
  contains(skip_list.search(1000));
  std::cout << std::endl;

  return 0; 
}