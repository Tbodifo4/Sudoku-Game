// C++ program to generate a valid sudoku 
// with k empty cells
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <iomanip>
#include <string>
#include <stack>

using namespace std;

vector<vector<int>> SolvedPuzzle;
int score = 0;

// Returns false if given 3x3 block contains num
// Ensure the number is not used in the box
bool unUsedInBox(vector<vector<int>>& grid, int rowStart, int colStart, int num) 
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (grid[rowStart + i][colStart + j] == num) 
            {
                return false;
            }
        }
    }
    return true;
}

// Fill a 3x3 matrix
// Assign valid random numbers to the 3x3 subgrid
void fillBox(vector<vector<int>>& grid, int row, int col) 
{
    int num;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            do 
            {

                // Generate a random number between 1 and 9
                num = (rand() % 9) + 1;
            } while (!unUsedInBox(grid, row, col, num));
            grid[row + i][col + j] = num;
        }
    }
}

// Check if it's safe to put num in row i
// Ensure num is not already used in the row
bool unUsedInRow(vector<vector<int>>& grid, int i, int num) 
{
    for (int j = 0; j < 9; j++) 
    {
        if (grid[i][j] == num) 
        {
            return false;
        }
    }
    return true;
}

// Check if it's safe to put num in column j
// Ensure num is not already used in the column
bool unUsedInCol(vector<vector<int>>& grid, int j, int num) 
{
    for (int i = 0; i < 9; i++) 
    {
        if (grid[i][j] == num) 
        {
            return false;
        }
    }
    return true;
}

// Check if it's safe to put num in the cell (i, j)
// Ensure num is not used in row, column, or box
bool checkIfSafe(vector<vector<int>>& grid, int i, int j, int num) 
{
    return (unUsedInRow(grid, i, num) && unUsedInCol(grid, j, num) &&
        unUsedInBox(grid, i - i % 3, j - j % 3, num));
}

// Fill the diagonal 3x3 matrices
// The diagonal blocks are filled to simplify the process
void fillDiagonal(vector<vector<int>>& grid) 
{
    for (int i = 0; i < 9; i = i + 3) 
    {

        // Fill each 3x3 subgrid diagonally
        fillBox(grid, i, i);
    }
}

// Fill remaining blocks in the grid
// Recursively fill the remaining cells with valid numbers
bool fillRemaining(vector<vector<int>>& grid, int i, int j) 
{

    // If we've reached the end of the grid
    if (i == 9) 
    {
        return true;
    }

    // Move to next row when current row is finished
    if (j == 9) 
    {
        return fillRemaining(grid, i + 1, 0);
    }

    // Skip if cell is already filled
    if (grid[i][j] != 0) 
    {
        return fillRemaining(grid, i, j + 1);
    }

    // Try numbers 1-9 in current cell
    for (int num = 1; num <= 9; num++) 
    {
        if (checkIfSafe(grid, i, j, num)) 
        {
            grid[i][j] = num;
            if (fillRemaining(grid, i, j + 1)) 
            {
                return true;
            }
            grid[i][j] = 0;
        }
    }

    return false;
}

// Remove K digits randomly from the grid
// This will create a Sudoku puzzle by removing digits
void removeKDigits(vector<vector<int>>& grid, int k) 
{
    while (k > 0) 
    {

        // Pick a random cell
        int cellId = rand() % 81;

        // Get the row index
        int i = cellId / 9;

        // Get the column index
        int j = cellId % 9;

        // Remove the digit if the cell is not already empty
        if (grid[i][j] != 0) 
        {

            // Empty the cell
            grid[i][j] = 0;

            // Decrease the count of digits to remove
            k--;
        }
    }
}

// Generate a Sudoku grid with K empty cells
vector<vector<int>> sudokuGenerator(int k) 
{

    // Initialize an empty 9x9 grid
    vector<vector<int>> grid(9, vector<int>(9, 0));

    // Fill the diagonal 3x3 matrices
    fillDiagonal(grid);

    // Fill the remaining blocks in the grid
    fillRemaining(grid, 0, 0);

    // Remove K digits randomly to create the puzzle.
    // This is a completed version of the puzzle
    SolvedPuzzle = grid;
    removeKDigits(grid, k);

    return grid;
}

void printPuzzle(vector<vector<int>> sudoku)
{
    char plus = 206;
    char horz = 205;
    char vert = 186;
    int row = 0;
    cout << "Col:    1 2 3   4 5 6   7 8 9"
        << endl << endl;
    cout << "Row 1   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << "Row 2   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << "Row 3   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << '\t' << horz << horz << horz << horz << horz << horz << plus << horz << horz << horz << horz << horz << horz << horz << plus << horz << horz << horz << horz << horz << horz << endl;
    cout << "Row 4   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << "Row 5   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << "Row 6   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << '\t' << horz << horz << horz << horz << horz << horz << plus << horz << horz << horz << horz << horz << horz << horz << plus << horz << horz << horz << horz << horz << horz << endl;
    cout << "Row 7   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << "Row 8   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
    cout << "Row 9   " << sudoku[row][0] << " " << sudoku[row][1] << " " << sudoku[row][2] << " " << vert << " " << sudoku[row][3] << " " << sudoku[row][4] << " " << sudoku[row][5] << " " << vert << " " << sudoku[row][6] << " " << sudoku[row][7] << " " << sudoku[row][8] << endl; row++;
}

int partition(vector<int>& vec, int low, int high) {

    // Selecting last element as the pivot
    int pivot = vec[high];

    // Index of elemment just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {

        // If current element is smaller than or
        // equal to pivot
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

void quickSort(vector<int>& vec, int low, int high) {

    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {

        // pi is Partitioning Index, arr[p] is now at
        // right place
        int pi = partition(vec, low, high);

        // Separately sort elements before and after the
        // Partition Index pi
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

int main() {

    // Seed the random number generator
    srand(time(0));
    int k = 0;

    // Set the number of empty cells
    int playerChoice;
    int customAmount = 0;

    cout << "Welcome to Sudoku!" << endl << endl;
    cout << "Your goal is to fill in the board with the missing digits represented by a 0." << endl;
    cout << "All correct digits will be 1-9 and there will only ever be one of each digit per row, column, square, and diagonal." << endl << endl;

    bool inloop = true;
    while (inloop)
    {
        cout << "Select your difficulty!" << endl;
        cout << left << setw(12) << "[1. Easy]" << right << setw(15) << " - 5 Missing digits." << endl 
            << left << setw(12) << "[2. Medium]" << right << setw(15) << " - 10 Missing digits" << endl
            << left << setw(12) << "[3. Hard] " << right << setw(15) << " - 15 Missing digits" << endl
            << left << setw(12) << "[4. Custom] " << right << setw(15) << " - Custom amount of missing digits" << endl
            << endl << "Selection (1-4): ";
        cin >> playerChoice;

        switch (playerChoice)
        {
        case 1:
            k = 5;
            inloop = false;
            break;
        case 2:
            k = 10;
            inloop = false;
            break;
        case 3:
            k = 15;
            inloop = false;
            break;
        case 4:
            while (true)
            {
                cout << "Enter how many missing digits you would like(1 - 40): ";
                cin >> customAmount;

                if (customAmount < 1 || customAmount > 40)
                {
                    cout << endl << "That is not in range of the allowed custom amount!" << endl;
                    continue;
                }
                else
                {
                    k = customAmount;
                    inloop = false;
                    break;
                }
            }
            break;
        default:
            cout << endl << "That is not an option. Try again!" << endl << endl;

        }

    }
    
    cout << endl << "Loading..";
    this_thread::sleep_for(chrono::milliseconds(2000));
    system("cls");

    
    vector<vector<int>> sudoku = sudokuGenerator(k);

    printPuzzle(sudoku);

    cout << endl << endl;
    
    bool GameNotFinished = true;
    bool bonusPoints = false; 
    int bpamount = 5;

    while (GameNotFinished)
    {
        int userRow, userCol, userGuess;
        cout << "There are " << k << " missing digits from the Sudoku! Your current score is: " << score << endl;
        cout << "Enter your guess as [row][col][digit]" << endl;
        cout << "Row: ";
        cin >> userRow;
        cout << "Col: ";
        cin >> userCol;
        cout << "Number guess: ";
        cin >> userGuess;

        if (userRow < 1 || userRow > 9 || userCol < 1 || userCol > 9 || userGuess < 1 || userGuess > 9)
        {
            cout << "Invalid format. Try again!" << endl;
            this_thread::sleep_for(chrono::milliseconds(2000));
            system("cls");
            printPuzzle(sudoku);
            continue;
        }
        else
        {
            if (SolvedPuzzle[userRow - 1][userCol - 1] == userGuess)
            {
                int points = 10;
                
                if (bonusPoints)
                {
                    cout << "Correct guess! " << points+bpamount << " gained! + " << bpamount << " bonus for consecutive correct answers!" << endl;
                    score = score + points;
                    score = score + bpamount;
                    bpamount = bpamount + 5;
                }
                else
                {
                    cout << "Correct guess! 10 points gained!" << endl;
                    score = score + points;
                }
                bonusPoints = true;
                this_thread::sleep_for(chrono::milliseconds(2000));
                system("cls");
                sudoku[userRow - 1][userCol - 1] = userGuess;
                printPuzzle(sudoku);
            }
            else
            {
                bpamount = 5;
                bonusPoints = false;
                cout << "Incorrect guess. 10 points lost." << endl;
                score = score - 10;
                this_thread::sleep_for(chrono::milliseconds(2000));
                system("cls");
                printPuzzle(sudoku);
            }
        }

        if (sudoku == SolvedPuzzle)
        {
            GameNotFinished = false;
        }

    }
    cout << endl;
    cout << "You won!" << endl;
    cout << "Your score is: " << score << "!!" << endl;

    ofstream output_file;
    output_file.open("Highscores.txt", ios::app);
    output_file << score << endl;
    output_file.close();

    cout << "Enter 'h' to see highscores or any other key to exit: ";
    char userExit;
    cin >> userExit;

    vector<int> highscores;
    if (userExit == 'h' || userExit == 'H')
    {
        string highscore;
        ifstream input_file;
        input_file.open("Highscores.txt");

        cout << endl << "  " << "HIGHSCORES" << endl << "==============" << endl;
        
        while (getline(input_file, highscore))
        {
            highscores.push_back(stoi(highscore));
        }
        input_file.close();

        quickSort(highscores, 0, highscores.size() - 1);

    }
   
    stack<int> reverseScoresOrder;

    for (auto score : highscores)
    {
        reverseScoresOrder.push(score);
    }
    int list = 10;
    if (highscores.size() < list)
    {
        for (int i = 0; i < highscores.size(); i++)
        {
            cout << "    #" << i + 1 << ": " << reverseScoresOrder.top() << endl;
            reverseScoresOrder.pop();
        }
    }
    else
    {
        for (int i = 0; i < list; i++)
        {
            cout << "    #" << i+1 << ": " << reverseScoresOrder.top() << endl;
            reverseScoresOrder.pop();
        }
    }

    
    
}