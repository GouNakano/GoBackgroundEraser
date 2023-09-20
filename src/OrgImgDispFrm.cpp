//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BGEraserDef.h"
#include "OrgImgDispFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOrgImgDispForm *OrgImgDispForm;
//---------------------------------------------------------------------------
__fastcall TOrgImgDispForm::TOrgImgDispForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//フォーム作成時
//---------------------------------------------------------------------------
void __fastcall TOrgImgDispForm::FormCreate(TObject *Sender)
{
	//表示ウィンドウ
	cv::namedWindow("orgimg");
	//ウィンドウの結合
	hWnd1        = (HWND)cvGetWindowHandle("orgimg");
	hWnd1_parent = ::GetParent(hWnd1);
	::SetParent(hWnd1,ImageBasePanel->Handle);
	::ShowWindow(hWnd1_parent,SW_HIDE);
	//ウィンドウの位置をセット
	BGE::setWindowPos(this);
}
//---------------------------------------------------------------------------
//フォーム表示時
//---------------------------------------------------------------------------
void __fastcall TOrgImgDispForm::FormShow(TObject *Sender)
{
	//画像の表示の大きさに合わせた描画用画像を作成する
	makeDrawMatFromOrignalMat();
	//描画用Matで表示更新
	updateDispFromDrawMat();
}
//---------------------------------------------------------------------------
//表示画像のMatを設定
//---------------------------------------------------------------------------
bool TOrgImgDispForm::setDisplayMat(const cv::Mat& disp_mat)
{
	imageMat = disp_mat.clone();

    return true;
}
//---------------------------------------------------------------------------
//描画用Matで表示更新
//---------------------------------------------------------------------------
void TOrgImgDispForm::updateDispFromDrawMat()
{
	if(displayMat.rows == 0 || displayMat.cols == 0)
	{
		//親パネルのサイズ
		win_sz = {ImageBasePanel->Width,ImageBasePanel->Height};
		//黒の表示用Mat作成
		displayMat = cv::Mat::zeros(win_sz,CV_8UC3);
	}
	//描画更新
	cv::imshow("orgimg",displayMat);
	cv::waitKey(1);
}
//---------------------------------------------------------------------------
//画像表示パネルのサイズ変更
//---------------------------------------------------------------------------
void __fastcall TOrgImgDispForm::ImageBasePanelResize(TObject *Sender)
{
	//元画像の表示画像を作成する
	makeDrawMatFromOrignalMat();
	//描画用Matで表示更新
	updateDispFromDrawMat();
}
//---------------------------------------------------------------------------
//画像の表示の大きさに合わせた描画用画像を作成する
//---------------------------------------------------------------------------
void TOrgImgDispForm::makeDrawMatFromOrignalMat()
{
	//元画像の有効性チェック
	if(imageMat.rows > 0 && imageMat.cols > 0)
	{
		//親パネルのサイズ
		win_sz = {ImageBasePanel->Width,ImageBasePanel->Height};
		//表示用Matにリサイズ
		cv::resize(imageMat,displayMat,win_sz);
	}
}
//---------------------------------------------------------------------------
//フォームを閉じる前
//---------------------------------------------------------------------------
void __fastcall TOrgImgDispForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	//ウィンドウの位置を記録
	BGE::saveWindowPos(this);
}
//---------------------------------------------------------------------------

