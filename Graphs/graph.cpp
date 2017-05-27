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
	num_l=999;
}

vertex::~vertex(void)
{
}

bool vertex::operator !=(vertex v)
{
	if(num!=v.num)return true;
}

void  vertex::createUni(vertex&v,int wgt)
{
	uni.resize(uni.size+1);
	uni[uni.size-1].wgt=wgt;
	uni[uni.size-1].sts=neut;
	uni[uni.size-1].one=this;
	uni[uni.size-1].two=&v;
	v.uni.resize(v.uni.size+1);
	v.uni[v.uni.size-1]=uni[uni.size-1];
}

Vector2i GetPosition(RenderWindow & window)
{
	static bool full=false;
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
