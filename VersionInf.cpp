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
// �@�\     �F̫�э쐬��
//
// �֐���` �Fvoid __fastcall FormCreate(TObject *Sender)
//
// �������� �F__published
//
// ����     �F
//
// �߂�l   �F
//
// �쐬�ҁ@ �F
//
// �����   �F
// -------------------------------------------------------------
void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
	//
}
// ---------------------------------------------------------------------------
// �@�\     �F̫�ѕ\����
//
// �֐���` �Fvoid __fastcall FormShow(TObject *Sender)
//
// �������� �F__published
//
// ����     �F
//
// �߂�l   �F
//
// �쐬�ҁ@ �F
//
// �����   �F
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
// �@�\     �F�z�[���y�[�W�̃��x���N���b�N
//
// �֐���` �Fvoid __fastcall URLLabelClick(TObject *Sender)
//
// �������� �F__published
//
// ����     �F
//
// �߂�l   �F
//
// �쐬�ҁ@ �F
//
// �����   �F
// -------------------------------------------------------------
void __fastcall TAboutBox::URLLabelClick(TObject *Sender)
{
	TLabel *L = (TLabel*)Sender;

	::ShellExecuteW(Handle, L"open", L->Caption.c_str(), L"", L"", SW_SHOW);
}
// ---------------------------------------------------------------------------
// �@�\     �F�t�H�[���L�[�v���r���[
//
// �֐���` �Fvoid __fastcall FormKeyPress(TObject *Sender, char &Key)
//
// �������� �F__published
//
// ����     �F
//
// �߂�l   �F
//
// �쐬�ҁ@ �F
//
// �����   �F
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