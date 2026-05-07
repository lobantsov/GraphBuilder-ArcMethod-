//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WeightForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormWeight *FormWeight;
//---------------------------------------------------------------------------
__fastcall TFormWeight::TFormWeight(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormWeight::Button1Click(TObject *Sender)
{
	this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormWeight::BTCancelClick(TObject *Sender)
{
	this->ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void __fastcall TFormWeight::FormShow(TObject *Sender)
{
	EWeight->Text = "";
}
//---------------------------------------------------------------------------

