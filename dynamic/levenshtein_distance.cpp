#include <iostream>
#include <vector>
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

int distanceDynamic(const string& first, const string& second)
{
	int rows = second.size() + 1;
	int columns = first.size() + 1;

	vector<vector<int>> table(rows, vector<int>(columns));

	for (int i = 1; i < rows; ++i) {
		table[i][0] = i;
	}

	for (int j = 1; j < columns; ++j) {
		table[0][j] = j;
	}

	for (int i = 1; i < rows; ++i) {
		auto& secondChar = second[i - 1];

		for (int j = 1; j < columns; ++j) {
			auto& firstChar = first[j - 1];
			auto& cell = table[i][j];

			if (firstChar == secondChar) {
				cell = table[i - 1][j - 1];
				continue;
			}

			cell = 1 + min(
				table[i][j - 1],
				table[i - 1][j],
				table[i - 1][j - 1]
			);
		}
	}

	return table[rows - 1][columns - 1];
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
	vector<pair<string, TestMethod>> groups {
		{"Recursive", distanceRecursive},
		{"Dynamic", distanceDynamic}
	};

	vector<tuple<string, string, int>> tests {
		{"future", "feature", 2},
		{"feature", "feature", 0},
		{"abc", "ac", 1},
		{"abbc", "abc", 1},
		{"aabbccdd", "abc", 5}
	};

	for (auto& group : groups) {
		cout << group.first << endl;
		for (auto& testInfo : tests) {
			test(
				group.second,
				get<0>(testInfo),
				get<1>(testInfo),
				get<2>(testInfo)
			);
		}
	}
	
	return 0;
}
