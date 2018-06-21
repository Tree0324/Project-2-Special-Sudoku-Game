#ifndef GEN_SUDOKU_H
#define GEN_SUDOKU_H
#include "Sol_su.h"
using namespace std;

class GenSudoku{
    friend class Sudoku;
    public:
        GenSudoku();
        GenSudoku(int board_temp[12][12]);
        void add_zero();
        bool Single_Sol();
        void bruteForceSolve(const Sudoku* sudoku_ref, Sudoku* answer[2]);
        void add();
        void change_symbol();
        void change_Column_Row();
        void do_total();
        Sudoku GenSingleSol_su();//retrun the result
        int board[12][12];
        
    private:
        int sudoku_temp[12][12] = 
        {{4,2,6,8,7,3,9,5,1,-1,-1,-1},
        {0,0,3,9,5,0,6,0,4,-1,-1,-1},
        {9,0,1,6,2,4,8,0,0,-1,-1,-1},
        {-1,-1,-1,1,3,2,0,8,7,9,5,6},
        {-1,-1,-1,0,8,0,1,9,0,4,2,0},
        {-1,-1,-1,4,9,6,2,3,0,8,7,1},
        {1,0,0,0,4,0,-1,-1,-1,6,9,5},
        {0,0,4,0,6,0,-1,-1,-1,1,3,7},
        {6,9,5,0,1,7,-1,-1,-1,2,8,4},
        {3,1,2,-1,-1,-1,7,4,0,5,0,9},
        {7,4,8,-1,-1,-1,0,6,9,3,0,2},
        {0,6,0,-1,-1,-1,3,1,0,7,0,8}};

};
#endif
