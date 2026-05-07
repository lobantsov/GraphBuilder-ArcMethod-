//---------------------------------------------------------------------------

#pragma hdrstop

#include "DrawAdjectiveMatrix.h"
//---------------------------------------------------------------------------
void DrawAdjectiveMatrix::draw_matrix() {
	if(size_of_matrix > 0){
		for (int i = 0; i < size_of_matrix + 1; i++) {
			for (int j = 0; j < size_of_matrix + 1; j++) {
				canvas->Rectangle(i * size_of_cell, j * size_of_cell,
								  i * size_of_cell + size_of_cell,
								  j * size_of_cell + size_of_cell);
				if (i > 0 && j > 0){
					canvas->TextOutW(j * size_of_cell + 7, 10, "n" + AnsiString(Nodes[j-1]));
					canvas->TextOutW(7, j * size_of_cell + 10, "n" + AnsiString(Nodes[j-1]));
					canvas->TextOutW(i * size_of_cell + 7, j * size_of_cell + 10, adjective_matrix[i - 1][j - 1]);
				}
			}
		}
	}
}
#pragma package(smart_init)
