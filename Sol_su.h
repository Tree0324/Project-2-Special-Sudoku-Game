#ifndef SOL_SU_H
#define SOL_SU_H
#include <bitset>
using namespace std;

struct Cell{
    int number;
    bitset<10> candidates; // regard it as bool candidates[10]
    Cell(int _number)
    {
        if(_number != 0) // 0 if for empty cell
        {
            number = _number;
            for(int i=1;i<=9;++i)
                candidates[i] = false;
        }
        else
        {
            number = 0;
            for(int i=1;i<=9;++i)
                candidates[i] = true;
        }
    }
};
 
typedef struct Group
{
    Cell* cells[9];
}Grid, Row, Column;
  
class Sudoku{
    public:
        Sudoku(int board[12][12]);
        void filterCandidates();
        void showStructure() const;
        void showSu() const;
        Sudoku* duplicate() const;
        bool isCorrect() const;
        bool check_validity(Group* group) const;
        ~Sudoku();

        Cell* cells[12][12];
        Grid* grids[12]; // grids which are not -1
        Row* rows[12];
        Column* columns[12];
};

#endif
