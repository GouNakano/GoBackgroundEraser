//---------------------------------------------------------------------------

#ifndef HelpFrmH
#define HelpFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class THelpForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TMemo *Memo1;
	TLabel *BGELabel;
	TShape *Shape1;
	TButton *OKButton;
	void __fastcall BGELabelClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// ユーザー宣言
public:		// ユーザー宣言
	__fastcall THelpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THelpForm *HelpForm;
//---------------------------------------------------------------------------
#endif
