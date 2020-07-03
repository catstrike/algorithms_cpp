#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <ctime>

using namespace std;

#define SQUARE_SIZE 3
#define BOARD_SIZE (SQUARE_SIZE * SQUARE_SIZE)
#define SQUARES_IN_ROW (BOARD_SIZE / SQUARE_SIZE)
#define MIN_VALUE 1
#define MAX_VALUE BOARD_SIZE

#define GET_SQUARE_INDEX(i, j) ((i / SQUARE_SIZE) * SQUARES_IN_ROW + (j / SQUARE_SIZE))

#define BIT_EXISTS(value, bit) ((value & (1 << bit)) > 0)

void print_board(const vector<vector<int>> &cells);

struct Vector2
{
    int i;
    int j;

    Vector2()
        : i(0), j(0)
    {}

    Vector2(int i, int j)
        : i(i), j(j)
    {}
};

class Options {
    static const int lastValue = MAX_VALUE + 1;
private:
    int allValues;

public:
    class iterator {
        int allValues;
        int currentValue;

    public:
        iterator(int allValues, int value) 
            : allValues(allValues)
        {
            currentValue = isValid(value) || value == lastValue
                ? value
                : getNext(value);
        }

        bool operator != (const iterator& other) {
            return currentValue != other.currentValue;
        }

        iterator& operator ++() {
            currentValue = getNext(currentValue);

            return *this;
        }

        int& operator *() {
            return currentValue;
        }
    private:
        int getNext(int value) const {
            if (value == lastValue) {
                return value;
            }

            do {
                value++;
            } while (value != lastValue && !isValid(value));

            return value;
        }

        bool isValid(int value) const
        {
            auto mask = 1 << value;
            return (mask & allValues) == mask;
        }
    };

public:
    Options(int allValues) 
        : allValues(allValues)
    {
    }

public:
    iterator begin() {
        return iterator(allValues, MIN_VALUE);
    }

    iterator end() {
        return iterator(allValues, MAX_VALUE + 1);
    }
};

class Board
{
    array<array<int, BOARD_SIZE>, BOARD_SIZE> cells {};

public:
    array<int, BOARD_SIZE> rows;
    array<int, BOARD_SIZE> columns;
    array<int, BOARD_SIZE> squares;

    Vector2 nextPosition;

    int emptyCells {BOARD_SIZE * BOARD_SIZE};
public:
    Board(const vector<vector<int>> &cells)
    {
        auto allNumbers = getAllValuesMask();

        rows.fill(allNumbers);
        columns.fill(allNumbers);
        squares.fill(allNumbers);

        // for (auto i = 0; i < BOARD_SIZE; ++i) {
        //     rows[i] = allNumbers;
        //     columns[i] = allNumbers;
        //     squares[i] = allNumbers;
        // }

        for (size_t i = 0; i < BOARD_SIZE; ++i) {
            for (size_t j = 0; j < BOARD_SIZE; j++) {
                auto cell = cells[i][j];

                if (cell == 0) {
                    continue;
                }

                setInplace(
                    Vector2(i, j),
                    cell
                );
            }
        }

        if (cells[0][0] != 0) {
            nextPosition = findNextEmpty(nextPosition);
        }
    }

public:
    bool isSolved() const {
        return emptyCells == 0;
    }

    Options getOptions() const {
        return Options(getPossibleValues(nextPosition));
    }

    Board getNextState(int value)
    {
        Board newBoard(*this);
        newBoard.setInplace(nextPosition, value);
        newBoard.nextPosition = findNextEmpty(nextPosition);

        return newBoard;
    }

    vector<vector<int>> getCells() const
    {
        vector<vector<int>> result(BOARD_SIZE, vector<int>(BOARD_SIZE));

        for (size_t i = 0; i < BOARD_SIZE; ++i) {
            for (size_t j = 0; j < BOARD_SIZE; ++j) {
                result[i][j] = cells[i][j];
            }
        }

        return result;
    }

private:
    constexpr int getAllValuesMask()
    {
        int result {};

        for (auto i = MIN_VALUE; i <= MAX_VALUE; ++i) {
            result |= (1 << i);
        }

        return result;
    }

    Board& setInplace(Vector2 position, int value)
    {
        auto squareIndex = GET_SQUARE_INDEX(
            position.i,
            position.j
        );
        int valueBit = ~(1 << value);

        rows[position.i] &= valueBit;
        columns[position.j] &= valueBit;
        squares[squareIndex] &= valueBit;
        cells[position.i][position.j] = value;

        emptyCells--;

        return *this;
    }

    Vector2 findNextEmpty(Vector2 position) const {
        auto j = position.j + 1;

        for (auto i = position.i; i < BOARD_SIZE; ++i) {
            for (; j < BOARD_SIZE; ++j) {
                if (cells[i][j] == 0) {
                    return Vector2(i, j);
                }
            }
            j = 0;
        }

        return Vector2(-1, -1);
    }

    int getPossibleValues(Vector2 position) const {
        if (cells[position.i][position.j] != 0) {
            return 0;
        }

        auto squareIndex = GET_SQUARE_INDEX(
            position.i,
            position.j
        );

        return rows[position.i] &
               columns[position.j] &
               squares[squareIndex];
    }
};

template<class State>
void findFirst(State state, vector<State>& result)
{
    if (state.isSolved()) {
        result.push_back(state);
        return;
    }

    auto options = state.getOptions();

    for (auto option : options) {
        auto nextState = state.getNextState(option);

        findFirst(nextState, result);

        if (result.size() > 0) {
            break;
        }
    }
}

void print_board(const vector<vector<int>> &cells)
{
    const string horizontalLine(31, '-');

    auto rowCount = cells.size();
    auto columnCount = cells[0].size();

    for (size_t i = 0; i < rowCount; ++i) {
        if (i % SQUARE_SIZE == 0) {
            cout << horizontalLine << '\n';
        }

        for (size_t j = 0; j < columnCount; j++) {
            if (j % SQUARE_SIZE == 0) {
                cout << "|";
            }

            cout << " " << cells[i][j] << " ";
        }

        cout << "|\n";
    }
    cout << horizontalLine << endl;
}


void report_elapsed_time(const char * tag, clock_t start, clock_t stop)
{
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("%s: %.2f ms\n", tag, elapsed);
}

int main()
{
    vector<vector<int>> cells0 {
        {0, 0, 0,  0, 0, 0,  0, 0, 8},
        {1, 8, 0,  0, 0, 2,  3, 0, 0},
        {0, 6, 0,  0, 5, 7,  0, 0, 1},

        {0, 7, 0,  9, 6, 0,  0, 0, 0},
        {0, 9, 0,  7, 0, 4,  0, 1, 0},
        {0, 0, 0,  0, 8, 1,  0, 4, 0},

        {6, 0, 0,  2, 4, 0,  0, 8, 0},
        {0, 0, 4,  5, 0, 0,  0, 9, 3},
        {5, 0, 0,  0, 0, 0,  0, 0, 0}
    };

    vector<vector<int>> cells1 {
        {0, 0, 0,  6, 7, 8,  9, 1, 0},
        {0, 0, 2,  0, 9, 0,  3, 0, 8},
        {1, 9, 0,  3, 4, 2,  0, 6, 7},

        {8, 0, 9,  7, 6, 1,  4, 2, 0},
        {0, 0, 0,  0, 5, 3,  7, 9, 1},
        {0, 0, 0,  9, 2, 4,  8, 5, 6},

        {9, 6, 0,  5, 3, 0,  2, 8, 0},
        {2, 0, 7,  4, 0, 9,  0, 3, 0},
        {0, 4, 5,  0, 8, 6,  0, 0, 9}
    };

    vector<vector<int>> cells2 {
        {9, 0, 0,  0, 0, 0,  5, 1, 0},
        {0, 7, 0,  0, 8, 0,  0, 0, 9},
        {5, 0, 0,  1, 0, 9,  2, 7, 8},

        {2, 5, 0,  0, 0, 7,  8, 0, 1},
        {1, 0, 0,  0, 5, 0,  0, 0, 0},
        {3, 0, 0,  0, 9, 0,  0, 0, 0},

        {0, 0, 0,  3, 1, 5,  0, 4, 0},
        {0, 0, 0,  0, 0, 0,  0, 0, 0},
        {7, 1, 4,  0, 2, 0,  0, 8, 0}
    };

    clock_t startTime = clock();

    Board board(cells2);
    vector<Board> results;

    findFirst(board, results);

    for (auto& result : results) {
        print_board(result.getCells());
    }

    report_elapsed_time("Elapsed time", startTime, clock());

    return 0;
}