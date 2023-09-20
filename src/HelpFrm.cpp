//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "HelpFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THelpForm *HelpForm;
//---------------------------------------------------------------------------
__fastcall THelpForm::THelpForm(TComponent* Owner)
	: TForm(Owner)
{
}
// ---------------------------------------------------------------------------
//URLのラベルクリック
// -------------------------------------------------------------
void __fastcall THelpForm::BGELabelClick(TObject *Sender)
{
	TLabel *L = (TLabel*)Sender;

	::ShellExecuteW(Handle, L"open", L->Caption.c_str(), L"", L"", SW_SHOW);
}
// ---------------------------------------------------------------------------
//フォームキープレビュー
// -------------------------------------------------------------
void __fastcall THelpForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	// ESC押下時のクローズ
	if (Key == '\x1b')
	{
		Close();
	}
}
//---------------------------------------------------------------------------
