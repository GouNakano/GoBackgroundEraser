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
__published:	// IDE �ŊǗ������R���|�[�l���g
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
	TBGEraser BGEraser;
	HWND      hWnd1;
	HWND      hWnd1_parent;
	//�E�B���h�E�T�C�Y
	cv::Size win_sz;
private:
	//���[�h�\��
	void dispMode(const std::string& mode_str);
public:
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
