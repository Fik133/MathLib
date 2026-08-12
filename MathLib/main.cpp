#include "lib/mathlib.hpp"
#include <iostream>
int main() {
	//for (float i = 0; i < 10; i += 0.01f)
	//{
	//	std::cout << "(2PI*" << i << ") " << mathlib::sin(2 * mathlib::PI * i) << " ";
	//	std::cout << mathlib::cos(2 * mathlib::PI * i) << " ";
	//	std::cout << mathlib::tan(2 * mathlib::PI * i) << "\n";
	//}
	std::cout << mathlib::tan(mathlib::PI / 2);
}