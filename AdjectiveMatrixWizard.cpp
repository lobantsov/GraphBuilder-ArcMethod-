//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AdjectiveMatrixWizard.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFAdjectiveMatrixWizard *FAdjectiveMatrixWizard;
int cell_size = 20;
int** adjective_matrix;
//---------------------------------------------------------------------------
__fastcall TFAdjectiveMatrixWizard::TFAdjectiveMatrixWizard(TComponent* Owner)
	: TForm(Owner)
{
	SaveDialog->Filter = "Txt files (*.txt)|*.txt|All files (*.*)|*.*";
	SaveDialog->DefaultExt = "txt";
	SaveDialog->Title = "Save graph";
}
//---------------------------------------------------------------------------
void __fastcall TFAdjectiveMatrixWizard::FormShow(TObject *Sender)
{
	ICanvas->Canvas->Pen->Color = clBlack;
	if(graph_collection->AdjectiveMatrix != NULL)
	{
		draw_adjective_matrix = new DrawAdjectiveMatrix(graph_collection->AdjectiveMatrix,
														graph_collection->getNodeCount(),
														ICanvas->Canvas,
														graph_collection->NodesId);
		draw_adjective_matrix->draw_matrix();
	}
}

void TFAdjectiveMatrixWizard::setComponent(GraphCollection* graph_collection, DrawAndThump *draw_and_thump){
	this->graph_collection = graph_collection;
    this->draw_and_thump = draw_and_thump;
}
//---------------------------------------------------------------------------
void __fastcall TFAdjectiveMatrixWizard::FormClose(TObject *Sender, TCloseAction &Action)

{
	ICanvas->Canvas->Pen->Color = clWhite;
	ICanvas->Canvas->Rectangle(0,0, ICanvas->Width, ICanvas->Height);
}
//---------------------------------------------------------------------------

void __fastcall TFAdjectiveMatrixWizard::Saveadjectivematrix1Click(TObject *Sender)

{
	if(SaveDialog->Execute()){
			graph_collection->saveAdjectiveMatrix(AnsiString(SaveDialog->FileName).c_str());
		}
}
//---------------------------------------------------------------------------

