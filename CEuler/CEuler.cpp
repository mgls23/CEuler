#include "CEuler.hpp"

#include <iostream>

int sum(int N) { return (N * (N + 1)) / 2; }
int sumOfMultiples(int upperBound, int multiple) { return multiple * (sum(upperBound / multiple)); }

int THOUSAND = 1000;
int MILLION = THOUSAND * THOUSAND;

int problem3(long long upperBound = 600851475143LL)
{
	long long remaining = upperBound;
	int maxPrime = -1;
	auto breakDown = [&remaining, &maxPrime](int potentialPrime) {
		while (remaining % potentialPrime == 0) {
			remaining /= potentialPrime;
			maxPrime = std::max(maxPrime, potentialPrime);
		}

		return remaining == 1;
	};

	if (!breakDown(2) && !breakDown(3))
		for (int number = 6; number <= upperBound + 1; number += 6)
			if (breakDown(number - 1) || breakDown(number + 1)) return maxPrime;

	return -1;
}

int problem2(int notBiggerThan = 4 * MILLION)
{
	// TODO :: for HackerRank, int -> long
	// Every 3rd fibonacci sequence is even
	// Odd + Odd  = Even (1 + 1 = 2) (3 + 5 = 8)
	// Odd + Even = Odd  (1 + 2 = 3)
	// Even + Odd = Odd  (2 + 3 = 5) [goto Odd + Odd for (3 + 5)]
	int fib1 = 1, fib2 = 1, fib3 = 2;
	int sumEvenFibonacci = 0;
	while (fib3 < notBiggerThan)
	{
		// std::cout << fib1 << ", " << fib2 << ", " << fib3 << std::endl;
		sumEvenFibonacci += fib3;

		// This way, it doesn't incur swap
		fib1 = fib2 + fib3;
		fib2 = fib1 + fib3;
		fib3 = fib1 + fib2;
	}

	return sumEvenFibonacci;
}

int problem1(int upperBound = 1000)
{
	// TODO :: for HackerRank, int -> long
	--upperBound;
	int multiplesOf3 = sumOfMultiples(upperBound, 3);
	int multiplesOf5 = sumOfMultiples(upperBound, 5);
	int multiplesOf15 = sumOfMultiples(upperBound, 15);

	return multiplesOf3 + multiplesOf5 - multiplesOf15;
}

int main()
{
	std::cout << problem3() << std::endl;
	return 0;
}