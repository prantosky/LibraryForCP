#include <cmath>
#include <cstddef>
#include <type_traits>
#include <vector>

namespace math {

	template <typename T,
			  std::enable_if_t<std::is_integral<T>::value, bool> = true>
	long pow_mod(long radix, unsigned long exponent, const long mod) {
		long result = 1;

		while (exponent > 0) {
			if ((exponent & 1) != 0) {
				result = (result * radix) % mod;
			}
			exponent >>= 1;
			if (exponent == 0) break;
			radix = (radix * radix) % mod;
		}
		return result;
	}

	template <typename T,
			  std::enable_if_t<std::is_integral<T>::value, bool> = true>
	long pow(T radix, int exponent) {
		long result = 1;
		while (exponent != 0) {
			if ((exponent & 1) != 0) {
				result *= radix;
			}
			exponent >>= 1;
			if (exponent == 0) break;
			radix *= radix;
		}
		return result;
	}

	template <typename T,
			  std::enable_if_t<std::is_floating_point<T>::value, bool> = true>
	double pow(double radix, int exponent) {
		double result = 1;
		while (exponent != 0) {
			if ((exponent & 1) != 0) {
				result *= radix;
			}
			exponent >>= 1;
			if (exponent == 0) break;
			radix *= radix;
		}
		return result;
	}
}  // namespace math

namespace prime {

	std::vector<std::size_t> first_n_primes(const std::size_t n) {
		if (n == 0) return {};
		if (n == 1) return {2};

		std::vector<size_t> primes({2, 3});
		primes.reserve(n);

		std::size_t i = 2;
		std::size_t candidate = 5;
		bool is_prime = false;

		while (i < n) {
			is_prime = true;
			long sqrt = std::ceil(std::sqrt(candidate));

			for (auto& prime : primes) {
				if (prime > sqrt) break;
				if (candidate % prime == 0) {
					is_prime = false;
				}
			}
			if (is_prime) {
				primes.emplace_back(candidate);
				i++;
			}
			candidate += 2;
		}
		return primes;
	}

	void generate_next_primes(std::vector<std::size_t>& primes,
							  const std::size_t count = 2) {
		if (primes.empty()) {
			primes = prime::first_n_primes(count);
			return;
		}

		size_t i = 0;
		size_t candidate = primes.back() + 2;
		bool is_prime = false;

		while (i < count) {
			is_prime = true;
			long sqrt = std::ceil(std::sqrt(candidate));

			for (auto& prime : primes) {
				if (prime > sqrt) break;
				if (candidate % prime == 0) {
					is_prime = false;
				}
			}
			if (is_prime) {
				primes.emplace_back(candidate);
				i++;
			}
			candidate += 2;
		}
	}

	bool is_prime(std::vector<size_t>& primes, const size_t num,
				  const int step = 2) {
		if (num <= 2) return num == 2;
		if (primes.empty()) {
			primes = prime::first_n_primes(step);
		}
		long sqrt = std::ceil(std::sqrt(num));
		while (sqrt > primes.back()) {
			prime::generate_next_primes(primes, step);
		}
		for (auto& prime : primes) {
			if (prime > sqrt) break;
			if (num % prime == 0) {
				return false;
			}
		}
		return true;
	}

}  // namespace prime
