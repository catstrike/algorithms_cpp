#include <iostream>
#include <vector>

using namespace std;

bool visitAll(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j)
{
    int rows = grid.size();
    int columns = grid[0].size();

    if (i < 0 || i >= rows ||
        j < 0 || j >= columns) 
    {
        return false;
    }

    if (visited[i][j] || grid[i][j] == '0') {
        return false;
    }

    visited[i][j] = true;

    visitAll(grid, visited, i - 1, j);
    visitAll(grid, visited, i + 1, j);
    visitAll(grid, visited, i, j - 1);
    visitAll(grid, visited, i, j + 1);

    return true;
}

int numIslands(vector<vector<char>>& grid) 
{
    int rows = grid.size();

    if (rows == 0) {
        return 0;
    }

    int columns = grid[0].size();

    vector<vector<bool>> visited(
        rows, 
        vector<bool>(columns)
    );

    int count = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (visitAll(grid, visited, i, j)) {
                count++;
            }
        }
    }

    return count;
}


int main()
{
    vector<vector<char>> map_01 {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };

    vector<vector<char>> map_02 {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };

    cout << "map_01: " << numIslands(map_01) << endl;
    cout << "map_02: " << numIslands(map_02) << endl;

    return 0;
}