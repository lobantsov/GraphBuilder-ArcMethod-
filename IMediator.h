//---------------------------------------------------------------------------

#ifndef IMediatorH
#define IMediatorH
#include <iostream>
#include "Node.h"
#include "Branch.h"
//---------------------------------------------------------------------------
class IMediator
{
public:
	virtual void Notify_node(Node* node) const = 0;
	virtual void Notify_branch(int c1_x, int c1_y, int c2_x, int c2_y, int branch_weight) const = 0;
	virtual void Notify_delete_node(Node* node) const = 0;
	virtual void Notify_delete_branch(Branch* branch) const = 0;
	virtual void Notify_load_node(Node* node) const = 0;
	virtual void Notify_load_branch(Branch* branch) const = 0;
	virtual void Notify_clear_canvas() const = 0;
	virtual void Notify_draw_selected_node(Node* node, bool select_mode) const = 0;
	virtual void Notify_draw_selected_branch(Branch* branch, bool select_mode) const = 0;
};
#endif
