//---------------------------------------------------------------------------
#ifndef BGEraserDefH
#define BGEraserDefH
#include <vcl.h>
//---------------------------------------------------------------------------
class BGE
{
public:
    //システム名
	static const wchar_t *SYSTEM_NAME;
private:
	//実行ファイルのディレクトリを得る
	static String getExeDir();
public:
	//ウィンドウの位置をセット
	static bool setWindowPos(TForm *Form,bool IsKeepWindowSize=false);
	//ウィンドウの位置を記録
	static bool saveWindowPos(TForm *Form,bool IsTopLeftOnly=false);
	//ブラシの太さを得る
	static int getThickness();
	//ブラシの太さをセット
	static bool setThickness(int tn);
	//ファイルバージョン情報の取得
	static String GetFileVer();
};

#endif
