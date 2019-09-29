#include <vector>
#include <iostream>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;


// Time:  n*log(k)
// Space: k
// Comparer: {less: k-th smallest, greater: k-th largest }
template <class ItemType, class Comparer = less<ItemType>>
ItemType kth_element_heap(const vector<ItemType>& array, ItemType k)
{
    priority_queue<ItemType, vector<ItemType>, Comparer> heap;

    for (int i = 0; i < k; i++) {
        heap.push(array[i]);
    }

    for (int i = k; i < array.size(); ++i) {
        heap.push(array[i]);
        heap.pop();
    }

    return heap.top();
}

// ---

template <class It>
It my_partition(It left, It right)
{
    It pivot = left;
    left++;
    right--;

    while (left <= right) {
        if (*left > *pivot && *right <= *pivot) {
            iter_swap(left, right);
        }

        if (*left <= *pivot) {
            left++;
        }
        if (*right > *pivot) {
            right--;
        }
    }

    iter_swap(right, pivot);

    return right;
}

// Time: avg n
// Space: 1

int kth_largest_partition(const vector<int>& sourceArray, int k)
{
    vector<int> array(sourceArray);

    auto end = array.end();
    auto left = array.begin();
    auto right = end;

    auto expected_it = array.end() - k;

    int n = 10;

    while (left <= right) {
        auto it = my_partition(left, right);
        auto d = distance(it, end);

        if (d == k) {
            return *it;
        }

        if (d > k) {
            left = it + 1;
        } else {
            right = it;
        }
        if (n-- == 0) {
            break;
        }
    }

    return -1;
}

// TESTS
template<class T> using TestMethod = function<int(const vector<T>&, T)>;

template<class T>
void test(TestMethod<T> method, const vector<T>& array, T value, T expected)
{
	auto result = method(array, value);
	auto resultString = expected == result
		? "[+]"
		: "[-]";

    stringstream ss;

    for (auto& item : array) {
        ss << item << " ";
    }

	cout << resultString << " " << ss.str() << "<- " << value << " : " << result << endl;
}

int main()
{
    TestMethod<int> testMethod1(kth_element_heap<int, greater<int>>);
    TestMethod<int> testMethod2(kth_largest_partition);

    test(testMethod1, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 2, 8);
    test(testMethod1, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 1, 9);
    test(testMethod1, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 3, 7);
    test(testMethod1, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 5, 5);
    test(testMethod1, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 9, 1);

    test(testMethod2, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 2, 8);
    test(testMethod2, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 1, 9);
    test(testMethod2, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 3, 7);
    test(testMethod2, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 5, 5);
    test(testMethod2, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 9, 1);

    return 0;
}