#include <iostream>
#include <vector>



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

bool dfs(char** arr, position pos, position final, size_t size, std::vector<std::vector<position>*>* pathArr);

/*

1 - discovered
. - not yet discovered
# - can't pass
X - shit cell


*/

int main()

{
	char** lab = new char*[SIZE];
	for (size_t i = 0; i < SIZE; ++i)
		lab[i] = new char[SIZE];

	for (size_t i = 0; i < SIZE; ++i)
	{
		for (size_t j = 0; j < SIZE; ++j)
		{
			if (i == 0 || i == SIZE - 1 || j == 0 || j == SIZE - 1)
				lab[i][j] = '#';
			else
			{
				lab[i][j] = rand() % 3 == 1 ? '#' : '.';
			}
		}

	}

	lab[6][7] = '.';

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
	std::vector<std::vector<position>*> pathArr;
	pathArr.push_back(&path);

	bool isPath = dfs(lab, position(1, 1), position(6, 7), SIZE, &pathArr);

	for (size_t i = 0; i < path.size(); ++i)
		pathArr.at(pathArr.size() - 1)->at(i).print();

	return 0;
}

int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, -1, 0, 1 };



bool dfs(char** arr, position pos, position final, size_t size, std::vector<std::vector<position>*>* pathArr)
{

	pathArr->at(pathArr->size()-1)->push_back(pos);

	if (pos.row == final.row && pos.col == final.col)
		return true;

	if (arr[pos.row][pos.col] == '#' ||
		arr[pos.row][pos.col] == 'X' ||
		arr[pos.row][pos.col] == '@')
	{
		pathArr->at(pathArr->size() - 1)->pop_back();
		return false;
	}

	if (arr[pos.row][pos.col] == '.')
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

			char* foo;
			foo = &arr[newRow][newCol];

			if (*foo == '.')
			{
				if (dfs(arr, position(newRow, newCol), final, size, pathArr) == true)
				{
					//arr[pos.row][pos.col] = '@';
					return true;
				}
			}
		}
	}
	arr[pos.row][pos.col] = 'X';

	pathArr->at(pathArr->size() - 1)->pop_back();
	return false;
}