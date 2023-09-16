//---------------------------------------------------------------------------
#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "TBGEraser.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TPanel *MenuPanel;
	TLabel *ModeLabel;
	TBitBtn *updateBtn;
	TBitBtn *saveBtn;
	TBitBtn *resetBtn;
	TBitBtn *specifyBGBtn;
	TBitBtn *specifyFGBtn;
	TMainMenu *MainMenu;
	TMenuItem *F1;
	TMenuItem *E1;
	TMenuItem *H1;
	TPanel *Panel1;
	TStatusBar *StatusBar1;
	TPanel *MainPanel;
	TTimer *Timer;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall updateBtnClick(TObject *Sender);
	void __fastcall saveBtnClick(TObject *Sender);
	void __fastcall resetBtnClick(TObject *Sender);
	void __fastcall specifyBGBtnClick(TObject *Sender);
	void __fastcall specifyFGBtnClick(TObject *Sender);
	void __fastcall MainPanelResize(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
private:
	//マウスイベント
	static void onmouse(int event,int x,int y,int flags,void *param);
private:
	TBGEraser BGEraser;
	HWND      hWnd1;
	HWND      hWnd1_parent;
	//ウィンドウサイズ
	cv::Size win_sz;
private:
	int      ix;
	int      iy;
	cv::Rect rect;
	cv::Mat  disp_mat;
	cv::Mat  disp_mask_mat;
	cv::Mat  original_mat;
	cv::Mat  original_mask_mat;
private:
	//モード表示
	void dispMode(const std::string& mode_str);
	//元画像の表示画像を作成する
	void makeDrawMatFromOrignalMat();
	//描画用Matで表示更新
	void updateDispFromDrawMat();
	//表示用矩形を元画像の大きさに合わせる
	bool adjustRectFromDrawRect(const cv::Rect& draw_rect,cv::Rect& adjust_rect);
	//表示用画像を元画像の大きさに合わせる
	bool adjustDispMatFromDrawMat(const cv::Mat& draw_mat,cv::Mat& adjust_mat);
	//表示用画像から元画像への座標変換
	bool adjustOriginalPointFromDrawPoint(const cv::Point& draw_point,cv::Point& adjust_point);
public:
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
