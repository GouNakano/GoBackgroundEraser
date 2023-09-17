//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ZZZZZ1Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	//背景除去オブジェクトの初期化
	BGEraser.init();
	BGEraser.readImage("messi5.png");
	//ウィンドウの結合
	hWnd1        = (HWND)cvGetWindowHandle("output");
	hWnd1_parent = ::GetParent(hWnd1);
	::SetParent(hWnd1,MainPanel->Handle);
	::ShowWindow(hWnd1_parent,SW_HIDE);
	//元画像を得る
	BGEraser.getOriginalMat(original_mat);
	//元マスクを得る
	BGEraser.getOriginalMaskMat(original_mask_mat);
//	//元画像の表示画像を作成する
//	makeDrawMatFromOrignalMat();
//	//作業用マスクMatを作成する
//	disp_mask_mat = original_mask_mat.clone();
//	//描画用Matで表示更新
//	updateDispFromDrawMat();
//	//マウスイベントの送信先設定
//	cv::setMouseCallback("output",TMainForm::onmouse,this);
//	//モード表示
//	dispMode("GoBackgroundEraser起動");

}
//---------------------------------------------------------------------------

