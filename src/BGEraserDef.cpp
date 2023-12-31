//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Win.Registry.hpp>
#pragma hdrstop

#include <memory>
#include "BGEraserDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//システム名
const wchar_t *BGE::SYSTEM_NAME = L"GoBackgroundEraser";

//IniﾌｧｲﾙSection名
const wchar_t *INI_DEF_STANDARD = L"STANDARD";  //標準定義
const wchar_t *INI_DEF_WINPOS   = L"WINPOS";    //ウィンドウの位置

//ウィンドウの状態(メインウィンドウ)
const wchar_t *INI_WINLEFT     = L"WIN_LEFT";       //Window-Left
const wchar_t *INI_WINTOP      = L"WIN_TOP";        //Window-Top
const wchar_t *INI_WINWIDTH    = L"WIN_WIDTH";      //Window-Width
const wchar_t *INI_WINHEIGHT   = L"WIN_HEIGHT";     //Window-Height
const wchar_t *INI_WINMAXSIZE  = L"WIN_MAX";        //Window-Maxsize

//各パラメータ
const wchar_t *INI_THICKNESS   = L"THICKNESS";      //ブラシの太さ

//iniファイル名
const wchar_t *INI_INIFILENAME = L"bge.ini";


//-------------------------------------------------------------
//実行ファイルのディレクトリを得る
//-------------------------------------------------------------
String BGE::getExeDir()
{
	//実行ファイルのディレクトリ
	String exe_dir = ExtractFilePath(ParamStr(0));

	return exe_dir;
}
//-------------------------------------------------------------
//ウィンドウの位置をセット
//-------------------------------------------------------------
bool BGE::setWindowPos(TForm *Form,bool IsKeepWindowSize)
{
	int               WinLeft;
	int               WinTop;
	int               WinWidth;
	int               WinHeight;
	String            Section;
	std::unique_ptr<TIniFile> pIni;

	//フォームのNameを得る(大文字)
	String FrmName = Form->Name.UpperCase();

	//フォーム関連関連アクセス
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
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
bool BGE::saveWindowPos(TForm *Form,bool IsTopLeftOnly)
{
	String                    Section;
	std::unique_ptr<TIniFile> pIni;
	//フォームのNameを得る(大文字)
	String FrmName = Form->Name.UpperCase();

	//フォーム関連関連アクセス
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
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
//-------------------------------------------------------------
//ブラシの太さを得る
//-------------------------------------------------------------
int BGE::getThickness()
{
	int                       thickness;
	String                    Section;
	std::unique_ptr<TIniFile> pIni;

	//フォーム関連関連アクセス
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
	Section = INI_DEF_STANDARD;

	//ブラシの太さを取得
	thickness = pIni->ReadInteger(Section,INI_THICKNESS,2);

	return thickness;
}

//-------------------------------------------------------------
//ブラシの太さをセット
//-------------------------------------------------------------
bool BGE::setThickness(int tn)
{
	String                    Section;
	std::unique_ptr<TIniFile> pIni;

	//フォーム関連関連アクセス
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
	Section = INI_DEF_STANDARD;

	//ブラシの太さを取得
	pIni->WriteInteger(Section,INI_THICKNESS,tn);

	return true;
}
//---------------------------------------------------------------------------
//ファイルバージョン情報の取得
//-------------------------------------------------------------
String BGE::GetFileVer()
{
	typedef struct
	{
		WORD wLanguage;
		WORD wCodePage;
	} LANGANDCODEPAGE, *LPLANGANDCODEPAGE;


	VS_FIXEDFILEINFO vffi;           // バージョン情報を受け取る構造体
	wchar_t          ExeName[512];
	wchar_t          VerOrgStr[512];
	String           VerStr;
	String           BuildStr;
	String           AllVerStr;

	wcscpy(ExeName,Application->ExeName.c_str());
	unsigned int size = GetFileVersionInfoSizeW(ExeName, 0);

	try
	{
		std::unique_ptr<::byte[]> vbuf(new ::byte[size]);

		if (GetFileVersionInfoW(ExeName,0,size,vbuf.get()))
		{
			String strwork;

			void     *buf;
			wchar_t  *pbuf;

			VerQueryValue(vbuf.get(),TEXT("\\"),&buf,&size);   // バージョンを取得
			CopyMemory( &vffi, buf, sizeof(VS_FIXEDFILEINFO)); //コピー

			LPLANGANDCODEPAGE lplgcode;
			UINT unLen;
			BOOL bret = VerQueryValueW(vbuf.get(),L"\\VarFileInfo\\Translation",(LPVOID *)&lplgcode, &unLen);

			if(bret == FALSE)
			{
				return "";
			}
			for( UINT i = 0;i < unLen / sizeof( LANGANDCODEPAGE); i++)
			{
				strwork.sprintf(L"\\StringFileInfo\\%04x%04x\\FileVersion",lplgcode[i].wLanguage, lplgcode[i].wCodePage);
				VerQueryValueW(vbuf.get(),strwork.c_str(),(LPVOID *)&pbuf, &unLen);
				if( unLen > 0)
				{
					wcscpy(VerOrgStr,pbuf);
					break;
				}
			}
		}
	}
	__finally
	{
	}

	//右から.を検索
	wchar_t *p = wcsrchr(VerOrgStr,L'.');
	//バージョンの分離
	if(p != nullptr)
	{
		*p       = '\0';
		VerStr   = VerOrgStr;
		BuildStr = (p+1);
	}
	//表示
	if(VerStr != "" && BuildStr != "")
	{
		AllVerStr = String("Version ") + VerStr + " Build(" + BuildStr +")";
	}
	else
	{
		AllVerStr = String("Version 0.10");
	}
	return AllVerStr;
}

