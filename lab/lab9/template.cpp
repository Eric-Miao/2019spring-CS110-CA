#include <iostream>

// For your reference
template <typename T>
T add (T a, T b)
{
  return a + b;
}

// Implement the following function
// Function that returns the product of two numbers
template <typename T>
T mul (T a, T b)
{
    return a*b;
  // Your code here
}

// Function that returns the maximum number of the two.
template <typename T>
T max(T a, T b)
{
    return a>b?a:b;
}
// Your code here

int main ()
{
  std::cout << "mul (1 + 2, 3 + 4) = " << mul (1 + 2, 3 + 4) << ", expected 21\n";
  int a, b;
  a = 10;
  b = 15;
  std::cout << "max (a++, b) is " << max (a++, b) << ", expected 15\n";
  std::cout << "After the function, a is " << a << ", expected 11\n";
  a = 15;
  b = 10;
  std::cout << "max (a++, b) is " << max (a++, b) << ", expected 15\n";
  std::cout << "After the function, a is " << a << ", expected 16\n";
  return 0;
}
