#include "lib/mathlib.hpp"
#include <iostream>
int main() {
	for (float i = 0; i < 10; i += 0.001f)
	{
		std::cout << "sin(2PI*" << i << ") " << mathlib::sin(2 * mathlib::PI * i) << "\n";
	}
}