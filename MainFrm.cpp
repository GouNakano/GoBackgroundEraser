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
	BGEraser.getOutputMat(original_mat);
	makeDrawMatFromOrignalMat();
	//描画更新
	updateDispFromDrawMat();
	//元画像を得る
	BGEraser.getOriginalMat(original_mat);
	//元マスクを得る
	BGEraser.getOriginalMaskMat(original_mask_mat);
	//元画像の表示画像を作成する
	makeDrawMatFromOrignalMat();
	//作業用マスクMatを作成する
	disp_mask_mat = original_mask_mat.clone();
	//描画用Matで表示更新
	updateDispFromDrawMat();
	//マウスイベントの送信先設定
	cv::setMouseCallback("output",TMainForm::onmouse,this);
	//モード表示
	dispMode("GoBackgroundEraser起動");

//Timer->Enabled = true;
}
//-------------------------------------------------
//背景削除表示更新ボタン
//-------------------------------------------------
void __fastcall TMainForm::updateBtnClick(TObject *Sender)
{
	//状態表示
	dispMode("背景除去画像表示更新中");
	//表示用マスクをオリジナルの大きさにする
	disp_mask_mat.copyTo(BGEraser.mask);
	//背景削除を進める
	if(BGEraser.segmentImage() == false)
	{
		//失敗状態表示
		dispMode("背景除去画像表示更新失敗");
	}
	//背景除去結果画像を取得
	BGEraser.getOutputMat(original_mat);
	//背景除去結果マスクを取得
	BGEraser.getOutputMasktMat(original_mask_mat);
	//元画像の表示画像を作成する
	makeDrawMatFromOrignalMat();
	//作業用マスクMatを作成する
	disp_mask_mat = original_mask_mat.clone();
	//描画用Matで表示更新
	updateDispFromDrawMat();
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
	//元画像の表示画像を作成する
	makeDrawMatFromOrignalMat();
	//描画用Matで表示更新
	updateDispFromDrawMat();
}
//-------------------------------------------------
//画像の表示の大きさに合わせた描画用画像を作成する
//-------------------------------------------------
void TMainForm::makeDrawMatFromOrignalMat()
{
	//元画像の有効性チェック
	if(original_mat.rows > 0 && original_mat.cols > 0)
	{
		//親パネルのサイズ
		int w = MainPanel->Width;
		int h = MainPanel->Height;
		win_sz = {MainPanel->Width,MainPanel->Height};
		//表示用Matにリサイズ
		cv::resize(original_mat,disp_mat,win_sz);
	}
}
//-------------------------------------------------
//描画用Matで表示更新
//-------------------------------------------------
void TMainForm::updateDispFromDrawMat()
{
	if(original_mat.rows == 0 || original_mat.cols == 0)
	{
		//親パネルのサイズ
		int w = MainPanel->Width;
		int h = MainPanel->Height;
		win_sz = {MainPanel->Width,MainPanel->Height};
		//黒の表示用Mat作成
		disp_mat = cv::Mat::zeros(win_sz,CV_8UC3);
	}
	//描画更新
	cv::imshow("output",disp_mat);
	cv::waitKey(1);
}
//-------------------------------------------------
//表示用矩形を元画像の大きさに合わせる
//-------------------------------------------------
bool TMainForm::adjustRectFromDrawRect(const cv::Rect& draw_rect,cv::Rect& adjust_rect)
{
	if(original_mat.rows == 0 || original_mat.cols == 0)
	{
		return false;
	}
	if(draw_rect.width < 1 || draw_rect.height < 1)
	{
		return false;
	}
	//比率を算出
	double w_ratio = static_cast<double>(original_mat.cols) / static_cast<double>(MainPanel->Width);
	double h_ratio = static_cast<double>(original_mat.rows) / static_cast<double>(MainPanel->Height);
	//Rect更新
	adjust_rect.x      = static_cast<int>(draw_rect.x      * w_ratio);
	adjust_rect.y      = static_cast<int>(draw_rect.y      * h_ratio);
	adjust_rect.width  = static_cast<int>(draw_rect.width  * w_ratio);
	adjust_rect.height = static_cast<int>(draw_rect.height * h_ratio);

	return true;
}
//-------------------------------------------------
//表示用画像を元画像の大きさに合わせる
//-------------------------------------------------
bool TMainForm::adjustDispMatFromDrawMat(const cv::Mat& draw_mat,cv::Mat& adjust_mat)
{
	if(draw_mat.rows == 0 || draw_mat.cols == 0)
	{
		return false;
	}
	//リサイズ
	cv::resize(draw_mat,adjust_mat,original_mat.size());

	return true;
}
//-------------------------------------------------
//表示用画像から元画像への座標変換
//-------------------------------------------------
bool TMainForm::adjustOriginalPointFromDrawPoint(const cv::Point& draw_point,cv::Point& adjust_point)
{
	//比率を算出
	double w_ratio = static_cast<double>(original_mat.cols) / static_cast<double>(MainPanel->Width);
	double h_ratio = static_cast<double>(original_mat.rows) / static_cast<double>(MainPanel->Height);
	//座標を変換する
	adjust_point.x = static_cast<int>(draw_point.x * w_ratio);
	adjust_point.y = static_cast<int>(draw_point.y * h_ratio);

	return true;
}
//---------------------------------------------------------------------------
//マウスイベント
//-------------------------------------------------
void TMainForm::onmouse(int event,int x,int y,int flags,void *param)
{
	//自身を得る
	TMainForm *pMainFrm = static_cast<TMainForm *>(param);
	TBGEraser *pMe      = static_cast<TBGEraser *>(&pMainFrm->BGEraser);

	//各マウスボタンごとの処理
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		if(pMe->rect_or_mask == TBGEraser::tmRect)
		{
			if(pMe->getDrawing() == false)
			{
				pMainFrm->ix = x;
				pMainFrm->iy = y;
				//元画像の表示画像を作成する
				pMainFrm->makeDrawMatFromOrignalMat();
				//メイン表示パネルの表示更新
				pMainFrm->updateDispFromDrawMat();
				//描画中にする
				pMe->setDrawing(true);
			}
		}
		else
		{
			//描画中にする
			pMe->setDrawing(true);
			//描画更新
			cv::circle(pMainFrm->disp_mat,cv::Point(x,y),pMe->getThickness(),pMe->value.color,-1);
			//マスク更新
			cv::Point adjust_point;
			pMainFrm->adjustOriginalPointFromDrawPoint(cv::Point(x,y),adjust_point);
			cv::circle(pMainFrm->disp_mask_mat,adjust_point,pMe->getThickness(),pMe->value.val,-1);
			//メイン表示パネルの表示更新
			pMainFrm->updateDispFromDrawMat();
		}
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(pMe->rect_or_mask == TBGEraser::tmRect)
		{
			if(pMe->getDrawing() == true)
			{
				//元画像の表示画像を作成する
				pMainFrm->makeDrawMatFromOrignalMat();
				//矩形を描く
				cv::rectangle(pMainFrm->disp_mat,cv::Point(pMainFrm->ix,pMainFrm->iy),cv::Point(x,y),pMe->DRAW_RECTANGLE.color,2);
				pMe->rect_or_mask = TBGEraser::tmRect;
				//メイン表示パネルの表示更新
				pMainFrm->updateDispFromDrawMat();
			}
		}
		else
		{
			if(pMe->getDrawing() == true)
			{
				//描画更新
				cv::circle(pMainFrm->disp_mat,cv::Point(x,y),pMe->getThickness(),pMe->value.color,-1);
				//マスク更新
				cv::Point adjust_point;
				pMainFrm->adjustOriginalPointFromDrawPoint(cv::Point(x,y),adjust_point);
				cv::circle(pMainFrm->disp_mask_mat,adjust_point,pMe->getThickness(),pMe->value.val,-1);
				//メイン表示パネルの表示更新
				pMainFrm->updateDispFromDrawMat();
			}
		}
	}
	else if(event == cv::EVENT_LBUTTONUP)
	{
		if(pMe->rect_or_mask == TBGEraser::tmRect)
		{
			//描画終了
			pMe->setDrawing(false);

			//選択矩形の大きさを補正して渡す
			cv::Rect sel_rect;
			cv::Rect adj_rect;

			sel_rect = cv::Rect(std::min(pMainFrm->ix,x),std::min(pMainFrm->iy,y),abs(pMainFrm->ix-x),abs(pMainFrm->iy-y));

			//表示用矩形を元画像の大きさに合わせる
			if(pMainFrm->adjustRectFromDrawRect(sel_rect,adj_rect) == true)
			{
				cv::rectangle(pMe->img,adj_rect,pMe->DRAW_RECTANGLE.color,2);
				pMe->rect         = adj_rect;
				pMe->rect_or_mask = TBGEraser::tmRect;
				pMe->updateMaskAndOutputImage();
			}
		}
		else
		{
			if(pMe->getDrawing() == true)
			{
				pMe->setDrawing(false);
				//描画更新
				cv::circle(pMainFrm->disp_mat,cv::Point(x,y),pMe->getThickness(),pMe->value.color,-1);
				//マスク更新
				cv::Point adjust_point;
				pMainFrm->adjustOriginalPointFromDrawPoint(cv::Point(x,y),adjust_point);
				cv::circle(pMainFrm->disp_mask_mat,adjust_point,pMe->getThickness(),pMe->value.val,-1);
				//メイン表示パネルの表示更新
				pMainFrm->updateDispFromDrawMat();
			}
		}
	}
}
//---------------------------------------------------------------------------

