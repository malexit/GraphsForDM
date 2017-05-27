#include "StdAfx.h"
#include "include.h"


UNI::UNI(void)
{
	sts=neut;
	nas=0;
}


UNI::~UNI(void)
{
}

int retNumber(RenderWindow & window)
{

	Font f;
	f.loadFromFile("Old.ttf");
	Text txt;
	txt.setFont(f);
	txt.setCharacterSize(30);
	txt.setColor(Color::Green);
	txt.setPosition(100,100);

	string str;
	while(!Keyboard::isKeyPressed(Keyboard::Return))
	{
		window.clear(Color::White);
		if(Keyboard::isKeyPressed(Keyboard::Num0))
			{
				str+='0';
				while(Keyboard::isKeyPressed(Keyboard::Num0));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num1))
			{
				str+='1';
				while(Keyboard::isKeyPressed(Keyboard::Num1));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num2))
			{
				str+='2';
				while(Keyboard::isKeyPressed(Keyboard::Num2));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num3))
			{
				str+='3';
				while(Keyboard::isKeyPressed(Keyboard::Num3));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num4))
			{
				str+='4';
				while(Keyboard::isKeyPressed(Keyboard::Num4));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num5))
			{
				str+='5';
				while(Keyboard::isKeyPressed(Keyboard::Num5));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num6))
			{
				str+='6';
				while(Keyboard::isKeyPressed(Keyboard::Num6));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num7))
			{
				str+='7';
				while(Keyboard::isKeyPressed(Keyboard::Num7));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num8))
			{
				str+='8';
				while(Keyboard::isKeyPressed(Keyboard::Num8));
			}
		if(Keyboard::isKeyPressed(Keyboard::Num9))
			{
				str+='9';
				while(Keyboard::isKeyPressed(Keyboard::Num9));
			}
		if(Keyboard::isKeyPressed(Keyboard::BackSpace))
			{
				if(str.size()!=0)str.resize(str.size()-1);
				while(Keyboard::isKeyPressed(Keyboard::BackSpace));
			}
		txt.setString(str);
		window.draw(txt);
		window.display();
	}
	while(Keyboard::isKeyPressed(Keyboard::Return));
	int res=0;

	res=atoi(str.c_str());


	return res;

}

void UNI::operator =(UNI *u)
{
	one=u->one;
	two=u->two;
	sts=u->sts;
	wgt=u->wgt;
}

bool UNI::operator ==(UNI u)
{
	if(one!=u.one)return false;
	if(two!=u.two)return false;

	return true;
}


