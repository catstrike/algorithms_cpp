#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int exploreRiverDFS(vector<vector<int>>& matrix, int i, int j)
{
    auto rows = matrix.size();
    auto columns = matrix[0].size();

    if (i < 0 || i >= rows || j < 0 || j >= columns) {
        return 0;
    }

    auto& cell = matrix[i][j];

    if (cell != 1) {
        return 0;
    }

    cell = 0;

    return 1 +
        exploreRiverDFS(matrix, i - 1, j) +
        exploreRiverDFS(matrix, i + 1, j) +
        exploreRiverDFS(matrix, i, j - 1) +
        exploreRiverDFS(matrix, i, j + 1);
}

struct Position {
    int i;
    int j;
    Position(int i, int j) : i(i), j(j) {}
};

int exploreRiverBFS(vector<vector<int>>& matrix, int i, int j)
{
    auto rows = matrix.size();
    auto columns = matrix[0].size();

    queue<Position> cells;

    cells.push(Position(i, j));
    auto counter = 0;

    while(!cells.empty()) {
        counter++;
        auto current = cells.front();
        cells.pop();
        matrix[current.i][current.j] = 0; // visited

        if (current.i - 1 > 0 && matrix[current.i - 1][current.j] == 1) {
            cells.push(Position(current.i - 1, current.j));
        }
        if (current.i + 1 < rows && matrix[current.i + 1][current.j] == 1) {
            cells.push(Position(current.i + 1, current.j));
        }
        if (current.j - 1 > 0 && matrix[current.i][current.j - 1] == 1) {
            cells.push(Position(current.i, current.j - 1));
        }
        if (current.j + 1 < columns && matrix[current.i][current.j + 1] == 1) {
            cells.push(Position(current.i, current.j + 1));
        }
    }

    return counter;
}

vector<int> riverSizes(vector<vector<int> > matrix) 
{
    auto rows = matrix.size();
    auto columns = matrix[0].size();

    vector<int> result;

    for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < columns; ++j) {
            if (matrix[i][j] != 1) {
                continue;
            }

            result.push_back(exploreRiverBFS(matrix, i, j));
        }
    }

    return result;
}

int main()
{
    vector<vector<int>> matrix {
        {1, 0, 0, 1, 0},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 1, 0}
    };

    auto result = riverSizes(matrix);

    for (auto item : result) {
        cout<<item<<" ";
    }
    cout<<endl;

    return 0;
}