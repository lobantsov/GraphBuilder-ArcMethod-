//---------------------------------------------------------------------------
#include <iostream>
#ifndef NodeH
#define NodeH
//---------------------------------------------------------------------------
class Node {
public:
	int id;
	int x,y;
	int radius;

	explicit Node(int id, int x, int y) : id(id){
		radius = 15;
		//this->x = x+radius;
		//this->y = y+radius;
		this->x = x;
		this->y = y;
	}
};
#endif
