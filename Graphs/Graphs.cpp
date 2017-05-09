// Graphs.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "include.h"

using namespace std;
using namespace sf;

void Line(RenderWindow&window,UNI u,vector<Graph>&g);
void Prim(vector<Graph>&g);
void keyboard(RenderWindow&window,vector<Graph>&g);

int main()
{
	vector<Graph> g;

	RenderWindow window(VideoMode(1280,720),"Graphs",Style::Fullscreen);

	Image gi;
	gi.loadFromFile("graph.png");
	gi.createMaskFromColor(Color::White);
	Texture gt;
	gt.loadFromImage(gi);
	Sprite gs;
	gs.setTexture(gt);
	gs.setOrigin(35,35);


	Font f;
	f.loadFromFile("Old.ttf");
	Text txt;
	txt.setFont(f);
	txt.setCharacterSize(15);

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
		
		for(int i=0;i<g.size();i++)
		{
			for(int j=0;j<g[i].uni.size();j++)
			{
				if((i+1)<g[i].uni[j]->two||(i+1)<g[i].uni[j]->one)
				Line(window,*g[i].uni[j],g);
			}
		}

		for(int i=0;i<g.size();i++)
		{

			char*str=new char[5];

			itoa(g[i].num,str,10);

			txt.setString(str);
			delete[]str;

			txt.setPosition(g[i].x,g[i].y);

			if(g[i].sts==neut)txt.setColor(Color::Black);
				else if(g[i].sts==color)txt.setColor(Color::Red);
				else txt.setColor(Color::Yellow);
			gs.setPosition(g[i].x,g[i].y);
			window.draw(gs);
			window.draw(txt);
		}

		

		window.display();

	}

	return 0;
}
Font f;
void Line(RenderWindow&window,UNI u,vector<Graph>&g)
{
	static bool load=true;
	Image img;
	Color c;
	if(u.sts==neut)c=Color::Black;
	else if(u.sts==color)c=Color::Red;
	else c=Color::Yellow;
	img.create(1,1,c);
	Texture t;
	Sprite s;
	t.loadFromImage(img);
	s.setTexture(t);

	Graph one,two;

	
	if(load){f.loadFromFile("Old.ttf");load=false;}
	Text txt;
	txt.setFont(f);
	txt.setCharacterSize(15);
	txt.setColor(c);

	char*str=new char[5];

	itoa(u.wgt,str,10);

	txt.setString(str);
	delete[]str;

	for(int i=0;i<g.size();i++)
		if((i+1)==u.one)one=g[i];
		else if((i+1)==u.two)two=g[i];

	int xb,xs,y,b;
	int sx,sy;

	sx=(one.x+two.x)/2;
	sy=(one.y+two.y)/2;

	float k;

	k=(1.0*(one.y-two.y))/(one.x-two.x);

	if(one.x>=two.x){xb=one.x;xs=two.x;}
	else {xb=two.x;xs=one.x;}

	b=one.y-k*one.x;
	int j;
	for(float i=xs;i<xb;i+=0.1)
	{
		j=k*i+b;
		s.setPosition(i,j);
		window.draw(s);
	} 

	txt.setPosition(sx,sy);
	window.draw(txt);
}

Graph& getGraph(vector<Graph>&g,int num)
{
	
	for(int i=0;i<g.size();i++)
		if(num==g[i].num)return g[i];
	Graph gg;
	return gg;
}

void Prim(vector<Graph>&g)
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
			Prim(g);
			while(Keyboard::isKeyPressed(Keyboard::P));
		}
}

