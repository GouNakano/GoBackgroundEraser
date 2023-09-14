//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------------------
//フォームが表示されるとき
//-------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
	//背景除去オブジェクトの初期化
	BGEraser.init("messi5.png");
	//背景削除タイマー起動
	BGEraseTimer->Enabled = true;
}
//-------------------------------------------------
//背景削除タイマー
//-------------------------------------------------
void __fastcall TMainForm::BGEraseTimerTimer(TObject *Sender)
{
	//背景削除タイマー停止
	BGEraseTimer->Enabled = false;
	//入力待ち
	BGEraser.run();
	//背景削除タイマー再開
	BGEraseTimer->Enabled = true;
}
//---------------------------------------------------------------------------

