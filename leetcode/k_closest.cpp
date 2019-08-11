#include <vector>
#include <iostream>

using namespace std;

// O(n * log(n))
vector<vector<int>> kClosest(vector<vector<int>>& points, int K) 
{
    auto size = points.size();
    vector<vector<int>> result(K);
    vector<long> sqrMagnitude(size);
    vector<int> order(size);

    for (int i = 0; i < size; ++i) {
        auto& point = points[i];
        sqrMagnitude[i] = point[0] * point[0] + point[1] * point[1];
        order[i] = i;
    }

    sort(order.begin(), order.end(), [&sqrMagnitude](int a, int b) { 
        return sqrMagnitude[a] < sqrMagnitude[b]; 
    });

    for (int i = 0; i < K; ++i) {
        result[i] = points[order[i]];
    }

    return result;
}

int main()
{
    vector<vector<int>> points {
        {3, 3}, {5, -1}, {-2, 4}
    };

    auto result = kClosest(points, 2);

    for (auto& point : result) {
        cout<<"{"<<point[0]<<", "<<point[1]<<"}"<<endl;
    }

    return 0;
}