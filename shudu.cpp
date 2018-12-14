#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<ctime>
#include<cmath>
#include<fstream>
#include<algorithm>
using namespace std;

int n, m;
int d[9][9];
void shengcheng();
void output();
bool check();
int panduan(char *q);
bool sign = false;
ofstream Output;
ifstream input;

//生成数独 
void shengcheng(int n)
{
	m = 0;
	int s[9] = { 0,3,6,1,4,7,2,5,8 };//行的平移 
	for (int i = 0; i < 2; i++)
	{
		if (i != 0) next_permutation(s + 1, s + 3);//23行变换 
		for (int j = 0; j < 6; j++)
		{
			if (j != 0) next_permutation(s + 3, s + 6);//456行变换?
			for (int k = 0; k < 6; k++)
			{
				if (k != 0) next_permutation(s + 6, s + 9);//789行变换
				int y[9] = { 7,1,2,3,4,5,6,8,9 };//初始行 
				for (int l = 0; l < 40320; l++)
				{
					if (l != 0) next_permutation(y + 1, y + 9);//行之间换 
					for (int b = 0; b < 9; b++)
						d[0][b] = y[b];
					for (int b = 0; b < 9; b++)
					{
						for (int c = 0; c < 9; c++)
						{
							int p = c + s[b];
							d[b][c] = d[0][p % 9];
							if (c == 8) Output << d[b][c];
							else Output << d[b][c] << " ";
						}

						Output << endl;
					}
					Output << endl;
					m++;
					if (m >= n)
						return;
				}
			}
		}
	}

}

//判断输出的是否为数字 
int panduan(char *q)
{
	int len = strlen(q);
	int a=0;
	for (int i = 0; i < len; i++)
	{
		if (q[i] < '0' || q[i] > '9')
		{
			a = 1;
		}
	}
	if (a == 1) return 1;
	else return 2;
}

void output()//输出 
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == 8) Output << d[i][j];
			else Output << d[i][j] << " ";
		}
		Output << endl;
	}
	Output << endl;
}

bool check(int n)
{
	int hang = n / 9;
	int lie = n % 9;
	for (int i = 0; i < 9; i++)
	{
		if (d[hang][i] == d[hang][lie] && i != lie)  return false;//检查行 
	}
	for (int i = 0; i < 9; i++)
	{
		if (d[i][lie] == d[hang][lie] && i != hang) return false;//检查列
	}
	int x = n / 9 / 3 * 3;
	int y = n % 9 / 3 * 3;
	for (int i = x; i < x + 3; i++)
	{
		for (int j = y; j < y + 3; j++)
		{
			if (d[i][j] == d[hang][lie] && i != hang && j != lie) return false;//检查小九宫格 
		}
	}
	return true;
}
int DFS(int n)
{
    if (n>80)
    {
        output();
        return 0;
    }
    if(d[n/9][n%9] == 0){
		for(int i = 1; i <= 9; ++i){
			d[n/9][n%9] = i;//赋值
			if(check(n)){//可以放
				DFS(n+1);//进入下一层
			}
		}
		d[n/9][n%9] = 0;//回溯
	}else{
		DFS(n+1);
	}

}

int main(int argc, char *argv[])
{
	ifstream input;
	Output.open("sudoku.txt");
	if (strcmp(argv[1], "-c") == 0)
	{

		int b = panduan(argv[2]);
		if (b == 1)
		{
			cout << "输入数字" << endl;
		}
		if (b == 2)
		{
			int n = atoi(argv[2]);
			if (n > 0 && n <= 1000000)
			{
				shengcheng(n);
			}
			else
			{
				cout << "输入正确的数字" << endl;
			}

		}
	}
	else if( strcmp(argv[1],"-s") == 0 )
	{
		input.open(argv[2]);
		int i = 0, j = 0;
		while (!input.eof())//输入至文件结尾
		{
			input >> d[i][j];
			j++;
			if (j>8) {
				j=0;
				i++;
			}
			if (i>8) 
			{
				DFS(0);//解给定的数独
				i = 0; j =0;
			}
		}
	}
	else cout << "Wrong input!" << endl;
	return 0;
}

