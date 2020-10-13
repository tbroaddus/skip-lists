#include <iostream>

#include "Skip_List.h"

int main(int argc, char** argv) {

  Skip_List<int,5> skip_list;
  skip_list.add_element(2);
  skip_list.add_element(3);
  skip_list.add_element(8);
  skip_list.add_element(9);
  skip_list.add_element(39);
  skip_list.add_element(11);
 // skip_list.add_element(10);
  skip_list.add_element(20);
  skip_list.add_element(19);
  skip_list.add_element(7);
  skip_list.add_element(340);
  skip_list.add_element(6);
  //skip_list.add_element(21);

  //skip_list.add_element(10);
  skip_list.print_layers();
}