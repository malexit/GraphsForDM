// Graphs.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include "include.h"

using namespace std;
using namespace sf;

void keyboard(RenderWindow&window,List<vertex>&g);
void Sleep(int s);
void Deykstr(List<vertex>&v,RenderWindow&window);
void Ford_Fulkerson(List<vertex>&v,RenderWindow&window);

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
		Ford_Fulkerson(g,window);
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
	cout<<"ћинимальный вес пути:"<<sum<<endl;
	cout<<endl;
}

void Ford_Fulkerson(List<vertex>&v,RenderWindow&window)
{
	int start=retNumber(window);
	int finish=retNumber(window);

	List<UNI*> stack;

	bool isDelete;
	while(true)
	{
		isDelete=false;

		vertex*W=&v[start-1];
		
		while(true)
		{
			for(int i=0;i<W->uni.size;i++)
				if(W->uni[i].two->num!=W->num&&W->uni[i].two->sts!=color&&W->uni[i].nas!=W->uni[i].wgt&&W->uni[i].two->sts!=delt)
				{	
							stack.resize(stack.size+1);
							stack[stack.size-1]=&W->uni[i];
							W->sts=color;
							W=W->uni[i].two;
							break;
				}
				else if(i==W->uni.size-1)
					{
						if(W->sts!=delt){W->sts=delt;isDelete=true;break;}
						else return;
					}
				if(isDelete)break;
				if(W->num==finish)break;
		}
		if(isDelete)continue;

		int min=9999;

		for(int m=0;m<stack.size;m++)
			if(min>=(stack[m]->wgt-stack[m]->nas))
				min=stack[m]->wgt-stack[m]->nas;


		for(int m=0;m<stack.size;m++)
		{
			for(int i=0;i<v.size;i++)
				for(int j=0;j<v[i].uni.size;j++)
					if(*stack[m]==v[i].uni[j])
						v[i].uni[j].nas+=min;

		}
		
		for(int i=0;i<v.size;i++)
			if(v[i].sts==color)v[i].sts=neut;

		stack.resize(0);
		//Draw(window,v);

	}

}