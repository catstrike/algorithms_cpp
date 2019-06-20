#include <vector>
#include <unordered_set>

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
