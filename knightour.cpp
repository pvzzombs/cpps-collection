#include <iostream>
#include <vector>

const int side = 5;

int board[side][side];

void InitBoard(){
  for(int i=0; i<side; i++){
    for(int j=0; j<side; j++){
      board[i][j] = -1;
    }
  }
}

void PrintBoard(){
  for(int i=0; i<side; i++){
    for(int j=0; j<side; j++){
      std::cout << board[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool IsSolved(){
  for(int i=0; i<side; i++){
    for(int j=0; j<side; j++){
      if(board[i][j] == -1){
        return false;
      }
    }
  }
  return true;
}

bool IsValidPosition(int i, int j){
  if(board[i][j] != -1){
    return false;
  }
  return true;
}

void PlaceKnight(int i, int j, int q){
  board[i][j] = q;  
}

void RemoveKnight(int i, int j){
  board[i][j] = -1;
}

std::vector<std::vector<int>> CalculatePosition(int a, int b){
  std::vector<std::vector<int>> out;
  int r, c;
  std::vector<int> temp(2);
 
  // +1 +2 
  r = a; c = b;
  r += 1; c += 2;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  // +2 +1
  r = a; c = b;
  r += 2; c += 1;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  // +2 -1
  r = a; c = b;
  r += 2; c -= 1;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  // +1 -2
  r = a; c = b;
  r += 1; c -= 2;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  // -1 -2
  r = a; c = b;
  r -= 1; c -= 2;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  // -2 -1
  r = a; c = b;
  r -= 2; c -= 1;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  // -2 1
  r = a; c = b;
  r -= 2; c += 1;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  // -1 2
  r = a; c = b;
  r -= 1; c += 2;
  if(r > -1 &&  c > -1 && r < side && c < side){
    temp.at(0) = r;
    temp.at(1) = c;
    out.push_back(temp);
  }
  
  return out;
}

bool Solve(int q, int r, int s){
  //base case
  if(IsSolved()/*qs == (side*side)-1*/){
    //std::cout << s << std::endl;
    PrintBoard();
    return true;
  }
  //Calculate Position
  std::vector<std::vector<int>> pos = CalculatePosition(q,r);
  //PlaceKnight(q, r, s);
  for(int i=0; i<pos.size(); i++){
    int a = pos.at(i).at(0);
    int b = pos.at(i).at(1);
    if(IsValidPosition(a, b)){
      PlaceKnight(a, b, s+1);
      if(Solve(a, b, s+1)){
        return true;
      }
      RemoveKnight(a, b);
    }
  }
  //RemoveKnight(q, r);
  //PrintBoard();
  //std::cout << s << std::endl;
  return false;
}

int main(int argc, char *argv[]) {
  InitBoard();
  PlaceKnight(0,0,0);
  Solve(0, 0, 0);
  RemoveKnight(0,0);
  /*std::vector<std::vector<int>> a;
  a = CalculatePosition(0,0);
  
  for(int i=0; i<a.size(); i++){
    for(int j=0; j<2; j++){
      std::cout << a.at(i).at(j) << " ";
    }
    std::cout << std::endl;
  }*/
  return 0;
}