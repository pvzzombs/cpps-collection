#include <iostream>

const int cols=5;
const int rows=5;

int board[rows][cols];

void InitBoard(){
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      board[i][j] = 0;
    }
  }
}

void PlaceQueen(int i, int j){
  board[i][j] = 1;
}

void RemoveQueen(int i, int j){
  board[i][j] = 0;
}

void PrintBoard(){
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }
}


bool IsValidPosition(int a, int b){
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      if(i==a){
        if(board[i][j] == 1){
          return false;
        }
      }
      if(j==b){
        if(board[i][j] == 1){
          return false;
        }
      }
    }
  }
  
  int i, j;
  i=a; j=b;
  while(true){
    i--; j--;
    if(i == -1 || j == -1){
      break;
    }
    if(board[i][j] == 1){
      return false;
    }
  }
  
  i=a; j=b;
  while(true){
    i--; j++;
    if(i == -1 || j == cols){
      break;
    }
    if(board[i][j] == 1){
      return false;
    }
  }
  
  i=a; j=b;
  while(true){
    i++; j--;
    if(i == rows || j == -1){
      break;
    }
    if(board[i][j] == 1){
      return false;
    }
  }
  
  i=a; j=b;
  while(true){
    i++; j++;
    if(i == rows || j == cols){
      break;
    }
    if(board[i][j] == 1){
      return false;
    }
  }
  return true;
}

/*bool Solve(int i){
  if(i == rows){
    PrintBoard();
    return true;
  }
  
  for(int k=0; k<cols; k++){
    if(IsValidPosition(i, k)){
      PlaceQueen(i, k);
      if(Solve(i+1)){
        return true;
      }
      RemoveQueen(i, k);
    }
  }
  return false;
}*/

void Solve(int i){
  if(i == rows){
    PrintBoard();
    std::cout << std::endl;
  }
  
  for(int k=0; k<cols; k++){
    if(IsValidPosition(i, k)){
      PlaceQueen(i, k);
      Solve(i+1);
      RemoveQueen(i, k);
    }
  }
}


int main(int argc, char *argv[]) {
  InitBoard();
  //PlaceQueen(1,2);
  Solve(0);
  //PrintBoard();
  return 0;
}