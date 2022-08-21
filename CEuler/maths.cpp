#include "maths.hpp"

template<class inputType>
int numberOfDigits(inputType number)
{
	int digits = 0;
	inputType ten = (inputType) 10;
	for (; number > 0; number /= ten) ++digits;
	return digits;
}