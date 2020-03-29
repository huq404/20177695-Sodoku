#include "pch.h"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#pragma warning(disable:4996)
using namespace std;

struct number  //ÿ�����Ľṹ�� sa
{
	int sign;//����һ�����,��ʾ��������м��ֿ��ܵ�ȡֵ 
	int maybe[9] = { 1,2,3,4,5,6,7,8,9 };//����num�Ŀ���ȡֵ 
	int num;//����num��ȷ��ֵ
}a[9][9];
int m, n;
int line, row;//line�У�row��
int gongline, gongrow;
void deletehl(int i, int j);
void del(int i, int j);
void deletegong(int i, int j);
void resetmay()
{
	for(int i=0; i<m; i++)
		for (int j = 0; j < m; j++)
		{
			a[i][j].num = 0;
			a[i][j].sign=m;
			for (int k = 0; k < 9; k++)
			{

				a[i][j].maybe[k] = k + 1;
			}
		}
}
void scanmay()
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			for (int k = 0; k < 9; k++)
			{
				cout<<a[i][j].maybe[k]<<" ";
			}
}
void inputsign()//��һ��������sign����ֵ 
{
	for (int i = 0; i < line; i++)
		for (int j = 0; j < row; j++)
		{
			if (a[i][j].num == 0)
			{
				a[i][j].sign = line;
			}
			else
			{
				a[i][j].sign = 0;
			}
		}
}

void onlyone(int i, int j)//��������ǰ�Ψһ��������� 
{
	for (int k = 0; k < line; k++) //Ψһ����maybe���� 
	{
		if (a[i][j].maybe[k] != 0)
		{
			a[i][j].num = a[i][j].maybe[k];
			a[i][j].maybe[k] = 0;
			a[i][j].sign = 0;
			del(i, j);
			break;
		}
	}
}

void del(int i, int j)
{
	if (m == 3 || m == 5 || m == 7)
	{
		deletehl(i, j);
	}
	else if (m == 4 || m == 6 || m == 8 || m == 9)
	{
		deletehl(i, j);
		deletegong(i, j);
	}
	else
	{
		cout << "m is not right." << endl;
	}
}
void deletehl(int i, int j)
{
	for (int k = 0; k < line; k++)//��ͬһ�е�sign��һ����maybe�Ŀ���ȡֵ���� 
	{
		if (a[i][k].maybe[a[i][j].num - 1] != 0)//�������0��˵����ûȥ��������ܣ�
		//��0�Ļ���˵��ǰ���Ѿ�ȥ���ˣ�sign�����ټ�һ�ˣ� 
		{
			a[i][k].maybe[a[i][j].num - 1] = 0;
			a[i][k].sign--;
			if (a[i][k].sign == 1)
			{
				onlyone(i, k);
			}
		}//��ͬһ�е���ͬ����ֵɾ�� 


		if (a[k][j].maybe[a[i][j].num - 1] != 0)
		{
			a[k][j].maybe[a[i][j].num - 1] = 0;
			a[k][j].sign--;
			if (a[k][j].sign == 1)
			{
				onlyone(k, j);
			}
		}//��ͬһ�е���ͬ����ֵɾ�� 
	}
}

void deletegong(int i, int j)
{
	//�����׵�ַ����  //x,y����������׸����ĵ�ַΪa[x][y] ;
	int x, y;
	x = (i / gongrow) * gongrow;
	y = (j / gongline) * gongline;
	for (int gi = 0; gi < gongrow; gi++)
		for (int gj = 0; gj < gongline; gj++)//��ͬһ����sign��һ����maybe��num����ȡֵ���� 
		{
			if (a[gi + x][gj + y].maybe[a[i][j].num - 1] != 0)
			{
				a[gi + x][gj + y].maybe[a[i][j].num - 1] = 0;
				a[gi + x][gj + y].sign--;
				if (a[gi + x][gj + y].sign == 1)
				{
					onlyone(gi + x, gj + y);
				}
			}
		}
}
void scansign()//����Ѱ��sign==1���� 
{
	for (int i = 0; i < line; i++)
		for (int j = 0; j < row; j++)
		{
			if (a[i][j].num == 0 && a[i][j].sign == 1)//���num==0��˵���������Ҫ�� 
			//sign����1��˵����Ψһ�⣻ 
			{
				onlyone(i, j);
			}
			else if (a[i][j].num != 0)
			{
				del(i, j);
			}
		}
}

void choosemn()//����ȷ��line��row�͹��Ĵ�С 
{
	if (m == 3 || m == 5 || m == 7)
	{
		line = row = m;
	}
	else if (m == 4)
	{
		line = row = m;
		gongline = gongrow = 2;
	}
	else if (m == 6)
	{
		line = row = m;
		gongline = 3;
		gongrow = 2;
	}
	else if (m == 8)
	{
		line = row = m;
		gongline = 2;
		gongrow = 4;
	}
	else if (m == 9)
	{
		line = row = m;
		gongline = 3;
		gongrow = 3;
	}
	else
	{
		cout << "m is not right." << endl;
	}
}

int main(int argc, char** argv)
{
	int i, j;
	ifstream ifp;
	ofstream ofp;
	m = atoi(argv[2]);//������
	n = atoi(argv[4]);//������
	choosemn();
	ifp.open(argv[6]);
	if (!ifp.is_open())//�ж��ļ��Ƿ�ɹ���
		cout << "�ļ���ʧ��" << endl;
	ofp.open(argv[8]);
	if (!ofp.is_open())
		cout << "�ļ���ʧ��" << endl;
	while (n > 0)
	{
		resetmay();
		for (i = 0; i < m; i++)//������������
		{
			for (j = 0; j < m; j++)
			{
				ifp >> a[i][j].num;
			}
		}
		inputsign();
		scansign();

		for (i = 0; i < m; i++)//������������
		{
			for (j = 0; j < m; j++)
			{
				if (j < (m - 1))
					ofp << a[i][j].num << " ";
				else
					ofp << a[i][j].num;
			}
			ofp << endl;
		}
		ofp << endl;
		n--;
	}
	return 0;
}