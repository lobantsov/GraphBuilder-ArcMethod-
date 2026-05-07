//---------------------------------------------------------------------------

#ifndef AdjectiveMatrixWizardH
#define AdjectiveMatrixWizardH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "GraphColection.h"
#include "DrawAndThump.h"
#include "DrawAdjectiveMatrix.h"
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TFAdjectiveMatrixWizard : public TForm
{
__published:	// IDE-managed Components
	TImage *ICanvas;
	TMainMenu *MainMenu1;
	TMenuItem *Saveadjectivematrix1;
	TSaveDialog *SaveDialog;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Saveadjectivematrix1Click(TObject *Sender);
private:	// User declarations
	GraphCollection* graph_collection;
	DrawAndThump *draw_and_thump;
    DrawAdjectiveMatrix* draw_adjective_matrix;
public:		// User declarations
	__fastcall TFAdjectiveMatrixWizard(TComponent* Owner);
	void setComponent(GraphCollection* graph_collection, DrawAndThump *draw_and_thump);

};
//---------------------------------------------------------------------------
extern PACKAGE TFAdjectiveMatrixWizard *FAdjectiveMatrixWizard;
//---------------------------------------------------------------------------
#endif
