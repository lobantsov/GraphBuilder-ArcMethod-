//---------------------------------------------------------------------------
#include <iostream>
#ifndef BranchH
#define BranchH
#include "Node.h"
//---------------------------------------------------------------------------
class Branch {
public:
	Node* node1;
	Node* node2;
    int weigth;

	explicit Branch(Node* n1, Node* n2, int weight = 0): node1(n1), node2(n2) {
        this->weigth = weight;
	}
};
#endif
