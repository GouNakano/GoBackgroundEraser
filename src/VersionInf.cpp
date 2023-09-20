// ---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BGEraserDef.h"
#include "VersionInf.h"
// ---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;

// ---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner) : TForm(AOwner)
{
}
// ---------------------------------------------------------------------------
//̫�э쐬��
// -------------------------------------------------------------
void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
	//
}
// ---------------------------------------------------------------------------
//̫�ѕ\����
// -------------------------------------------------------------
void __fastcall TAboutBox::FormShow(TObject *Sender)
{
	String VerStr;
	String BuildStr;
	//�t�@�C���o�[�W�������̎擾
	String file_ver = BGE::GetFileVer();

	// �^�C�g���ƃo�[�W������\��
	TitleLabel  ->Caption = String(BGE::SYSTEM_NAME);
	VersionLabel->Caption = file_ver;
}
// ---------------------------------------------------------------------------
//URL�̃��x���N���b�N
// -------------------------------------------------------------
void __fastcall TAboutBox::URLLabelClick(TObject *Sender)
{
	TLabel *L = (TLabel*)Sender;

	::ShellExecuteW(Handle, L"open", L->Caption.c_str(), L"", L"", SW_SHOW);
}
// ---------------------------------------------------------------------------
//�t�H�[���L�[�v���r���[
// -------------------------------------------------------------
void __fastcall TAboutBox::FormKeyPress(TObject *Sender, char &Key)
{
	// ESC�������̃N���[�Y
	if (Key == '\x1b')
	{
		Close();
	}
}
// -------------------------------------------------------------
