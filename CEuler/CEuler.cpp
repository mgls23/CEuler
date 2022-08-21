#include "CEuler.hpp"

#include <iostream>
#include <chrono>

#include "prime.hpp"
#include "debug.hpp"

int sum(int N) { return (N * (N + 1)) / 2; }
int sumOfMultiples(int upperBound, int multiple) { return multiple * (sum(upperBound / multiple)); }

int THOUSAND = 1000;
int MILLION = THOUSAND * THOUSAND;

int problem3Sieve(long long upperBound = 600851475143LL)
{
	int maxPrimeFactor = -1;
	auto primeNumbers = Prime::generate((int) sqrt(upperBound));
	for (auto primeNumber : primeNumbers) {
		std::cout << primeNumber << std::endl;
		while (upperBound % primeNumber == 0) {
			upperBound /= primeNumber;
			maxPrimeFactor = primeNumber;
		}

		if (upperBound == 1LL) break;
	}
	
	return maxPrimeFactor;
}

int problem3Copied(unsigned long long x = 600851475143LL)
{
	// https://euler.stephan-brumme.com/3/
	for (unsigned long long factor = 2; factor * factor <= x; factor++)
		// remove factor, actually it's a prime
		// (can occur multiple times, e.g. 20=2*2*5)
		while (x % factor == 0 && x != factor) // note: keep last prime
			x /= factor;
	
	return (int) x;
}

int problem3(unsigned long long upperBound = 600851475143LL)
{
	unsigned long long remaining = upperBound;
	auto breakDown = [&remaining](long long potentialPrime) {
		while (remaining % potentialPrime == 0 && remaining != potentialPrime)
			remaining /= potentialPrime;

		return remaining == potentialPrime;
	};

	// TODO :: not sure why this version is not working for 
	// HackerRank
	if (!breakDown(2LL) && !breakDown(3LL))
		for (unsigned long long number = 6LL; number <= upperBound + 1LL; number += 6LL)
			if (breakDown(number - 1LL) || breakDown(number + 1LL)) break;

	return (int) remaining;
}

int problem2(int notBiggerThan = 4 * MILLION)
{
	// TODO :: for HackerRank, int -> long
	// Every 3rd fibonacci sequence is even
	// Odd + Odd  = Even (1 + 1 = 2) (3 + 5 = 8)s
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

long problem5(int upperBound = 2 * 10)
{
	using namespace std;
	// This is duplicating code - however, just because this is C++, I have written a
	// specially optimised version (using the sieve)
	long sum = 0;
	bool* sieve = new bool[upperBound + 1];
	memset(sieve, true, sizeof(sieve));
	
	for (int number = 2; number <= upperBound; ++number) {
		std::cout << number << std::endl;
		Debug::print(sieve);

		if (sieve[number]) {
			std::cout << "Prime" << std::endl;
			sum += number;
			// https://www.researchgate.net/post/Is-multiplication-slower-than-addition-on-modern-CPUs
			// There is disagreement on whether adding number to itself is faster or if multiplying by 2 is
			for (int multiple = number + number; multiple < upperBound; multiple += number) {
				sieve[multiple] = false;
			}
		}
	}

	return sum;
}



int main()
{
	using namespace std;
	using namespace std::chrono;

	auto beg = high_resolution_clock::now();

	auto answer = problem5();

	auto end = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(end - beg);
	cout << "Answer = " << answer << ", took " << duration.count() << "[ms]" << endl;
	return 0;
}