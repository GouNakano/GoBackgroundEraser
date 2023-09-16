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
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TBitBtn *updateBtn;
	TBitBtn *saveBtn;
	TBitBtn *resetBtn;
	TLabel *ModeLabel;
	TBitBtn *specifyBGBtn;
	TBitBtn *specifyFGBtn;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall updateBtnClick(TObject *Sender);
	void __fastcall saveBtnClick(TObject *Sender);
	void __fastcall resetBtnClick(TObject *Sender);
	void __fastcall specifyBGBtnClick(TObject *Sender);
	void __fastcall specifyFGBtnClick(TObject *Sender);
private:
	TBGEraser BGEraser;
private:
	//モード表示
	void dispMode(const std::string& mode_str);
public:
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
