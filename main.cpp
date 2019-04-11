#include <iostream>
#include <string>
using namespace std;
#include "expression.hpp"

int main() {
  cout << "Expression Test:" << endl;
  Expression test("1 -5 -");
  cout << "Computed value: " << test.compute() << endl;
  return 0;
}