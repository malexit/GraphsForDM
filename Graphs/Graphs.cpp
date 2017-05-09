// Graphs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "include.h"

using namespace std;
using namespace sf;

void Prim(vector<Graph>&g,RenderWindow&window);
void keyboard(RenderWindow&window,vector<Graph>&g);
void Sleep(int s);

int main()
{
	vector<Graph> g;

	RenderWindow window(VideoMode(1280,720),"Graphs",Style::Fullscreen);

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
		
		keyboard(window,g);
		
		Draw(window,g);
		
		window.display();

	}

	return 0;
}

Graph& getGraph(vector<Graph>&g,int num)
{
	for(int i=0;i<g.size();i++)
		if(num==g[i].num)return g[i];
	Graph gg;
	return gg;
}

void Prim(vector<Graph>&g,RenderWindow&window)
{
	vector<UNI*>t;
	t.resize(g[0].uni.size());

	for(int i=0;i<t.size();i++)
		t[i]=g[0].uni[i];
	UNI *u;
	for(int i=0;i<g.size()-1;i++)
	{
		int min=0;
		for(int j=0;j<t.size();j++)
			if(min<t[j]->wgt)min=t[j]->wgt;
		for(int j=0;j<t.size();j++)
			if(t[j]->wgt<=min&&t[j]->sts==neut&&(getGraph(g,t[j]->one).sts==neut||getGraph(g,t[j]->two).sts==neut)){min=t[j]->wgt;u=t[j];}

			getGraph(g,u->one).sts=color;
			getGraph(g,u->two).sts=color;
			u->sts=color;

			
			for(int j=0;j<getGraph(g,u->one).uni.size();j++)
				if(getGraph(g,u->one).uni[j]->sts!=color)
				{
					for(int k=0;k<t.size();k++)
						if(getGraph(g,u->one).uni[j]==t[k])break;
						else if(k==t.size()-1)
						{
							t.resize(t.size()+1);
							t[t.size()-1]=getGraph(g,u->one).uni[j];
							break;
						}
				}

			for(int j=0;j<getGraph(g,u->two).uni.size();j++)
				if(getGraph(g,u->two).uni[j]->sts!=color)
				{
					for(int k=0;k<t.size();k++)
						if(getGraph(g,u->two).uni[j]==t[k])break;
						else if(k==t.size()-1)
						{
							t.resize(t.size()+1);
							t[t.size()-1]=getGraph(g,u->two).uni[j];
							break;
						}
				}
				window.clear(Color::White);

				Draw(window,g);
				Sleep(7);
				window.display();
	}
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

void keyboard(RenderWindow&window,vector<Graph>&g)
{
	if(Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i pos=GetPosition(window);

			if(!Keyboard::isKeyPressed(Keyboard::LShift)&&!Keyboard::isKeyPressed(Keyboard::LControl))
				for(int i=0;i<g.size();i++)
					if(FloatRect(pos.x,pos.y,1,1).intersects(FloatRect(g[i].x-35,g[i].y-35,70,70)))
						while(true)
						{
							Vector2i pos=GetPosition(window);

							if(!Mouse::isButtonPressed(Mouse::Left))
							{
								g[i].x=pos.x;
								g[i].y=pos.y;
								break;
							}

						}


		if(Keyboard::isKeyPressed(Keyboard::LShift))
		{
			while(true)
			{
				if(!Keyboard::isKeyPressed(Keyboard::LShift))break;
				else if(!Mouse::isButtonPressed(Mouse::Left))
				{
					pos=GetPosition(window);

					g.resize(g.size()+1);
					g[g.size()-1].Init();
					g[g.size()-1].x=pos.x;
					g[g.size()-1].y=pos.y;
					break;
				}
			}
			
		}

		if(Keyboard::isKeyPressed(Keyboard::LControl))	
				for(int i=0;i<g.size();i++)
					if(FloatRect(pos.x,pos.y,1,1).intersects(FloatRect(g[i].x-35,g[i].y-35,70,70)))
					{
						int wgt=0;

					
						while(Keyboard::isKeyPressed(Keyboard::LControl))
						{
							if(!Mouse::isButtonPressed(Mouse::Left))
							{
								pos=GetPosition(window);

								for(int j=0;j<g.size();j++)
									if(FloatRect(pos.x,pos.y,1,1).intersects(FloatRect(g[j].x-35,g[j].y-35,70,70)))
										if(i!=j){wgt=retNumber(window);g[i].createUni(g[j],wgt);break;}
										else break;

								break;
							}
						}
						break;
					}

		
		}


		if(Keyboard::isKeyPressed(Keyboard::P))
		{
			Prim(g,window);
			while(Keyboard::isKeyPressed(Keyboard::P));
		}
}

