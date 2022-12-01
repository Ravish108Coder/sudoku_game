#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

int option = 0;
int filled = 0;
int mistake_max = 5;
#define N 10 // defining grid dimension, that is 9 by 9
string gg(70, '-');
string hh = "            ";
string cpy = hh + gg;

bool ValidMove(vector<vector<int>> &arr, int r, int c, int value);
bool SolveSudoku(vector<vector<int>> &grid)
{
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            if (grid[i][j] == 0)
            {
                for (int num = 1; num <= 9; num++)
                {
                    if (ValidMove(grid, i, j, num))
                    {
                        grid[i][j] = num;
                        if (SolveSudoku(grid))
                        {
                            return true;
                        }
                        grid[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}
string strc_(int n)
{
    if (n == 0)
    {
        return "-";
    }
    return to_string(n);
}
void printHyphen()
{
    cout << cpy
         << endl;
}
void printSudokoBoard(vector<vector<int>> a)
{
    int cnt = 1;
    printHyphen();
    for (int i = 1; i <= 9; i++)
    {
        if (i % 3 == 1)
        {
            printHyphen();
            cout << endl;
        }
        for (int j = 1; j <= 9; j++)
        {
            if (j == 1)
            {
                cout << cnt++ << "--->|   ";
            }
            else if (j % 3 == 1)
            {
                cout << "  ||  ";
            }
            cout << "   " << strc_(a[i][j]) << "   ";
        }
        cout << endl
             << endl
             << endl;
        if (i == 9)
        {
            printHyphen();
            printHyphen();
            cout << "\t    _      _      _            _       _      _           _      _      _\n";
            cout << "\t    ^      ^      ^            ^       ^      ^           ^      ^      ^\n";
            cout << "\t    |      |      |            |       |      |           |      |      |\n";
            cout << "\t    1      2      3            4       5      6           7      8      9\n";
        }
    }
}
void swapTwoValuesInSudoku(vector<vector<int>> &arr, int value1, int value2)
{
    if (value1 == value2)
    {
        return;
    }

    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            if (arr[i][j] == value1)
            {
                arr[i][j] = value2;
                continue;
            }
            if (arr[i][j] == value2)
            {
                arr[i][j] = value1;
            }
        }
    }
}
void copyTwo2dArrays(vector<vector<int>> &grid1, vector<vector<int>> &grid2)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            grid1[i].push_back(grid2[i][j]);
        }
    }
}
void copyTwo2dvecAndArrays(vector<vector<int>> &v, int grid2[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            v[i].push_back(grid2[i][j]); //    isime dikkat hai
        }
    }
}
void swapTwoColumns(vector<vector<int>> &arr, int col1, int col2)
{
    for (int i = 1; i < N; i++)
    {
        swap(arr[i][col1], arr[i][col2]);
    }
}

void sudokuGenerator(vector<vector<int>> &sudokuboard)
{
    srand(time(0));
    int random[3] = {1, 4, 7};
    int m = rand() % 3;
    int n = rand() % 3;
    while (random[m] == random[n])
    {
        srand(time(0));
        n = rand() % 3;
    }
    swapTwoColumns(sudokuboard, random[m], random[n]);
    swapTwoColumns(sudokuboard, random[m] + 1, random[n] + 1);
    swapTwoColumns(sudokuboard, random[m] + 2, random[n] + 2);
    swap(sudokuboard[random[m]], sudokuboard[random[n]]);
    swap(sudokuboard[random[m] + 1], sudokuboard[random[n] + 1]);
    swap(sudokuboard[random[m] + 2], sudokuboard[random[n] + 2]);

    int z = (rand() % 2) + 1;
    swap(sudokuboard[random[3 - n - m]], sudokuboard[random[3 - n - m] + z]);
    srand(time(0));
    swapTwoValuesInSudoku(sudokuboard, (rand() % 9) + 1, (rand() % 9) + 1);
    swapTwoValuesInSudoku(sudokuboard, (rand() % 9) + 1, (rand() % 9) + 1);
    swapTwoValuesInSudoku(sudokuboard, (rand() % 9) + 1, (rand() % 9) + 1);
    printSudokoBoard(sudokuboard);
}
bool checkInBox(vector<vector<int>> &arr, int r, int c, int value)
{
    if (r >= 1 && r <= 3)
    {
        r = 1;
    }
    else if (r >= 4 && r <= 6)
    {
        r = 4;
    }
    else if (r >= 7 && r <= 9)
    {
        r = 7;
    }

    if (c >= 1 && c <= 3)
    {
        c = 1;
    }
    else if (c >= 4 && c <= 6)
    {
        c = 4;
    }
    else if (c >= 7 && c <= 9)
    {
        c = 7;
    }

    for (int i = r; i < (r + 3); i++)
    {
        for (int j = c; j < (c + 3); j++)
        {
            if (arr[i][j] == value)
            {
                return false;
            }
        }
    }
    return true;
}
bool checkInLine(vector<vector<int>> &arr, int r, int c, int value)
{
    for (int i = 1; i < N; i++)
    {
        if (arr[i][c] == value)
        {
            return false;
        }
    }
    for (int j = 1; j < N; j++)
    {
        if (arr[r][j] == value)
        {
            return false;
        }
    }
    return true;
}

bool ValidMove(vector<vector<int>> &arr, int r, int c, int value)
{   
    return checkInLine(arr, r, c, value) & checkInBox(arr, r, c, value);
}

void takeOption(vector<vector<int>> &v)
{
    cout << "\nOPTIONS\n1: Easy\n2: Medium\n3: Hard\n4: Expert\n5: Evil" << endl;
    cout << "Enter Option : ";
    cin >> option;
    switch (option)
    {
    case 1: // easy
    {
        int sudokuboard1[N][N] =
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 3, 0, 6, 5, 0, 8, 4, 0, 0},
                {0, 5, 2, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 8, 7, 0, 0, 0, 0, 3, 1},
                {0, 0, 0, 3, 0, 1, 0, 0, 8, 0},
                {0, 9, 0, 0, 8, 6, 3, 0, 0, 5},
                {0, 0, 5, 0, 0, 9, 0, 6, 0, 0},
                {0, 1, 3, 0, 0, 0, 0, 2, 5, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 7, 4},
                {0, 0, 0, 5, 2, 0, 6, 3, 0, 0}};
        copyTwo2dvecAndArrays(v, sudokuboard1);
        return;
    }
    case 2: // medium
    {
        int sudokuboard2[N][N] =
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 6, 4, 0, 0, 0, 0, 7},
                {0, 0, 0, 9, 0, 0, 7, 0, 0, 0},
                {0, 0, 0, 8, 9, 2, 0, 0, 4, 6},
                {0, 0, 6, 0, 1, 0, 4, 2, 0, 0},
                {0, 0, 8, 1, 0, 0, 0, 0, 3, 0},
                {0, 2, 0, 0, 8, 0, 5, 6, 0, 1},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 3, 4, 0, 6, 0, 7, 0, 0},
                {0, 0, 1, 7, 0, 0, 0, 9, 6, 0}};
        copyTwo2dvecAndArrays(v, sudokuboard2);
        return;
    }
    case 3: // hard
    {
        int sudokuboard3[N][N] =
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 5, 8, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 2, 0, 8, 7, 9, 0, 0},
                {0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
                {0, 0, 6, 0, 0, 0, 0, 0, 3, 0},
                {0, 3, 0, 0, 0, 6, 0, 5, 0, 0},
                {0, 0, 0, 0, 5, 0, 8, 7, 0, 4},
                {0, 0, 9, 6, 3, 0, 0, 0, 7, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 9},
                {0, 0, 0, 0, 8, 0, 0, 2, 5, 0}};
        copyTwo2dvecAndArrays(v, sudokuboard3);
        return;
    }
    case 4: // expert
    {
        int sudokuboard4[N][N] =
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                {0, 0, 0, 0, 0, 0, 7, 8, 0, 0},
                {0, 0, 8, 0, 0, 0, 3, 0, 0, 0},
                {0, 0, 4, 0, 0, 0, 0, 0, 0, 5},
                {0, 1, 0, 0, 0, 0, 0, 0, 6, 0},
                {0, 0, 7, 0, 0, 9, 0, 0, 0, 0},
                {0, 0, 9, 2, 0, 0, 0, 4, 0, 0},
                {0, 0, 0, 5, 4, 2, 0, 7, 0, 0},
                {0, 0, 0, 4, 5, 6, 0, 9, 8, 0}};
        copyTwo2dvecAndArrays(v, sudokuboard4);
        return;
    }
    case 5: // evil
    {
        int sudokuboard5[N][N] =
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 7, 4, 0, 1, 0, 2, 9},
                {0, 8, 0, 0, 0, 0, 0, 0, 0, 7},
                {0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
                {0, 0, 5, 0, 0, 0, 0, 6, 0, 0},
                {0, 0, 0, 8, 2, 0, 7, 0, 1, 0},
                {0, 0, 0, 0, 0, 9, 0, 0, 0, 0},
                {0, 0, 0, 4, 0, 3, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 8, 0, 0, 9, 0},
                {0, 6, 0, 0, 9, 0, 4, 1, 0, 0}};
        copyTwo2dvecAndArrays(v, sudokuboard5);
        return;
    }

    default:
        break;
    }
    return;
}

int main()
{
    vector<vector<int>> sudokuSolution(N);
    vector<vector<int>> sudokuboard(N);
    takeOption(sudokuboard);

    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j < N; j++)
        {
            if (sudokuboard[i][j] != 0)
            {
                filled++;
            }
        }
    }
    string mode[6] = {"PAPER", "EASY", "MEDIUM", "HARD", "EXPERT", "EVIL"};
    srand(time(0));
    // cout << "\n\t\t\t\t----->MOBILE SUDOKU BEGINS<-----\n";
    cout << "\n\t\t\t\t----->" << mode[option] << " SUDOKU BEGINS<-----\n";
    sudokuGenerator(sudokuboard);
    copyTwo2dArrays(sudokuSolution, sudokuboard);
    SolveSudoku(sudokuSolution);
    // cout<<"\n\n\t\t\t\t----->"<<mode[option]<<" Sudoku Solution<-----\n\n";
    // printSudokoBoard(sudokuSolution);

    int row, col, value, mistake = 0;
    cout << "\n\t\t----->Maximum " << mistake_max << " mistakes you can make<-----\n";
    while (filled != 81)
    {
        if (mistake == mistake_max)
        {
            cout << "\n\t\t----->Y O U   L O S E   B R O<----- \n\n\n";
            cout << "\n\t\t----->Game Over<----- \n\n\n";
            return 0;
        }
        cout << endl;
        cout << "Enter (Row no.)  (Column no.)  (Value)  :  ";
        cin >> row >> col >> value;
        if (value > 9 || value < 1)
        {
            mistake++;
            cout << "\nInvalid Move\nMistakes remaining " << mistake_max - mistake << endl;
            continue;
        }
        //  if (ValidMove(sudokuboard, row, col, value))
        //  {
        //      sudokuboard[row][col] = value; // paper sudoku
        //      filled++;
        //      printSudokoBoard(sudokuboard);
        //  }
        if ((sudokuboard[row][col] == 0) && (value == sudokuSolution[row][col]))
        {
            sudokuboard[row][col] = value;
            filled++;
            system("cls");
            printSudokoBoard(sudokuboard);
        }
        else
        {
            mistake++;
            cout << "\nInvalid Move\nMistakes remaining " << mistake_max - mistake << endl;
        }
    }
    if (filled == 81)
    {
        cout << "\n\t\t----->Y O U   W I N<----- \n\n\n";
        cout << "\n\t\t----->Game Over<----- \n\n\n";
    }
    return 0;
}