//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
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
#include "TBGEraser.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TMainMenu *MainMenu1;
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
	TMainMenu *MainMenu;
	TMenuItem *F1;
	TMenuItem *LoadImageMenu;
	TMenuItem *MenuItem1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *EndMenu;
	TMenuItem *E1;
	TMenuItem *undoMenu;
	TMenuItem *N5;
	TMenuItem *UpdateMenu;
	TMenuItem *H1;
	TMenuItem *N4;
	TMenuItem *aaaaaa1;
	TOpenPictureDialog *OpenPictureDialog;
	void __fastcall ZZZZZ1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:
	TBGEraser BGEraser;
	HWND      hWnd1;
	HWND      hWnd1_parent;
	//�E�B���h�E�T�C�Y
	cv::Size win_sz;
private:
	int      ix;
	int      iy;
	cv::Rect rect;
	cv::Mat  disp_mat;
	cv::Mat  disp_mask_mat;
	cv::Mat  original_mat;
	cv::Mat  original_mask_mat;
public:
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif