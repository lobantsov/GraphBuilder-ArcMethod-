//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#ifndef DrawAdjectiveMatrixH
#define DrawAdjectiveMatrixH
//---------------------------------------------------------------------------
class DrawAdjectiveMatrix{
private:
	std::vector<int> Nodes;
	int size_of_cell;
	int size_of_matrix;
	int** adjective_matrix;
	TCanvas* canvas;
public:
	DrawAdjectiveMatrix(int** adj_matrix, int size_of_matrix, TCanvas* canvas, std::vector<int> Nodes){
		size_of_cell = 40;
		this->size_of_matrix = size_of_matrix;
		adjective_matrix = adj_matrix;
		this->canvas = canvas;
        this->Nodes = Nodes;
	}

    void draw_matrix();
};
#endif
