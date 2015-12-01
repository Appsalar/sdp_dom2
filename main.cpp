/*
Иван Велков група 2 ФН:45039

Извинявам се за забавеното предаване, нямах интернет и нямаше 
как да предам домашното. Говорих с Армянов и той каза, че 
няма проблем.

Не знам дали валидацията на входа е нужна. направих я за всеки
случай и е сръдливо животно.


*/




#include <iostream>
#include <vector>
#include "Tail.h"

#define SIZE 10


struct position
{
	size_t row;
	size_t col;

	position()
	{
		row = 0;
		col = 0;
	}

	position(size_t row, size_t col)
	{
		this->row = row;
		this->col = col;
	}

	position(const position& other)
	{
		this->row = other.row;
		this->col = other.col;
	}
	
	position& operator=(const position& other)
	{
		this->row = other.row;
		this->col = other.col;
		return *this;
	}

	~position()
	{}

	void print()
	{
		printf("( %d, %d ) ", row, col);
	}
};

typedef std::vector<position> path;
typedef std::vector<path*> roads;

inline void printlab(char** arr, int n, int m)
{
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			std::cout << arr[i][j] << "  ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << "----------------------------------------------------";
	std::cout << std::endl;
}

bool dfs(char** arr, position pos, position final, int n, int m, roads* pathArr);
void bfs(char** arr, position pos, int n, int m, Tail<position>* destinations);

void sort(roads* pathArr);
/*

@ - discovered
. - not yet discovered
# - can't pass
X - shit cell


*/

int main()

{

	int n;
	int m;

	std::cin >> n >> m;
	if (n <= 0 || m <= 0)
		return -1;


	char** lab = new char*[n];
	for (size_t i = 0; i < n; ++i)
	{
		char buf[255];
		std::cin >> buf;
		if (strlen(buf) < n)
			return -1;
		lab[i] = _strdup(buf);
	}

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			if (lab[i][j] != '#' && lab[i][j] != '.')
				return -1;
		}
	}

	int a, b;
	std::cin >> a >> b;
	if (a < 0 || a >= n ||
		b < 0 || b >= m)
		return -1;

	position pos;

	pos.row = a;
	pos.col = b;

	/*
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			lab[i][j] = rand() % 3 == 1 ? '#' : '.';
			/*if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
				;//lab[i][j] = '#';
			else
		}
	}
	lab[6][7] = '.';
	lab[6][6] = '.';

	lab[0] = _strdup("###");
	lab[1] = _strdup("#..");
	lab[2] = _strdup("#..");

	pos.row = 1;
	pos.col = 1;
	*/

	//printlab(lab, n, m);

	Tail<position> destinations;

	std::vector<roads*> pathArr;


	bfs(lab, pos, n, m, &destinations);
	while (!destinations.empty())
	{
		destinations.top().print();
		pathArr.push_back(new roads);
		pathArr.back()->push_back(new path);
		dfs(lab, pos, destinations.top(), n, m, pathArr.back());
		destinations.pop();
	}
	std::cout << std::endl;

	for (size_t i = 0; i < n; ++i)
		delete[] lab[i];
	delete lab;

	/*
	pathArr.push_back(new roads);
	pathArr.back()->push_back(new path);
	bool isPath = dfs(lab, pos, position(6, 7), n, m, pathArr.back());
	*/

	for (size_t j = 0; j < pathArr.size(); ++j)
	{
		pathArr.at(j)->back()->back().print();
		std::cout << std::endl;
		sort(pathArr[j]);

		for (size_t k = 0; k < pathArr.at(j)->size(); ++k)
		{
			for (size_t i = 0; i < pathArr.at(j)->at(k)->size(); ++i)
				pathArr.at(j)->at(k)->at(i).print();
			std::cout << std::endl;
		}
		//std::cout << pathArr.at(j)->size() << std::endl;
	}

	for (size_t i = 0; i < pathArr.size(); ++i)
	{
		for (size_t j = 0; j < pathArr.at(j)->size(); ++j)
		{
			delete pathArr.at(i)->at(j);
		}
		delete pathArr.at(i);
	}

	return 0;

}

int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, -1, 0, 1 };

void bfs(char** arr, position pos, int n, int m, Tail<position>* destinations)
{
	Tail<position> Wave;
	Wave.push(pos);
	arr[pos.row][pos.col] = '@';

	while (!Wave.empty())
	{
		for (size_t i = 0; i < 4; ++i)
		{
			int newRow = Wave.top().row + dRow[i];
			int newCol = Wave.top().col + dCol[i];

			if (newRow >= 0 && newRow < n &&
				newCol >= 0 && newCol < m)
			{
				char* foo;
				foo = &arr[newRow][newCol];
				if (*foo == '.')
				{
					*foo = '@';
					position nextpos(newRow, newCol);
					Wave.push(nextpos);
					destinations->push(nextpos);
				}
			}
		}
		Wave.pop();
		//printlab(arr, n, m);
	}

	//printlab(arr, n, m);
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			if (arr[i][j] == '@')
				arr[i][j] = '.';
		}
	}
	//printlab(arr, n, m);
}

bool dfs(char** arr, position pos, position final, int n, int m, roads* pathArr)
{
	//if (pathArr->size() > 4)
		//return false;

	pathArr->back()->push_back(pos);

	if (pos.row == final.row && pos.col == final.col)
		return true;

	if (arr[pos.row][pos.col] == '#' ||
		arr[pos.row][pos.col] == 'X' ||
		arr[pos.row][pos.col] == '@')
	{
		pathArr->back()->pop_back();
		if (pathArr->back()->size() == 0)
			pathArr->pop_back();
		return false;
	}

	if (arr[pos.row][pos.col] == '.')
	{
		arr[pos.row][pos.col] = '@';

		//printlab(arr, n, m);

		for (size_t i = 0; i < 4; ++i)
		{
			int newRow = pos.row + dRow[i];
			int newCol = pos.col + dCol[i];

			if (newRow >= 0 && newRow < n &&
				newCol >= 0 && newCol < m)
			{
				char* foo;
				foo = &arr[newRow][newCol];
				if (*foo == '.')
				{
					if (dfs(arr, position(newRow, newCol), final, n, m, pathArr) == true)
					{
						*foo = '.';
						//return true;
						pathArr->push_back(new path);
						path* temp = pathArr->at(pathArr->size() - 2);
						*(pathArr->back()) = *temp;
						/*while(pathArr->back()->back()!= pos)
						{
						position bar=pathArr->back()->back();
						arr[bar.row][bar.col]='@';
						pathArr->back()->pop_back();
						}
						*/
						//position bar=pathArr->back()->back();
						//arr[bar.row][bar.col]='.';
						pathArr->back()->pop_back();

					}
				}
			}
		}
	}
	//arr[pos.row][pos.col] = 'X';
	arr[pos.row][pos.col] = '.';

	pathArr->back()->pop_back();
	if (pathArr->back()->size() == 0)
		pathArr->pop_back();
	return false;
}

void swapif(path* a, path* b)
{
	if (a->size() > b->size())
	{
		path* temp = a;
		a = b;
		b = temp;
	}
}

void sort(roads* pathArr)
{
	for (size_t i = pathArr->size() - 1; i != 0; --i)
	{
		if (pathArr->at(i - 1)->size() > pathArr->at(i)->size())
		{
			path* foo = pathArr->at(i - 1);
			pathArr->at(i - 1) = pathArr->at(i);
			pathArr->at(i) = foo;
		}
	}

	for (size_t i = 2; i < pathArr->size(); ++i)
	{
		path* foo = pathArr->at(i);

		size_t j = i;
		while (pathArr->at(j)->size()>foo->size())
		{
			pathArr->at(j) = pathArr->at(j - 1);
			--j;
		}
		pathArr->at(j) = foo;
	}
}
