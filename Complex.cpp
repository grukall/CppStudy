#include "Complex.h"

Complex::~Complex()
{
}


int main() {
  Complex a(1.0, 2.0);
  Complex b(3.0, -2.0);

  Complex c = a * b;

  c.println();
}