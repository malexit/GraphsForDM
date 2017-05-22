#include "StdAfx.h"
#include "include.h"

using namespace std;
using namespace sf;

Image gi;
Texture gt;
Sprite gs;
Font f;
Text txt;

void Draw(RenderWindow& window,List<vertex>&g)
{
	static bool load=false;
	if(!load)
	{
	gi.loadFromFile("graph.png");
	gi.createMaskFromColor(Color::White);
	gt.loadFromImage(gi);	
	gs.setTexture(gt);
	gs.setOrigin(35,35);
	f.loadFromFile("Old.ttf");
	txt.setFont(f);
	}
	txt.setCharacterSize(15);


	for(int i=0;i<g.size;i++)
	{
		for(int j=0;j<g[i].uni.size;j++)
		Line(window,g[i].uni[j],g);
	}

		for(int i=0;i<g.size;i++)
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
}


void Line(RenderWindow&window,UNI u,List<vertex>&g)
{

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

	vertex one,two;

	txt.setCharacterSize(15);
	txt.setColor(c);

	char*str=new char[5];

	itoa(u.wgt,str,10);

	txt.setString(str);
	delete[]str;

	for(int i=0;i<g.size;i++)
		if((i+1)==u.one->num)one=g[i];
		else if((i+1)==u.two->num)two=g[i];

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