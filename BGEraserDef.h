//---------------------------------------------------------------------------
#ifndef BGEraserDefH
#define BGEraserDefH
//---------------------------------------------------------------------------
namespace BGE
{
	//�E�B���h�E�̈ʒu���Z�b�g
	bool SetWindowPos(TForm *Form,bool IsKeepWindowSize=false);
	//�E�B���h�E�̈ʒu���L�^
	bool SaveWindowPos(TForm *Form,bool IsTopLeftOnly=false);
}

#endif
