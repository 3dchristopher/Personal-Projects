//Sudoku Solver using Backtracking method
//Christopher Little
//Last modified: September 19, 2017

//The following are example sudoku puzzles in the appropriate format. Once the program begins, paste one of the below sets of numbers into the program and press enter to solve.

//0 8 0 0 7 0 0 9 0 9 0 0 0 0 0 0 0 7 0 0 2 0 0 0 6 0 0 0 3 0 6 0 4 0 8 0 0 0 0 0 0 0 0 0 0 0 7 0 2 0 8 0 5 0 0 0 4 0 0 0 8 0 0 5 0 0 0 0 0 0 0 2 0 1 0 0 9 0 0 3 0

//0 2 7 9 8 0 0 0 0 1 0 0 4 5 0 6 0 0 0 0 4 0 0 0 0 8 0 4 0 0 0 9 7 0 5 8 0 5 9 0 3 0 2 1 0 3 8 0 5 1 0 0 0 9 0 6 0 0 0 0 4 0 0 0 0 5 0 4 9 0 0 6 0 0 0 0 7 8 5 2 0

//0 0 0 2 6 0 7 0 1 6 8 0 0 7 0 0 9 0 1 9 0 0 0 4 5 0 0 8 2 0 1 0 0 0 4 0 0 0 4 6 0 2 9 0 0 0 5 0 0 0 3 0 2 8 0 0 9 3 0 0 0 7 4 0 4 0 0 5 0 0 3 6 7 0 3 0 1 8 0 0 0

//0 2 0 0 0 0 0 0 0 0 0 0 6 0 0 0 0 3 0 7 4 0 8 0 0 0 0 0 0 0 0 0 3 0 0 2 0 8 0 0 4 0 0 1 0 6 0 0 5 0 0 0 0 0 0 0 0 0 1 0 7 8 0 5 0 0 0 0 9 0 0 0 0 0 0 0 0 0 0 4 0

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
using namespace std;

struct cell{
  bool changeable;
  int val;
};

void fillBoard(cell board[9][9]){ // Initializes the board with values provided by the user
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
      cin >> board[i][j].val;
      if(board[i][j].val!=0){
        board[i][j].changeable = false;
      }
      else{
        board[i][j].changeable=true;
      }
    }
  }
  return;
}

void outputBoard (cell board[9][9], int state){ // Outputs the current state of the board
  if(state==0){
    cout << "Inputted Board" << endl << "_____________________" << endl;
  }
  else{
    cout << "Solved Board" << endl << "_____________________" << endl;
  }
  for(int i=0; i<9; i++){
    for(int j=0; j<9; j++){
      cout << board[i][j].val << " ";
      if(j==2||j==5){
        cout << "* ";
      }
    }
    cout << endl;
    if(i==2||i==5){
      cout << string(21, '*') << endl;
    }
  }
  return;
}

bool rowCheck(cell board[9][9],int i, int j){ // Checks a cell's row for instances where a cell in the row's value matches that cell's value. Returns false if one is found, true otherwise.
  for(int k=0; k<9; k++){
    if(k==i){
      k++;
    }
    if(k>8){
      break;
    }
    else if(board[k][j].val==board[i][j].val){
      return false;
    }
  }
  return true;
}

bool colCheck(cell board[9][9],int i, int j){// Checks a cell's column for instances where a cell in the column's value matches that cell's value. Returns false if one is found, true otherwise.
  for(int k=0; k<9; k++){
    if(k==j){
      k++;
    }
    if(k>8){
      break;
    }
    else if(board[i][k].val==board[i][j].val){
      return false;
    }
  }
  return true;
}

bool boxCheckHelper2(cell board[9][9], int i, int j, int rowMin, int rowMax, int colMin, int colMax){ //Checks a cell's box for duplicate values
  for(int k=rowMin; k<rowMax; k++){
    for(int l=colMin; l<colMax; l++){
      if (board[k][l].val==board[i][j].val && !(k==i&&l==j)){
          return false;
      }
    }
  }
  return true;
}

bool boxCheck(cell board[9][9],int i, int j){ //Finds the 3x3 box the cell resides in
  if(i<3){
    if(j<3){
      return boxCheckHelper2(board, i, j, 0, 3, 0, 3);
    }
    else if(j<6){
      return boxCheckHelper2(board, i, j, 0, 3, 3, 6);
    }
    else{
      return boxCheckHelper2(board, i, j, 0, 3, 6, 9);
    }
  }
  else if(i<6){
    if(j<3){
      return boxCheckHelper2(board, i, j, 3, 6, 0, 3);
    }
    else if(j<6){
      return boxCheckHelper2(board, i, j, 3, 6, 3, 6);
    }
    else{
      return boxCheckHelper2(board, i, j, 3, 6, 6, 9);
    }
  }
  else{
    if(j<3){
      return boxCheckHelper2(board, i, j, 6, 9, 0, 3);
    }
    else if(j<6){
      return boxCheckHelper2(board, i, j, 6, 9, 3, 6);
    }
    else{
      return boxCheckHelper2(board, i, j, 6, 9, 6, 9);
    }
  }
}

bool boardSolver(cell board[9][9], int i, int j, bool solved){ 
  if(j>8){
    solved=true;
  }
  int cellVal=1;
  while(cellVal<10 && solved==false){
    board[i][j].val=cellVal;
    if(rowCheck(board,i,j)&&colCheck(board,i,j)&&boxCheck(board,i,j)){ // If the current cell value is not already in the cell's row, column, or box, it is a valid number, so continue.
      if(i==8 && j==8){ // If (8,8), the last cell of the puzzle, passes the above statement, the puzzle is solved
        solved=true;
        break;
      }
      int k=i;
      int r=j;
      while(1!=0){// Loop to find next changeable cell to hop to
        k++;
        if(k>8){
          k=0;
          r++;
        }
        if(board[k][r].changeable==true){ // Once next changeable cell is found, continue
          break;
        }
      }
      if(solved==false){
        solved=boardSolver(board, k, r, solved);
      }
    }
    cellVal++;
  }
  if(cellVal>9 && solved==false){
    board[i][j].val=0;
    return false;
  }
  return true;
}

int main() {
  string in="N";
  cell board[9][9];
  do{
    cout << "Please enter the soduku board. List each row as a string of numbers with spaces between each digit, and an asterisk in the positions that are empty" << endl;
    for(int i=0; i<9; i++){
      for(int j=0; j<9; j++){
        board[i][j].val=0;
        board[i][j].changeable=true;
      }
    }
    fillBoard (board);
    outputBoard(board, 0);
    do{
      cout<< "Is this correct? (Y/N)" << endl;
      cin >> in;
      if(in!="Y" && in!="N"){
        cout<< "Sorry, that input was not recognized. Please input either Y or N for your response of yes or no, respectively." << endl;
      }
    }while(in!="Y"&&in!="N");
  }while(in!="Y");
  
  //At this point, inputted sudoku puzzle is confirmed correct. Time to enter recursive backtracking solution
  boardSolver(board,0,0,false);
  cout<<endl;
  outputBoard(board, 1);
}



















//0 8 0 0 7 0 0 9 0 9 0 0 0 0 0 0 0 7 0 0 2 0 0 0 6 0 0 0 3 0 6 0 4 0 8 0 0 0 0 0 0 0 0 0 0 0 7 0 2 0 8 0 5 0 0 0 4 0 0 0 8 0 0 5 0 0 0 0 0 0 0 2 0 1 0 0 9 0 0 3 0







