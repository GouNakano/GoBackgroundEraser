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
//URL�̃��x���N���b�N
// -------------------------------------------------------------
void __fastcall THelpForm::BGELabelClick(TObject *Sender)
{
	TLabel *L = (TLabel*)Sender;

	::ShellExecuteW(Handle, L"open", L->Caption.c_str(), L"", L"", SW_SHOW);
}
// ---------------------------------------------------------------------------
//�t�H�[���L�[�v���r���[
// -------------------------------------------------------------
void __fastcall THelpForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	// ESC�������̃N���[�Y
	if (Key == '\x1b')
	{
		Close();
	}
}
//---------------------------------------------------------------------------
