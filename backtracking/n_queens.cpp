#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

bool checkDiagonals(const vector<int>& state, int position)
{
    auto currentIndex = state.size();

    for (int j = 1; j <= currentIndex; ++j) {
        auto& line = state[currentIndex - j];
        if (position + j == line || position - j == line) {
            return true;
        }
    }

    return false;
}

void n_queens_internal(int boardSize, vector<int>& state, vector<vector<int>>& result)
{
    if (state.size() == boardSize) {
        result.push_back(state);
        return;
    }

    auto currentIndex = state.size();

    vector<bool> columnBlocked(boardSize);
    for (auto& item : state) {
        columnBlocked[item] = true;
    }

    for (int i = 0; i < boardSize; ++i) {
        if (columnBlocked[i] || checkDiagonals(state, i)) {
            continue;
        }

        state.push_back(i);
        n_queens_internal(boardSize, state, result);
        state.pop_back();
    }
}

vector<vector<int>> n_queens(int boardSize)
{
    vector<vector<int>> result;
    vector<int> state;

    n_queens_internal(boardSize, state, result);

    return result;
}

string renderBoard(const vector<int>& result)
{
    stringstream ss;
    auto size = result.size();

    for (auto& item : result) {
        for (auto i = 0; i < size; ++i) {
            ss << (item == i ? 'Q' : '.');
        }
        ss << endl;
    }

    return ss.str();
}

int main()
{
    auto size = 4;
    auto results = n_queens(size);

    for (auto& result : results) {
        auto board = renderBoard(result);
        cout << board;
        cout << string(size, '-') << endl;
    }

    return 0;
}