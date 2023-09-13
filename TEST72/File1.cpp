#pragma hdrstop
#pragma argsused

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>

//src�̓���̒l(v)�̃s�N�Z����new_val�A���̑��͕ύX���Ȃ�
bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);

int main(int argc, char* argv[])
{
	cv::Mat img     = cv::imread("messi5.png");

	cv::Mat  bgdModel;
	cv::Mat  fgdModel;
	cv::Rect rect(1,1,img.cols-2,img.rows-2);

	cv::Mat mask = cv::Mat(img.size(),CV_8UC1);
	mask.setTo(cv::Scalar::all(cv::GC_PR_FGD));
	//�Z�O�����e�[�V�����̏�����
	cv::grabCut(img,mask,rect,bgdModel,fgdModel,1,cv::GC_INIT_WITH_RECT);

	//src�̓���̒l�̃s�N�Z����new_val�A���̑���0�ɂ���
	cv::Mat dst = cv::Mat::zeros(mask.size(),CV_8UC1);
	setNewValFromVal(mask,dst,255,cv::GC_FGD);
	setNewValFromVal(mask,dst,255,cv::GC_PR_FGD);
	cv::imshow("dst",dst);
	cv::waitKey(30);

	//�ǉ��̃}�X�N�ǂݍ���
	cv::Mat newmask = cv::imread("newmask.png",0);
	//dst�ƒǉ��̃}�X�N������
	dst |= newmask;
	//dst�̔��̕�����GC_FGD(1:���炩�ȑO�i(����)�s�N�Z��)�ɂ���
	mask = 0;
	setNewValFromVal(dst,mask,cv::GC_FGD,255);
	//GrabCut�A���S���Y�������s���܂�
	cv::grabCut(img,mask,rect,bgdModel,fgdModel,1,cv::GC_EVAL);

	//GrabCut��K�p���ē���ꂽmask�ŁA���炩�ȑO�i�Ɣw�i��������Ȃ��s�N�Z����
	//���̑������ɂ��܂�
	dst = 0;
	setNewValFromVal(mask,dst,255,cv::GC_FGD);
	setNewValFromVal(mask,dst,255,cv::GC_PR_FGD);

cv::imshow("dst",dst);
cv::waitKey(30);
	//�w�i�̃}�X�N�ǂݍ���
	cv::Mat bgmask = cv::imread("logomask.png",0);

cv::imshow("bgmask",bgmask);
cv::waitKey(30);
	//bgmask�̔��̕�����GC_BGD(1:���炩�ɔw�i�s�N�Z��)�ɂ���
setNewValFromVal(bgmask,dst,0,255);
cv::imshow("dst",dst);
cv::waitKey(30);


	setNewValFromVal(dst,mask,cv::GC_FGD,255);
	setNewValFromVal(bgmask,mask,cv::GC_BGD,255);

cv::imshow("bg_dst",dst);
cv::waitKey(30);
	//GrabCut�A���S���Y�������s���܂�
	cv::grabCut(img,mask,rect,bgdModel,fgdModel,5,cv::GC_EVAL);
	//�w�i�����������摜���A���摜��mask2���}�X�N�ɂ��č쐬����
	cv::Mat remove_bg_img;
	img.copyTo(remove_bg_img,dst);
	//�w�i�����������摜��\������
	cv::imshow("remove_bg_img",remove_bg_img);
	cv::waitKey(30000);

	return 0;
}

//-------------------------------------------------
//src�̓���̒l(v)�̃s�N�Z����new_val�A���̑��͕ύX���Ȃ�
//-------------------------------------------------
bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v)
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
