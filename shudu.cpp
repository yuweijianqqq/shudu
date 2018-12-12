#include<iostream>
#include<cstring>
#include<string>
#include<vector>
#include<ctime>
#include<cmath>
#include<fstream>
#include<algorithm>
using namespace std;

int n,m;
int d[9][9];
void shengcheng();
void output();
bool check();
void jie();
int panduan(char *q);
bool sign = false;
ofstream Output;

//Éú³ÉÊı¶À 
void shengcheng(int n)
{
	m=0;
	int s[9]={0,3,6,1,4,7,2,5,8};//ĞĞµÄÆ½ÒÆ 
	for(int i=0;i<2;i++)
	{
		if(i!=0) next_permutation(s+1,s+3);//23ĞĞ±ä»» 
		for(int j=0;j<6;j++)
		{
			if(j!=0) next_permutation(s+3,s+6);//456ĞĞ±ä»»ş
			for(int k=0;k<6;k++)
			{
				if(k!=0) next_permutation(s+6,s+9);//789ĞĞ±ä»»
				int y[9]={7,1,2,3,4,5,6,8,9};//³õÊ¼ĞĞ 
				for(int l=0;l<40320;l++)
				{
				    if(l!=0) next_permutation(y+1,y+9);//ĞĞÖ®¼ä»» 
				    for(int b=0;b<9;b++)
				    d[0][b]=y[b];
				    for(int b=0;b<9;b++)
				    {
				    	for(int c=0;c<9;c++)
				    	{
						 int p=c+s[b];
				    	 d[b][c]=d[0][p%9];
						 if(c==8) Output<<d[b][c];
				    	 else Output<<d[b][c]<<" ";
						}
				    	 
						Output << endl;
					}
				Output << endl;
			    m++;
				if (m >= n)
				return ;
				}
			}
		}
	}
	
}

//ÅĞ¶ÏÊä³öµÄÊÇ·ñÎªÊı×Ö 
int panduan(char *q)
{
	int len = strlen(q);
	int a; 
		for (int i = 0; i < len; i++)
	    {
		if (q[i] < '0'||q[i] > '9')
	      {
	    	a=1;
		  }
	    }
		if(a==1) return 1;
		else return 2;	
}

void output()//Êä³ö 
{
	for (int i=0;i<9;i++)
	{
		for (int j =0; j<9;j++)
		{
			if (j==8) Output << d[i][j];
			else Output << d[i][j]<<" ";
		}
		Output << endl;
	}
	Output << endl;
}

bool check(int n)
{
    int hang=n/9; 
	int lie=n%9;
	for(int i=0;i<9;i++)
	{
		if(d[hang][i]==d[hang][lie]&&i!=lie)  return false;//¼ì²éĞĞ 
	}
	for(int i=0;i<9;i++)
	{
		if(d[i][lie]==d[hang][lie]&&i!=hang ) return false;//¼ì²éÁĞ
	}
	int x = n / 9 / 3 * 3;
    int y = n % 9 / 3 * 3; 
    for (int i = x; i < x + 3; i++)
    {
        for (int j = y; j < y + 3; j++)
        {
            if (d[i][j]==d[hang][lie]&&i!=hang&&j!=lie) return false;//¼ì²éĞ¡¾Å¹¬¸ñ 
        }
    }
    return true;
} 

int main(int argc, char *argv[])
{
	ifstream input;
	Output.open("sudoku.txt");
	if (strcmp(argv[1],"-c") == 0)
	{
	    
	 int b=panduan(argv[2]);
	 if(b==1)
	 {
	 	cout<<"ÊäÈëÊı×Ö"<<endl; 
	 }
	 if(b==2)
	 {
	  		int n = atoi(argv[2]);
	  		if(n>0&&n<=1000000)
	  		  {
	  			shengcheng(n);
			  }
			  else
			  {
			  	cout<<"ÊäÈëÕıÈ·µÄÊı×Ö"<<endl; 
			  }
		
     }
	}
}


