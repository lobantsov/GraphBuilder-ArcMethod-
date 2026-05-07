//---------------------------------------------------------------------------

#ifndef ConcreteMediatorH
#define ConcreteMediatorH
#include <string>
#include "IMediator.h"
#include "GraphColection.h"
#include "DrawAndThump.h"
#include "Node.h"
#include "Branch.h"
//---------------------------------------------------------------------------
class ConcreteMediator: public IMediator{
private:
	GraphCollection* graph_collection;
	DrawAndThump* draw_and_thump;
public:
	ConcreteMediator(GraphCollection* graph_collection, DrawAndThump* draw_and_thump){
		this->graph_collection = graph_collection;
		this->draw_and_thump = draw_and_thump;
		this->graph_collection->SetMediator(this);
        this->draw_and_thump->SetMediator(this);
	}
	virtual void Notify_node(Node* node) const;

	virtual void Notify_branch(int c1_x, int c1_y, int c2_x, int c2_y, int branch_weight) const;

	virtual void Notify_delete_node(Node* node) const;

	virtual void Notify_delete_branch(Branch* branch) const;

	virtual void Notify_load_node(Node* node) const;

	virtual void Notify_load_branch(Branch* branch) const;

	virtual void Notify_clear_canvas() const;

	virtual void Notify_draw_selected_node(Node* node, bool select_mode) const;

    virtual void Notify_draw_selected_branch(Branch* branch, bool select_mode) const;
};
#endif
