#include "prime.hpp"

#include <memory>

namespace Prime {

std::vector<int> generate(int upTo)
{
	// Note - std::vector<bool> is not an STL - so we have to use dynamic array.
	// https://stackoverflow.com/questions/2468203/how-can-i-make-new-default-initialize-the-array-of-primitive-types/2468254#2468254 
	std::unique_ptr<bool[]> sieve{ new bool[upTo + 1] {true} };
	std::vector<int> primeNumbers;

	// We create 0 and 1 unnecessarily, but better this than to introduce potential offset by 1 error
	for (int number = 2; number < upTo; ++number) {
		if (sieve[number]) {
			primeNumbers.emplace_back(number);
			for (int multiple = number * 2; multiple < upTo; ++multiple) {
				sieve[multiple] = false;
			}
		}
	}

	return primeNumbers;
}

}