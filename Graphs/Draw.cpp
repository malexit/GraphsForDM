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

			txt.setColor(Color::Black);

			gs.setPosition(g[i].x,g[i].y);
			window.draw(gs);
			window.draw(txt);
		}
}


void Line(RenderWindow&window,UNI u,List<vertex>&g)
{

	Image img;
	Color c;
	if(u.sts==neut)c=Color(50,200,20);
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

	string sstr;
	char*str=new char[5];

	itoa(u.wgt,str,10);
	sstr+=str;
	sstr+="(";
	itoa(u.nas,str,10);
	sstr+=str;
	sstr+=")";
	txt.setString(sstr);
	delete[]str;

	for(int i=0;i<g.size;i++)
		if((i+1)==u.one->num)one=g[i];
		else if((i+1)==u.two->num)two=g[i];

	int xb,xs,y,b,ys,yb;
	int sx,sy;

	bool xso,yso;

	sx=(one.x+two.x)/2;
	sy=(one.y+two.y)/2;

	float k;

	k=(1.0*(one.y-two.y))/(one.x-two.x);

	if(one.x>=two.x){xb=one.x;xs=two.x;xso=false;}
	else {xb=two.x;xs=one.x;xso=true;}

	if(one.y>=two.y){yb=one.y;ys=two.y;yso=false;}
	else {yb=two.y;ys=one.y;yso=true;}

	b=one.y-k*one.x;
	int j;

	bool color=false;

	if(xso)img.setPixel(0,0,Color::Black);
	else img.setPixel(0,0,Color::Red);
	t.loadFromImage(img);
	s.setTexture(t);

	for(float i=xs;i<xb;i+=1)
	{
		j=k*i+b;
		s.setPosition(i,j);

		if(!color)
		{
			if(xso==true)
			{
				if((i-xs)/((xb-xs)*1.0)>=0.85)
				{
				img.setPixel(0,0,Color::Red);
				t.loadFromImage(img);
				s.setTexture(t);
				color=true;
				}
			}
			else if((i-xs)/((xb-xs)*1.0)>=0.15)
			{
				img.setPixel(0,0,Color::Black);
				t.loadFromImage(img);
				s.setTexture(t);
				color=true;
			}
		}


		window.draw(s);
	} 

	if(yso)img.setPixel(0,0,Color::Black);
	else img.setPixel(0,0,Color::Red);
	t.loadFromImage(img);
	s.setTexture(t);
	color=false;

	j;
	for(float i=ys;i<yb;i+=1)
	{
		j=(i-b)/(k*1.0);
		s.setPosition(j,i);

		if(!color)
		{
			if(yso==true)
			{
				if((i-ys)/((yb-ys)*1.0)>=0.85)
				{
				img.setPixel(0,0,Color::Red);
				t.loadFromImage(img);
				s.setTexture(t);
				color=true;
				}
			}
			else if((i-ys)/((yb-ys)*1.0)>=0.15)
			{
				img.setPixel(0,0,Color::Black);
				t.loadFromImage(img);
				s.setTexture(t);
				color=true;
			}
		}

		window.draw(s);
	} 

	txt.setPosition(sx,sy);
	window.draw(txt);
}