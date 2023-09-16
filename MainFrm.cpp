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
	//ウィンドウの結合
	hWnd1        = (HWND)cvGetWindowHandle("output");
	hWnd1_parent = ::GetParent(hWnd1);
	::SetParent(hWnd1,MainPanel->Handle);
	::ShowWindow(hWnd1_parent,SW_HIDE);
	win_sz = {MainPanel->Width,MainPanel->Height};
	//出力表示Mat作成
	cv::Mat dispMat;
	BGEraser.getOutputMat(dispMat);
	cv::resize(dispMat,dispMat,win_sz);
	//描画更新
	BGEraser.updateDisplayWindow();
	cv::imshow("output",dispMat);
	cv::waitKey(30);
	//モード表示
	dispMode("GoBackgroundEraser起動");

Timer->Enabled = true;
}
//-------------------------------------------------
//背景削除表示更新ボタン
//-------------------------------------------------
void __fastcall TMainForm::updateBtnClick(TObject *Sender)
{
	//状態表示
	dispMode("背景除去画像表示更新中");
	//背景削除を進める
	if(BGEraser.segmentImage() == false)
	{
		//失敗状態表示
		dispMode("背景除去画像表示更新失敗");
	}
	//状態表示
	dispMode("背景除去画像表示更新完了");
}
//-------------------------------------------------
//保存ボタン
//-------------------------------------------------
void __fastcall TMainForm::saveBtnClick(TObject *Sender)
{
	//背景削除画像の保存
	BGEraser.saveBGErasedImage("output.png");
}
//-------------------------------------------------
//リセットボタン
//-------------------------------------------------
void __fastcall TMainForm::resetBtnClick(TObject *Sender)
{
	//編集結果を無効にしてリセットする
	BGEraser.resetState();
}
//-------------------------------------------------
//モード表示
//-------------------------------------------------
void TMainForm::dispMode(const std::string& mode_str)
{
	//状態表示ラベルの文字列更新
	ModeLabel->Caption = mode_str.c_str();
	Application->ProcessMessages();
}
//-------------------------------------------------
//背景指定モードにする
//-------------------------------------------------
void __fastcall TMainForm::specifyBGBtnClick(TObject *Sender)
{
	//背景指定モードにする
	if(BGEraser.setSpecifyBackgroundMode() == true)
	{
		//モード表示
		dispMode("背景指定モード");
	}
}
//-------------------------------------------------
//前景指定モードにする
//-------------------------------------------------
void __fastcall TMainForm::specifyFGBtnClick(TObject *Sender)
{
	//前景指定モードにする
	if(BGEraser.setSpecifyForegroundMode() == true)
	{
		//モード表示
		dispMode("前景指定モード");
	}
}
//-------------------------------------------------
//メイン表示パネルのサイズ変更
//-------------------------------------------------
void __fastcall TMainForm::MainPanelResize(TObject *Sender)
{
	//親パネルのサイズ
	int w = MainPanel->Width;
	int h = MainPanel->Height;
	win_sz = {MainPanel->Width,MainPanel->Height};
	//出力表示Mat作成
	cv::Mat dispMat;
	if(BGEraser.getOutputMat(dispMat) == false)
	{
		//表示内容が空なので処理しない
		return;
	}
	cv::resize(dispMat,dispMat,win_sz);
	//描画更新
	cv::imshow("output",dispMat);
	cv::waitKey(1);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::TimerTimer(TObject *Sender)
{
	//出力表示Mat作成
	cv::Mat dispMat;
	BGEraser.getOutputMat(dispMat);
	cv::resize(dispMat,dispMat,win_sz);
	//描画更新
	BGEraser.updateDisplayWindow();
	cv::imshow("output",dispMat);
	cv::waitKey(1);
}
//---------------------------------------------------------------------------

