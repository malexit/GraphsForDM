#pragma once
#ifndef INCLUDE_H
#define INCLUDE_H


#include <iostream>
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

enum status {neut,color,delt};



class UNI;
class vertex;
template <class T>
class List;

int retNumber(RenderWindow & window);

Vector2i GetPosition(RenderWindow & window);

void Draw(RenderWindow& window,List<vertex>&g);

void Line(RenderWindow&window,UNI u,List<vertex>&g);

template <class T>
class List
{
public:
	T **v;
	int size;

	List()
	{
		size=0;
		v=new T*[size];
	}

	void resize(int nsize)
	{
		if(nsize<0) return;

        T **nstr=new T*[nsize];

        if(nsize<size) size=nsize;
		else nstr[nsize-1]=new T;

        if(size!=0)
        for(int i=0;i<size;i++)
            nstr[i]=v[i];

        delete [] v;

        v=nstr;

        size=nsize;
    }

	T& operator [](int n)
	{
		return *v[n];
	}

};


class vertex
{
public:
	
	status sts;
	List<UNI>uni;
	int num;
	int num_l;
	int x,y;
	

	vertex(void);

	void Init();

	~vertex(void);

	void createUni(vertex & v,int wgt);

	bool operator !=(vertex v);

};

class UNI
{
public:
	vertex *one;
	vertex *two;
	int wgt;
	status sts;

	UNI(void);

	~UNI(void);

	void operator =(UNI *u);

	bool operator ==(UNI u);
};



#endif INCLUDE_H
