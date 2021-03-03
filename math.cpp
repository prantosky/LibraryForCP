#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace Math {
	template <typename T,
			  std::enable_if_t<std::is_integral<T>::value, bool> = true>
	static long pow_mod(T radix, int exponent, const T mod) {
		if (exponent < 0) {
			throw std::invalid_argument(
				"math::pow_mod: pow_mod will misbehave for negative values of "
				"exponent");
		}
		long base = radix;
		long result = 1;

		while (exponent > 0) {
			if ((exponent & 1) != 0) {
				result = (result * base) % mod;
			}
			exponent >>= 1;
			if (exponent == 0) break;
			base = (base * base) % mod;
		}
		return result;
	}

	template <typename T,
			  std::enable_if_t<std::is_integral<T>::value, bool> = true>
	static long pow(T radix, int exponent) {
		long base = radix;
		long result = 1;
		while (exponent != 0) {
			if ((exponent & 1) != 0) {
				result *= base;
			}
			exponent >>= 1;
			if (exponent == 0) break;
			base *= base;
		}
		return result;
	}

	template <typename T,
			  std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
	static double pow(T radix, int exponent) {
		double base = radix;
		double result = 1;
		while (exponent != 0) {
			if ((exponent & 1) != 0) {
				result *= base;
			}
			exponent >>= 1;
			if (exponent == 0) break;
			base *= base;
		}
		return result;
	}

}  // namespace Math

namespace primes {}
