#include <fstream>
#include <iostream>
using namespace std;

bool isSafe(int *grid, int i, int j, int no, int mat_type, int N) {
  // Check fi=or Row and Column
  for (int k = 0; k < N; k++) {
    if (*((grid + k * N) + j) == no || *((grid + i * N) + k) == no) {
      return false;
    }
  }

  // Check for SubGrid
  int sx = (i / mat_type) * mat_type;
  int sy = (j / mat_type) * mat_type;

  for (int x = sx; x < sx + mat_type; x++) {
    for (int y = sy; y < sy + mat_type; y++) {
      if (*((grid + x * N) + y) == no) {
        return false;
      }
    }
  }
  return true;
}

bool solveSudoku(int *grid, int i, int j, int mat_type, int N) {
  // grid[N][N];
  // Base Case
  if (i == N) {

    // Sudoku printer
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (j % mat_type == 0)
          cout << "| ";

        cout << *((grid + i * N) + j) << " ";
        if (j == (N - 1))
          cout << "|";
      }
      int count = 0;
      if ((i + 1) % mat_type == 0)
        cout << "\n";
      while ((i + 1) % mat_type == 0) {
        cout << "--";
        count++;
        if (count > (mat_type * mat_type + mat_type - 1))
          break;
      }
      cout << "\n";
    }

    return true;
  }

  // Recursive Case
  if (j == N) {
    return solveSudoku((int *)grid, i + 1, 0, mat_type, N);
  }

  // Skip the prefilled cell
  if (*((grid + i * N) + j) != 0) {
    return solveSudoku((int *)grid, i, j + 1, mat_type, N);
  }

  // Cell to be filled
  // Try out all the possibilities
  for (int no = 1; no <= N; no++) {
    // Check if it is safe to place the number or not

    if (isSafe((int *)grid, i, j, no, mat_type, N)) {
      *((grid + i * N) + j) = no;
      bool solveSubproblem = solveSudoku((int *)grid, i, j + 1, mat_type, N);

      //  Checking for next possibility with next column
      if (solveSubproblem == true) {
        return true;
      }
    }
  }
  // If no option works
  *((grid + i * N) + j) = 0;
  return false;
}

bool sudokuChecker(int *arr2, int *og, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (*((arr2 + i * N) + j) != *((og + i * N) + j))
        return false;
    }
  }
  return true;
}

int main() {
  int type, N;
  ifstream s2;
  string l;

  int ptrfilepossud1 = 0;
  int ptrfilepossud2 = 0;

  cout << "\n||       Sudoku Game     ||\n";
  cout << "RULES:\n1)Each row,column,and region must contain all of the digits "
          "from 1 to the size of the grid (e.g. 1-4 for a 4x4 grid or 1-9 for "
          "a 9x9 grid).\n\n2)No digit can be repeated within a row, column, or "
          "region.\n\n3)The puzzle is solved when all cells are filled in with "
          "digits.\n\n4)There may be additional constraints or clues given in "
          "the puzzle, such as the placement of certain digits in certain "
          "cells.\n\n5)The goal is to fill in the grid using logic and "
          "deduction, without the need for guessing.";
start:
  cout << "\n\nSelect sudoku type:\n1.4*4   2.9*9   3.Quit Game     ";
  cin >> type;
  if (type == 1)
    goto sudoku1;
  else if (type == 2) {
    goto sudoku2;
  } else {
    cout << "\nThankYou for Playing!\n";
    return 0;
  }

// for 4*4 sudoku
sudoku1:
  s2.open("matrix2*2.csv");
  cout << "||    Sudoku 4*4    ||\n";
  int arr[4][4], og[4][4], temp;
  N = 4;
  // string l;
  s2.seekg(ptrfilepossud1);
  ptrfilepossud1 = s2.tellg();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      getline(s2, l, ',');
      temp = stoi(l);
      arr[i][j] = temp;
      og[i][j] = temp;
      if (j % 2 == 0)
        cout << "| ";

      cout << arr[i][j] << " ";
      if (j == 3)
        cout << "|";
    }
    int count = 0;
    if ((i + 1) % 2 == 0)
      cout << "\n";
    while ((i + 1) % 2 == 0) {
      cout << "--";
      count++;
      if (count > 5)
        break;
    }
    cout << "\n";
  }
  // saves the current pointer position and stores.
  ptrfilepossud1 = s2.tellg();
  if (ptrfilepossud1 == -1)
    ptrfilepossud1 = 0;

  int r, c;
  while (1) {
    cout << "Enter position to insert number(row,column):\n";
    cin >> r >> c;
    if (arr[r - 1][c - 1] != 0 || (r > 4 && c > 4)) {
      cout << "Cannot change value!\n";
    } else {
    number:
      cout << "Enter number(1-4): ";
      cin >> arr[r - 1][c - 1];
      if (arr[r - 1][c - 1] > 4) {
        cout << "Enter valid number!\n";
        goto number;
      }
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
          if (j % 2 == 0)
            cout << "| ";

          cout << arr[i][j] << " ";
          if (j == 3)
            cout << "|";
        }
        int count = 0;
        if ((i + 1) % 2 == 0)
          cout << "\n";
        while ((i + 1) % 2 == 0) {
          cout << "--";
          count++;
          if (count > 5)
            break;
        }
        cout << "\n";
      }
    }

    int mat_type = 2;
    char ch;
    cout << "Do u want to continue? (y/n): ";
    cin >> ch;
    if (ch == 'n') {
      cout << "\n||     Solution of Sudoku      ||\n\n";
      solveSudoku((int *)og, 0, 0, mat_type, N);
      // cout<<"No Solution Exists !"<<endl;
      if (!sudokuChecker((int *)og, (int *)arr, N))
        cout << "Your Solution is Incorrect!!\n";
      else
        cout << "Congrats!!...Your solution is correct\n";

      cout << "\nThankyou for Playing!\n";
      s2.close();
      goto start;
    }
  }

sudoku2:
  // For 9*9 Matrix
  cout << "\n|| Sudoku 9*9 ||\n\n";
  ifstream s3("matrix3*3.csv");
  string l2;
  int mat_type = 3;
  N = 9;
  s3.seekg(ptrfilepossud2);
  ptrfilepossud2 = s3.tellg();
  // cout<<"pos is "<<ptrfilepossud2<<endl;

  int arr2[9][9], original[9][9];
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      getline(s3, l2, ',');
      temp = stoi(l2);
      arr2[i][j] = temp;
      original[i][j] = temp;

      if (j % 3 == 0)
        cout << "| ";

      cout << arr2[i][j] << " ";
      if (j == 8)
        cout << "|";
    }
    int count = 0;
    if ((i + 1) % 3 == 0)
      cout << "\n";
    while ((i + 1) % 3 == 0) {
      cout << "--";
      count++;
      if (count > 11)
        break;
    }
    cout << "\n";
  }
  ptrfilepossud2 = s3.tellg();
  // cout<<"pos is "<<ptrfilepos<<endl;
  if (ptrfilepossud2 == -1) {
    ptrfilepossud2 = 0;
  }

  int r2, c2, no = 0;
  while (1) {
    cout << "Enter position to insert number(row,column):\n";
    cin >> r2 >> c2;
    if ((r2 > 9 && c2 > 9) || original[r2 - 1][c2 - 1] != 0)
      cout << "Cannot insert number!\n";

    else {
    number2:
      cout << "Enter number(1-9): ";
      cin >> arr2[r2 - 1][c2 - 1];
      if (arr2[r2 - 1][c2 - 1] > 9) {
        cout << "Enter valid number!\n";
        goto number2;
      }

      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          if (j % 3 == 0)
            cout << "| ";

          cout << arr2[i][j] << " ";
          if (j == 8)
            cout << "|";
        }
        int count = 0;
        if ((i + 1) % 3 == 0)
          cout << "\n";
        while ((i + 1) % 3 == 0) {
          cout << "--";
          count++;
          if (count > 11)
            break;
        }
        cout << "\n";
      }
    }
    char ch;
    cout << "Do u want to continue?(y/n): ";
    cin >> ch;
    if (ch == 'n') {
      cout << "\n||     Solution of Sudoku      ||\n\n";
      solveSudoku((int *)original, 0, 0, mat_type, N);
      // cout<<"No Solution Exists !"<<endl;
      if (!sudokuChecker((int *)original, (int *)arr2, N))
        cout << "Your Solution is Incorrect!!\n";
      else
        cout << "Congrats!!...Your solution is correct\n";

      cout << "\n\nThankyou for Playing!\n";
      s3.close();
      goto start;
    }
  }
}
