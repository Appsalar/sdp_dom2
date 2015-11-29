#include <iostream>
#include <vector>


/*

#define SIZE 10

struct position
{
	size_t row;
	size_t col;

	position(size_t row, size_t col)
	{
		this->row = row;
		this->col = col;
	}

	void print()
	{
		printf_s("( %d, %d ) ", row, col);
	}
};

bool dfs(int** arr, position pos, position final, size_t size, std::vector<position>* path);

/*

1 - discovered
0 - not yet discovered
3 - can't pass
2 - shit cell
42 - objective

*/
/*
int old_main()

{
	int** lab = new int*[SIZE];
	for (size_t i = 0; i < SIZE; ++i)
		lab[i] = new int[SIZE];

	for (size_t i = 0; i < SIZE; ++i)
	{
		for (size_t j = 0; j < SIZE; ++j)
		{
			if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1)
				lab[i][j] = 3;
			else
			{
				lab[i][j] = rand() % 3 == 1 ? 3 : 0;
			}
		}

	}

	lab[6][7] = 0;

	for (size_t i = 0; i < SIZE; ++i)
	{
		for (size_t j = 0; j < SIZE; ++j)
		{
			std::cout << lab[i][j] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "----------------------------------------------------";
	std::cout << std::endl;

	std::vector<position> path;

	bool vyh = dfs(lab, position(1, 1), position(6, 7), SIZE, &path);

	for (size_t i = 0; i < path.size(); ++i)
		path[i].print();

	return 0;
}

int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, -1, 0, 1 };



bool dfs(int** arr, position pos, position final, size_t size, std::vector<position>* path)
{

	path->push_back(pos);

	if (arr[pos.row][pos.col] == 42)
		return true;

	if (pos.row == final.row && pos.col == final.col)
		return true;

	for (int i = 1; i <= 3; ++i)
	{
		if (arr[pos.row][pos.col] == i)
			return false;
	}

	if (arr[pos.row][pos.col] == 0)
	{
		arr[pos.row][pos.col] = 1;

		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
			{
				std::cout << arr[i][j] << "  ";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl;
		std::cout << "----------------------------------------------------";
		std::cout << std::endl;

		for (size_t i = 0; i < 4; ++i)
		{
			size_t newRow = pos.row + dRow[i];
			size_t newCol = pos.col + dCol[i];

			int* foo;
			foo = &arr[newRow][newCol];

			//if (*foo == 42)
			//return true;

			if (*foo == 0)
			{
				//path->push_back(position(newRow, newCol));
				if (dfs(arr, position(newRow, newCol), final, size, path) == true)
				{
					arr[pos.row][pos.col] = 1;
					return true;
				}
			}
		}
	}
	arr[pos.row][pos.col] = 2;

	path->pop_back();
	return false;
}*/