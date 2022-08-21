#include <string>

namespace Debug
{
template<class IteratorType>
void print(IteratorType it, IteratorType end);
void print(const bool array[]);

std::string toString(const bool boolean);
}