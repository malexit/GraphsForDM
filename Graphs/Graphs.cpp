// Graphs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "include.h"
#include <fstream>

using namespace std;
using namespace sf;

void keyboard(RenderWindow&window,List<vertex>&g);
void Sleep(int s);
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



	if(Keyboard::isKeyPressed(Keyboard::A))
	{
		Ford_Fulkerson(g,window);
		while(Keyboard::isKeyPressed(Keyboard::A));
	}
	

}
int Ford_Fulkerson(List<vertex>&v,RenderWindow&window)
{
	int start=1;
	int finish=v.size;
	List<UNI*>stack;

	
	while(true)
	{
	vertex *W=&v[start-1];
	
	//Create stack
	while(true)
	{
		int num=W->num;
		for(int i=0;i<W->uni.size;i++)
		{
			if(W->uni[i]->nas==W->uni[i]->wgt&&W->num==W->uni[i]->one->num)continue;
			if(W->uni[i]->nas==0&&W->num==W->uni[i]->two->num)continue;
			if(W->uni[i]->one->sts==color||W->uni[i]->two->sts==color)continue;

			stack.resize(stack.size+1);
			stack[stack.size-1]=W->uni[i];

			W->sts=color;
			if(W->uni[i]->one->num==W->num)W=W->uni[i]->two;
			else W=W->uni[i]->one;
			break;
		}
		if(W->num==finish)break;
		if(stack.size==0)return 0;
		if(num==W->num)
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
	
	//calculate stack
	int min=stack[0]->wgt-stack[0]->nas;

	for(int i=1;i<stack.size;i++)
	{
		if(stack[i]->two->num==stack[i-1]->two->num)
		{
			if(stack[i]->nas-min<0)min=stack[i]->nas;
		}
		else
		{
			if(min>(stack[i]->wgt-stack[i]->nas))min=stack[i]->wgt-stack[i]->nas;
		}
	}
	stack[0]->nas+=min;
	for(int i=1;i<stack.size;i++)
	{
		if(stack[i]->two->num==stack[i-1]->two->num)
			stack[i]->nas-=min;
		else
			stack[i]->nas+=min;
	}
	//clear stack
	for(int i=0;i<v.size;i++)
			if(v[i].sts==color)v[i].sts=neut;
		stack.resize(0);
	}
	return 0;
}





/*
int Ford_Fulkerson(List<vertex>&v,RenderWindow&window)
{
	int start=retNumber(window);
	int finish=retNumber(window);
	List<UNI*> stack;
	while(true)
	{
		vertex*W=&v[start-1];
		
		
		while(true)
		{
			for(int i=0;i<W->uni.size;i++)
				if(\
					(W->uni[i]->two->sts!=color&&W->uni[i]->one->sts!=color)&&\
					((W->uni[i]->nas!=W->uni[i]->wgt&&W->uni[i]->one->num==W->num)||(W->uni[i]->nas!=0&&W->uni[i]->two->num==W->num))\
					)
					//(W->uni[i].sts!=delt||W->uni[i].one->num==W->num)
					
				{	
							stack.resize(stack.size+1);
							stack[stack.size-1]=W->uni[i];
							W->sts=color;
							if(W->num!=W->uni[i]->two->num)W=W->uni[i]->two;
							else W=W->uni[i]->one;
							break;
				}
				else if(i==W->uni.size-1)
					{
						if(stack.size==0)
						{
							int result=0;
							for(int k=0;k<v[start-1].uni.size;k++)
								result+=v[start-1].uni[k]->nas;
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
	
		int min=0;
		for(int i=0;i<stack.size;i++)
			cout<<stack[i]->one->num<<"-"<<stack[i]->two->num<<endl;
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
				//for(int i=0;i<v.size;i++)
				//	for(int j=0;j<v[i].uni.size;j++)
					//	if(*stack[m]==*v[i].uni[j])v[i].uni[j]->sts=delt;
				stack[m]->sts=delt;
				break;
			}
		}
		cout<<min<<endl<<endl;

		///for(int i=0;i<v.size;i++)
			//	for(int j=0;j<v[i].uni.size;j++)
				//	if(*stack[0]==*v[i].uni[j])
					//	v[i].uni[j]->nas+=min;
		stack[0]->nas+=min;

		for(int m=1;m<stack.size;m++)
		{
			//for(int i=0;i<v.size;i++)
				//for(int j=0;j<v[i].uni.size;j++)
					//if(*stack[m]==*v[i].uni[j])
						if(stack[m]->two->num!=stack[m-1]->two->num){stack[m]->nas+=min;if(stack[m]->sts==delt)stack[m]->sts=neut;}
						else stack[m]->nas-=min;
						
		}
		
		
		for(int i=0;i<v.size;i++)
			if(v[i].sts==color)v[i].sts=neut;
		stack.resize(0);
		
	}
}*/