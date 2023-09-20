//---------------------------------------------------------------------------
#include <vcl.h>
#include <System.Win.Registry.hpp>
#pragma hdrstop

#include <memory>
#include "BGEraserDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//�V�X�e����
const wchar_t *BGE::SYSTEM_NAME = L"GoBackgroundEraser";

//Ini̧��Section��
const wchar_t *INI_DEF_STANDARD = L"STANDARD";  //�W����`
const wchar_t *INI_DEF_WINPOS   = L"WINPOS";    //�E�B���h�E�̈ʒu

//�E�B���h�E�̏��(���C���E�B���h�E)
const wchar_t *INI_WINLEFT     = L"WIN_LEFT";       //Window-Left
const wchar_t *INI_WINTOP      = L"WIN_TOP";        //Window-Top
const wchar_t *INI_WINWIDTH    = L"WIN_WIDTH";      //Window-Width
const wchar_t *INI_WINHEIGHT   = L"WIN_HEIGHT";     //Window-Height
const wchar_t *INI_WINMAXSIZE  = L"WIN_MAX";        //Window-Maxsize

//�e�p�����[�^
const wchar_t *INI_THICKNESS   = L"THICKNESS";      //�u���V�̑���

//ini�t�@�C����
const wchar_t *INI_INIFILENAME = L"bge.ini";


//-------------------------------------------------------------
//���s�t�@�C���̃f�B���N�g���𓾂�
//-------------------------------------------------------------
String BGE::getExeDir()
{
	//���s�t�@�C���̃f�B���N�g��
	String exe_dir = ExtractFilePath(ParamStr(0));

	return exe_dir;
}
//-------------------------------------------------------------
//�E�B���h�E�̈ʒu���Z�b�g
//-------------------------------------------------------------
bool BGE::setWindowPos(TForm *Form,bool IsKeepWindowSize)
{
	int               WinLeft;
	int               WinTop;
	int               WinWidth;
	int               WinHeight;
	String            Section;
	std::unique_ptr<TIniFile> pIni;

	//�t�H�[����Name�𓾂�(�啶��)
	String FrmName = Form->Name.UpperCase();

	//�t�H�[���֘A�֘A�A�N�Z�X
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
	Section = INI_DEF_WINPOS;

	//�ʒu���擾
	WinLeft   = pIni->ReadInteger(Section,FrmName + INI_WINLEFT  ,-999);
	WinTop    = pIni->ReadInteger(Section,FrmName + INI_WINTOP   ,   0);
	WinWidth  = pIni->ReadInteger(Section,FrmName + INI_WINWIDTH ,   0);
	WinHeight = pIni->ReadInteger(Section,FrmName + INI_WINHEIGHT,   0);
	//�E�B���h�E�ʒu�Z�b�g
	if(WinLeft != -999)
	{
		//�t�H�[���ʒu�Z�b�g
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
		//�t�H�[���𒆉��ɔz�u
		Form->Left  = (Screen->WorkAreaWidth  - Form->Width) / 2;
		Form->Top   = (Screen->WorkAreaHeight - Form->Width) / 2;
	}
	//Top�̕␳
	if(Form->Top < 50)
	{
		Form->Top = 100;
	}
	return true;
}
//-------------------------------------------------------------
//�E�B���h�E�̈ʒu���L�^
//-------------------------------------------------------------
bool BGE::saveWindowPos(TForm *Form,bool IsTopLeftOnly)
{
	String                    Section;
	std::unique_ptr<TIniFile> pIni;
	//�t�H�[����Name�𓾂�(�啶��)
	String FrmName = Form->Name.UpperCase();

	//�t�H�[���֘A�֘A�A�N�Z�X
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
	Section = INI_DEF_WINPOS;

	//�ʒu��ݒ�
	pIni->WriteInteger(Section,FrmName + INI_WINLEFT  ,Form->Left  );
	pIni->WriteInteger(Section,FrmName + INI_WINTOP   ,Form->Top   );
	//���A�����̐ݒ�
	if(IsTopLeftOnly == false)
	{
		pIni->WriteInteger(Section,FrmName + INI_WINWIDTH ,Form->Width );
		pIni->WriteInteger(Section,FrmName + INI_WINHEIGHT,Form->Height);
	}
	return true;
}
//-------------------------------------------------------------
//�u���V�̑����𓾂�
//-------------------------------------------------------------
int BGE::getThickness()
{
	int                       thickness;
	String                    Section;
	std::unique_ptr<TIniFile> pIni;

	//�t�H�[���֘A�֘A�A�N�Z�X
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
	Section = INI_DEF_STANDARD;

	//�u���V�̑������擾
	thickness = pIni->ReadInteger(Section,INI_THICKNESS,2);

	return thickness;
}

//-------------------------------------------------------------
//�u���V�̑������Z�b�g
//-------------------------------------------------------------
bool BGE::setThickness(int tn)
{
	String                    Section;
	std::unique_ptr<TIniFile> pIni;

	//�t�H�[���֘A�֘A�A�N�Z�X
	pIni.reset(new TIniFile(getExeDir() + INI_INIFILENAME));
	Section = INI_DEF_STANDARD;

	//�u���V�̑������擾
	pIni->WriteInteger(Section,INI_THICKNESS,tn);

	return true;
}
//---------------------------------------------------------------------------
//�t�@�C���o�[�W�������̎擾
//-------------------------------------------------------------
String BGE::GetFileVer()
{
	typedef struct
	{
		WORD wLanguage;
		WORD wCodePage;
	} LANGANDCODEPAGE, *LPLANGANDCODEPAGE;


	VS_FIXEDFILEINFO vffi;           // �o�[�W���������󂯎��\����
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

			VerQueryValue(vbuf.get(),TEXT("\\"),&buf,&size);   // �o�[�W�������擾
			CopyMemory( &vffi, buf, sizeof(VS_FIXEDFILEINFO)); //�R�s�[

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

	//�E����.������
	wchar_t *p = wcsrchr(VerOrgStr,L'.');
	//�o�[�W�����̕���
	if(p != nullptr)
	{
		*p       = '\0';
		VerStr   = VerOrgStr;
		BuildStr = (p+1);
	}
	//�\��
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
