//---------------------------------------------------------------------------

#ifndef WeightFormH
#define WeightFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFormWeight : public TForm
{
__published:	// IDE-managed Components
	TEdit *EWeight;
	TButton *Button1;
	TButton *BTCancel;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BTCancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormWeight(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWeight *FormWeight;
//---------------------------------------------------------------------------
#endif
