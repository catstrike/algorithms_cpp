#include <vector>
#include <iostream>
#include <functional>
#include <sstream>

using namespace std;

template <class T>
void adjust_boundries(const vector<T>& array, size_t& left, size_t& right, T value)
{
    auto l = left;
    auto r = right;
    while (l < r) {
        auto middle = l + (r - l) / 2;

        if (array[middle] > array[r]) {
            l = middle + 1;
        } else {
            r = middle;
        }
    }

    if (array[left] > value) {
        left = l;
    } else {
        right = l - 1;
    }
}

template <class T>
int search_rotated(const vector<T>& array, T value)
{
    if (array.size() == 0) {
        return -1;
    }

    size_t left = 0;
    size_t right = array.size() - 1;

    if (array[left] > array[right]) {
        adjust_boundries(array, left, right, value);
    }

    if (array[left] > value || array[right] < value) {
        return -1;
    }

    while (left <= right) {
        auto middle = left + (right - left) / 2;

        if (array[middle] == value) {
            return middle;
        }

        if (array[middle] < value) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1;
}

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
    TestMethod<int> testMethod(search_rotated<int>);
    
    //                0  1  2  3  4  5  6  7  8
    test(testMethod, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 5, 2);
    test(testMethod, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 1, 7);
    test(testMethod, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 1, 0);
    test(testMethod, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 9, 8);
    test(testMethod, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 5, 4);
    test(testMethod, {9, 1, 2, 3, 4, 5, 6, 7, 8}, 9, 0);
    test(testMethod, {9, 1, 2, 3, 4, 5, 6, 7, 8}, 8, 8);
    test(testMethod, {9, 1, 2, 3, 4, 5, 6, 7, 8}, 1, 1);
    test(testMethod, {9, 1, 2, 3, 4, 5, 6, 7, 8}, 7, 7);
    test(testMethod, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 10, -1);
    test(testMethod, {3, 4, 5, 6, 7, 8, 9, 1, 2}, 0, -1);
    test(testMethod, {3, 4, 5, 6, 7, 8, 10, 1, 2}, 9, -1);
    return 0;
}