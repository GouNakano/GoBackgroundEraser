// ----------------------------------------------------------------------------
#ifndef VersionInfH
#define VersionInfH
// ----------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <StdActns.hpp>

// ----------------------------------------------------------------------------
class TAboutBox : public TForm {
__published:
	TButton *OKButton;
	TLabel *TitleLabel;
	TLabel *URLLabel;
	TLabel *Label7;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TShape *Shape1;
	TLabel *VersionLabel;
	TImage *Image1;

	void __fastcall URLLabelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall FormCreate(TObject *Sender);

private:
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
};

// ----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
// ----------------------------------------------------------------------------
#endif
