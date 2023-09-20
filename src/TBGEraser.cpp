//---------------------------------------------------------------------------
#pragma hdrstop

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include "BGEraserDef.h"
#include "TBGEraser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//-------------------------------------------------
//�Œ�l
//-------------------------------------------------
const TmaskInf TBGEraser::DRAW_BACKGROUND(cv::Scalar(  0,  0,  0), 0);
const TmaskInf TBGEraser::DRAW_FOREGROUND(cv::Scalar(255,255,255), 1);
const TmaskInf TBGEraser::DRAW_RECTANGLE (cv::Scalar(255,  0,  0),-1);

//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
TBGEraser::TBGEraser()
{
}
//-------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------
TBGEraser::~TBGEraser()
{
}
//-------------------------------------------------
//�����l�ݒ�
//-------------------------------------------------
bool TBGEraser::init()
{
	//�t���O�̐ݒ�
	rect      = cv::Rect(0,0,0,0);
	drawing   = false;                // �Ȑ��`��̃t���O
	BGEMode   = tmNone;               // �}�E�X���샂�[�h�̃t���O
	maskInf   = DRAW_BACKGROUND;      // �������݃��[�h��w�i�ɏ�����
	thickness = BGE::getThickness();  // �u���V�̑���
	//���o�̓E�B���h�E
	cv::namedWindow("output");
	printf("�}�E�X�̉E�{�^�����g�p���ăI�u�W�F�N�g�̎��͂ɒ����`��`���܂��B\n");

	return true;
}
//-------------------------------------------------
//�摜�̓Ǎ�
//-------------------------------------------------
bool TBGEraser::readImage(const std::string& file_name)
{
	//�摜�̓Ǎ�
	cv::Mat read_img = cv::imread(file_name);
	//�ǂݍ��݃`�F�b�N
	if(read_img.cols == 0 || read_img.rows == 0)
	{
		//�摜�Ǎ����s
		return false;
	}
	//�摜�ɑ΂���Mat�̏����ݒ�
	rect    = cv::Rect(0,0,0,0);
	drawing = false;                                      // �Ȑ��`��̃t���O
	BGEMode = tmNone;                                     // �}�E�X���샂�[�h�̃t���O
	img_org = read_img.clone();                           // ���̉摜�̃R�s�[
	mask    = cv::Mat::ones(read_img.size(),CV_8UC1)*255; // �}�X�N�͔w�i�ɏ�����
	output  = read_img.clone();                           // �\�������o�͉摜

	return true;
}
//-------------------------------------------------
//�w�i�폜��i�߂�
//-------------------------------------------------
bool TBGEraser::segmentImage()
{
	if(BGEMode == tmRect)
	{
		//��`�̈���̏�����ɏ����l�����߂�
		cv::Mat bgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		cv::Mat fgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		cv::grabCut(img_org,mask,rect,bgdmodel,fgdmodel,1,cv::GC_INIT_WITH_RECT);
		//�}�X�N�X�V���[�h�Ɉڍs
		BGEMode = tmMask;
	}
	else if(BGEMode == tmMask)
	{
		//�}�X�N�X�V�Ŕw�i�������s��
		cv::Mat bgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		cv::Mat fgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		cv::grabCut(img_org,mask,rect,bgdmodel,fgdmodel,1,cv::GC_INIT_WITH_MASK);
	}
	//�}�X�N���X�V���ďo�͉摜���쐬����
	updateMaskAndOutputImage();

	return true;
}
//-------------------------------------------------
//�w�i�����摜��png�t�@�C���ɕۑ�����
//-------------------------------------------------
bool TBGEraser::saveBGErasedImage(const std::string& file_name)
{
	//�Ō�� . �̈ʒu�𓾂�
	std::string::size_type pos = file_name.find_last_of(".");
	//����������
	if(pos == std::string::npos)
	{
		return false;
	}
	//�g���q�̐؂�o��
	std::string extname = file_name.substr(pos,file_name.size()-pos);
	//�g���q��啶���ɂ���
	std::transform(extname.begin(),extname.end(),extname.begin(),std::toupper);
	//�g���q��.PNG���`�F�b�N
	if(extname != ".PNG")
	{
		return false;
	}
	//�ۑ��pMat
	cv::Mat save_img = cv::Mat::zeros(output.size(),CV_8UC4);
	//�����s�N�Z��
	cv::Vec4b alpha0(0,0,0,0);
	//�s�N�Z��
	cv::Vec4b pixcel;
	//���s�N�Z��
	cv::Vec3b src_px3;
	cv::Vec4b src_px4;

	//�`�����l����
	int ch = output.channels();

	//�A���t�@�`�����l���t���s�N�Z���̐ݒ�
	for(int y = 0;y < save_img.rows;y++)
	{
		for(int x = 0;x < save_img.cols;x++)
		{
			//�}�X�N���`�F�b�N
			if(mask.at<unsigned char>(y,x) == cv::GC_BGD || mask.at<unsigned char>(y,x) == cv::GC_PR_BGD)
			{
				//�}�X�N�����Ȃ̂œ����ɂ���
				save_img.at<cv::Vec4b>(y,x) = alpha0;
			}
			else
			{
				//�}�X�N�����Ȃ̂Ō��摜�̃s�N�Z���F��ݒ�
				if(ch == 3)
				{
					src_px3 = img_org.at<cv::Vec3b>(y,x);

					pixcel[0] = src_px3[0];
					pixcel[1] = src_px3[1];
					pixcel[2] = src_px3[2];
					pixcel[3] = 255;
					save_img.at<cv::Vec4b>(y,x) = pixcel;
				}
				else if(ch == 4)
				{
					src_px4 = img_org.at<cv::Vec4b>(y,x);

					pixcel[0] = src_px4[0];
					pixcel[1] = src_px4[1];
					pixcel[2] = src_px4[2];
					pixcel[3] = 255;
					save_img.at<cv::Vec4b>(y,x) = pixcel;
				}
				else //if(ch == 1)
				{
					unsigned char val = img_org.at<unsigned char>(y,x);

					pixcel[0] = val;
					pixcel[1] = val;
					pixcel[2] = val;
					pixcel[3] = 255;
					save_img.at<cv::Vec4b>(y,x) = pixcel;
				}
			}
		}
	}
	//�摜�̕ۑ�
	if(cv::imwrite(file_name,save_img) == false)
	{
		return false;
	}
	return true;
}
//-------------------------------------------------
//�w�i�w�胂�[�h�ɂ���
//-------------------------------------------------
bool TBGEraser::setSpecifyBackgroundMode()
{
	//�w�i�w�胂�[�h
	maskInf = DRAW_BACKGROUND;

	return true;
}
//-------------------------------------------------
//�O�i�w�胂�[�h�ɂ���
//-------------------------------------------------
bool TBGEraser::setSpecifyForegroundMode()
{
	//�O�i�w�胂�[�h
	maskInf = DRAW_FOREGROUND;

	return true;
}
//-------------------------------------------------
//�o��Mat�𓾂�
//-------------------------------------------------
bool TBGEraser::getOutputMat(cv::Mat& output_mat)
{
	//�o��Mat�̃R�s�[���Z�b�g
	output_mat = output.clone();

	return true;
}
//-------------------------------------------------
//�o��Mat���Z�b�g
//-------------------------------------------------
bool TBGEraser::setOutputMat(const cv::Mat& output_mat)
{
	//�o��Mat�̃R�s�[���Z�b�g
	output = output_mat.clone();

	return true;
}
//-------------------------------------------------
//�͈͂��擾
//-------------------------------------------------
cv::Rect TBGEraser::getSelectRect()
{
	return rect;
}
//-------------------------------------------------
//�͈͂��Z�b�g
//-------------------------------------------------
bool TBGEraser::setSelectRect(const cv::Rect& r)
{
	rect = r;

	return true;
}
//-------------------------------------------------
//�o�̓}�X�N�𓾂�
//-------------------------------------------------
bool TBGEraser::getOutputMasktMat(cv::Mat& mask_mat)
{
	//�o��Mat�̃R�s�[���Z�b�g
	mask_mat = mask.clone();

	return true;
}
//-------------------------------------------------
//�o�̓}�X�N���Z�b�g
//-------------------------------------------------
bool TBGEraser::setOutputMasktMat(cv::Mat& mask_mat)
{
	//�o��Mat�̃R�s�[���Z�b�g
	mask = mask_mat.clone();

	return true;
}
//-------------------------------------------------
//���摜Mat�𓾂�
//-------------------------------------------------
bool TBGEraser::getOriginalMat(cv::Mat& original_mat)
{
	//���e�̗L���`�F�b�N
	if(img_org.rows == 0 || img_org.cols == 0)
	{
		return false;
	}
	//���摜Mat�̃R�s�[���Z�b�g
	original_mat = img_org.clone();

	return true;
}
//-------------------------------------------------
//���}�X�N�𓾂�
//-------------------------------------------------
bool TBGEraser::getOriginalMaskMat(cv::Mat& original_mask_mat)
{
	//���e�̗L���`�F�b�N
	if(mask.rows == 0 || mask.cols == 0)
	{
		mask = cv::Mat::zeros(img_org.size(),CV_8UC1);
	}
	//���}�X�NMat�̃R�s�[���Z�b�g
	original_mask_mat = mask.clone();

	return true;
}
//-------------------------------------------------
//�}�X�N���X�V���ďo�͉摜���쐬����
//-------------------------------------------------
bool TBGEraser::updateMaskAndOutputImage()
{
	//mask���L���ł��邩�`�F�b�N
	if(mask.rows > 0 && mask.cols > 0)
	{
		//�O�i�����𔒂ɂ����}�X�N���쐬
		cv::Mat mask2 = cv::Mat::zeros(mask.size(),CV_8UC1);
		setNewValFromVal(mask,mask2,255,cv::GC_FGD);     //���炩�ȑO�i
		setNewValFromVal(mask,mask2,255,cv::GC_PR_FGD);  //�O�i��������Ȃ�
		//���摜�Ƀ}�X�N��K�p
		output = 0;
		img_org.copyTo(output,mask2);
	}
	return true;
}
//-------------------------------------------------
//�u���V�̑������擾
//-------------------------------------------------
int TBGEraser::getThickness()
{
	return thickness;
}
//-------------------------------------------------
//�u���V�̑������Z�b�g
//-------------------------------------------------
bool TBGEraser::setThickness(int tn)
{
	BGE::setThickness(tn);
	thickness = tn;

	return true;
}
//-------------------------------------------------
//�}�X�N�`�惂�[�h�̗L��
//-------------------------------------------------
bool TBGEraser::getDrawing()
{
	return drawing;
}
//-------------------------------------------------
//�}�X�N�`�惂�[�h�̗L�����Z�b�g
//-------------------------------------------------
void TBGEraser::setDrawing(bool is_draw)
{
	drawing = is_draw;
}
//-------------------------------------------------
//src�̓���̒l(v)�̃s�N�Z����new_val�A���̑��͕ύX���Ȃ�
//-------------------------------------------------
bool TBGEraser::setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v)
{
	for(int row=0;row < src.rows;row++)
	{
		const unsigned char *psrc = src.ptr<unsigned char>(row);
		unsigned char       *pdst = dst.ptr<unsigned char>(row);

		for(int col = 0;col < src.cols;col++)
		{
			if(psrc[col] == v)
			{
				//���ɂ���
				pdst[col] = new_val;
			}
		}
	}
	return true;
}
//-------------------------------------------------
//Undo����Push����
//-------------------------------------------------
bool TBGEraser::pushUndoInf()
{
	//���݂̒l���X�^�b�N�ɐς�
	if(BGEMode == tmRect)
	{
		TUndotiness undoInf(img_org,mask,rect,BGEMode);
		histStack.push(undoInf);
	}
	else
	{
		TUndotiness undoInf(output,mask,rect,BGEMode);
		histStack.push(undoInf);
	}

	return true;
}
//-------------------------------------------------
//Undo����pop����(undo�̎��s�̓L�����Z��
//-------------------------------------------------
bool TBGEraser::popUndoInf()
{
	//�X�^�b�N�̐����`�F�b�N
	if(histStack.size() < 1)
	{
		//�X�^�b�N�������̂ŏ������Ȃ�
		return false;
	}
	//�Ō�ɃX�^�b�N�ɐς񂾗v�f��pop
	histStack.top();

	return true;
}
//-------------------------------------------------
//Undo�����s����
//-------------------------------------------------
bool TBGEraser::undo()
{
	//�X�^�b�N�̐����`�F�b�N
	if(histStack.size() < 1)
	{
		//�X�^�b�N�������̂ŏ������Ȃ�
		return false;
	}
	//�Ō�ɃX�^�b�N�ɐς񂾗v�f�𓾂�
	TUndotiness last_stck = histStack.top();

	cv::Mat    last_original_mat;
	cv::Mat    last_original_mask_mat;
	cv::Rect   last_original_rect;
	typBGEMode last_mode;

	last_stck.get(last_original_mat,last_original_mask_mat,last_original_rect,last_mode);

	//�w�i�������ʉ摜���Z�b�g
	setOutputMat(last_original_mat);
	//�w�i�������ʃ}�X�N���Z�b�g
	setOutputMasktMat(last_original_mask_mat);
	//�͈͂��Z�b�g
	setSelectRect(last_original_rect);
	//�w�i�������ʉ摜���擾
	getOutputMat(output);
	//�w�i�������ʃ}�X�N���擾
	getOutputMasktMat(mask);
	//���[�h�Z�b�g
	BGEMode = last_mode;
	//�X�^�b�N����pop����
	histStack.pop();

	return true;
}
//-------------------------------------------------
//BGE���[�h�𓾂�
//-------------------------------------------------
typBGEMode TBGEraser::getBGEMode()
{
	return BGEMode;
}
//-------------------------------------------------
//BGE���[�h���Z�b�g
//-------------------------------------------------
bool TBGEraser::setBGEMode(typBGEMode mde)
{
	BGEMode = mde;

	return true;
}
//-------------------------------------------------
//�}�X�N�Ɋւ�����𓾂�
//-------------------------------------------------
const TmaskInf& TBGEraser::getMaskInf()
{
	return maskInf;
}
