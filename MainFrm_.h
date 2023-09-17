//---------------------------------------------------------------------------
#ifndef MainFrm_H
#define MainFrm_H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <stack>
#include "TBGEraser.h"
//---------------------------------------------------------------------------
class TMainForm_ : public TForm
{
__published:	// IDE �ŊǗ������R���|�[�l���g
	TPanel *MenuPanel;
	TBitBtn *updateBtn;
	TBitBtn *saveBtn;
	TBitBtn *undoBtn;
	TBitBtn *specifyBGBtn;
	TBitBtn *specifyFGBtn;
	TMainMenu *MainMenu;
	TMenuItem *F1;
	TMenuItem *E1;
	TMenuItem *H1;
	TPanel *Panel1;
	TStatusBar *StatusBar1;
	TPanel *MainPanel;
	TBitBtn *dispOrigImgBtn;
	TBitBtn *LoadImageBtn;
	TOpenPictureDialog *OpenPictureDialog;
	TBitBtn *SelRectBtn;
	TPanel *Panel2;
	TPanel *Panel3;
	TLabel *ModeLabel;
	TBitBtn *EndBtn;
	TMenuItem *undoMenu;
	TMenuItem *LoadImageMenu;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *EndMenu;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *UpdateMenu;
	TMenuItem *aaaaaa1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall updateBtnClick(TObject *Sender);
	void __fastcall saveBtnClick(TObject *Sender);
	void __fastcall undoBtnClick(TObject *Sender);
	void __fastcall specifyBGBtnClick(TObject *Sender);
	void __fastcall specifyFGBtnClick(TObject *Sender);
	void __fastcall MainPanelResize(TObject *Sender);
	void __fastcall dispOrigImgBtnClick(TObject *Sender);
	void __fastcall LoadImageBtnClick(TObject *Sender);
	void __fastcall SelRectBtnClick(TObject *Sender);
	void __fastcall EndBtnClick(TObject *Sender);
	void __fastcall aaaaaa1Click(TObject *Sender);
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
	//���ɖ߂����������邽�߂̃X�^�b�N
	std::stack<std::tuple<cv::Mat,cv::Mat,TBGEraser::typMode>> histStack;
private:
	//���[�h�\��
	void dispMode(const std::string& mode_str);
	//���摜�̕\���摜���쐬����
	void makeDrawMatFromOrignalMat();
	//�`��pMat�ŕ\���X�V
	void updateDispFromDrawMat();
	//�\���p��`�����摜�̑傫���ɍ��킹��
	bool adjustRectFromDrawRect(const cv::Rect& draw_rect,cv::Rect& adjust_rect);
	//�\���p�摜�����摜�̑傫���ɍ��킹��
	bool adjustDispMatFromDrawMat(const cv::Mat& draw_mat,cv::Mat& adjust_mat);
	//�\���p�摜���猳�摜�ւ̍��W�ϊ�
	bool adjustOriginalPointFromDrawPoint(const cv::Point& draw_point,cv::Point& adjust_point);
	//wstring����string�ɕϊ�
	std::string wstring2string(const std::wstring& wstr);
public:
	__fastcall TMainForm_(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm_ *MainForm_;
//---------------------------------------------------------------------------
#endif