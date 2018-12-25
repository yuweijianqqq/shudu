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
char w[500000000];
char u[500000000];
ofstream Output;
ifstream input;

//�������� 
void shengcheng(int n)
{
	m = 0;
	int t=0;
	int s[9] = { 0,3,6,1,4,7,2,5,8 };//�е�ƽ�� 
	for (int i = 0; i < 2; i++)
	{
		if (i != 0) next_permutation(s + 1, s + 3);//23�б任 
		for (int j = 0; j < 6; j++)
		{
			if (j != 0) next_permutation(s + 3, s + 6);//456�б任?
			for (int k = 0; k < 6; k++)
			{
				if (k != 0) next_permutation(s + 6, s + 9);//789�б任
				char y[9] = {'7','1','2','3','4','5','6','8','9'};//��ʼ�� 
				for (int l = 0; l < 40320; l++)
				{
					if (l != 0) next_permutation(y + 1, y + 9);//��֮�任 
					for (int b = 0; b < 9; b++)
						d[0][b] = y[b];
					for (int b = 0; b < 9; b++)
					{
						for (int c = 0; c < 9; c++)
						{
							int p = c + s[b];
							d[b][c] = d[0][p % 9];
							if (c == 8&&b<8) 
							{
								w[t++]=d[b][c];
								w[t++]='\n';
							}
							if(c==8&&b==8)
							{
								w[t++]=d[b][c];
								w[t++]='\n';
								w[t++]='\n';
							}
							if(c<8&&b<9)
							{
							w[t++]=d[b][c];
							w[t++]=' ';	
							} 
						}
					}
					m++;
					if (m >= n)
					{
					   Output<<w;
				    	return;
					}
					
				}
			}
		}
	}
	

}

//�ж�������Ƿ�Ϊ���� 
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

void output()//��� 
{
	int t=0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (j == 8&&i<8) 
			{
				u[t++]=d[i][j]+'0';
				u[t++]='\n';
			}
			if(j==8&&i==8)
			{
				u[t++]=d[i][j]+'0';
				u[t++]='\n';
		    	u[t++]='\n';
			}
			if(j<8&&i<9)
			{
			
		    	u[t++]=d[i][j]+'0';
			    u[t++]=' ';	
			} 
		}	
	}
	Output<<u;	
}

bool check(int n)
{
    int hang=n/9; 
	int lie=n%9;
	for(int i=0;i<9;i++)
	{
		if(d[hang][i]==d[hang][lie]&&i!=lie)  return false;//����� 
	}
	for(int i=0;i<9;i++)
	{
		if(d[i][lie]==d[hang][lie]&&i!=hang ) return false;//�����
	}
	int x = n / 9 / 3 * 3;
    int y = n % 9 / 3 * 3; 
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (d[i][j]==d[hang][lie]&&i!=hang&&j!=lie) return false;//���С�Ź��� 
        }
    }
    return true;
} 
int DFS(int n)
{
	if (sign) return 0;
    if (n>80)
    {
    	output();
		sign=true;
        return 0;
    }
    if(d[n/9][n%9] == 0){
		for(int i = 1; i <= 9; i++)
		{
			d[n/9][n%9] = i;//��ֵ
			if(check(n))//���Է�
			{
				DFS(n+1);//������һ��
			}
		}
		d[n/9][n%9] = 0;//����
	}else
	{
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
			cout << "��������" << endl;
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
				cout << "������ȷ������" << endl;
			}

		}
	}
	else if( strcmp(argv[1],"-s") == 0 )
	{
		input.open(argv[2]);
		int i = 0, j = 0;
		while (!input.eof())//�������ļ���β
		{
			input >> d[i][j];
			j++;
			if (j>8) {
				j=0;
				i++;
			}
			if (i>8) 
			{
				sign=false;
				DFS(0);//�����������
				i = 0; j =0;
			}
		}
	}
	else cout << "���������" << endl;
	return 0;
}