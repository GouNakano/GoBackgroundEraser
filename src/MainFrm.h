//---------------------------------------------------------------------------
#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <stack>
#include "TBGEraser.h"
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TMainMenu *MainMenu;
	TMenuItem *N1;
	TMenuItem *ReadImageMenu;
	TPanel *MenuPanel;
	TBitBtn *updateBtn;
	TBitBtn *saveBtn;
	TBitBtn *undoBtn;
	TBitBtn *specifyBGBtn;
	TBitBtn *specifyFGBtn;
	TBitBtn *dispOrigImgBtn;
	TBitBtn *LoadImageBtn;
	TBitBtn *SelRectBtn;
	TPanel *Panel2;
	TLabel *ModeLabel;
	TPanel *Panel3;
	TBitBtn *EndBtn;
	TPanel *Panel1;
	TStatusBar *StatusBar1;
	TPanel *MainPanel;
	TOpenPictureDialog *OpenPictureDialog;
	TMenuItem *N6;
	TMenuItem *UndoMemu;
	TMenuItem *N2;
	TMenuItem *UpdateMenu;
	TSavePictureDialog *SavePictureDialog;
	TMenuItem *H1;
	TMenuItem *VersionMenu;
	TLabel *Label1;
	TComboBox *ThicknessComboBox;
	TMenuItem *HelpMenu;
	TMenuItem *N4;
	TMenuItem *N3;
	TMenuItem *SaveImageMenu;
	TMenuItem *N5;
	TMenuItem *EndMenu;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *dispOrigImgMenu;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LoadImageBtnClick(TObject *Sender);
	void __fastcall SelRectBtnClick(TObject *Sender);
	void __fastcall specifyBGBtnClick(TObject *Sender);
	void __fastcall specifyFGBtnClick(TObject *Sender);
	void __fastcall dispOrigImgBtnClick(TObject *Sender);
	void __fastcall undoBtnClick(TObject *Sender);
	void __fastcall saveBtnClick(TObject *Sender);
	void __fastcall updateBtnClick(TObject *Sender);
	void __fastcall EndBtnClick(TObject *Sender);
	void __fastcall UndoMemuClick(TObject *Sender);
	void __fastcall MainPanelResize(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall ThicknessComboBoxChange(TObject *Sender);
	void __fastcall VersionMenuClick(TObject *Sender);
	void __fastcall HelpMenuClick(TObject *Sender);
private:
	//�}�E�X�C�x���g
	static void onmouse(int event,int x,int y,int flags,void *param);
private:
	TBGEraser BGEraser;
	HWND      hWnd1;
	HWND      hWnd1_parent;
	//�E�B���h�E�T�C�Y
	cv::Size win_sz;
private:
	int      ix;
	int      iy;
	cv::Rect rect;
	cv::Mat  disp_mat;
	cv::Mat  disp_mask_mat;
	cv::Mat  original_mat;
	cv::Mat  original_mask_mat;
private:
	//���[�h�\��
	void dispMode(const std::string& mode_str);
	//���摜�̕\���摜���쐬����
	void makeDrawMatFromOrignalMat();
	//�\���p��`�����摜�̑傫���ɍ��킹��
	bool adjustRectFromDrawRect(const cv::Rect& draw_rect,cv::Rect& adjust_rect);
	//���摜�̋�`��\���p�̑傫���ɍ��킹��
	bool adjustDrawRectFromRect(const cv::Rect& rect,cv::Rect& adjust_rect);
	//�`��pMat�ŕ\���X�V
	void updateDispFromDrawMat();
	//�\���p�摜���猳�摜�ւ̍��W�ϊ�
	bool adjustOriginalPointFromDrawPoint(const cv::Point& draw_point,cv::Point& adjust_point);
	//�u���V�̑����̃R���{�{�b�N�X���Z�b�g
	bool setThicknessComboBox();
	//wstring����string�ɕϊ�
	std::string wstring2string(const std::wstring& wstr);
public:
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif