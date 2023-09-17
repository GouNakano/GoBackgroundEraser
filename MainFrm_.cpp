//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "nsDebug.h"
#include "OrgImgDispFrm.h"
#include "MainFrm_.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm_ *MainForm_;
//---------------------------------------------------------------------------
__fastcall TMainForm_::TMainForm_(TComponent* Owner)
	: TForm(Owner)
{
}
//-------------------------------------------------
//�t�H�[�����\�������Ƃ�
//-------------------------------------------------
void __fastcall TMainForm_::FormShow(TObject *Sender)
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
	//���摜�̕\���摜���쐬����
	makeDrawMatFromOrignalMat();
	//��Ɨp�}�X�NMat���쐬����
	disp_mask_mat = original_mask_mat.clone();
	//�`��pMat�ŕ\���X�V
	updateDispFromDrawMat();
	//�}�E�X�C�x���g�̑��M��ݒ�
	cv::setMouseCallback("output",TMainForm_::onmouse,this);
	//���[�h�\��
	dispMode("GoBackgroundEraser�N��");
}
//-------------------------------------------------
//�w�i�폜�\���X�V�{�^��
//-------------------------------------------------
void __fastcall TMainForm_::updateBtnClick(TObject *Sender)
{
	//���[�h�`�F�b�N
	if(BGEraser.rect_or_mask == TBGEraser::tmNone)
	{
		//��ԕ\��
		dispMode("�w�i�����͈͂��w�肵�Ă���X�V���s���Ă�������");
		return;
	}
	//��ԕ\��
	dispMode("�w�i�����摜�\���X�V��");
	//���݂̒l���X�^�b�N�ɐς�
	histStack.push({original_mat.clone(),original_mask_mat.clone(),BGEraser.rect_or_mask});
	//�\���p�}�X�N���I���W�i���̑傫���ɂ���
	disp_mask_mat.copyTo(BGEraser.mask);
	//�w�i�폜��i�߂�
	if(BGEraser.segmentImage() == false)
	{
		//���������s�����̂ŃX�^�b�N��߂�
		histStack.pop();
		//���s��ԕ\��
		dispMode("�w�i�����摜�\���X�V���s");
	}
	//�w�i�������ʉ摜���擾
	BGEraser.getOutputMat(original_mat);
	//�w�i�������ʃ}�X�N���擾
	BGEraser.getOutputMasktMat(original_mask_mat);
	//���摜�̕\���摜���쐬����
	makeDrawMatFromOrignalMat();
	//��Ɨp�}�X�NMat���쐬����
	disp_mask_mat = original_mask_mat.clone();
	//�`��pMat�ŕ\���X�V
	updateDispFromDrawMat();
	//��ԕ\��
	dispMode("�w�i�����摜�\���X�V����");
}
//-------------------------------------------------
//�ۑ��{�^��
//-------------------------------------------------
void __fastcall TMainForm_::saveBtnClick(TObject *Sender)
{
	//�w�i�폜�摜�̕ۑ�
	BGEraser.saveBGErasedImage("output.png");
}
//-------------------------------------------------
//���ɖ߂��{�^��
//-------------------------------------------------
void __fastcall TMainForm_::undoBtnClick(TObject *Sender)
{
	//�X�^�b�N�̐����`�F�b�N
	if(histStack.size() < 1)
	{
		//�X�^�b�N�������̂ŏ������Ȃ�
		return;
	}
	//�Ō�ɃX�^�b�N�ɐς񂾗v�f�𓾂�
	std::tuple<cv::Mat,cv::Mat,TBGEraser::typMode>& last_stck = histStack.top();

	cv::Mat&            last_original_mat      = std::get<0>(last_stck);
	cv::Mat&            last_original_mask_mat = std::get<1>(last_stck);
	TBGEraser::typMode& last_mode              = std::get<2>(last_stck);
	//�w�i�������ʉ摜���Z�b�g
	BGEraser.setOutputMat(last_original_mat);
	//�w�i�������ʃ}�X�N���擾
	BGEraser.setOutputMasktMat(last_original_mask_mat);
	//�w�i�������ʉ摜���擾
	BGEraser.getOutputMat(original_mat);
	//�w�i�������ʃ}�X�N���擾
	BGEraser.getOutputMasktMat(original_mask_mat);
	//���摜�̕\���摜���쐬����
	makeDrawMatFromOrignalMat();
	//��Ɨp�}�X�NMat���쐬����
	disp_mask_mat = original_mask_mat.clone();
	//���[�h�Z�b�g
	BGEraser.rect_or_mask = last_mode;
	//�`��pMat�ŕ\���X�V
	updateDispFromDrawMat();
	//�X�^�b�N����pop����
	histStack.pop();

//	//�ҏW���ʂ𖳌��ɂ��ă��Z�b�g����
//	BGEraser.resetState();
}
//-------------------------------------------------
//���[�h�\��
//-------------------------------------------------
void TMainForm_::dispMode(const std::string& mode_str)
{
	//��ԕ\�����x���̕�����X�V
	ModeLabel->Caption = mode_str.c_str();
	Application->ProcessMessages();
}
//-------------------------------------------------
//�w�i�w�胂�[�h�ɂ���
//-------------------------------------------------
void __fastcall TMainForm_::specifyBGBtnClick(TObject *Sender)
{
	//���[�h�`�F�b�N
	if(BGEraser.rect_or_mask != TBGEraser::tmMask)
	{
		//���[�h�\��
		dispMode("�}�X�N�ҏW���[�h�ł͂���܂���A�͈͎w����s���čX�V���ɍs���Ă�������");
		return;
	}
	//�w�i�w�胂�[�h�ɂ���
	if(BGEraser.setSpecifyBackgroundMode() == true)
	{
		//���[�h�\��
		dispMode("�w�i�w�胂�[�h�Ɉڍs���܂���");
	}
}
//-------------------------------------------------
//�O�i�w�胂�[�h�ɂ���
//-------------------------------------------------
void __fastcall TMainForm_::specifyFGBtnClick(TObject *Sender)
{
	//���[�h�`�F�b�N
	if(BGEraser.rect_or_mask != TBGEraser::tmMask)
	{
		//���[�h�\��
		dispMode("�}�X�N�ҏW���[�h�ł͂���܂���A�͈͎w����s���čX�V���ɍs���Ă�������");
		return;
	}
	//�O�i�w�胂�[�h�ɂ���
	if(BGEraser.setSpecifyForegroundMode() == true)
	{
		//���[�h�\��
		dispMode("�O�i�w�胂�[�h�Ɉڍs���܂���");
	}
}
//-------------------------------------------------
//���C���\���p�l���̃T�C�Y�ύX
//-------------------------------------------------
void __fastcall TMainForm_::MainPanelResize(TObject *Sender)
{
	//���摜�̕\���摜���쐬����
	makeDrawMatFromOrignalMat();
	//�`��pMat�ŕ\���X�V
	updateDispFromDrawMat();
}
//-------------------------------------------------
//�摜�̕\���̑傫���ɍ��킹���`��p�摜���쐬����
//-------------------------------------------------
void TMainForm_::makeDrawMatFromOrignalMat()
{
	//���摜�̗L�����`�F�b�N
	if(original_mat.rows > 0 && original_mat.cols > 0)
	{
		//�e�p�l���̃T�C�Y
		int w = MainPanel->Width;
		int h = MainPanel->Height;
		win_sz = {w,h};
		//�\���pMat�Ƀ��T�C�Y
		cv::resize(original_mat,disp_mat,win_sz);
	}
}
//-------------------------------------------------
//�`��pMat�ŕ\���X�V
//-------------------------------------------------
void TMainForm_::updateDispFromDrawMat()
{
	if(original_mat.rows == 0 || original_mat.cols == 0)
	{
		//�e�p�l���̃T�C�Y
		int w = MainPanel->Width;
		int h = MainPanel->Height;
		win_sz = {MainPanel->Width,MainPanel->Height};
		//���̕\���pMat�쐬
		disp_mat = cv::Mat::zeros(win_sz,CV_8UC3);
	}
	//�`��X�V
	cv::imshow("output",disp_mat);
	cv::waitKey(1);
}
//-------------------------------------------------
//�\���p��`�����摜�̑傫���ɍ��킹��
//-------------------------------------------------
bool TMainForm_::adjustRectFromDrawRect(const cv::Rect& draw_rect,cv::Rect& adjust_rect)
{
	if(original_mat.rows == 0 || original_mat.cols == 0)
	{
		return false;
	}
	if(draw_rect.width < 1 || draw_rect.height < 1)
	{
		return false;
	}
	//�䗦���Z�o
	double w_ratio = static_cast<double>(original_mat.cols) / static_cast<double>(MainPanel->Width);
	double h_ratio = static_cast<double>(original_mat.rows) / static_cast<double>(MainPanel->Height);
	//Rect�X�V
	adjust_rect.x      = static_cast<int>(draw_rect.x      * w_ratio);
	adjust_rect.y      = static_cast<int>(draw_rect.y      * h_ratio);
	adjust_rect.width  = static_cast<int>(draw_rect.width  * w_ratio);
	adjust_rect.height = static_cast<int>(draw_rect.height * h_ratio);

	return true;
}
//-------------------------------------------------
//�\���p�摜�����摜�̑傫���ɍ��킹��
//-------------------------------------------------
bool TMainForm_::adjustDispMatFromDrawMat(const cv::Mat& draw_mat,cv::Mat& adjust_mat)
{
	if(draw_mat.rows == 0 || draw_mat.cols == 0)
	{
		return false;
	}
	//���T�C�Y
	cv::resize(draw_mat,adjust_mat,original_mat.size());

	return true;
}
//-------------------------------------------------
//�\���p�摜���猳�摜�ւ̍��W�ϊ�
//-------------------------------------------------
bool TMainForm_::adjustOriginalPointFromDrawPoint(const cv::Point& draw_point,cv::Point& adjust_point)
{
	//�䗦���Z�o
	double w_ratio = static_cast<double>(original_mat.cols) / static_cast<double>(MainPanel->Width);
	double h_ratio = static_cast<double>(original_mat.rows) / static_cast<double>(MainPanel->Height);
	//���W��ϊ�����
	adjust_point.x = static_cast<int>(draw_point.x * w_ratio);
	adjust_point.y = static_cast<int>(draw_point.y * h_ratio);

	return true;
}
//---------------------------------------------------------------------------
//�}�E�X�C�x���g
//---------------------------------------------------------------------------
void TMainForm_::onmouse(int event,int x,int y,int flags,void *param)
{
	//���g�𓾂�
	TMainForm_ *pMainFrm = static_cast<TMainForm_ *>(param);
	TBGEraser *pMe      = static_cast<TBGEraser *>(&pMainFrm->BGEraser);

	//�e�}�E�X�{�^�����Ƃ̏���
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		if(pMe->rect_or_mask == TBGEraser::tmNone)
		{
			if(pMe->getDrawing() == false)
			{
				pMainFrm->ix = x;
				pMainFrm->iy = y;
				//���摜�̕\���摜���쐬����
				pMainFrm->makeDrawMatFromOrignalMat();
				//���C���\���p�l���̕\���X�V
				pMainFrm->updateDispFromDrawMat();
				//�`�撆�ɂ���
				pMe->setDrawing(true);
			}
		}
		else if(pMe->rect_or_mask == TBGEraser::tmMask)
		{
			//�`�撆�ɂ���
			pMe->setDrawing(true);
			//�`��X�V
			cv::circle(pMainFrm->disp_mat,cv::Point(x,y),pMe->getThickness(),pMe->value.color,-1);
			//�}�X�N�X�V
			cv::Point adjust_point;
			pMainFrm->adjustOriginalPointFromDrawPoint(cv::Point(x,y),adjust_point);
			cv::circle(pMainFrm->disp_mask_mat,adjust_point,pMe->getThickness(),pMe->value.val,-1);
			//���C���\���p�l���̕\���X�V
			pMainFrm->updateDispFromDrawMat();
		}
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(pMe->rect_or_mask == TBGEraser::tmNone)
		{
			if(pMe->getDrawing() == true)
			{
				//���摜�̕\���摜���쐬����
				pMainFrm->makeDrawMatFromOrignalMat();
				//��`��`��
				cv::rectangle(pMainFrm->disp_mat,cv::Point(pMainFrm->ix,pMainFrm->iy),cv::Point(x,y),pMe->DRAW_RECTANGLE.color,2);
				//���C���\���p�l���̕\���X�V
				pMainFrm->updateDispFromDrawMat();
			}
		}
		else if(pMe->rect_or_mask == TBGEraser::tmMask)
		{
			if(pMe->getDrawing() == true)
			{
				//�`��X�V
				cv::circle(pMainFrm->disp_mat,cv::Point(x,y),pMe->getThickness(),pMe->value.color,-1);
				//�}�X�N�X�V
				cv::Point adjust_point;
				pMainFrm->adjustOriginalPointFromDrawPoint(cv::Point(x,y),adjust_point);
				cv::circle(pMainFrm->disp_mask_mat,adjust_point,pMe->getThickness(),pMe->value.val,-1);
				//���C���\���p�l���̕\���X�V
				pMainFrm->updateDispFromDrawMat();
			}
		}
	}
	else if(event == cv::EVENT_LBUTTONUP)
	{
		if(pMe->rect_or_mask == TBGEraser::tmNone)
		{
			//�`��I��
			pMe->setDrawing(false);
			//�͈͐ݒ�ς݃t���O�ɂ���
			pMe->rect_or_mask = TBGEraser::tmRect;
			//�I����`�̑傫����␳���ēn��
			cv::Rect sel_rect;
			cv::Rect adj_rect;

			sel_rect = cv::Rect(std::min(pMainFrm->ix,x),std::min(pMainFrm->iy,y),abs(pMainFrm->ix-x),abs(pMainFrm->iy-y));

			//�\���p��`�����摜�̑傫���ɍ��킹��
			if(pMainFrm->adjustRectFromDrawRect(sel_rect,adj_rect) == true)
			{
				cv::rectangle(pMe->img,adj_rect,pMe->DRAW_RECTANGLE.color,2);
				pMe->rect         = adj_rect;
				pMe->rect_or_mask = TBGEraser::tmRect;
				pMe->updateMaskAndOutputImage();
			}
		}
		else if(pMe->rect_or_mask == TBGEraser::tmMask)
		{
			if(pMe->getDrawing() == true)
			{
				pMe->setDrawing(false);
				//�`��X�V
				cv::circle(pMainFrm->disp_mat,cv::Point(x,y),pMe->getThickness(),pMe->value.color,-1);
				//�}�X�N�X�V
				cv::Point adjust_point;
				pMainFrm->adjustOriginalPointFromDrawPoint(cv::Point(x,y),adjust_point);
				cv::circle(pMainFrm->disp_mask_mat,adjust_point,pMe->getThickness(),pMe->value.val,-1);
				//���C���\���p�l���̕\���X�V
				pMainFrm->updateDispFromDrawMat();
			}
		}
	}
}
//---------------------------------------------------------------------------
//���摜�̕\��
//---------------------------------------------------------------------------
void __fastcall TMainForm_::dispOrigImgBtnClick(TObject *Sender)
{
	//�摜��荞�܂�Ă��邩�`�F�b�N
	if(original_mat.empty() == true || original_mat.cols == 0 || original_mat.rows == 0)
	{
		//�G���[�\��
		MessageBoxA(Handle,"�摜���ǂݍ��܂�Ă��܂���B","GoBackgroundEraser",MB_OK | MB_ICONERROR);
		return;
	}
	//Mat�̃Z�b�g
	OrgImgDispForm->setDisplayMat(original_mat);
	//���摜�̃E�B���h�E�����[�_���X�ŕ\��
	OrgImgDispForm->Show();
}
//---------------------------------------------------------------------------
//�摜�Ǎ��{�^��
//---------------------------------------------------------------------------
void __fastcall TMainForm_::LoadImageBtnClick(TObject *Sender)
{
	//�摜�I��
	if(OpenPictureDialog->Execute(Handle) == false)
	{
		return;
	}
	//�摜�t�@�C���p�X�𓾂�
	std::wstring wfile_name = OpenPictureDialog->FileName.c_str();
	std::string  file_name  = wstring2string(wfile_name);

	//�摜�̓Ǎ�
	if(BGEraser.readImage(file_name) == false)
	{
		MessageBoxA(Handle,"�摜�̓ǂݍ��݂Ɏ��s���܂����B","GoBackgroundEraser",MB_OK | MB_ICONERROR);
		return;
	}
	//���摜�𓾂�
	BGEraser.getOriginalMat(original_mat);
	//���}�X�N�𓾂�
	BGEraser.getOriginalMaskMat(original_mask_mat);
	//���摜�̕\���摜���쐬����
	makeDrawMatFromOrignalMat();
	//��Ɨp�}�X�NMat���쐬����
	disp_mask_mat = original_mask_mat.clone();
	//�`��pMat�ŕ\���X�V
	updateDispFromDrawMat();
}
//---------------------------------------------------------------------------
//�͈͎w�胂�[�h�{�^��
//---------------------------------------------------------------------------
void __fastcall TMainForm_::SelRectBtnClick(TObject *Sender)
{
	//���摜�𓾂�
	if(BGEraser.getOriginalMat(original_mat) == false)
	{
		//���[�h�\��
		dispMode("�摜�Ǎ����ɍs���Ă�������");
		return;
	}
	//�摜�\��������������
	//���摜�𓾂�
	BGEraser.getOriginalMat(original_mat);
	//���}�X�N�𓾂�
	BGEraser.getOriginalMaskMat(original_mask_mat);
	//���摜�̕\���摜���쐬����
	makeDrawMatFromOrignalMat();
	//��Ɨp�}�X�NMat���쐬����
	disp_mask_mat = original_mask_mat.clone();
	//�`��pMat�ŕ\���X�V
	updateDispFromDrawMat();

	//�͈͎w��Ɋւ���l������������
	BGEraser.rect_or_mask = TBGEraser::tmNone;
	BGEraser.rect         = cv::Rect(0,0,0,0);
	//���[�h�\��
	dispMode("�͈͎w�胂�[�h�Ɉڍs���܂���");
}
//---------------------------------------------------------------------------
//�I���{�^��
//---------------------------------------------------------------------------
void __fastcall TMainForm_::EndBtnClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
//wstring����string�ɕϊ�
//---------------------------------------------------------------------------
std::string TMainForm_::wstring2string(const std::wstring& wstr)
{
	//Unicode����}���`�o�C�g�ւ̕ϊ�
	int in_length = (int)wstr.length();
	int out_length = WideCharToMultiByte(CP_ACP,0,wstr.c_str(),in_length,0,0,0,0);
	std::string result(out_length, '\0');
	if(out_length > 0)
	{
		WideCharToMultiByte(CP_ACP,0,wstr.c_str(),in_length,&result[0],out_length,0,0);
	}
	//std::string�ւ̕ϊ����ʂ�ԋp
	return result;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm_::aaaaaa1Click(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
