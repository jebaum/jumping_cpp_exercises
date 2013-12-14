#include <iostream>
#include <stdlib.h>

using namespace std;

enum TicTacToeSquare { TTT_BLANK, TTT_O, TTT_X };

void print(int** board, int SIZE)
{
  for (int i=0; i<SIZE; ++i)
  {
    cout << "                              "; // 30 spaces
    for (int j=0; j<SIZE; ++j)
    {
      switch(board[i][j])
      {
        case TTT_BLANK:
          cout << "-";
          break;
        case TTT_O:
          cout << "O";
          break;
        case TTT_X:
          cout << "X";
          break;
        default:
          cerr << "invalid board value";
      }
    }
    cout << endl;
  }
  cout << endl;
}

int** initialize(int SIZE)
{
  int** board = new int*[SIZE];
  for (int i=0; i < SIZE; ++i)
    board[i] = new int[SIZE];

  /* initialize */
  for (int i=0; i<SIZE; ++i)
    for (int j=0; j<SIZE; ++j)
      board[i][j] = TTT_BLANK;

  return board;
}

bool gameover(int** board, int SIZE, int last_move, int move_row, int move_col)
{
  /* check if player won by completing a row */
  for (int j=0; j < SIZE; ++j)
  {
    if (board[move_row][j] != last_move)
      break;
    if (j == SIZE-1)
      return true;
  }

  /* check if player won by completing a column */
  for (int i=0; i < SIZE; ++i)
  {
    if (board[i][move_col] != last_move)
      break;
    if (i == SIZE-1)
      return true;
  }

  /* check if we moved on a diagonal, and if so, see if we won */
  if (move_row != move_col)
    return false;

  for (int i=0, j=0; i < SIZE && j < SIZE; ++i, ++j)
  {
    if (board[i][j] != last_move)
      break;
    if (i == SIZE-1 && j == SIZE-1)
      return true;
  }
  return false;
}

void clean(int** board, int SIZE)
{
  for (int i=0; i < SIZE; ++i)
    delete[] board[i];
  delete[] board;
}

int main(int argc, char *argv[])
{
  int SIZE = 3;
  if (argc == 2)
    SIZE = atoi(argv[1]);
  else if (argc >= 3)
    cout << "Invalid number of arguments. Please pass one number indicating board size, or nothing" << endl;
  int** board = initialize(SIZE);

  cout << "Player 1 is X, Player 2 is O" << endl;
  cout << "Bottom left corner has coordinate (3,1)" << endl;
  cout << "To place a tile in the bottom left corner, type '31'" << endl;
  cout << endl;

  print(board, SIZE);

  int total_moves = SIZE*SIZE;
  for (int cur_move = 0; cur_move < total_moves; ++cur_move)
  {
    /* figure out which player is moving */
    int player = 1;
    if (cur_move % 2 == 1) // odd numbered moves are player 2
      player = 2;

    /* read the player's move */
    int move_row, move_col;
    cout << "Player " << player << ", choose row:    ";
    cin >> move_row;
    cout << "Player " << player << ", choose column: ";
    cin >> move_col;
    if (move_row > SIZE || move_col > SIZE || move_row < 1 || move_col < 1)
    {
      cout << "Invalid move, board size is " << SIZE << "x" << SIZE << ". Try again." << endl;
      cur_move--;
      continue;
    }

    /* convert to zero-indexing */
    move_row--;
    move_col--;

    /* attempt the move */
    if (board[move_row][move_col] == TTT_BLANK)
      board[move_row][move_col] = player == 1 ? TTT_X : TTT_O;
    else
    {
      cout << "Invalid move. Please place a tile on a square that isn't already covered" << endl;
      cur_move--;
      continue;
    }

    /* handle aftermath of move */
    print(board, SIZE);
    if (gameover(board, SIZE, (player == 1 ? TTT_X : TTT_O), move_row, move_col))
    {
      cout << "Player " << player << " wins!" << endl;
      break;
    }
  }

  clean(board, SIZE);
  return 0;
}
