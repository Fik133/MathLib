#include <math.h>
namespace mathlib {
	inline constexpr double PI = 3.14159265358979323846;
	inline double abs(double value) {
		return value < 0 ? -value : value;
	}
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
		constexpr int PRECISION = 10; // length of the sine series, the higher the number the higher the precision
		double currentAngle = angle;

		// let say angle = 15 => 15.0 / 6.28 = 2.388 or angle = -15 => -15.0 / 6.28 = -2.388
		// so static cast makes the safe_multiplier = 2 or safe_multiplier = -2
		// and it adds up the value of 2 * PI which is currentAngle -= 2 * 6.28 or currentAngle -= (-2) * 6.28 so currentAngle += 2 * 6.28
		int safe_multiplier = static_cast<int>(currentAngle / (2 * PI));
		currentAngle -= safe_multiplier * (2 * PI);

		double result = 0.0;
		double term = currentAngle;

		//this sums up to a simple series of sum n = 0 to n = PRECISION (-1)^n * x^(2n+1)/(2n+1)!
		for (size_t n = 1; n <= PRECISION; n++)
		{
			result += term;
			term = -(term * (currentAngle * currentAngle)) / ((2 * n) * (2 * n + 1));
		}

		return result;
	}

	inline double cos(double angle) {
		// sure I could've made this function with another series and it'd work just fine
		// but I wanted to use the DRY rule from Pragmatic Programmer book
		return sin(angle + (PI / 2));
	}

	inline double tan(double angle) {
		// basic trigonometric identity: tan(x) = sin(x)/cos(x)
		const double rise = sin(angle);
		const double run = cos(angle);

		if (run == 0) {
			// this simple code returns infinity or -infinity
			// and yes it's safe so there'll be no exceptions
			return rise >= 0 ? 1.0 / 0.0 : -1.0 / 0.0;
		}

		return rise / run;
	}

	// Inverse trigonometric functions

	inline double atan(double value) {
		// trigonometric identity -atan(x) = atan(-x)
		// I used it so I wouldn't repeat myself below
		if (value < 0.0) {
			return -atan(-value);
		}

		// this series works correctly only for values = [from -1 to 1]
		// so I had to use trig identity atan(x) = PI/2 - atan(1/x)
		if (value > 1.0) {
			return (PI / 2.0) - atan(1.0 / value);
		}

		// atan series -> sum n = 0, n = a (-1)^n * x^(2n+1)/(2n+1)
		double term = value;
		double result = 0.0;
		constexpr double PRECISION = 1000;
		for (double n = 0; n < PRECISION; n++)
		{
			result += term;
			term = -term * (value * value) * ((2.0 * n + 1.0) / (2.0 * n + 3.0));

			// maximum double precision is 1 * 10^-16
			// so we wanna break from the loop once we reach that point
			if (abs(term) < 1e-16) {
				break;
			}
		}

		return result;
	}
}