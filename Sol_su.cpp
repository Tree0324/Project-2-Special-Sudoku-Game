#include <iostream>
#include <bitset>
#include <vector>
#include "Sol_su.h"
#include <iomanip>
using namespace std;

Sudoku::Sudoku(int board[12][12])//initialize the whole sudoku
{
    // read in cells, and construct rows[]
    //construct row
    for (int i=0;i<12;++i)
    {
        rows[i] = new Row();
        int row_size = 0;
        for (int j=0;j<12;++j)
        {
            cells[i][j] = new Cell(board[i][j]);
            if (cells[i][j]->number != -1)
                rows[i]->cells[row_size++] = cells[i][j]; // push_back a cell in rows[i]
        }
    }
    // construct columns[]
    for (int j=0;j<12;++j)
    {
        columns[j] = new Column();
        int columns_size = 0;
        for (int i=0;i<12;++i)
        {
            if (cells[i][j]->number != -1)
                columns[j]->cells[columns_size++] = cells[i][j];
        }
    }
    // construct grids[]
    static const int grids_first_idx[16] = 
    {
        0,   3,   6,   9,
        36,  39,  42,  45,
        72,  75,  78,  81,
        108, 111, 114, 117
    };
    int grids_size = 0;
    for (int i=0;i<12;++i)
        grids[i] = new Grid();
    for (int t=0;t<16;++t)
    {
        int x = grids_first_idx[t] / 12;
        int y = grids_first_idx[t] % 12;
        if( cells[x][y]->number != -1 )
        {
            for(int i=0;i<3;++i)
            {
                for(int j=0;j<3;++j)
                {
                    grids[ grids_size ]->cells[i*3 + j] = cells[x+i][y+j];
                }
            }
            grids_size++;
        }
    }
    filterCandidates();
}

void Sudoku::showStructure() const
{
    for(int t=0;t<12;++t)
    {
        cout << "row " << t << " : ";
        for(int i=0;i<9;++i)
            cout << this -> rows[t]->cells[i]->number << ' ';
        cout << endl;
    }

    for(int t=0;t<12;++t)
    {
        cout << "col " << t << " : ";
        for(int i=0;i<9;++i)
            cout << this -> columns[t]->cells[i]->number << ' ';
        cout << endl;
    }
 
    for(int t=0;t<12;++t)
    {
        cout << "grid " << t << " : ";
        for(int i=0;i<9;++i)
            cout << this -> grids[t]->cells[i]->number << ' ';
        cout << endl;
    }

}
 
void Sudoku::filterCandidates()
{
    for(int t=0;t<12;++t)// for each row
    { 
        vector<int> delete_list; // remove these number in candidates[]
        for(int i=0;i<9;++i)
        {
            if( rows[t]->cells[i]->number > 0 )
                    delete_list.push_back( rows[t]->cells[i]->number );
        }
        for(int i=0;i<9;++i)
        {
            if( rows[t]->cells[i]->number == 0 )
                for(int del : delete_list)
                    rows[t]->cells[i]->candidates[del] = false;
        }
    }

    for(int t=0;t<12;++t)// for each column
    { 
        vector<int> delete_list; // remove these number in candidates[]
        for(int i=0;i<9;++i)
        {
            if( columns[t]->cells[i]->number > 0 )
                delete_list.push_back( columns[t]->cells[i]->number );
        }
        for(int i=0;i<9;++i)
        {
            if( columns[t]->cells[i]->number == 0 )
                for(int del : delete_list)
                    columns[t]->cells[i]->candidates[del] = false;
        }
    }

    for(int t=0;t<12;++t)// for each grid
    {
        vector<int> delete_list; // remove these number in candidates[]
        for(int i=0;i<9;++i)
        {
            if( grids[t]->cells[i]->number > 0 )
                delete_list.push_back( grids[t]->cells[i]->number );
        }
        for(int i=0;i<9;++i)
        {
            if( grids[t]->cells[i]->number == 0 )
                for(int del : delete_list)
                    grids[t]->cells[i]->candidates[del] = false;
        }
    }
}

 
Sudoku* Sudoku::duplicate() const
{
    int board[12][12];
    for(int i=0;i<12;++i)
        for(int j=0;j<12;++j)
            board[i][j] = cells[i][j]->number;
    return new Sudoku(board); 
}

void Sudoku::showSu() const
{
    cout << "i/j";
    for(int idx=0;idx<12;idx++)
        cout <<setw(3)<<idx<<" ";
    cout << endl;
    for(int i=0;i<12;i++)
    {
        cout <<setw(3)<<i;
        for(int j=0;j<12;j++)
            cout << setw(3)<<cells[i][j]->number << " ";
        cout << endl;
    }
}

bool Sudoku::isCorrect() const
{
    for (int i=0;i<12;i++)
        if ( !check_validity(grids[i]) || !check_validity(rows[i]) || !check_validity(columns[i]) )
            return false;
    return true;
}

bool Sudoku::check_validity(Group* group) const
{
    for (int i=0;i<9;i++)
        if (group->cells[i]->number>10 || group->cells[i]->number < 1)
            return false;
    for (int i =0;i<9;i++)
    {
        for (int j=i+1;j<9;j++)
            if (group->cells[i]->number == group->cells[j]->number)
                return false;
    }
    return true;
}

Sudoku::~Sudoku()
{
    for(int i=0;i<12;++i)
    {
        delete grids[i];
        delete rows[i];
        delete columns[i];
        for(int j=0;j<12;++j)
                delete cells[i][j];
        
    }
}
//end