#include "StdAfx.h"
#include "include.h"


vertex::vertex(void)
{

}

void vertex::Init()
{
	static int cnt=1;
	num=cnt;
	cnt++;
	sts=neut;
}

vertex::vertex(const vertex&v)
{
	num=v.num;
	sts=v.sts;
	uni.resize(v.uni.size());

	for(int i=0;i<uni.size();i++)
		uni[i]=v.uni[i];
	x=v.x;
	y=v.y;
}

vertex::~vertex(void)
{
}

void  vertex::createUni(vertex&v,int wgt)
{
	uni.resize(uni.size()+1);
	uni[uni.size()-1]=new UNI;
	uni[uni.size()-1]->one=num;
	uni[uni.size()-1]->two=v.num;
	uni[uni.size()-1]->sts=neut;
	uni[uni.size()-1]->wgt=wgt;
	v.uni.resize(v.uni.size()+1);
	v.uni[v.uni.size()-1]=uni[uni.size()-1];
}

Vector2i GetPosition(RenderWindow & window)
{
	static bool full=true;
	Vector2i pos;
	pos=Mouse::getPosition();
	if(full)pos.x-=window.getPosition().x;
	else pos.x-=window.getPosition().x+8;
	if(full)pos.y-=window.getPosition().y;
	else pos.y-=window.getPosition().y+30;

	if(Keyboard::isKeyPressed(Keyboard::F))
		{
			while(Keyboard::isKeyPressed(Keyboard::F));
			full?full=false:full=true;
			full?window.create(VideoMode(window.getSize().x,window.getSize().y),"Graphs",Style::Fullscreen):window.create(VideoMode(1000,562),"Graphs");
			
		}
	return pos;
}
