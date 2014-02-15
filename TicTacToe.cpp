#include <iostream>
#include <windows.h>
using namespace std;

const int GRID_SIZE=3;
struct Player
{
	char name [80];
	char piece;
};

void InitializeGrid(char grid[GRID_SIZE][GRID_SIZE],int size, char value);
void SetGridValue(char grid[GRID_SIZE][GRID_SIZE], int size, int x, int y, char value);
void PrintGrid(char grid[GRID_SIZE][GRID_SIZE],int size);
void PlayerMove(char grid[GRID_SIZE][GRID_SIZE], int size, Player player, char empty);
bool IsMoveValid(char grid[GRID_SIZE][GRID_SIZE], int size, int x, int y, char empty);
bool IsMoveAvailable(char grid[GRID_SIZE][GRID_SIZE], int size, char empty);
bool HasPlayerWon (char grid[GRID_SIZE][GRID_SIZE], int size, Player player, char winningPlayer[]);
void SetColor(unsigned char color)
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}

int main()
{
	Player p1, p2;
	cout << "Player One enter name: ";
	cin >> p1.name;
	p1.piece = 'X';
	cout << "Player Two enter name: ";
	cin >> p2.name;
	p2.piece = 'O';
	char grid[GRID_SIZE][GRID_SIZE], empty = '.', winningPlayer[80];
	InitializeGrid( grid, GRID_SIZE, empty);
	bool MoveAvailable = IsMoveAvailable (grid, GRID_SIZE, empty);
	bool PlayerWon = false;
	SetColor(0xF0);
	cout << "7 8 9" << endl << "4 5 6" << endl << "1 2 3" << endl;
	SetColor(0x07);
	do
	{
		PlayerMove (grid, GRID_SIZE, p1, empty);
		MoveAvailable = IsMoveAvailable (grid, GRID_SIZE, empty);
		PlayerWon = HasPlayerWon (grid, GRID_SIZE, p1, winningPlayer);
		if (MoveAvailable == true && PlayerWon == false)
		{
			
			PlayerMove (grid, GRID_SIZE, p2, empty);
			MoveAvailable = IsMoveAvailable (grid, GRID_SIZE, empty);
			PlayerWon = HasPlayerWon (grid, GRID_SIZE, p2, winningPlayer);
		}
	}while (MoveAvailable == true && PlayerWon == false);
	if (MoveAvailable == false)
		cout << endl << "Tie game!" << endl;
	if (PlayerWon == true)
		cout << endl << winningPlayer << " has won!" << endl ;

	return 0;
}

void InitializeGrid(char grid[GRID_SIZE][GRID_SIZE],int size, char value)
{
	for(int y=0; y<size; y++)
	{
		for(int x=0; x<size; x++)
		{
			grid[y][x] = value;
		}
	}
}

void PlayerMove (char grid[GRID_SIZE][GRID_SIZE], int size, Player player, char empty)
{
	int x, y;
	bool valid;
	do
	{
		/*cout << player.name << " enter x coordinate(1-3):";
		cin >> x;
		x -=1;
		cout << player.name << " enter y coordinate(1-3):";
		cin >> y;
		y-=1;
		valid = IsMoveValid( grid,  size,  x,  y,  empty);*/
		int move;
		char input[80];
		x = -1, y = -1;
		cout << player.name << ", where on the grid will you place your " << player.piece << "?: ";
		cin >> input;
		move = atoi (input);
		if (move == 1)
		{
			y = 2;
			x = 0;
		}
		if (move == 2)
		{
			y = 2;
			x = 1;
		}
		if (move == 3)
		{
			y = 2;
			x = 2;
		}
		if (move == 4)
		{
			y = 1;
			x = 0;
		}
		if (move == 5)
		{
			y = 1;
			x = 1;
		}
		if (move == 6)
		{
			y = 1;
			x = 2;
		}
		if (move == 7)
		{
			y = 0;
			x = 0;
		}
		if (move == 8)
		{
			y = 0;
			x = 1;
		}
		if (move == 9)
		{
			y = 0;
			x = 2;
		}
		valid = IsMoveValid( grid,  size,  x,  y,  empty);
		if (valid == false)
			cout << "That position is either taken or invalid, try again." << endl;
	}while (valid == false);
	SetGridValue( grid, GRID_SIZE, x, y, player.piece);
	PrintGrid(grid,GRID_SIZE);
}

bool IsMoveValid(char grid[GRID_SIZE][GRID_SIZE], int size, int x, int y, char empty)

{
	if( !(x >= 0 && x < size && y >= 0 && y < size))
		return false;

	if (grid [y][x] != empty)
		return false;

	return true;
}

bool IsMoveAvailable (char grid[GRID_SIZE][GRID_SIZE], int size, char empty)
{
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (grid[y][x] == '.')
				return true;	
		}
	}
	return false;
}

bool HasPlayerWon (char grid[GRID_SIZE][GRID_SIZE], int size, Player player, char winningPlayer[])
{
	for (int y = 0; y < size; y++)
	{
		int count = 0;
		for (int x = 0; x < size; x++)
		{
			if (grid[y][x] == player.piece)
				count++;
		}
		if (count == size)
		{
			strcpy(winningPlayer, player.name);
			return true;
		}
	}
	for (int x = 0; x < size; x++)
	{
		int count = 0;
		for (int y = 0; y < size; y++)
		{
			if (grid[y][x] == player.piece)
				count++;
		}
		if (count == size)
		{
			strcpy(winningPlayer, player.name);
			return true;
		}
	}
	if (grid[0][0] == player.piece && grid[1][1] == player.piece && grid[2][2] == player.piece)
	{
		strcpy(winningPlayer, player.name);
			return true;
	}

	if (grid[0][2] == player.piece && grid[1][1] == player.piece && grid[2][0] == player.piece)
	{
		strcpy(winningPlayer, player.name);
			return true;
	}

	return false;
}

void SetGridValue(char grid[GRID_SIZE][GRID_SIZE], int size, int x, int y, char value)
{
	if( x >= 0 && x < size && y >= 0 && y < size)
		grid[y][x] = value;
}

void PrintGrid(char grid[GRID_SIZE][GRID_SIZE],int size)
{
	cout << endl;
	SetColor(0xF0);
	for(int y=0; y<size; y++)
	{
		for(int x=0; x<size; x++)
		{
			if (grid[y][x] == 'X')
				SetColor(0xFC);
			else if (grid[y][x] == 'O')
				SetColor(0xF9);
			else
				SetColor(0xF0);
			cout << grid[y][x] ;
			if (x < 2)
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	SetColor(0x07);
}