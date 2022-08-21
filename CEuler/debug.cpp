#include "debug.hpp"

#include <iostream>

using namespace std;

namespace Debug 
{
template<class IteratorType>
void print(IteratorType it, IteratorType end)
{
    cout << "[";
    while (it != end) {
        cout << *(it++);
        if (it != end) cout << ",";
    }
    cout << "]" << endl;
}

void print(const bool booleanArray[])
{
    cout << "[";
    for (bool boolean : booleanArray) {
        cout << boolean << ",";
    }
    cout << "]" << endl;
}

std::string toString(bool boolean) { return boolean ? "true" : "false"; }
}