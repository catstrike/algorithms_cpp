#include <vector>
#include <unordered_set>

#include "my_serialization.h"
#include "my_test.h"

using namespace std;

vector<int> twoNumberSum(vector<int> array, int targetSum) {
	unordered_set<int> numbers;
	
	for (auto value : array) {
		auto delta = targetSum - value;
		
		if (!numbers.count(delta)) {
			numbers.insert(value);
			continue;
		}
		
		if (value < delta) {
			return {value, delta};
		} else {
			return {delta, value};
		}
		break;
	}
	
	return {};
}

int main()
{
	my_test(twoNumberSum, vector<int>{2, 7}, vector<int>{10, 20, 2, 7, -1}, 9);
	my_test(twoNumberSum, vector<int>{-1, 7}, vector<int>{10, 20, 2, 7, -1}, 6);
	my_test(twoNumberSum, vector<int>{10, 20}, vector<int>{10, 20, 2, 7, -1}, 30);

	return 0;
}