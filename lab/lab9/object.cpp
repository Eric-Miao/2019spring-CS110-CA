#include <iostream>

class Int
{
public:
  Int ();
  Int (int v);
  ~Int ();

  // Here const means this method will not
  // modify class's members.
  int get_value () const;

  // Which one is related to i++?
  // Give it a try.
  int &operator++ (); //++a return a+1
  int operator++ (int); //a++ return a
private:
  int value;
};

// Default constructor.
// Implement method outside the class body needs to add
// field name `<class_name>::' in front of the function name.
// The thing after colon is an initializer list, which is
// used to simplify initialzation.
Int::Int () : value (0) {}

// Implement the remaining methods here.
Int::Int(int v) : value(v){};

Int::~Int(){};

int Int::get_value() const{
    return this->value;
}

int& Int::operator++(){
    this->value++;
    return this->value;
}

int Int::operator++ (int){
    int ret = this->value;
    this->value++;
    return ret;
}

int main ()
{
  Int a;
  std::cout << "Value of a is " << a.get_value () << ", expected 0.\n";
  Int b (5);
  std::cout << "Value of b is " << b.get_value () << ", expected 5.\n";
  int c = b++;
  std::cout << "Value of c is " << c << ", expected 5.\n";
  int d = ++b;
  std::cout << "Value of d is " << d << ", expected 7." << std::endl;
  return 0;
}
