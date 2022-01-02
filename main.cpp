#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
#define N 9

bool UsedInRow(int grid[N][N], int prow, int number){
    for (int col = 0; col < N; col++)
        if (grid[prow][col] == number)
            return true;
    return false;
}
bool UsedInCol(int grid[N][N], int pcol, int number){
    for (int row = 0; row < N; row++)
        if (grid[row][pcol] == number)
            return true;
  else 
     return false;
}
bool UsedInBox(int grid[N][N], int boxBeginRow, int boxBeginCol, int number){
    bool tf = false;
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxBeginRow][col+boxBeginCol] == number)
                tf = true;
    return tf;
}
bool isGridSafe(int grid[N][N], int prow, int pcol, int number){
    return !UsedInRow(grid, prow, number) && !UsedInCol(grid, pcol, number) &&
           !UsedInBox(grid, prow - prow % 3 , pcol - pcol % 3, number);
}

bool isEmptyLocationExist(int grid[N][N]){
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return true;
    return false;
}

bool fixedValue(int r, int c){
    if((r==1 && (c==5 || c==7 || c==8)) || (r==2 && (c==2 || c==4)) || 
    (r==3 && (c==3 || c==5)) || (r==4 && (c==2 || c==6)) || 
    (r==5 && (c==1)) || (r==6 && (c==0 || c==7 || c==8)) || 
    (r==7 && (c==2 || c==4)) || (r==8 && (c==4 || c==8)))
        return true;
    return false;
}

bool solveSudoku(int grid[N][N]){
    int row, col;
    if (!isEmptyLocationExist(grid))
       return true;
    for (int num = 1; num <= 9; num++){
        if (isGridSafe(grid, row, col, num)){
            grid[row][col] = num;
            if (solveSudoku(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

void printGrid(int grid[N][N]){
    for (int row = 0; row < N; row++){
        for (int col = 0; col < N; col++)
            cout<< grid[row][col]<<"  ";
        cout<<endl;
    }
}

void playSudoku(int grid[N][N]){
    printGrid(grid);
    cout << "\n\nMake a choice (row col number): ";
    int r, c, n;
    cin >> r >> c >> n;
    while(grid[r][c]!=0){
        while(fixedValue(r,c)){
            cout << "This is a fixed value. You can't change it. Enter again";
            cin >> r >> c >> n;
        }
        if(grid[r][c]==0)
            break;
        cout << "Position already occupied! You want to change it ?! ";
        bool change;
        cin >> change;
        if(change)
            break;
        cout << "Okay, make a choice again: ";
        cin >> r >> c >> n;
    }
    while(!isGridSafe(grid, r, c, n)){
        cout << "This isn't right! Please enter again: ";
        cin >> r >> c >> n;
    }
    if(!isEmptyLocationExist(grid)){
       cout << "\n\nCongratulations !!! You completed the game" << endl;
       return ;
    }
    if(solveSudoku(grid))
        playSudoku(grid);
    else
        cout << "\n\nThis board can no longer be solved" << endl; 
}

int main(){
    int grid[N][N] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 3, 0, 8, 5},
                      {0, 0, 1, 0, 2, 0, 0, 0, 0},
                      {0, 0, 0, 5, 0, 7, 0, 0, 0},
                      {0, 0, 4, 0, 0, 0, 1, 0, 0},
                      {0, 9, 0, 0, 0, 0, 0, 0, 0},
                      {5, 0, 0, 0, 0, 0, 0, 7, 3},
                      {0, 0, 2, 0, 1, 0, 0, 0, 0},
                      {0, 0, 0, 0, 4, 0, 0, 0, 9}};
    system("cls");
    playSudoku(grid);
    return 0;
}