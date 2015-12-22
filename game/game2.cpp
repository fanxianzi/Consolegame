#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
const int M=11;
const int N=12;
const int B=13;

class Map
{
public:
	bool sign;								//声明标志以判断格子输出类型
	int data;								//声明格子周围雷的数目

	Map();
};

class Boom
{
	int sum;								//输出格子数
	Map map[M][N];							//声明雷图
public:
	Boom();									//初始化雷图
	void generateboom();					//随机生成雷图
	void setsign(int, int);					//设置标记
	int judgeboom(int ram, int column);		//判断雷图
	void showboom();						//输出雷图
	bool mapsign(int, int);					//返回map[i][j].sign的值，用于判断是否输入已输出格子
};

Map::Map()					//初始化格子
{
	sign=false;
	data=0;
}

Boom::Boom()				//初始化雷图
{
	sum=0;
}

void Boom::generateboom()	//随机生成雷图
{
	int count=0;
	int i, j, boom, r, c;

	srand(time(0));
	
	while (count<B)		//随机布雷
	{
		boom=rand()%(M*N);
		i=boom/N;
		j=boom%N;
		if (map[i][j].data==-1)
			continue;
		map[i][j].data=-1;
		count++;
	}
	
	for (i=0; i<M; i++)	//生成雷周围的格子
	{
		for(j=0; j<N; j++)
		{
			if (map[i][j].data!=-1)
				for (r=i-1; r<=i+1; r++)
				{
					if (r<0 || r>M-1)
						continue;
					c=j-1;
					for (;c<=j+1; c++)
					{
						if (c<0 || c>N-1)
							continue;
						if (map[r][c].data==-1)
							map[i][j].data++;
					}
				}
		}
	}

}

void Boom::setsign(int i, int j)			//递归设置标记
{
	int r, c;

	for (r=i-1; r<=i+1; r++)
		{
			if (r<0 || r>M-1)
				continue;
			c=j-1;
			for (;c<=j+1; c++)
				{
					if (c<0 || c>N-1)
						continue;
					if (map[r][c].sign==false)
					{
						map[r][c].sign=true;
						sum++;
						if (map[r][c].data==0)
							setsign(r, c);
					}
				}
		}
}

int Boom::judgeboom(int row, int column)	//判断雷图
{
	if (map[row][column].data==-1)
	{
		for (int i=0; i<M; i++)
			for (int j=0; j<N; j++)
				if (map[i][j].data==-1)
					map[i][j].sign=true;
		return -1;
	}

	if (map[row][column].data==0)
		setsign(row, column);
	else
	{
		map[row][column].sign=true;
		sum++;
	}

	if (sum==M*N-B)
		return 0;
	return 1;
}

void Boom::showboom()		//输出雷图
{
	int i, j;
	system("cls");

	cout<<"    ";
	for (j=0; j<N; j++)
	{
		if (j<10)
			cout<<j<<"   ";
		else
			cout<<j<<"  ";
	}
	cout<<endl;
	
	cout<<"  ┏";
	for (j=0; j<N-1; j++)
	{
		cout<<"━┯";
	}
	cout<<"━┓";
	cout<<endl;

	for (i=0; i<M; i++)
	{
		if (i<10)
			cout<<i<<" ┃";
		else
			cout<<i<<"┃";

		for(j=0; j<N; j++)
		{
			if (map[i][j].sign==false)
				cout<<"■";
			else if (map[i][j].data==-1)
				cout<<"¤";
			else if (map[i][j].data==0)
				cout<<"  ";
			else
				cout<<map[i][j].data<<" ";
			if (j<N-1)
				cout<<"│";
			else cout<<"┃";
		}
		cout<<endl;

		if (i<M-1)
		{
			cout<<"  ┠";
			for (j=0; j<N-1; j++)
				cout<<"─┼";
			cout<<"─┨";
		}
		else 
		{
			cout<<"  ┗";
			for (j=0; j<N-1; j++)
				cout<<"━┷";
			cout<<"━┛";
		}
		cout<<endl;
	}
}

bool Boom::mapsign(int i, int j)		//判断是否输入已输出格子
	{
		return map[i][j].sign;
	}

void main()
{
	char a;
	int row, column, i;

	cout<<"\t\t\tWecome to this game!\n";
	cout<<"The board is "<<M<<"*"<<N<<".\n";
	cout<<"And the sum of boom is "<<B<<".\n";
	cout<<endl;
	system("pause");

	do
	{
		Boom boom;
		boom.generateboom();
		do
		{
			do
			{
				boom.showboom();
				cout<<"Please input your row and column:\n";
				cin>>row>>column;
				if (row>=0 && row<=M-1 && column>=0 && column<=N-1 && boom.mapsign(row, column)==false)
					break;
				cout<<"Your input was wrong! Please input again!\n";
				cout<<endl;
				system("pause");
			}while(true);

			i=boom.judgeboom(row, column);
			boom.showboom();
		}while(i==1);

		if (i==0)
			cout<<"You win! O(∩_∩)O \n";
		else
			cout<<"You lose! o(╯□╰)o\n";

		cout<<endl;
		cout<<"Try again? (y/n)\n";
		cin>>a;
		if (a=='N' || a=='n')
			break;
		system("cls");
	}while(true);
	
	cout<<endl;
	cout<<"All right! ( ^_^ )/~~Bye!\n";
	cout<<endl;
	system("pause");
	cout<<endl;
}

