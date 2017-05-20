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

int retNumber(RenderWindow & window);

Vector2i GetPosition(RenderWindow & window);

void Draw(RenderWindow& window,vector<vertex>&g);

void Line(RenderWindow&window,UNI u,vector<vertex>&g);

class vertex
{
public:
	
	status sts;
	vector<UNI*>uni;
	int num;
	int x,y;

	vertex(void);

	void Init();

	vertex(const vertex&);

	~vertex(void);

	void createUni(vertex & g,int wgt);

};

class UNI
{
public:
	int one;
	int two;
	int wgt;
	status sts;

	UNI(void);

	UNI(const UNI&);

	~UNI(void);

	void operator =(UNI *u);

	bool operator ==(UNI *u);
};

#endif INCLUDE_H
