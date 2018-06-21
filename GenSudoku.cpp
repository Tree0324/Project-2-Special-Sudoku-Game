#include "GenSudoku.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GenSudoku::GenSudoku()
{
    for (int i=0;i<12;i++)
        for (int j=0;j<12;j++)
            board[i][j] = sudoku_temp[i][j];

}

GenSudoku::GenSudoku(int board_temp[12][12])
{
    for (int i=0;i<12;i++)
        for (int j=0;j<12;j++)
            board[i][j] = board_temp[i][j];   
}

void GenSudoku::add_zero()
{
    srand(time(NULL));
    int times = 10 + rand()%10; //arbitrary choosing 
    int t=0;

    while (t<times)
    {
        int m=rand()%12;
        int n=rand()%12;
        if ( !( (board[m][n]==0 || board[m][n]==-1) ) )
        {
            int save = board[m][n];
            board[m][n] = 0;
            if (this->Single_Sol())
                t++;
            else
                board[m][n] = save;
        }
    }
}

bool GenSudoku::Single_Sol() 
{
    Sudoku* sudoku = new Sudoku(board);
    Sudoku* sudoku_answer[2] = {nullptr,nullptr};
    bruteForceSolve(sudoku,sudoku_answer);
    if (sudoku_answer[0]!=nullptr && sudoku_answer[1] == nullptr)
        return true;
    else 
        return false;
}

void GenSudoku::add()
{
    srand(time(NULL));
    int times = rand()%9;  
    int t=0;

    while (t<times)
    {
        for (int m=0;m<12;m++)
            for (int n=0;n<12;n++)
                if  (!(board[m][n] == 0  || board[m][n] == -1))
                    board[m][n] = ( board[m][n] == 9 ) ? 1 : board[m][n] +1;//ensure valdity
        t++;
    }
}

void GenSudoku::change_symbol()
{
    srand(time(NULL));
    int times = rand()%5;  
    int t=0;

    while (t<times)
    {
        int m=rand()%4;
        int n=rand()%4;
        for (int i=0;i<12;i++)
        {
            int idx=0;
            for (int j=0;j<3;j++)
            {
                int k = board[i][m*3+j];
                board[i][m*3+j] = board[i][3*n+idx];
                board[i][3*n+idx] = k;
                idx++;
            }
        }
        t++;
    }
}

void GenSudoku::change_Column_Row()
{
    srand(time(NULL));
    int times = rand()%5;  
    int t=0;
    const int sel_bucket[4]={0,3,6,9};
    
    while (t<times)
    {
        int m = sel_bucket[rand()%4];
        for (int i=0;i<12;i++)
        {
            int k = board[i][m];
            board[i][m] = board[i][m+1];
            board[i][m+1] = k;
        }
        for (int j=0;j<12;j++)
        {
            int k = board[m][j];
            board[m][j] = board[m+1][j];
            board[m+1][j] = k;
        }   
        t++;
    }
}

//note before use this function u must generate a sudoku first
void GenSudoku::bruteForceSolve(const Sudoku* sudoku_ref, Sudoku* answer[2])
{
    if(answer[1] != nullptr) // already found 2rd sol.
        return;
    Sudoku* sudoku = sudoku_ref->duplicate();
    Cell* first_empty_cell = nullptr;
    for(int i=0;i<12;++i)
    {
        for(int j=0;j<12;++j)
        {
            if( sudoku->cells[i][j]->number == 0 )
                first_empty_cell = sudoku->cells[i][j];
        }
    }
    if( first_empty_cell == nullptr  )
    {   
        if ( sudoku_ref -> isCorrect() )
        {
            for(int i=0;i<2;++i)
                if(answer[i] == nullptr)// fill one unfilled answer
                {
                answer[i] = sudoku_ref->duplicate();
                break;
                }
            delete sudoku;
            return;
        }
        else
            return;
    }
   
    for(int i=1;i<=9;++i)
    {
        if( first_empty_cell->candidates[i] )// try each candidate
        { 
            first_empty_cell->number = i;
            bruteForceSolve(sudoku, answer);
        }
    }
    delete sudoku;
}

void GenSudoku::do_total()
{
    add_zero();
    add();
    change_symbol();
    change_Column_Row();
}

Sudoku GenSudoku::GenSingleSol_su()//for output the single solution sudoku
{
    Sudoku su_ref(board);
    return su_ref;
}