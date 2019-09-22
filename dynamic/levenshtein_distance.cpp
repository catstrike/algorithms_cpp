#include <iostream>
#include <functional>

using namespace std;

using TestMethod = function<int(const string&, const string&)>;

int min(int a, int b, int c)
{
	return min(a < b ? a : b, c);
}

template <class It>
int distanceRecursiveInternal(It first, It firstEnd, It second, It secondEnd)
{
	if (first == firstEnd) {
		return distance(second, secondEnd);
	}

	if (second == secondEnd) {
		return distance(first, firstEnd);
	}

	if (*first == *second) {
		return distanceRecursiveInternal(
			first + 1, firstEnd,
			second + 1, secondEnd
		);
	}

	return 1 + min(
		distanceRecursiveInternal(first + 1, firstEnd, second + 1, secondEnd),
		distanceRecursiveInternal(first, firstEnd, second + 1, secondEnd),
		distanceRecursiveInternal(first + 1, firstEnd, second, secondEnd)
 	);
}

int distanceRecursive(const string& first, const string& second)
{
	return distanceRecursiveInternal(
		first.begin(), first.end(),
		second.begin(), second.end()
	);
}

void test(TestMethod method, const string& first, const string& second, int expected)
{
	auto result = method(first, second);
	auto resultString = expected == result
		? "[+]"
		: "[-]";

	cout << resultString << " " << first << " and " << second << ": " << result << endl;
}

int main()
{
	test(distanceRecursive, "future", "feature", 2);
	test(distanceRecursive, "feature", "feature", 0);
	test(distanceRecursive, "abc", "ac", 1);
	test(distanceRecursive, "abbc", "abc", 1);
	test(distanceRecursive, "aabbccdd", "abc", 5);	
	
	return 0;
}
