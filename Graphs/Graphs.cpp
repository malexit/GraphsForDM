// Graphs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "include.h"

using namespace std;
using namespace sf;

void keyboard(RenderWindow&window,vector<vertex>&g);
void Sleep(int s);

int main()
{
	vector<vertex> v;

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
		
		keyboard(window,v);
		
		Draw(window,v);
		
		window.display();

	}

	return 0;
}

vertex& getVertex(vector<vertex>&v,int num)
{
	for(int i=0;i<v.size();i++)
		if(num==v[i].num)return v[i];
	vertex vv;
	return vv;
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

void keyboard(RenderWindow&window,vector<vertex>&g)
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

}

