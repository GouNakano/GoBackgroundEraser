// ---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "BGEraserDef.h"
#include "VersionInf.h"
// ---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;

// ---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner) : TForm(AOwner)
{
}
// ---------------------------------------------------------------------------
//ﾌｫｰﾑ作成時
// -------------------------------------------------------------
void __fastcall TAboutBox::FormCreate(TObject *Sender)
{
	//
}
// ---------------------------------------------------------------------------
//ﾌｫｰﾑ表示時
// -------------------------------------------------------------
void __fastcall TAboutBox::FormShow(TObject *Sender)
{
	String VerStr;
	String BuildStr;
	//ファイルバージョン情報の取得
	String file_ver = BGE::GetFileVer();

	// タイトルとバージョンを表示
	TitleLabel  ->Caption = String(BGE::SYSTEM_NAME);
	VersionLabel->Caption = file_ver;
}
// ---------------------------------------------------------------------------
//URLのラベルクリック
// -------------------------------------------------------------
void __fastcall TAboutBox::URLLabelClick(TObject *Sender)
{
	TLabel *L = (TLabel*)Sender;

	::ShellExecuteW(Handle, L"open", L->Caption.c_str(), L"", L"", SW_SHOW);
}
// ---------------------------------------------------------------------------
//フォームキープレビュー
// -------------------------------------------------------------
void __fastcall TAboutBox::FormKeyPress(TObject *Sender, char &Key)
{
	// ESC押下時のクローズ
	if (Key == '\x1b')
	{
		Close();
	}
}
// -------------------------------------------------------------
