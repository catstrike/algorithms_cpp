#ifndef _SHARED_TEST_H_
#define _SHARED_TEST_H_

#include <iostream>
#include <vector>

template <class TypeArgument>
void output_argument(TypeArgument argument)
{
    std::cout << argument;
}

template <class TypeArgument, class ... TypeOther>
void output_argument(TypeArgument argument, TypeOther... otherArguments)
{
    std::cout << argument << ", ";

    output_argument(otherArguments...);
}

template <class TypeReturn, class ... TypesInput>
void my_test_method(std::string methodName, TypeReturn method(TypesInput...), TypeReturn expected, TypesInput... arguments)
{
    TypeReturn result = method(arguments...);

    bool testResult = result == expected;
    std::string plusMinus = testResult ? "[+]" : "[-]";

    std::cout << plusMinus << " " << methodName << "(";
    output_argument(arguments...);
    std::cout << ") -> " << result << ", expected: " << expected << std::endl; 
}

#define my_test(method, result, ...) my_test_method(#method, method, result, __VA_ARGS__)

#endif // _SHARED_TEST_H_