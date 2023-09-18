//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Win.Registry.hpp>
#pragma hdrstop

#include <memory>
#include "BGEraserDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//IniﾌｧｲﾙSection名
const wchar_t *INI_DEF_STANDARD = L"STANDARD";  //標準定義
const wchar_t *INI_DEF_WINPOS   = L"WINPOS";    //ウィンドウの位置

//ドッキング情報
const wchar_t *INI_DOK_BTOMHEIGHT = L"DOCK_BTOMHEIGHT";  //下パネルの高さ
const wchar_t *INI_DOK_LEFTWIDTH  = L"DOCK_LEFTWIDTH";   //左パネルの幅
//表示系
const wchar_t *INI_MINIMIZERUN       = L"MINIMIZE_RUN";        //最小化して起動
const wchar_t *INI_MINIMIZETRAYICON  = L"MINIMIZE_TRAY_ICON";  //最小化時タスクトレイアイコンに格納
const wchar_t *INI_WINME             = L"DESKTOP_DISP_PROC";   //「デスクトップに画面が残る」に対する対応

//ウィンドウの状態(メインウィンドウ)
const wchar_t *INI_WINLEFT     = L"WIN_LEFT";       //Window-Left
const wchar_t *INI_WINTOP      = L"WIN_TOP";        //Window-Top
const wchar_t *INI_WINWIDTH    = L"WIN_WIDTH";      //Window-Width
const wchar_t *INI_WINHEIGHT   = L"WIN_HEIGHT";     //Window-Height
const wchar_t *INI_WINMAXSIZE  = L"WIN_MAX";        //Window-Maxsize

//iniファイル名
const wchar_t *INI_INIFILENAME = L"bge.ini";


namespace BGE
{

//-------------------------------------------------------------
//ウィンドウの位置をセット
//-------------------------------------------------------------
bool SetWindowPos(TForm *Form,bool IsKeepWindowSize)
{
	int               WinLeft;
	int               WinTop;
	int               WinWidth;
	int               WinHeight;
	String            Section;
	std::unique_ptr<TRegistryIniFile> pIni;

	//フォームのNameを得る(大文字)
	String FrmName = Form->Name.UpperCase();

	//フォーム関連関連アクセス
	pIni.reset(new TRegistryIniFile(INI_DEF_WINPOS));
	Section = INI_DEF_WINPOS;

	//位置を取得
	WinLeft   = pIni->ReadInteger(Section,FrmName + INI_WINLEFT  ,-999);
	WinTop    = pIni->ReadInteger(Section,FrmName + INI_WINTOP   ,   0);
	WinWidth  = pIni->ReadInteger(Section,FrmName + INI_WINWIDTH ,   0);
	WinHeight = pIni->ReadInteger(Section,FrmName + INI_WINHEIGHT,   0);
	//ウィンドウ位置セット
	if(WinLeft != -999)
	{
		//フォーム位置セット
		Form->Left     = WinLeft;
		Form->Top      = WinTop;
		if(IsKeepWindowSize == false)
		{
			Form->Width    = WinWidth;
			Form->Height   = WinHeight;
		}
	}
	else
	{
		//フォームを中央に配置
		Form->Left  = (Screen->WorkAreaWidth  - Form->Width) / 2;
		Form->Top   = (Screen->WorkAreaHeight - Form->Width) / 2;
	}
	//Topの補正
	if(Form->Top < 50)
	{
		Form->Top = 100;
	}
	return true;
}

//-------------------------------------------------------------
//ウィンドウの位置を記録
//-------------------------------------------------------------
bool SaveWindowPos(TForm *Form,bool IsTopLeftOnly)
{
	String                            Section;
	std::unique_ptr<TRegistryIniFile> pIni;
	//フォームのNameを得る(大文字)
	String FrmName = Form->Name.UpperCase();

	//フォーム関連関連アクセス
	pIni.reset(new TRegistryIniFile(INI_DEF_WINPOS));
	Section = INI_DEF_WINPOS;

	//位置を設定
	pIni->WriteInteger(Section,FrmName + INI_WINLEFT  ,Form->Left  );
	pIni->WriteInteger(Section,FrmName + INI_WINTOP   ,Form->Top   );
	//幅、高さの設定
	if(IsTopLeftOnly == false)
	{
		pIni->WriteInteger(Section,FrmName + INI_WINWIDTH ,Form->Width );
		pIni->WriteInteger(Section,FrmName + INI_WINHEIGHT,Form->Height);
	}
	return true;
}

} //BGE