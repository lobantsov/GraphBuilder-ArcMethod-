	//---------------------------------------------------------------------------

	#ifndef DrawAndThumpH
	#define DrawAndThumpH
	#include <vcl.h>
    #include <cmath>
	#include <vector>
	#include "BaseComponent.h"
	#include "Node.h"
	#include "Branch.h"
	//---------------------------------------------------------------------------
	class DrawAndThump:public BaseComponent{
	private:
		int Radius;
		TCanvas* canvas;
        float mod(int c1_x, int c1_y, int c2_x, int c2_y);
	public:
		DrawAndThump(TCanvas* canvas){
			Radius = 15;
			this->canvas = canvas;
		}
		void Draw_node(int index, int x1, int y1);

        void Draw_node(Node* node);

		void Draw_selected_node(Node* node, bool select_mode);

		void Draw_select_branch(Branch* branch, bool select_mode);

		void Draw_deselect_branch(Branch* branch);

		void Hide_node(Node* node);

		void Hide_branch(Branch* branch);

		void Draw_branch(int c1_x, int c1_y, int c2_x, int c2_y, int branch_weight);

		void Draw_clear();

		__property int RadiusProperty = {read = Radius};
	};
	#endif
