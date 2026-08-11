#include <math.h>
namespace mathlib {
	inline double PI = 3.14159f;
	inline double floor(double value) {
		int i = static_cast<int>(value);

		if (value < 0 && value != i) {
			return i - 1;
		}

		return i;
	}
	inline unsigned int factorial(unsigned int value) {
		if (value == 0) return 1;

		unsigned int result = 1;
		for (unsigned int i = 2; i <= value; ++i) {
			result *= i;
		}
		return result;
	}
	inline double sin(double angle) {
		constexpr int PRECISION = 10; // length of the sin series, the more the higher precision
		double currentAngle = angle;

		if (angle > 2 * PI) {
			double multiplier = currentAngle / (2 * PI);
			int safe_multiplier = floor(multiplier);
			currentAngle = currentAngle - (static_cast<double>(safe_multiplier) * (2 * PI));
		}
		else if (angle < -2 * PI) {
			double multiplier = currentAngle / (2 * PI);
			int safe_multiplier = floor(multiplier);
			currentAngle = currentAngle - (static_cast<double>(safe_multiplier) * (2 * PI));
		}

		double result = 0.0;
		double term = currentAngle;

		for (size_t n = 1; n <= PRECISION; n++)
		{
			result += term;

			term = -term * (currentAngle * currentAngle) / ((2 * n) * (2 * n + 1));
		}

		return result;
	}
}