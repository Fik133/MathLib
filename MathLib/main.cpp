#include <iostream>
#include <iomanip>
#include "lib/mathlib.hpp"

int main() {
	std::cout << std::setprecision(17) << "PI: " << mathlib::atan(3) << "\n";
}