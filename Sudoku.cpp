#include"Sudoku.h"

using namespace std;

void Sudoku::giveQuestion()
{
	ifstream read("Question.txt", ios::in);
	for(int i = 0 ; i < 81 ; i++)
	{
		read >> map[i];
	}
	for(int i = 0 ; i < 81 ; i++)
	{
		cout << map[i] << " ";

		if((i + 1) % 9 == 0)
		{
			cout << "\n";
		}
	}
}

void Sudoku::readIn()
{
	for(int i = 0 ; i < 81 ; i++)
	{
		cin >> map[i];
	}	
}

void Sudoku::solve()
{
	char a[9][9];
	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
		{
			a[i][j] = map[i * 9 + j];
		}
	}

	element b[9][9];

	ele(a, b);
	sudu(a, b, 0, 0);

	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
		{
			map[i * 9 + j] = a[i][j];
		}
	}
}

void Sudoku::sudu(char a[9][9],element b[9][9], int i, int j)
{
	int next_i, next_j, v, q, c_i, c_j;
	int flag = 1;
	int p;
	int space = 0;
	char num;
	char c[9][9];

	for(c_i = 0 ; c_i < 9 ; c_i++)
	{
		for(c_j = 0 ; c_j < 9 ; c_j++)
		{
			c[c_i][c_j] = a[c_i][c_j];
		}														    
	}

	if(i == 9)
	{
		for(v = 0 ; v < 9 ; v++)
		{
			for(q = 0 ; q < 9 ; q++)
			{
				if(c[v][q] == '0')
				{
					flag = 0;
					space++;
				}
			}
		}
		if(flag == 1)
		{
			for(v = 0 ; v < 9 ; v++)
			{
				for(q = 0 ; q < 9 ; q++)
				{
					a[v][q] = c[v][q];
				}
			}
		}
	}
	else
	{
		if( j < (9 - 1))
		{
			next_i = i;
			next_j = j + 1;
		}
		else
		{
			next_i = i + 1;
			next_j = 0;
		}

		if(c[i][j] == '0')
		{
			for(p = 0 ; p < b[i][j].length ; p++)
			{
				num = b[i][j].c[p];
				if(checkRow(c, num, i))
				{
					if(checkColumn(c, num, j))
					{
						if(checkBlock(c, num, i, j))
						{
							c[i][j]= num;
							sudu(c, b, next_i, next_j);
						}
					}
				}
			}
		}
		else
		{
			sudu(c, b, next_i, next_j);
		}
	}
}

void Sudoku::ele(char a[9][9], element b[9][9])
{
	int i, j, k, r, s, m, n;
	char test;
	int flag = 1;

	while(flag == 1)
	{
		flag = 0;
		for(i = 0 ; i < 9 ; i++)
		{
			for(j = 0 ; j < 9 ; j++)
			{
				for(k = 0 ,test = '1' ; k < 9 ; k++, test++)
				{
					b[i][j].c[k] = 1;
				}

				b[i][j].length = 0;
			}
		}
		for(i = 0 ; i < 9 ; i++)
		{
			for(j = 0 ; j < 9 ; j++)
			{
				for(k = 0 ; k < 9 ; k++)
				{
					if(a[i][k] != '0')
					{
						b[i][j].c[a[i][k] - 49] ='0';
					}
				}
			}
		}
		for(i = 0 ; i < 9 ; i++)
		{
			for(j = 0 ; j < 9 ; j++)
			{
				for(k = 0 ; k < 9 ; k++)
				{
					if(a[k][j] != '0')
					{
						b[i][j].c[a[k][j] - 49] ='0';
					}
				}
			}
		}
		for(i = 0 ; i < 9 ; i++)
		{
			for(j = 0 ; j < 9 ; j++)
			{
				if(i > 2)
				{
					if(i > 5)
					{
						r = 6;
					}
					else r = 3;
				}
				else r = 0;

				if(j > 2)
				{
					if(j > 5)
					{
						s = 6;
					}
					else s = 3;
				}
				else s = 0;

				for(m = r ; m < r + 3 ; m++)
				{
					for(n = s ; n < s + 3 ; n++)
					{
						if (a[m][n] != '0')
						{
							b[i][j].c[a[m][n] - 49] = '0';
						}
					}
				}
			}
		}
		for(i = 0 ; i < 9 ; i++)
		{
			for(j = 0 ; j < 9 ; j++)
			{
				for(k = 0 ; k < 9 ; k++)
				{
					int p = 1;
					while(b[i][j].c[k] == '0')
					{
						b[i][j].c[k] = b[i][j].c[k + p];
						b[i][j].c[k + p] = '0';
						p++;
						if((k + p) > 8)
						{
							break;
						}
					}
				}
			}
		}
		for(i = 0 ; i < 9 ; i++)
		{
			for(j = 0 ; j < 9 ; j++)
			{
				for(k = 0 ; k < 9 ; k++)
				{
					if(b[i][j].c[k] != '0')
					{
						b[i][j].length++;
					}
				}
			}
		}
		for(i = 0 ; i < 9 ; i++)
		{
			for(j = 0 ; j < 9 ; j++)
			{
				for(k = 0 ; k < 9 ; k++)
				{
					if(b[i][j].length == 1)
					{
						if(a[i][j] == '0')
						{
							a[i][j] = b[i][j].c[0];
							flag = 1;
						}
					}
				}
			}
		}
	}

}

int Sudoku::checkRow(char a[9][9], char x, int i)
{
	int j, flag = 1;
	if(x == '0')
	{
		return flag;
	}
	for(j = 0 ; j < 9 ; j++)
	{
		if(x == a[i][j])
		{
			flag = 0;
		}
	}
	return flag;
}

int Sudoku::checkColumn(char a[9][9], char x, int j)
{
	int i, flag = 1;
	if(x == '0')
	{
		return flag;
	}
	for(i = 0 ; i < 9 ; i++)
	{
		if(x == a[i][j])
		{
			flag = 0;
		}
	}
	return flag;
}

int Sudoku::checkBlock(char a[9][9], char x, int i, int j)
{
	int r, s;
	int flag = 1;
	if(x == '0')
	{
		return flag;
	}
	if(i > 2)
	{
		if(i > 5)
		{
			i = 6;
		}
		else i = 3;
	}
	else i = 0;

	if(j > 2)
	{
		if(j > 5)
		{
			j = 6;
		}
		else j = 3;
	}
	else j = 0;

	for(r = i ; r < (i + 3) ; r++)
	{
		for(s = j ; s < (j + 3) ; s++)
		{
			if(x == a[r][s])
			{
				flag = 0;
			}
		}
	}
	return flag;
}


void Sudoku::changeNum(int a, int b)
{
	int temp[81];

	for(int i = 0 ; i < 81 ; i++)
	{
		temp[i] = map[i];
	}
    for(int i = 0 ; i < 81 ; i++)
	{
		if(temp[i] = a) map[i] = b;
		if(temp[i] = b) map[i] = a;
	}
}

void Sudoku::changeRow(int a, int b)
{
	int temp[81];

	for(int i = 0 ; i < 27 ; i++)
	{
		temp[i]         = map[i + 27 * a];
		map[i + 27 * a] = map[i + 27 * b];
		map[i + 27 * b] = temp[i];
	}
}

void Sudoku::changeCol(int a, int b)
{
	int temp[81];

	for(int i = 0 ; i < 81 ; i++)
	{
		temp[i]         = map[i];
		map[i + 3 * a]  = map[i + 3 * b];
		if((i + 1) % 3 == 0) i += 6;
	}
	for(int i = 0 ; i < 81 ; i++)
	{
		map[i + 3 * b]  = temp[i + 3 * a];
		if((i + 1) % 3 == 0) i += 6;
	}
}

void Sudoku::rotate(int n)
{
	n %= 4;

	if(n == 0)
	{

	}

	if(n == 1)
	{
		int temp[9][9];
		int tmp;
		
		for(int i = 0 ; i < 9 ; i++)
		{
			for(int j = 0 ; j < 9 ; j++)
			{
				temp[i][j] =  map[i * 9 + j];
			}
		}

		for(int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 5 ; j++)
			{
				tmp                = temp[i][j];
				temp[i][j]         = temp[8 - j][i];
				temp[8 - j][i]     = temp[8 - i][8 - j];
				temp[8 - i][8 - j] = temp[j][8 - i];
				temp[j][8 - i]     = tmp;
			}
		}

		for(int i = 0 ; i < 9 ; i++)
		{
			for(int j = 0 ; j < 9 ; j++)
			{
				map[i * 9 + j] = temp[i][j];
			}
		}
	}

	if(n == 2)
	{
		int temp[9][9];
		int tmp;

		for(int i = 0 ; i < 9 ; i++)
		{
			for(int j = 0 ; j < 9 ; j++)
			{
				temp[i][j] = map[i * 9 + j];
			}
		}

		for(int i = 0 ; i < 4 ; i++)
		{
		    for(int j = 0 ; j < 5 ; j++)
			{
				tmp                = temp[i][j];
				temp[i][j]         = temp[8 - j][i];
				temp[8 - j][i]     = temp[8 - i][8 - j];
				temp[8 - i][8 - j] = temp[j][8 - i];
				temp[j][8 - i]     = tmp;
			}
		}

		for (int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 5 ; j++)
			{
				tmp                = temp[i][j];
				temp[i][j]         = temp[8 - j][i];
				temp[8 - j][i]     = temp[8 - i][8 - j];
				temp[8 - i][8 - j] = temp[j][8 - i];
				temp[j][8 - i]     = tmp;
			}
		}

		for(int i = 0 ; i < 9 ; i++)
		{
			for(int j = 0 ; j < 9 ; j++)
			{
				map[i * 9 + j] = temp[i][j];
			}
		}
	}

	if(n == 3)
	{
		int temp[9][9];
		int tmp;

		for(int i = 0 ; i < 9 ; i++)
		{
			for(int j = 0 ; j < 9 ; j++)
			{
				temp[i][j] = map[i * 9 + j];
			}
		}

		for (int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 5 ; j++)
			{
				tmp                = temp[i][j];
				temp[i][j]         = temp[8 - j][i];
				temp[8 - j][i]     = temp[8 - i][8 - j];
				temp[8 - i][8 - j] = temp[j][8 - i];
				temp[j][8 - i]     = tmp;
			}
		}

		for (int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 5 ; j++)
			{
				tmp                = temp[i][j];
				temp[i][j]         = temp[8 - j][i];
				temp[8 - j][i]     = temp[8 - i][8 - j];
				temp[8 - i][8 - j] = temp[j][8 - i];
				temp[j][8 - i]     = tmp;
			}
		}

		for (int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 5 ; j++)
			{
				tmp                = temp[i][j];
				temp[i][j]         = temp[8 - j][i];
				temp[8 - j][i]     = temp[8 - i][8 - j];
				temp[8 - i][8 - j] = temp[j][8 - i];
				temp[j][8 - i]     = tmp;
			}
		}

		for(int i = 0 ; i < 9 ; i++)
		{
			for(int j = 0 ; j < 9 ; j++)
			{
				temp[i][j] = map[i * 9 + j];
			}
		}
	}
}

void Sudoku::flip(int n)
{
	int tmp[9][9];
	int temp;
	
	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
		{
			tmp[i][j] = map[i * 9 + j];
		}
	}

	if(n == 0)
	{
		for(int i = 0 ; i < 4 ; i++)
		{
			for(int j = 0 ; j < 9 ; j++)
			{
				temp          = tmp[i][j];
				tmp[i][j]     = tmp[8 - i][j];
				tmp[8 - i][j] = temp;
			}
		}
	}

	if(n == 1)
	{
		for(int i = 0 ; i < 9 ; i++)
		{
			for(int j = 0 ; j < 4 ; j++)
			{
				temp          = tmp[i][j];
				tmp[i][j]     = tmp[i][8 - j];
				tmp[i][8 - j] = temp;
			}
		}
	}

	for(int i = 0 ; i < 9 ; i++)
	{
	}
}

void Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand() % 9 + 1, rand() % 9 + 1);
	changeRow(rand() % 3, rand() % 3);
	changeCol(rand() % 3, rand() % 3);
	rotate(rand() % 4);
	flip(rand() % 2);
}

void Sudoku::transform()
{
	readIn();
	change();
}
