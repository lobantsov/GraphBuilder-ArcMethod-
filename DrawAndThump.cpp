//---------------------------------------------------------------------------

#pragma hdrstop

#include "DrawAndThump.h"
//---------------------------------------------------------------------------
void DrawAndThump::Draw_node(int index, int x1, int y1){
	Node* node = new Node(index, x1, y1);
	canvas->Ellipse(node->x - node->radius, node->y - node->radius, node->x + node->radius, node->y + node->radius);
	canvas->TextOutW(node->x-7,node->y-7, node->id);
	this->mediator_->Notify_node(node);
}

void DrawAndThump::Draw_node(Node* node){
    canvas->Ellipse(node->x - node->radius, node->y - node->radius, node->x + node->radius, node->y + node->radius);
	canvas->TextOutW(node->x-7,node->y-7, node->id);
}

void DrawAndThump::Draw_selected_node(Node* node, bool select_mode){
	if(select_mode){
		canvas->Pen->Color = (TColor)RGB(255, 128, 0);
		canvas->Font->Color = (TColor)RGB(255, 128, 0);
	}
	canvas->Ellipse(node->x - node->radius, node->y - node->radius, node->x + node->radius, node->y + node->radius);
	canvas->TextOutW(node->x-7,node->y-7, node->id);
	canvas->Pen->Color = clBlack;
	canvas->Font->Color = clBlack;
}

void DrawAndThump::Draw_branch(int c1_x, int c1_y, int c2_x, int c2_y, int branch_weight){
	float mod_of_line_between_radius = mod(c1_x, c1_y, c2_x, c2_y);

	float new_pos1_x = c1_x + (c2_x - c1_x) * (Radius / mod_of_line_between_radius);
	float new_pos1_y = c1_y + (c2_y - c1_y) * (Radius / mod_of_line_between_radius);

	float new_pos2_x = c2_x - (c2_x - c1_x) * (Radius / mod_of_line_between_radius);
	float new_pos2_y = c2_y - (c2_y - c1_y) * (Radius / mod_of_line_between_radius);

	canvas->MoveTo(new_pos1_x, new_pos1_y);
	canvas->LineTo(new_pos2_x, new_pos2_y);

	canvas->TextOutW((new_pos2_x + new_pos1_x)/2, (new_pos2_y + new_pos1_y)/2, branch_weight);
}

void DrawAndThump::Draw_select_branch(Branch* branch, bool select_mode){
	if(select_mode){
		canvas->Pen->Color = (TColor)RGB(255, 128, 0);
		canvas->Font->Color = (TColor)RGB(255, 128, 0);
	}
	Draw_branch(branch->node1->x, branch->node1->y, branch->node2->x, branch->node2->y, branch->weigth);
	canvas->Pen->Color = clBlack;
	canvas->Font->Color = clBlack;
}

void DrawAndThump::Hide_node(Node* node){
	canvas->Pen->Color = clWhite;
	canvas->Font->Color = clWhite;
	canvas->Ellipse(node->x - node->radius, node->y - node->radius, node->x + node->radius, node->y + node->radius);
	canvas->TextOutW(node->x-7,node->y-7, node->id);
    canvas->Pen->Color = clBlack;
	canvas->Font->Color = clBlack;
}

void DrawAndThump::Hide_branch(Branch* branch){
	canvas->Pen->Color = clWhite;
	canvas->Font->Color = clWhite;
	Draw_branch(branch->node1->x, branch->node1->y, branch->node2->x, branch->node2->y, branch->weigth);
	canvas->Pen->Color = clBlack;
    canvas->Font->Color = clBlack;
}

float DrawAndThump::mod(int c1_x, int c1_y, int c2_x, int c2_y) {
	return (float)sqrt((double)((c2_x - c1_x) * (c2_x - c1_x) + (c2_y - c1_y) * (c2_y - c1_y)));
}

void DrawAndThump::Draw_clear(){
    canvas->Brush->Color = clWhite;
	canvas->FillRect(canvas->ClipRect);
}
#pragma package(smart_init)

