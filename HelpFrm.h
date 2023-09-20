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
__published:	// IDE �ŊǗ������R���|�[�l���g
	TMemo *Memo1;
	TLabel *BGELabel;
	TShape *Shape1;
	TButton *OKButton;
	void __fastcall BGELabelClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
private:	// ���[�U�[�錾
public:		// ���[�U�[�錾
	__fastcall THelpForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THelpForm *HelpForm;
//---------------------------------------------------------------------------
#endif
