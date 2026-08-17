#include <iostream>
#include <iomanip>
#include "lib/mathlib.hpp"

int main() {
	std::cout << std::setprecision(17) << mathlib::atan(1) * 4 << "\n";
}