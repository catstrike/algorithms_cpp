#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Range {
    int start;
    int end;
};

vector<Range> mergeRanges(vector<Range> ranges)
{
    vector<Range> result;

    if (ranges.empty()) {
        return result;
    }

    sort(ranges.begin(), ranges.end(), [](auto a, auto b) {
        return a.start < b.start; 
    });

    auto& first = ranges[0];
    int start = first.start;
    int end = first.end;

    for (int i = 1; i < ranges.size(); ++i) {
        auto& current = ranges[i];

        if (current.start > end) {
            result.push_back({start, end});

            start = current.start;
            end = current.end;
            continue; 
        }

        end = max(current.end, end);
    }

    result.push_back({start, end});

    return result;
}

int main()
{
    // [0, 6], [8, 9], [10, 11]
    vector<Range> ranges {
        {3, 4},
        {2, 5},
        {3, 6},
        {0, 3},
        {8, 9},
        {10, 11}
    };

    auto merged = mergeRanges(ranges);

    for (auto& range : merged) {
        cout << "[" << range.start << ", " << range.end << "] ";
    }

    cout<<endl;

    return 0;
}