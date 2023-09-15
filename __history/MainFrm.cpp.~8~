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
	//初期化
	PressKey = 0;
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
	BGEraser.run(PressKey);
	//押下したキーを初期化
	PressKey = 0;
	//背景削除タイマー再開
	BGEraseTimer->Enabled = true;
}
//-------------------------------------------------
//キーダウンイベント
//-------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	PressKey = (Key & 0xFF);
}
//-------------------------------------------------
//背景削除表示更新ボタン
//-------------------------------------------------
void __fastcall TMainForm::updateBtnClick(TObject *Sender)
{
	PressKey = 'N';
}
//---------------------------------------------------------------------------

