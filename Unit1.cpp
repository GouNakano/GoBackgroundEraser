//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ZZZZZ1Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
	//�w�i�����I�u�W�F�N�g�̏�����
	BGEraser.init();
	BGEraser.readImage("messi5.png");
	//�E�B���h�E�̌���
	hWnd1        = (HWND)cvGetWindowHandle("output");
	hWnd1_parent = ::GetParent(hWnd1);
	::SetParent(hWnd1,MainPanel->Handle);
	::ShowWindow(hWnd1_parent,SW_HIDE);
	//���摜�𓾂�
	BGEraser.getOriginalMat(original_mat);
	//���}�X�N�𓾂�
	BGEraser.getOriginalMaskMat(original_mask_mat);
//	//���摜�̕\���摜���쐬����
//	makeDrawMatFromOrignalMat();
//	//��Ɨp�}�X�NMat���쐬����
//	disp_mask_mat = original_mask_mat.clone();
//	//�`��pMat�ŕ\���X�V
//	updateDispFromDrawMat();
//	//�}�E�X�C�x���g�̑��M��ݒ�
//	cv::setMouseCallback("output",TMainForm::onmouse,this);
//	//���[�h�\��
//	dispMode("GoBackgroundEraser�N��");

}
//---------------------------------------------------------------------------
