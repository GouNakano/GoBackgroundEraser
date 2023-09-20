//---------------------------------------------------------------------------
#ifndef BGEraserDefH
#define BGEraserDefH
#include <vcl.h>
//---------------------------------------------------------------------------
class BGE
{
public:
    //�V�X�e����
	static const wchar_t *SYSTEM_NAME;
private:
	//���s�t�@�C���̃f�B���N�g���𓾂�
	static String getExeDir();
public:
	//�E�B���h�E�̈ʒu���Z�b�g
	static bool setWindowPos(TForm *Form,bool IsKeepWindowSize=false);
	//�E�B���h�E�̈ʒu���L�^
	static bool saveWindowPos(TForm *Form,bool IsTopLeftOnly=false);
	//�u���V�̑����𓾂�
	static int getThickness();
	//�u���V�̑������Z�b�g
	static bool setThickness(int tn);
	//�t�@�C���o�[�W�������̎擾
	static String GetFileVer();
};

#endif