#include <iostream>
#include <vector>
#include <sstream>

using namespace std;


class Options {
private:
    vector<int>* rows;
    int boardSize;
public:
    class iterator {
        vector<int>* rows;
        int boardSize;
        int currentColumn;
    public:
        iterator(vector<int>* rows, int boardSize, int startColumn) 
            : rows(rows)
            , boardSize(boardSize)
        {
            currentColumn = getNextColumn(startColumn);
        }

        bool operator != (const iterator& other) {
            return currentColumn != other.currentColumn;
        }

        bool operator == (const iterator& other) {
            return currentColumn == other.currentColumn;
        }

        iterator& operator ++() {
            currentColumn = getNextColumn(currentColumn);

            return *this;
        }

        int& operator *() {
            return currentColumn;
        }
    private:
        int getNextColumn(int column) const {
            if (column == boardSize) {
                return column;
            }

            do {
                column++;
            } while (column < boardSize && isUnderAttack(column));

            return column;
        }

        bool isUnderAttack(int position) const {
            auto currentIndex = rows->size();

            for (int j = 1; j <= currentIndex; ++j) {
                auto& line = rows->at(currentIndex - j);

                if (position == line ||
                    position + j == line ||
                    position - j == line) {
                    return true;
                }
            }

            return false;
        }
    };

public:
    Options(vector<int>* rows, int boardSize) 
        : rows(rows)
        , boardSize(boardSize)
    {
    }

public:
    iterator begin() {
        return iterator(rows, boardSize, -1);
    }

    iterator end() {
        return iterator(rows, boardSize, boardSize);
    }
};


class NQueensState {
private: // - State
    vector<int> rows;
    int boardSize;

public: // - Lifecycle
    NQueensState(int boardSize)
        : boardSize(boardSize)
    {}

public: // - Public
    Options getOptions() {
        return Options(&rows, boardSize);
    }

    NQueensState getNextState(int option) {
        NQueensState newState(*this);
        newState.rows.push_back(option);

        return newState;
    }

    bool isSolved() {
        return rows.size() == boardSize;
    }

    const vector<int>& getRows()
    {
        return rows;
    }
};

template<class State>
void backtrackIteration(State state, vector<State>& result)
{
    if (state.isSolved()) {
        result.push_back(state);
        return;
    }

    auto options = state.getOptions();

    for (auto option : options) {
        auto nextState = state.getNextState(option);

        backtrackIteration(nextState, result);
    }
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
    NQueensState nQueens(6);
    vector<NQueensState> result;

    backtrackIteration(nQueens, result);

    for (auto& board : result) {
        cout << renderBoard(board.getRows()) << endl;
    }

    return 0;
}