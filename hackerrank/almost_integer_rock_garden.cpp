#include <iostream>
#include <vector>
#include <unordered_set>
#include <sstream>

#include <cmath>
#include <ctime>

using namespace std;

const int MinSize = -12;
const int MaxSize = 12;

const double Delta = 0.000000000001;

struct Position {
    int x;
    int y;

    string toString() const {
        stringstream ss;
        ss << "{" << x << ", " << y << "}";
        return ss.str();
    }
};

class Garden {
public: // - Types
    using TableRow = vector<double>;
    using Table = vector<TableRow>;

public: // - Properties
    int getMin() const { return min; }
    int getMax() const { return max; }

private: // - State
    Table table;
    int min;
    int max;

public: // - Lifecycle
    Garden(int min, int max)
        : min(min)
        , max(max)
    {
        auto size = abs(max - min) + 1;
        table = Table(size, TableRow(size));

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                auto x = min + i;
                auto y = min + j;
                table[i][j] = sqrt(x*x + y*y);
            }
        }
    }

public: // - Public
    double distance(const Position& point) const {
        return distance(point.x, point.y);
    }

    double distance(int x, int y) const {
        return table[y - min][x - min];
    }

    constexpr void print()
    {
        for (auto& row : table) {
            for (auto& item : row) {
                cout << item << " ";
            }
            cout << endl;
        }
    }
};

bool isAlmostInt(double value)
{
    double integralPart;
    auto fractionalPart = modf(value, &integralPart);
    return fractionalPart <= Delta || fractionalPart + Delta > 1;
}

bool backtrack(const Garden& garden, int depth, double sum, vector<Position>& positions,
             vector<vector<bool>>& visited, vector<vector<Position>>& result)
{
    if (depth == 0) {
        if (isAlmostInt(sum)) {
            result.push_back(positions);
            return true;
        }

        return false;
    }

    // for (auto y = garden.getMin(), yMax = garden.getMax(); y <= yMax; ++y) {
    //     for (auto x = garden.getMin(), xMax = garden.getMax(); x <= xMax; ++x) {
    for (auto y = 0, yMax = garden.getMax(); y <= yMax; ++y) {
        for (auto x = 0, xMax = garden.getMax(); x <= xMax; ++x) {
            Position position {x, y};
            auto magnitude = garden.distance(x, y);

            if (visited[y][x]) {
                continue;
            }

            
            visited[y][x] = true;
            positions.push_back(position);
            auto found = backtrack(garden, depth - 1, sum + magnitude, positions, visited, result);
            positions.pop_back();
            visited[y][x] = false;

            if (found) {
                return true;
            }
        }
    }

    return false;
}

vector<vector<Position>> getPositions(const Garden& garden, const vector<Position>& startPositions, int totalPoints)
{
    auto size = abs(garden.getMax() - garden.getMin()) + 1;
    int depth = totalPoints - startPositions.size();
    vector<Position> positions(begin(startPositions), end(startPositions));
    vector<vector<bool>> visited(size, vector<bool>(size));
    vector<vector<Position>> result;

    double sum = 0;
    for (const auto& point : startPositions) {
        sum += garden.distance(point);
    }
    backtrack(garden, depth, sum, positions, visited, result);

    return result;
}

void printPositions(const vector<Position>& positions)
{
    for (auto& position : positions) {
        cout << position.toString() << endl;
    }
}

void report_elapsed_time(const char * tag, clock_t start, clock_t stop)
{
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("%s: %.2f ms\n", tag, elapsed);
}

int main()
{
    Garden garden(MinSize, MaxSize);

    vector<Position> positions {
        {7, 11},
        {11, 1},
        {-2, 12},
        {5, 4},
        {12, -3},
        {10, 3},
        {9, 6},
        // {-12, -7},
        // {1, 11},
        // {-6, -6},
        // {12, -4},
        //{4, 12}
    };

    cout << "Calculating..." << endl;

    auto start = clock();

    auto results = getPositions(
        garden,
        positions,
        12
    );

    report_elapsed_time("Total time: ", start, clock());

    int n = 1;

    for (auto& result : results) {
        cout << "Answer " << n++ << endl;
        printPositions(result);
    }
}