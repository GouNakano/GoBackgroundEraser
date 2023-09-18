//---------------------------------------------------------------------------
#ifndef BGEraserDefH
#define BGEraserDefH
//---------------------------------------------------------------------------
namespace BGE
{
	//ウィンドウの位置をセット
	bool SetWindowPos(TForm *Form,bool IsKeepWindowSize=false);
	//ウィンドウの位置を記録
	bool SaveWindowPos(TForm *Form,bool IsTopLeftOnly=false);
}

#endif
