// Graphs.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "include.h"

using namespace std;
using namespace sf;

void keyboard(RenderWindow&window,List<vertex>&g);
void Sleep(int s);
void Deykstr(List<vertex>&v,RenderWindow&window);
int Ford_Fulkerson(List<vertex>&v,RenderWindow&window);

int main()
{
	setlocale(LC_ALL,"");
	List<vertex> v;

	RenderWindow window(VideoMode(1000,562),"Graphs");

	while(window.isOpen())
	{
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if(Keyboard::isKeyPressed(Keyboard::Escape))window.close();
		}
		window.clear(Color::White);
		
		keyboard(window,v);
		
		Draw(window,v);
		
		window.display();

	}

	return 0;
}

void Sleep(int s)
{
	Clock clock;
	float time=0;
	while(time<s)
	{
		system("CLS");
		time+=clock.getElapsedTime().asSeconds();
	}
}

void keyboard(RenderWindow&window,List<vertex>&g)
{
	if(Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i pos=GetPosition(window);

			if(!Keyboard::isKeyPressed(Keyboard::LShift)&&!Keyboard::isKeyPressed(Keyboard::LControl))
				for(int i=0;i<g.size;i++)
					if(FloatRect(pos.x,pos.y,1,1).intersects(FloatRect(g[i].x-35,g[i].y-35,70,70)))
						while(true)
						{
							 pos=GetPosition(window);

							if(!Mouse::isButtonPressed(Mouse::Left))
							{
								g[i].x=pos.x;
								g[i].y=pos.y;
								return;
							}

						}


		if(Keyboard::isKeyPressed(Keyboard::LShift))
		{
			while(true)
			{
				if(!Keyboard::isKeyPressed(Keyboard::LShift))return;
				else if(!Mouse::isButtonPressed(Mouse::Left))
				{
					pos=GetPosition(window);

					g.resize(g.size+1);
					g[g.size-1].Init();
					g[g.size-1].x=pos.x;
					g[g.size-1].y=pos.y;
					return;
				}
			}
			
		}

		if(Keyboard::isKeyPressed(Keyboard::LControl))	
				for(int i=0;i<g.size;i++)
					if(FloatRect(pos.x,pos.y,1,1).intersects(FloatRect(g[i].x-35,g[i].y-35,70,70)))
					{
						int wgt=0;

					
						while(Keyboard::isKeyPressed(Keyboard::LControl))
						{
							if(!Mouse::isButtonPressed(Mouse::Left))
							{
								pos=GetPosition(window);

								for(int j=0;j<g.size;j++)
									if(FloatRect(pos.x,pos.y,1,1).intersects(FloatRect(g[j].x-35,g[j].y-35,70,70)))
										if(i!=j){wgt=retNumber(window);g[i].createUni(g[j],wgt);break;}
										else break;

								break;
							}
						}
						break;
					}

		
		}

	if(Keyboard::isKeyPressed(Keyboard::D))
	{
		Deykstr(g,window);
		while(Keyboard::isKeyPressed(Keyboard::D));
	}

	if(Keyboard::isKeyPressed(Keyboard::A))
	{
		cout<<"������������ �����"<<Ford_Fulkerson(g,window)<<endl;
		while(Keyboard::isKeyPressed(Keyboard::A));
	}
	

}



void Deykstr(List<vertex>&v,RenderWindow&window)
{
	if(v.size<2)return;
	int start=retNumber(window);
	int end=retNumber(window);

	v[start-1].num_l=0;

	vertex *W;
	vector<int>P;
	P.resize(v.size);
	for(int i=0;i<v.size;i++)
		P[i]=start;

	while(true)
	{
		W=NULL;
		int min=999;
		for(int i=0;i<v.size;i++)
			if(min>=v[i].num_l&&v[i].sts!=color){min=v[i].num_l;W=&v[i];}
			if(W==NULL)break;

			for(int i=0;i<W->uni.size;i++)
				if((W->uni[i].one->num_l>=(W->num_l+W->uni[i].wgt)||W->uni[i].two->num_l>=(W->num_l+W->uni[i].wgt))&&(W->uni[i].one->sts!=color||W->uni[i].two->sts!=color))
					if(W->uni[i].one->num==W->num){W->uni[i].two->num_l=W->num_l+W->uni[i].wgt;P[W->uni[i].two->num-1]=W->num;}
					else{ W->uni[i].one->num_l=W->num_l+W->uni[i].wgt;P[W->uni[i].one->num-1]=W->num;}
					W->sts=color;

					Draw(window,v);
	}
	int sum=0;
	int res=end-1;
	cout<<res+1<<"->";
	while(true)
	{
		
		for(int i=0;i<v[res].uni.size;i++)
			if(v[res].uni[i].one->num==P[res]||v[res].uni[i].two->num==P[res])
				{
					v[res].uni[i].sts=color;
					sum+=v[res].uni[i].wgt;
				}
		
		res=P[res]-1;
		cout<<res+1;
		if(res==start-1){cout<<endl;break;}
		cout<<"->";
	}
	cout<<endl;
	cout<<"����������� ��� ����:"<<sum<<endl;
	cout<<endl;
}

/*int Ford_Fulkerson(List<vertex>&v,RenderWindow&window)
{
	int start=retNumber(window);
	int finish=retNumber(window);

	List<UNI*> stack;

	while(true)
	{
		vertex*W=&v[start-1];
		
		//������ ����
		while(true)
		{
			for(int i=0;i<W->uni.size;i++)
				if((W->uni[i].two->sts!=color&&W->uni[i].one->sts!=color)&&W->uni[i].nas!=W->uni[i].wgt&&(W->uni[i].sts!=delt||W->uni[i].one->num==W->num))
				{	
							stack.resize(stack.size+1);
							stack[stack.size-1]=&W->uni[i];
							W->sts=color;
							if(W->num!=W->uni[i].two->num)W=W->uni[i].two;
							else W=W->uni[i].one;
							break;
				}
				else if(i==W->uni.size-1)
					{
						if(stack.size==0)
						{
							int result=0;
							for(int k=0;k<v[start-1].uni.size;k++)
								result+=v[start-1].uni[k].nas;
							return result;
						}
						else 
						{
							cout<<W->num<<"->>";
							W->sts=color;
							if(W->num==stack[stack.size-1]->one->num)W=stack[stack.size-1]->two;
							else W=stack[stack.size-1]->one;
							W->sts=neut;
							cout<<W->num<<endl;
							stack.resize(stack.size-1);
						}
					}
				if(W->num==finish)break;
		}
		//������������ ������������ ����� � ���� ����
		int min=0;

		for(int i=0;i<stack.size;i++)
			cout<<stack[i]->one->num<<"-";
		cout<<finish<<endl;
		
		if(stack[0]->one->num==v[start-1].num)
		{
			min=stack[0]->wgt-stack[0]->nas;
		}
		else 
			if(stack[0]->nas-min<0)min=stack[0]->nas;

		for(int m=1;m<stack.size;m++)
		{
			
			if(stack[m]->two->num!=stack[m-1]->two->num)
			{
			if(min>=(stack[m]->wgt-stack[m]->nas))
				min=stack[m]->wgt-stack[m]->nas;
			}
			else if(stack[m]->nas-min<0) min=stack[m]->nas;
			if(min==0)
			{
				for(int i=0;i<v.size;i++)
					for(int j=0;j<v[i].uni.size;j++)
						if(*stack[m]==v[i].uni[j])v[i].uni[j].sts=delt;
				break;
			}
		}

		cout<<min<<endl<<endl;


		for(int i=0;i<v.size;i++)
				for(int j=0;j<v[i].uni.size;j++)
					if(*stack[0]==v[i].uni[j])
						v[i].uni[j].nas+=min;

		for(int m=1;m<stack.size;m++)
		{
			for(int i=0;i<v.size;i++)
				for(int j=0;j<v[i].uni.size;j++)
					if(*stack[m]==v[i].uni[j])
						if(stack[m]->two->num!=stack[m-1]->two->num)v[i].uni[j].nas+=min;
						else if(stack[m]->nas-min<0) v[i].uni[j].nas-=min;
						

		}
		
		//������ ����
		for(int i=0;i<v.size;i++)
			if(v[i].sts==color)v[i].sts=neut;

		stack.resize(0);
		//Draw(window,v);

	}

}*/

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 100
#define oo 10000000

int n;  
int e; 
int capacity[MAX_NODES][MAX_NODES]; 
int flow[MAX_NODES][MAX_NODES];    
int ColoR[MAX_NODES]; 
int pred[MAX_NODES];  

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
	q[tail] = x;
	tail++;
	ColoR[x] = GRAY;
}

int dequeue() {
	int x = q[head];
	head++;
	ColoR[x] = BLACK;
	return x;
}

int bfs(int start, int target) {
	int u, v;
	for (u = 0; u<n; u++) {
		ColoR[u] = WHITE;
	}
	head = tail = 0;
	enqueue(start);
	pred[start] = -1;
	while (head != tail) {
		u = dequeue();
		for (v = 0; v<n; v++) {
			if (ColoR[v] == WHITE && capacity[u][v] - flow[u][v]>0) {
				enqueue(v);
				pred[v] = u;
			}
		}
	}
	return ColoR[target] == BLACK;
}

int max_flow(int source, int sink) 
{

	int i, j, u;
	int max_flow = 0;

	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			flow[i][j] = 0;
		}
	}

	while (bfs(source, sink)) 
	{
		int increment = oo;

		for (u = n - 1; pred[u] >= 0; u = pred[u])
			increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
			for (u = n - 1; pred[u] >= 0; u = pred[u])
			{
				flow[pred[u]][u] += increment;
				flow[u][pred[u]] -= increment;
			}
			max_flow += increment;
	}

	return max_flow;
}

int Ford_Fulkerson(List<vertex>&v,RenderWindow&window)
{

	int i, j;
	n=v.size;
	e=0;
	for(int i=0;i<v.size;i++) 
		for(int j=0;j<v[i].uni.size;j++) 
			if(v[i].num<=v[i].uni[j].one->num&&v[i].num<=v[i].uni[j].two->num)e++;

	for (i = 0; i<n; i++) 
		for (j = 0; j<n; j++) 
			capacity[i][j] = 0;


	for(int i=0;i<v.size;i++) 
		for(int j=0;j<v[i].uni.size;j++) 
			if(v[i].num==v[i].uni[j].one->num)capacity[v[i].uni[j].one->num-1][v[i].uni[j].two->num-1] = v[i].uni[j].wgt;
			else capacity[v[i].uni[j].two->num-1][v[i].uni[j].one->num-1] = v[i].uni[j].wgt;


	int start=retNumber(window),finish=retNumber(window);
	int res= max_flow(start-1, finish-1) ;

	int aaa=0;
	for(int i=0;i<v.size;i++) 
		for(int j=0;j<v[i].uni.size;j++)
			if(v[i].uni[j].nas<0)aaa+=v[i].uni[j].nas;
	res+=aaa;

	//system("pause");
	return res;
}

class GeomObject
{
protected:
	float originX,originY;
	float angel;
	float scale;

public:

	virtual void Draw(){};
	void deleteImage(){};
	void Rotate(float angel){};
	void move(float x,float y){};
};

class Angel3:public GeomObject
{
public:
	Angel3()
	{
		scale=1;
		originX=10;
		originY=20;
	}

	void Draw()
	{
		cout<<"Position:";
		cout<<originX<<", ";
		cout<<originY<<endl;
		cout<<"Angel rotate";
		cout<<angel<<endl;
		cout<<"Scale:";
		cout<<scale<<endl;
	}
	void Draw(int a)
	{

	}

	void deleteImage()
	{
		cout<<"Delete image"<<endl;
	}

	void Rotate(float angel)
	{
		this->angel=angel;
	}

	void move(float x,float y)
	{
		this->originX=originX;
		this->originY=originY;
	}
};
