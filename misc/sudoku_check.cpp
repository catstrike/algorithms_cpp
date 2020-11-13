#include <iostream> // std::cout, std::endl
#include <vector> // std::vector

using namespace std;

#define SQUARE_SIZE 3
#define BOARD_SIZE (SQUARE_SIZE * SQUARE_SIZE)
#define SQUARES_IN_ROW (BOARD_SIZE / SQUARE_SIZE)
#define MIN_VALUE 1
#define MAX_VALUE BOARD_SIZE

bool sudokuCheck(const vector<vector<int>>& board) 
{
    auto rows = board.size();
    auto columns = board[0].size();

    if (rows != columns && rows != BOARD_SIZE) {
        return false;
    }

    short columnMasks[BOARD_SIZE] {};
    short squareMasks[BOARD_SIZE] {};

    for (auto i = 0; i < BOARD_SIZE; ++i) {
        auto squareRowOffset = (i / SQUARE_SIZE) * SQUARES_IN_ROW;
        short rowMask {0};

        for (auto j = 0; j < BOARD_SIZE; ++j) {
            auto value = board[i][j];

            if (value < MIN_VALUE || value > MAX_VALUE) {
                return false;
            }

            auto valueMask = 1 << (value - 1);
            auto squareIndex = squareRowOffset + (j / SQUARE_SIZE);

            if ((rowMask & valueMask) ||
                (columnMasks[j] & valueMask) ||
                (squareMasks[squareIndex] & valueMask)) 
            {
                return false;
            }

            rowMask |= valueMask;
            columnMasks[j] |= valueMask;
            squareMasks[squareIndex] |= valueMask;
        }
    }

    return true;
}

int main()
{
    vector<vector<int>> board0 {
        {5, 3, 4,  6, 7, 8,  9, 1, 2},
        {6, 7, 2,  1, 9, 5,  3, 4, 8},
        {1, 9, 8,  3, 4, 2,  5, 6, 7},

        {8, 5, 9,  7, 6, 1,  4, 2, 3},
        {4, 2, 6,  8, 5, 3,  7, 9, 1},
        {7, 1, 3,  9, 2, 4,  8, 5, 6},

        {9, 6, 1,  5, 3, 7,  2, 8, 4},
        {2, 8, 7,  4, 1, 9,  6, 3, 5},
        {3, 4, 5,  2, 8, 6,  1, 7, 9}
    };

    vector<vector<int>> board1 {
        {1, 4, 3,  5, 2, 6,  9, 7, 8},
        {3, 6, 8,  2, 5, 7,  1, 4, 9},
        {2, 1, 9,  7, 8, 3,  4, 5, 6},
         
        {7, 8, 2,  6, 1, 9,  5, 3, 4},
        {5, 3, 7,  4, 6, 8,  2, 9, 1},
        {8, 9, 5,  1, 7, 4,  3, 6, 2},
 
        {4, 5, 1,  9, 3, 2,  6, 8, 7},
        {6, 2, 4,  8, 9, 5,  7, 1, 3},
        {9, 7, 6,  3, 4, 1,  8, 2, 5}
    };

    vector<vector<int>> board2 {
        {2, 4, 5,  1, 3, 6,  7, 9, 8},
        {1, 8, 7,  4, 9, 2,  3, 5, 6},
        {3, 6, 9,  8, 5, 7,  2, 4, 1},

        {1, 7, 4,  9, 6, 2,  3, 5, 8},
        {5, 9, 8,  7, 3, 4,  2, 1, 6},
        {2, 3, 6,  5, 8, 1,  7, 4, 9},
        
        {6, 1, 3,  2, 4, 9,  5, 8, 7},
        {2, 7, 4,  5, 1, 8,  6, 9, 3},
        {5, 8, 9,  3, 6, 7,  1, 2, 4}
    };

    vector<vector<int>> board3 {
        {7, 4, 2,  6, 1, 3,  9, 5, 8},
        {1, 8, 5,  4, 9, 2,  3, 6, 7},
        {9, 6, 3,  8, 5, 7,  4, 2, 1},

        {4, 7, 1,  9, 6, 5,  8, 3, 2},
        {3, 9, 8,  7, 2, 4,  5, 1, 6},
        {2, 5, 6,  3, 8, 1,  7, 4, 9},

        {6, 3, 7,  2, 4, 9,  1, 8, 5},
        {8, 1, 4,  5, 7, 6,  2, 9, 3},
        {5, 2, 9,  1, 3, 8,  6, 7, 4}
    };

    cout<<"The board 0 is "<<(sudokuCheck(board0) ? "valid" : "invalid")<<endl;
    cout<<"The board 1 is "<<(sudokuCheck(board1) ? "valid" : "invalid")<<endl;
    cout<<"The board 2 is "<<(sudokuCheck(board2) ? "valid" : "invalid")<<endl;
    cout<<"The board 3 is "<<(sudokuCheck(board3) ? "valid" : "invalid")<<endl;

    return 0;
}