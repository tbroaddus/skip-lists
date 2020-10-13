#include <iostream>

#include "Skip_List.h"

int main(int argc, char** argv) {

  Skip_List<int,3> skip_list;
  skip_list.add_element(5);
  skip_list.add_element(4);
  skip_list.add_element(6);
  skip_list.add_element(8);
  skip_list.add_element(5);
  skip_list.add_element(7);
  skip_list.print_layers();
}