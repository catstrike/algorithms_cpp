#include <iostream> // std::cout, std::endl
#include <vector> // std::vector

using namespace std;

#define BOARD_SIZE 9
#define SQUARE_SIZE 3
#define SQUARES_IN_ROW (BOARD_SIZE / SQUARE_SIZE)
#define MIN_VALUE 1
#define MAX_VALUE 9

#define SET_FLAG(x, value) (x |= (1 << value))
#define IS_FLAG_SET(x, value) ((x & (1 << value)) == (1 << value))

bool isValid(const vector<vector<int>>& board) 
{
    auto rows = board.size();
    auto columns = board[0].size();

    if (rows != columns && rows != BOARD_SIZE) {
        return false;
    }

    vector<short> rowMasks(BOARD_SIZE);
    vector<short> columnMasks(BOARD_SIZE);
    vector<short> squareMasks(BOARD_SIZE);

    for (auto i = 0; i < BOARD_SIZE; ++i) {
        for (auto j = 0; j < BOARD_SIZE; ++j) {
            auto value = board[i][j];

            if (value < MIN_VALUE || value > MAX_VALUE) {
                return false;
            }

            auto squareIndex = (i / SQUARE_SIZE) * SQUARES_IN_ROW + (j / SQUARE_SIZE);

            if (IS_FLAG_SET(rowMasks[i], value) ||
                IS_FLAG_SET(columnMasks[j], value) ||
                IS_FLAG_SET(squareMasks[squareIndex], value)) 
            {
                return false;
            }

            SET_FLAG(rowMasks[i], value);
            SET_FLAG(columnMasks[j], value);
            SET_FLAG(squareMasks[squareIndex], value);
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

    cout<<"The board 0 is "<<(isValid(board0) ? "valid" : "invalid")<<endl;
    cout<<"The board 1 is "<<(isValid(board1) ? "valid" : "invalid")<<endl;

    return 0;
}