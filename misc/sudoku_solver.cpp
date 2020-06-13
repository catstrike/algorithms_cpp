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


struct Vector2
{
    int i;
    int j;

    Vector2(int i, int j)
        : i(i), j(j)
    {}
};

class Board
{
    array<array<int, BOARD_SIZE>, BOARD_SIZE> cells {};

public:
    array<int, BOARD_SIZE> rows;
    array<int, BOARD_SIZE> columns;
    array<int, BOARD_SIZE> squares;

    int emptyCells {BOARD_SIZE * BOARD_SIZE};
public:
    Board(const vector<vector<int>> &cells)
    {
        auto allNumbers = getAllValuesMask();

        for (auto i = 0; i < BOARD_SIZE; ++i) {
            rows[i] = allNumbers;
            columns[i] = allNumbers;
            squares[i] = allNumbers;
        }

        for (size_t i = 0; i < BOARD_SIZE; ++i) {
            for (size_t j = 0; j < BOARD_SIZE; j++) {
                auto cell = cells[i][j];

                if (cell == 0) {
                    continue;
                }

                setInplace(i, j, cell);
            }
        }
    }

public:
    bool isSolved() const
    {
        return emptyCells == 0;
    }

    Board setValue(int i, int j, int value) const
    {
        return Board(*this).setInplace(i, j, value);
    }

    int getValue(int i, int j) const
    {
        return cells[i][j];
    }

    int getPossibleValues(int i, int j) const
    {
        if (cells[i][j] != 0) {
            return 0;
        }

        auto squareIndex = GET_SQUARE_INDEX(i, j);

        return rows[i] & columns[j] & squares[squareIndex];
    }

    vector<vector<int>> getCells() const
    {
        vector<vector<int>> result(BOARD_SIZE, vector<int>(BOARD_SIZE));

        auto rowCount = cells.size();
        auto columnCount = cells.size();

        for (size_t i = 0; i < rowCount; ++i) {
            for (size_t j = 0; j < columnCount; ++j) {
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

    Board& setInplace(int i, int j, int value)
    {
        auto squareIndex = GET_SQUARE_INDEX(i, j);
        int valueBit = ~(1 << value);

        rows[i] &= valueBit;
        columns[j] &= valueBit;
        squares[squareIndex] &= valueBit;
        cells[i][j] = value;

        emptyCells--;

        return *this;
    }
};

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

Vector2 getNextEmpty(const Board& board, Vector2 position)
{
    auto j = position.j;

    for (auto i = position.i; i < BOARD_SIZE; ++i) {
        for (; j < BOARD_SIZE; ++j) {
            if (board.getValue(i, j) == 0) {
                return Vector2(i, j);
            }
        }
        j = 0;
    }

    return Vector2(-1, -1);
}

void solveSudoku(const Board& board, Vector2 position, unique_ptr<Board>& result)
{
    if (board.isSolved()) {
        result = make_unique<Board>(board);
        return;
    }

    position = getNextEmpty(board, position);

    auto possibleValues = board.getPossibleValues(
        position.i,
        position.j
    );

    for (auto value = MIN_VALUE; value <= MAX_VALUE; ++value) {
        if (!BIT_EXISTS(possibleValues, value)) {
            continue;
        }

        auto newBoard = board.setValue(
            position.i,
            position.j,
            value
        );

        solveSudoku(newBoard, position, result);

        if (result != nullptr) {
            return;
        }
    }
}

auto solveSudoku(const vector<vector<int>> &cells)
{
    auto board = Board(cells);
    unique_ptr<Board> result;

    solveSudoku(board, Vector2(0, 0), result);

    if (result == nullptr) {
        return cells;
    }

    return result->getCells();
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

    auto result = solveSudoku(cells2);

    print_board(result);

    report_elapsed_time("Elapsed time", startTime, clock());

    return 0;
}