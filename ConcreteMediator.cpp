//---------------------------------------------------------------------------

#pragma hdrstop

#include "ConcreteMediator.h"
//---------------------------------------------------------------------------
void ConcreteMediator::Notify_node(Node* node) const{
	graph_collection->addNode(node);
}

void ConcreteMediator::Notify_branch(int c1_x, int c1_y, int c2_x, int c2_y, int branch_weight) const{
	draw_and_thump->Draw_branch(c1_x, c1_y, c2_x, c2_y, branch_weight);
}

void ConcreteMediator::Notify_delete_node(Node* node) const{
	draw_and_thump->Hide_node(node);
}

void ConcreteMediator::Notify_delete_branch(Branch* branch) const{
    draw_and_thump->Hide_branch(branch);
}

void ConcreteMediator::Notify_load_node(Node* node) const{
    draw_and_thump->Draw_node(node);
}

void ConcreteMediator::Notify_load_branch(Branch* branch) const{
	draw_and_thump->Draw_branch(branch->node1->x, branch->node1->y, branch->node2->x,
	 							branch->node2->y, branch->weigth);
}

void ConcreteMediator::Notify_clear_canvas() const{
    draw_and_thump->Draw_clear();
}

void ConcreteMediator::Notify_draw_selected_node(Node* node, bool select_mode) const{
    draw_and_thump->Draw_selected_node(node, select_mode);
}

void ConcreteMediator::Notify_draw_selected_branch(Branch* branch, bool select_mode) const{
    draw_and_thump->Draw_select_branch(branch, select_mode);
}
#pragma package(smart_init)
