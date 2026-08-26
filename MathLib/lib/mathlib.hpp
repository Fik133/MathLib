#include <math.h>
namespace mathlib {
	namespace constants {
		inline constexpr double PI = 3.14159265358979323846;
		inline constexpr double E = 2.71828182845904523536;
	}

	namespace definitions {
		inline const double NaN = 0.0 / 0.0;
		inline const double INF_POSITIVE = 1.0 / 0.0;
		inline const double INF_NEGATIVE = -1.0 / 0.0;
	}

	inline double degrees(double rad) {
		return (180.0 / constants::PI) * rad;
	}

	inline double radians(double deg) {
		return (constants::PI / 180.0) * deg;
	}

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

	inline double ceil(double value) {
		const double f = floor(value);
		return f != value ? f + 1.0 : f;
	}

	inline unsigned int factorial(unsigned int value) {
		if (value == 0) return 1;

		unsigned int result = 1;
		for (unsigned int i = 2; i <= value; ++i) {
			result *= i;
		}
		return result;
	}

	template<typename T>
	inline void swap(T& e1, T& e2) {
		T temp1 = e1;
		e1 = e2;
		e2 = temp1;
	}

	template<typename T>
	inline T clamp(T value, T min, T max) {
		if (min > max)
			swap(max, min);

		return (value > max) ? max : ((value < min) ? min : value);
	}

	template<typename T>
	inline T lerp(T a, T b, double t) {
		return static_cast<T>(a + (b - a) * t);
	}

	// Sine trigonometric function [Taylor series]
	inline double sin(double angle) {
		constexpr int PRECISION = 10; // length of the sine series, the higher the number the higher the precision
		double currentAngle = angle;

		// let say angle = 15 => 15.0 / 6.28 = 2.388 or angle = -15 => -15.0 / 6.28 = -2.388
		// so static cast makes the safe_multiplier = 2 or safe_multiplier = -2
		// and it adds up the value of 2 * PI which is currentAngle -= 2 * 6.28 or currentAngle -= (-2) * 6.28 so currentAngle += 2 * 6.28
		int safe_multiplier = static_cast<int>(currentAngle / (2 * constants::PI));
		currentAngle -= safe_multiplier * (2 * constants::PI);

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
		return sin(angle + (constants::PI / 2));
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

	// Inverse tangent [Taylor Series]
	inline double atan(double value) {
		// trigonometric identity -atan(x) = atan(-x)
		// I used it so I wouldn't repeat myself below
		if (value < 0.0) {
			return -atan(-value);
		}

		// this series works correctly only for values = [from -1 to 1]
		// so I had to use trig identity atan(x) = PI/2 - atan(1/x)
		if (value > 1) {
			return (constants::PI / 2.0) - atan(1.0 / value);
		}

		// atan series -> sum n = 0 to n = PRECISION (-1)^n * x^(2n+1)/(2n+1)
		double term = value;
		double result = 0.0;
		constexpr double PRECISION = 10000;
		for (double n = 0; n < PRECISION; n++)
		{
			result += term;

			// maximum double precision is 1 * 10^-16
			// so we wanna break from the loop once we reach that point
			if (abs(term) < 1e-16) {
				break;
			}

			term = -term * (value * value) * ((2.0 * n + 1.0) / (2.0 * n + 3.0));
		}

		return result;
	}

	// Inverse sine [Taylor Series]
	inline double asin(double value) {
		if (abs(value) > 1) // sine can be only in range from -1 to 1
			return definitions::NaN;

		if (value < -0.5) {
			return -asin(-value);
		}

		// need this because when value is close to 1 the series converges really slowly
		// so to fix that I had to change the range from -1 to 1 to a range from -0.5 to 0.5
		if (value > 0.5) {
			return constants::PI / 2.0 - 2.0 * asin(sqrt((1 - value) / 2));
		}
		constexpr size_t PRECISION = 100;

		double term = value;
		double result = 0.0;

		// asin series -> sum n = 0 to PRECISION ((2n-1)!!)/((2n)!! * (2n+1)) * x^(2n+1)
		for (size_t n = 0; n < PRECISION; n++)
		{
			result += term;

			// maximum double precision is 1 * 10^-16
			// so we wanna break from the loop once we reach that point
			if (abs(term) < 1e-16) {
				break;
			}

			term = (term * (value * value)) * ((2 * n + 1) * (2 * n + 1)) / ((2 * n + 2) * (2 * n + 3));
		}

		return result;
	}

	// Inverse cosine based on defined arcus sine
	inline double acos(double value) {
		// trigonometric identity acos(x) = PI/2 - asin(x)
		if (abs(value) > 1) return definitions::NaN;
		return (constants::PI / 2) - asin(value);
	}

	// Inverse cotangent based on defined inverse tangent
	inline double acot(double value) {
		// trigonometric identity acot(x) = PI/2 - atan(x)
		return (constants::PI / 2) - atan(value);
	}

	// Inverse full range tangent defined on inverse tangent
	inline double atan2(double y, double x) {
		// 1st and 4th quadrant
		if (x > 0)
			return atan(y / x);
		if (x < 0) {
			// 2nd quadrant
			if (y >= 0) {
				return atan(y / x) + constants::PI;
			}
			// 3rd quadrant
			else {
				return atan(y / x) - constants::PI;
			}
		}

		// Y-axis (x == 0)
		if (y > 0) return constants::PI / 2;
		if (y < 0) return -constants::PI / 2;

		return 0.0;
	}

	// Natural logarithm
	inline double ln(double value) {
		// value of ln(0) is undefined
		// value of ln(x < 0) doesn't belong to the set of real numbers
		if (value <= 0)
			return definitions::NaN;

		long int k = 0;

		// need this because when the value is bigger than 2 this series diverges
		// you can derrive this by x = e^k * m => ln (e^k * m) = k + ln(m)
		// i'm getting k value here where value so the m is < 2
		while (value > 1.5) {
			value /= constants::E;
			k++;
		}
		while (value < 0.5) {
			value *= constants::E;
			k--;
		}

		constexpr size_t PRECISION = 100;

		// i had to use -1.0 because i'm getting the output of function g(x) = ln(x+1) so to get x I'm doing (x - 1) operation
		double term = value - 1.0;
		double result = 0.0;

		for (size_t n = 1; n <= PRECISION; n++)
		{
			result += term;

			// maximum double precision is 1 * 10^-16
			// so we wanna break from the loop once we reach that point
			if (abs(term) < 1e-16) {
				break;
			}

			term = -term * (n) / (n + 1.0) * (value - 1.0);
		}

		return static_cast<double>(k) + result; // ln(e^k * m) = k + ln(m)
	}

	// Exponential function e^x
	inline double exp(double value) {
		// 0^0 is undefined in mathematical analysis but since we're in a real world I had to define it somehow
		// since a^0 where a != 0 for every real number is equal to 1 then 1 is a pretty good guess
		if (value == 0.0) return 1.0;

		// this basically shifts from negative value to positive because in order to get e^x where x is big
		// i'd have to set the precision up to a very high number or it might be even impossible because of a variable limits
		// also the series would shift to 1 - value + value^2/2! - a + ... a_n so the function diverges way slower
		if (value < 0.0) {
			return 1.0 / exp(-value);
		}

		// using magic of recursion we change the range of this function. it will do this operation until the condition is met
		// basic power identity e^x = (e^x/2)^2
		if (value > 1.0) {
			double half_exp = exp(value / 2);
			return half_exp * half_exp;
		}

		// term = 1.0 because I assume that x != 0 and a = x^n/n! = x^0/0! = 1
		// and if value = x = 0 then in mathematical analysis the symbol 0^0 is undefined
		// so in that case for the very first term in our series we'd get undefined symbol
		double term = 1.0;
		double result = 0.0;
		constexpr size_t PRECISION = 100;

		// taylor series -> sum n = 0 to n = PRECISION x^n/n!
		for (size_t n = 0; n < PRECISION; n++)
		{
			result += term;

			// maximum double precision is 1 * 10^-16
			// so we wanna break from the loop once we reach that point
			if (abs(term) < 1e-16) {
				break;
			}

			term = term * (value / (n + 1.0));
		}

		return result;
	}

	// Power a^x function implemented using ln and exp functions

	inline double pow(double base, double power) {
		// 0^0 is undefined in mathematical analysis but since we're in a real world I had to define it somehow
		// since a^0 where a != 0 for every real number is equal to 1 then 1 is a pretty good guess
		if (power == 0)
			return 1.0;

		if (base == 0) {
			// since x^-n = 1/x^n and when x = 0 then this expression is equal to 1/0 which is +inf
			if (power < 0) {
				return definitions::INF_POSITIVE;
			}
			return 0.0;
		}

		if (base < 0) {
			long long int_power = static_cast<long long>(power);

			if (int_power != power) {
				// if power is fractional like 1/2 it means it's a root and we can't get root of -1 in the set of real numbers
				// to do so we'd need to use imaginary set of numbers and I don't really want to implement that
				// maybe some day but I doubt it :P
				return definitions::NaN;
			}

			// even power -> 1 odd -> -1
			short direction = (int_power % 2 == 0) ? 1 : -1;

			return direction * exp(ln(abs(base)) * power);
		}

		return exp(ln(base) * power);
	}

	// add sqrt function and add it to asin function
	inline double sqrt(double value) {
		if (value < 0) return definitions::NaN;
		if (value == 0) return 0.0;
		// to be finished
	}
}