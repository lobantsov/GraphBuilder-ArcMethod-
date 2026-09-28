//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
#include "WeightForm.h"
#include "AdjectiveMatrixWizard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
DrawAndThump *draw_and_thump;
ConcreteMediator* mediator;
int index = 0;
int switcher = -1;
int branch_weight = 0;
int click_index= 0;
bool is_selected = false;
bool is_first_node = true;
int TotalWeight = 0;
Node* node1;
Node* node2;
Branch* branch;
std::vector<int> path;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	draw_and_thump = new DrawAndThump(ICanvas->Canvas);
	graph_collection = new GraphCollection();
	mediator = new ConcreteMediator(graph_collection, draw_and_thump);

	OpenDialog->Filter = "Graph files (*.graph)|*.graph|All files (*.*)|*.*";
	OpenDialog->DefaultExt = "graph";
	OpenDialog->Title = "Save graph";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ICanvasMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(is_selected){
	   draw_and_thump->Draw_selected_node(node1, false);
	   node1 = NULL;
	   is_selected = false;
	}
    if(path.size()>0)
		graph_collection->buildPath(path, false);
	//create node
	if(RGButtons->ItemIndex == 0){
		draw_and_thump->Draw_node(++index, X,Y);
	}//create branch | create branch with weight
	else if(RGButtons->ItemIndex == 1 || RGButtons->ItemIndex == 2){
		switch(click_index){
			case 0:
				node1 = graph_collection->findNodeByPoint(X,Y);
				click_index++;
				if(node1)
					draw_and_thump->Draw_selected_node(node1, true);
				break;
			case 1:
				node2 = graph_collection->findNodeByPoint(X,Y);
				if(node1 && node2){
					if(RGButtons->ItemIndex == 2){
						if(FormWeight->ShowModal() == mrOk){
							if(FormWeight->EWeight->Text != "")
								branch_weight = StrToInt (FormWeight->EWeight->Text);
								TotalWeight += StrToInt (FormWeight->EWeight->Text);
								LBTotalWeight->Caption = TotalWeight;
						}
					}
					graph_collection->addBranch(node1, node2, branch_weight);
                    branch_weight = 0;
				}
				if(node1) draw_and_thump->Draw_selected_node(node1, false);
				if(node2) draw_and_thump->Draw_selected_node(node2, false);
                click_index = 0;
				node1 = NULL;
                node2 = NULL;
			break;
		}
	}
	//select node
	else if(RGButtons->ItemIndex == 3){
		node1 = graph_collection->findNodeByPoint(X,Y);
		if(node1){
			draw_and_thump->Draw_selected_node(node1, true);
			is_selected = true;
		}
	}//select branch
	else if(RGButtons->ItemIndex == 4){
		if(branch != NULL){
			draw_and_thump->Draw_select_branch(branch, false);
			branch = NULL;
		}
		branch = graph_collection->findBranchByPoint(X,Y);
		if(branch != NULL){
			draw_and_thump->Draw_select_branch(branch, true);
		}
	}//delete node
	else if(RGButtons->ItemIndex == 5){
		if(node1 == NULL){
			node1 = graph_collection->findNodeByPoint(X,Y);
			std::vector<Branch*> tmp = graph_collection->findBranchesByNode(node1);
			for (int i = 0; i < tmp.size(); i++) {
				TotalWeight -= tmp[i]->weigth;
			}
			LBTotalWeight->Caption = TotalWeight;
		}
		if(node1 != NULL)
			graph_collection->deleteNode(node1);
		node1=NULL;
	}//delete branch
	else if(RGButtons->ItemIndex == 6){
	   if(branch == NULL){
			branch = graph_collection->findBranchByPoint(X,Y);
		}
		if(branch != NULL)
		{
			TotalWeight -= branch->weigth;
			LBTotalWeight->Caption = TotalWeight;
			graph_collection->deleteBranch(branch);
		}
		branch=NULL;
	}
	//select two nodes for path search
	else if(RGButtons->ItemIndex == 7){
		RGButtons->Enabled = false;
		if (is_first_node) {
			if (node1 != NULL) {
				draw_and_thump->Draw_selected_node(node1, false);
				node1 = NULL;
			}
			if (node2 != NULL) {
				draw_and_thump->Draw_selected_node(node2, false);
				node2 = NULL;
			}

			node1 = graph_collection->findNodeByPoint(X, Y);

			if (node1 != NULL) {
				draw_and_thump->Draw_selected_node(node1, true);
				is_first_node = false;
			} else {
				is_first_node = true;
			}
		} else {
			if (node1 == NULL) {
				is_first_node = true;
				return;
			}

			node2 = graph_collection->findNodeByPoint(X, Y);
			if (node2 != NULL) {
				draw_and_thump->Draw_selected_node(node2, true);
				is_first_node = true;
			} else {
				draw_and_thump->Draw_selected_node(node1, false);
				node1 = NULL;
				node2 = NULL;
				is_first_node = true;
			}
		}
	}
		MainForm->Caption = "Node: " + AnsiString(graph_collection->getNodeCount()) +
					" branch: " + AnsiString(graph_collection->getBranchCount());
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_ESCAPE)
    {
		if(node1){
		draw_and_thump->Draw_selected_node(node1, false);
        node1 = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Savevector1Click(TObject *Sender)
{
	SaveDialog->Filter = "Graph files (*.graph)|*.graph|All files (*.*)|*.*";
	SaveDialog->DefaultExt = "graph";
	SaveDialog->Title = "Save graph";
	if(SaveDialog->Execute()){
		graph_collection->saveBinary(AnsiString(SaveDialog->FileName).c_str());
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Openvector1Click(TObject *Sender)
{
	if(OpenDialog->Execute()){
		std::pair<int,int> a = graph_collection->loadBinary(AnsiString(OpenDialog->FileName).c_str());
		index = a.first;
		TotalWeight = a.second;
        LBTotalWeight->Caption = TotalWeight;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Savevector2Click(TObject *Sender)
{
	SaveDialog->Filter = "Txt files (*.txt)|*.txt|All files (*.*)|*.*";
	SaveDialog->DefaultExt = "txt";
	SaveDialog->Title = "Save graph";
	if(SaveDialog->Execute()){
		graph_collection->saveAdjectiveMatrix(AnsiString(SaveDialog->FileName).c_str());
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Openadjectivematrixwizard1Click(TObject *Sender)
{
	graph_collection->saveAdjectiveMatrix("ADJM.txt");
	FAdjectiveMatrixWizard->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
    FAdjectiveMatrixWizard->setComponent(graph_collection, draw_and_thump);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Savelist1Click(TObject *Sender)
{
	SaveDialog->Filter = "Txt files (*.txt)|*.txt|All files (*.*)|*.*";
	SaveDialog->DefaultExt = "txt";
	SaveDialog->Title = "Save graph";
	if(SaveDialog->Execute()){
		graph_collection->saveAdjectiveList(AnsiString(SaveDialog->FileName).c_str());
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::BTFindPathClick(TObject *Sender)
{
	RGButtons->Enabled = true;
	if(node1 != NULL && node2 != NULL){
		if(path.size()>0)
			graph_collection->buildPath(path, false);
		if (((TButton*)Sender)->Tag == 1)
		{
			path = graph_collection->find_shorted_path(node1->id, node2->id);
		}
		else if (((TButton*)Sender)->Tag == 2)
		{
			if(ENValue->Text != ""){
			  path = graph_collection->find_target_path(node1->id, node2->id, StrToInt(ENValue->Text));
			}
			else{
                ShowMessage("Set N");
			}
		}
		draw_and_thump->Draw_selected_node(node1, false);
		draw_and_thump->Draw_selected_node(node2, false);
		Memo1->Lines->Clear();
		for (int i = 0; i < path.size(); ++i) {
			Memo1->Lines->Add(IntToStr(path[i]));
		}
		LBTargetWeight->Caption = graph_collection->buildPath(path, true);
	}

}
//---------------------------------------------------------------------------


