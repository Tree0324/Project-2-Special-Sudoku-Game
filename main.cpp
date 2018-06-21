#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <iomanip>
#include <algorithm>
#include "Sol_su.h"
#include "GenSudoku.h"
using namespace std;
/*content
line 103~197 sudoku game play
line 238~249 solve single-solution probelm
line 250~290 judge the type of the solution (btw can still solve it)
P.S line 205~237 is file-processing. read file from user
*/

//for socreboard
struct UserData
{         
	string Name;
	int passing_time;
};

bool cmp(const UserData &a, const UserData &b) // sorting priciple
{
	return a.passing_time < b.passing_time;					
}

//this fun is used to check the type of solution
void bruteForceSolve(const Sudoku* sudoku_ref, Sudoku* answer[2])
{
    if(answer[1] != nullptr) // already found 2rd sol.
        return;
    Sudoku* sudoku = sudoku_ref->duplicate();
    Cell* first_empty_cell = nullptr;
    for(int i=0;i<12;++i)
    {
        for(int j=0;j<12;++j){
            if( sudoku->cells[i][j]->number == 0 )
                first_empty_cell = sudoku->cells[i][j];
        }
    }
    if( first_empty_cell == nullptr  )
    {   
        if ( sudoku_ref -> isCorrect())
        {
            for(int i=0;i<2;++i)
                if(answer[i] == nullptr)//fill one unfill answer
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
   
    for(int i=1;i<=9;++i){
        if( first_empty_cell->candidates[i] )// try each candidate
        { 
            first_empty_cell->number = i;
            bruteForceSolve(sudoku, answer);
        }
    }
    delete sudoku;
}

//this fun is used to solove single solution problem <- more effeciency
Sudoku* bruteForceSolve(const Sudoku* sudoku_ref)
{
    Sudoku* sudoku = sudoku_ref->duplicate();
    Sudoku* result = nullptr;
    Cell* first_empty_cell = nullptr;
    for(int i=0;i<12;++i)
        for(int j=0;j<12;++j)
            if( sudoku->cells[i][j]->number == 0 )
                first_empty_cell = sudoku->cells[i][j];
    if( first_empty_cell == nullptr  )
    {   
        delete sudoku;
        return sudoku_ref -> duplicate();
    }
    for(int i=1;i<=9;++i)
    {
        if( first_empty_cell->candidates[i] )
        { // try each candidate
            first_empty_cell->number = i;
            result = bruteForceSolve(sudoku);
            if (result != nullptr)
                break;
        }
    }   
    delete sudoku;
    return result;
}


int main(){
//give user a problem and solve it. after solving show answer for user
//
//
    //for scoreboard information
    vector<UserData> UserIn(100);
    vector<UserData> show(100);
    int player_number = 0;

    //generate the sudoku process
    GenSudoku test;
    test.do_total();
    bool start = 1;
    time_t gogo;
    time_t endend;
    const Sudoku* save_for_answer = new Sudoku(test.board);
    
    //for user to play this sudoku
    while (start || test.GenSingleSol_su().isCorrect() )
    {
        int order = 1;
        gogo = time (NULL);
        test.GenSingleSol_su().showSu();
        cout << "\nenter the idx of the number row u want to fill\n";
        int _row,_column,chosen_number;
        cin >> _row;
        cout << "enter the idx of the number column u want to fill in\n";
        cin >> _column;
        cout << "enter the number u would like to fill\n";
        cin >> chosen_number;
        if (test.GenSingleSol_su().isCorrect())
        {
            endend = time(NULL);
            start = 0;
            cout << "congratulation u done a great job !!\n";
            cout << "the total time u use is "<<( endend - gogo )/CLOCKS_PER_SEC <<endl;
        }

        if( test.board[_row][_column] !=0 || chosen_number > 9 || chosen_number < 1)
        {
            cout << "hey bad user !! PLEASE ENTER A VALID NUMBER !\n";
            cout << "hey bad user !! PLEASE ENTER A VALID NUMBER !\n";
            cout << "hey bad user !! PLEASE ENTER A VALID NUMBER !\n";
        }
        else
        {
            test.board[_row][_column] =chosen_number; 
            test.GenSingleSol_su().showSu();
        }

        char option;
        cout << "\nEnter 'q' if u want to quick the game directly \nEnter 'c' if u want to continue fill other blan in this problem\n";
        cout << "Enter 'b' if u want to see the answer of the board and continue other problem\n";
        cin >> option;
        switch (option)
        {
            case 'b':
                endend = time(NULL);
                start = 1;
                cout << "here comes the answer and time u solve this sudoku\n";
                bruteForceSolve(save_for_answer) -> showSu();
                cout << endl;
                cout << "time u use  = " <<( double(endend) - gogo ) << "seconds" <<endl;
                cout << "please enter ur name to see the scoreboard \n";
                cin >> UserIn[player_number].Name;
                UserIn[player_number].passing_time = endend - gogo ;
	            show = UserIn;
                sort(show.begin(),show.end(),cmp);
                cout << setw(10)<<"the scoreboard" << endl;
                cout << "order" << setw(10) << "Name" << setw(20) << "passing_time\n";
                for (int idx=0;idx<show.size();idx++)
                {
                    if (show[idx].passing_time != 0)
                    {
                       cout << order << setw(10) << show[idx].Name << setw(20) <<show[idx].passing_time <<endl;
                       order++; 
                    }
                }
                cout<<"\n\n\n\n\n\n";
                player_number++;          
                break;

            case 'q':
                start = 0;
                cout << "leaving the game\n\n\n\n";
                break;
            
            case 'c':
                start = 1;
                break;
            
            default:
                start = 1;
        }
    }
    
//read file and check the solution type and solve 
//
//
//
//

    //read su from the file 
    ifstream inFile("infile",ios::in);
    if (!inFile)
    {
        cerr << "Fail opening" << endl;
        exit(1);
    }
    int board[12][12];
    for(int i =0;i<12;i++)
    {
        int j = 0;
        string line;
        getline(inFile,line);

        for(int k=0;k<line.size();k++)
        {
            if (line[k] != ',')
            {
                int a;
                if (line[k] != '-')
                {
                    a = line[k] - '0' ;
                }
                else
                {
                    a = -(line[k+1] - '0');
                    k++;
                }
                board[i][j] = a ;
                j++;
            }
        }
    }
    
    //slove for sing soluntion problem
    //
    //

    clock_t start_solving=clock();
    const Sudoku* just_for_one = new Sudoku(board);
    bruteForceSolve(just_for_one)->showSu();
    clock_t end_solving = clock();
    delete just_for_one;
    cout << "the elpased time for solving this sudoku is  "<< (end_solving - start_solving)/CLOCKS_PER_SEC << " seconds" <<endl;
    cout << "\n\n\n\n";

    //judge single or no or multple solution
    //
    //
    Sudoku* sudoku = new Sudoku(board);
    Sudoku* sudoku_answer[2] = {nullptr,nullptr};
    clock_t start_time = clock();
    bruteForceSolve(sudoku,sudoku_answer);
    clock_t finished_time = clock();
    //sudoku -> showStructure();
    cout << "the problem is as below" << endl;
    sudoku -> showSu();
    cout << "meow meow" << endl;

    //check the sudoku is mutiple solution or just one solution
    if(sudoku_answer[0] == nullptr)
    {
        cout << "there's no solution for this sudoku"<<endl;
        return 0;
    }
    else if (sudoku_answer[1] == nullptr && sudoku_answer[0] != nullptr)
    {
        cout <<"it's a single solution case." <<endl;
        cout << "the answer is...." <<endl;
        sudoku_answer[0] -> showSu();
        if (sudoku_answer[0] -> isCorrect())
            cout << "it's really a solution of the sudoku\n";
    }
    else
    {
        cout <<"it's multiple solution case" << endl;
        cout << "the first answer is...." <<endl;
        sudoku_answer[0] -> showSu();
        cout << "\nand the second solution is" << endl;
        sudoku_answer[1] ->showSu();
        if ( sudoku_answer[0] -> isCorrect() && sudoku_answer[1] -> isCorrect() )
            cout << "they are all really  solutions of the sudoku\n";
    }
    //show the answer of the sudoku <- not require but i did it


    //sudoku -> isCorrect();  //just check for the function is valid or not
    cout << "Elapsed time for solving the sudoku is " << ( double(finished_time) - start_time )/CLOCKS_PER_SEC <<" seconds" <<endl;
    delete sudoku;
    delete sudoku_answer[0];
    delete sudoku_answer[1];
    return 0;
}
