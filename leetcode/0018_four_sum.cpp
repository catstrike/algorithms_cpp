#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

using tuple4 = tuple<int, int, int, int>;

struct tuple4_hash {
    size_t operator()(const tuple4& input) const {
        return get<0>(input) ^ get<1>(input) ^ get<2>(input) ^ get<3>(input);
    }
};

vector<vector<int>> fourSum2(vector<int>& nums, int target) 
{
    auto count = nums.size();

    if (count < 4) {
        return {};
    }

    sort(begin(nums), end(nums));

    unordered_set<tuple4, tuple4_hash> candidates;

    auto last1 = nums[count - 1];
    auto last2 = nums[count - 2];
    auto last3 = nums[count - 3];
    
    for (int i = 0; i < count - 3; ++i) {
        auto a = nums[i];
        if(i > 0 && nums[i] == nums[i - 1]) { continue; }
        if(a + last3 + last2 + last1 < target) {continue;}
        if(a + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) { break; }

        for (int j = i + 1; j < count - 2; ++j) {
            auto b = nums[j];
            auto sum2 = a + b;

            if(j > i + 1 && b == nums[j - 1]) {continue;}
            if(sum2 + last2 + last1 < target) {continue;}
            if(sum2 + nums[j + 1] + nums[j + 2] > target) {break;}

            auto left = j + 1;
            auto right = count - 1;
            
            while (left < right) {
                if (left == i) {
                    left++;
                    continue;
                }
                if (right == i) {
                    right--;
                    continue;
                }

                auto c = nums[left];
                auto d = nums[right];
                auto sum4 = sum2 + c + d;

                if (sum4 == target) {
                    candidates.insert(make_tuple(a, b, c, d));
                    right--;
                    left++;
                    continue;
                }

                if (sum4 > target) {
                    right--;
                } else {
                    left++;
                }
            }

        }
    }

    vector<vector<int>> result;

    for (auto& candidate : candidates) {
        result.push_back({
            get<0>(candidate),
            get<1>(candidate),
            get<2>(candidate),
            get<3>(candidate)
        });
    }

    return result;
}

vector<vector<int>> fourSum(const vector<int>& nums, int target) 
{
    using pair_vector = vector<pair<int, int>>;

    auto size = nums.size();

    unordered_map<int, pair_vector> sum2((size * size - size) / 2);

    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            sum2[nums[i] + nums[j]].push_back({i, j});
        }
    }

    vector<vector<int>> candidates;

    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            auto expected = target - (nums[i] + nums[j]);
            auto it = sum2.find(expected);

            if (it == end(sum2)) {
                continue;
            }

            for (auto& indices : it->second) {
                auto a = indices.first;
                auto b = indices.second;

                if (a == i || a == j || b == i || b == j) {
                    continue;
                }

                vector<int> candidate {
                    nums[i],
                    nums[j],
                    nums[indices.first],
                    nums[indices.second]
                };

                sort(begin(candidate), end(candidate));

                if (find(begin(candidates), end(candidates), candidate) != end(candidates)) {
                    continue;
                }

                candidates.push_back(candidate);
            }
        }
    }

    return candidates;
}


void print_result(const vector<vector<int>>& result)
{
    cout << "[" << endl;
    for (auto& row : result) {
        cout << "  {";
        if (row.empty()) {
            continue;
        }
        cout << row[0];
        auto it = begin(row);
        advance(it, 1);

        for (; it != end(row); ++it) {
            cout << ", " << *it;
        }
        cout << "}" << endl;
    }
    cout << "]" << endl;
}

int main()
{
    vector<int> test01 {1, 0, -1, 0, -2, 2};
    vector<int> test02 {-3,-2,-1,0,0,1,2,3};
    auto result = fourSum2(test02, 0);

    print_result(result);

    return 0;
}