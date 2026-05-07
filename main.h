//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "GraphColection.h"
#include "DrawAndThump.h"
#include "ConcreteMediator.h"
#include "Node.h"
#include <Vcl.ButtonGroup.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TImage *ICanvas;
	TRadioGroup *RGButtons;
	TMainMenu *MainMenu;
	TMenuItem *S1;
	TMenuItem *Savevector1;
	TMenuItem *Savevector2;
	TMenuItem *Open1;
	TMenuItem *Openvector1;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TMenuItem *Openadjectivematrixwizard1;
	TMenuItem *Savelist1;
	TButton *BTFindPath;
	TMemo *Memo1;
	TButton *Button1;
	TEdit *ENValue;
	TLabel *Label1;
	TLabel *LBTotalWeight;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *LBTargetWeight;
	void __fastcall ICanvasMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Savevector1Click(TObject *Sender);
	void __fastcall Openvector1Click(TObject *Sender);
	void __fastcall Savevector2Click(TObject *Sender);
	void __fastcall Openadjectivematrixwizard1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Savelist1Click(TObject *Sender);
	void __fastcall BTFindPathClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	GraphCollection* graph_collection;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
