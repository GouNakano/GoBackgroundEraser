//---------------------------------------------------------------------------
#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <stack>
#include "TBGEraser.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TMainMenu *MainMenu;
	TMenuItem *N1;
	TMenuItem *ZZZZZ1;
	TPanel *MenuPanel;
	TBitBtn *updateBtn;
	TBitBtn *saveBtn;
	TBitBtn *undoBtn;
	TBitBtn *specifyBGBtn;
	TBitBtn *specifyFGBtn;
	TBitBtn *dispOrigImgBtn;
	TBitBtn *LoadImageBtn;
	TBitBtn *SelRectBtn;
	TPanel *Panel2;
	TLabel *ModeLabel;
	TPanel *Panel3;
	TBitBtn *EndBtn;
	TPanel *Panel1;
	TStatusBar *StatusBar1;
	TPanel *MainPanel;
	TOpenPictureDialog *OpenPictureDialog;
	TMenuItem *N6;
	TMenuItem *UndoMemu;
	TMenuItem *N2;
	TMenuItem *UpdateMenu;
	void __fastcall ZZZZZ1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LoadImageBtnClick(TObject *Sender);
	void __fastcall SelRectBtnClick(TObject *Sender);
	void __fastcall specifyBGBtnClick(TObject *Sender);
	void __fastcall specifyFGBtnClick(TObject *Sender);
	void __fastcall dispOrigImgBtnClick(TObject *Sender);
	void __fastcall undoBtnClick(TObject *Sender);
	void __fastcall saveBtnClick(TObject *Sender);
	void __fastcall updateBtnClick(TObject *Sender);
	void __fastcall EndBtnClick(TObject *Sender);
	void __fastcall UndoMemuClick(TObject *Sender);
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
	//元に戻すを実現するためのスタック
	std::stack<std::tuple<cv::Mat,cv::Mat,TBGEraser::typMode>> histStack;
private:
	//モード表示
	void dispMode(const std::string& mode_str);
	//元画像の表示画像を作成する
	void makeDrawMatFromOrignalMat();
	//表示用矩形を元画像の大きさに合わせる
	bool adjustRectFromDrawRect(const cv::Rect& draw_rect,cv::Rect& adjust_rect);
	//描画用Matで表示更新
	void updateDispFromDrawMat();
	//表示用画像から元画像への座標変換
	bool adjustOriginalPointFromDrawPoint(const cv::Point& draw_point,cv::Point& adjust_point);
	//wstringからstringに変換
	std::string wstring2string(const std::wstring& wstr);
public:
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
