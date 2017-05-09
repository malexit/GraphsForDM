#include "StdAfx.h"
#include "include.h"


Graph::Graph(void)
{

}

void Graph::Init()
{
	static int cnt=1;
	num=cnt;
	cnt++;
	sts=neut;
}

Graph::Graph(const Graph&g)
{
	num=g.num;
	sts=g.sts;
	uni.resize(g.uni.size());

	for(int i=0;i<uni.size();i++)
		uni[i]=g.uni[i];
	x=g.x;
	y=g.y;
}

Graph::~Graph(void)
{
}

void  Graph::createUni(Graph&g,int wgt)
{
	uni.resize(uni.size()+1);
	uni[uni.size()-1]=new UNI;
	uni[uni.size()-1]->one=num;
	uni[uni.size()-1]->two=g.num;
	uni[uni.size()-1]->sts=neut;
	uni[uni.size()-1]->wgt=wgt;
	g.uni.resize(g.uni.size()+1);
	g.uni[g.uni.size()-1]=uni[uni.size()-1];
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
