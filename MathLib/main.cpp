#include <iostream>
#include <iomanip>
#include "lib/mathlib.hpp"
#include <math.h>

int main() {
	// Przypadki brzegowe i wartości testowe
	double test_values[] = {
		1e-15, 1e-5, 0.001, 0.1, 0.49, 0.5, 0.99, 1.0, 1.01, 1.5, 2.0, 10.0, 1000.0, 1e10
	};

	std::cout << std::setw(15) << "Value"
		<< std::setw(20) << "Twoje ln(x)"
		<< std::setw(20) << "std::log(x)"
		<< std::setw(20) << "Błą d" << "\n";
	std::cout << std::string(75, '-') << "\n";

	for (double val : test_values) {
		double my_res = mathlib::ln(val);
		double std_res = std::log(val);
		double diff = std::abs(my_res - std_res);

		std::cout << std::scientific << std::setprecision(6)
			<< std::setw(15) << val
			<< std::setw(20) << my_res
			<< std::setw(20) << std_res
			<< std::setw(20) << diff << "\n";
	}
}