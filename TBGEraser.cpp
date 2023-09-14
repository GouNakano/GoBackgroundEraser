//---------------------------------------------------------------------------
#pragma hdrstop

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include "TBGEraser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TBGEraser *pBGEraser;

//-------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------
TBGEraser::TBGEraser()
{
	// �ϊ��͈͂̋�`�̐F
	BLUE = cv::Scalar(255,0,0);
	// �w�i�ɑ΂���F
	RED  = cv::Scalar(0,0,255);
	// �O�i�ɑ΂���F
	GREEN = cv::Scalar(0,255,0);
	// �w�i��������Ȃ��ɑ΂���F
	BLACK = cv::Scalar(0,0,0);
	// �O�i��������Ȃ��ɑ΂���F
	WHITE = cv::Scalar(255,255,255);
	//���g�̃|�C���^��ݒ�
	pBGEraser = this;
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
bool TBGEraser::init(const std::string& file_name)
{
	//�t���O�̐ݒ�
	rect         = cv::Rect(0,0,1,1);
	drawing      = false;    // flag for drawing curves
	rectangle    = false;    // flag for drawing rect
	rect_over    = false;    // flag to check if rect drawn
	rect_or_mask = 100;      // flag for selecting rect or mask mode
	value        = DRAW_FG;  // drawing initialized to FG
	thickness    = 3;        // brush thickness

	DRAW_BG   .set(BLACK,0);
	DRAW_FG   .set(WHITE,1);
	DRAW_PR_FG.set(GREEN,3);
	DRAW_PR_BG.set(RED  ,2);

	printf("No input image given, so loading default image, ../data/lena.jpg \n");
	printf("Correct Usage: python grabcut.py <filename> \n");

	img    = cv::imread(file_name);
	img2   = img.clone();                                         // a copy of original image
	mask   = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1); // mask initialized to PR_BG
	output = cv::Mat::zeros(img.size(),CV_8UC1);                  // output image to be shown
	// input and output windows
	cv::namedWindow("output");
	cv::namedWindow("input");
	cv::setMouseCallback("input",TBGEraser::onmouse);
	cv::moveWindow("input",img.cols+10,90);
	printf(" Instructions: \n");
	printf(" Draw a rectangle around the object using right mouse button \n");

	return true;
}
//-------------------------------------------------
//���͑҂����[�v�J�n
//-------------------------------------------------
bool TBGEraser::run()
{
	//���͑҂����[�v
	while(true)
	{
		cv::imshow("output",output);
		cv::imshow("input" ,img);

		int k = 0xFF & cv::waitKey(1);
		// key bindings
		if(k == 27)         // esc to exit
		{
			break;
		}
		else if(k == '0') // BG drawing
		{
			printf(" mark background regions with left mouse button \n");
			value = DRAW_BG;
		}
		else if(k == '1') // FG drawing
		{
			printf(" mark foreground regions with left mouse button \n");
			value = DRAW_FG;
		}
		else if(k == '2') // PR_BG drawing
		{
			value = DRAW_PR_BG;
		}
		else if(k == '3') // PR_FG drawing
		{
			value = DRAW_PR_FG;
		}
		else if(k == 's') // save image
		{
			//�ۑ��pMat
			cv::Mat save_img = cv::Mat::zeros(img.size(),CV_8UC4);
			//�����s�N�Z��
			cv::Vec4b alpha0(0,0,0,0);
			//�s�N�Z��
			cv::Vec4b pixcel;
			//���s�N�Z��
			cv::Vec3b src_px3;
			cv::Vec4b src_px4;

			//�`�����l����
			int ch = img.channels();

			//�A���t�@�`�����l���t���s�N�Z���̐ݒ�
			for(int y = 0;y < save_img.rows;y++)
			{
				for(int x = 0;x < save_img.cols;x++)
				{
					//�}�X�N���`�F�b�N
					if(mask2.at<unsigned char>(y,x) == 0)
					{
						//�}�X�N�����Ȃ̂œ����ɂ���
						save_img.at<cv::Vec4b>(y,x) = alpha0;
					}
					else
					{
						//�}�X�N�����Ȃ̂Ō��摜�̃s�N�Z���F��ݒ�
						if(ch == 3)
						{
							src_px3 = img2.at<cv::Vec3b>(y,x);

							pixcel[0] = src_px3[0];
							pixcel[1] = src_px3[1];
							pixcel[2] = src_px3[2];
							pixcel[3] = 255;
							save_img.at<cv::Vec4b>(y,x) = pixcel;
						}
						else if(ch == 4)
						{
							src_px4 = img2.at<cv::Vec4b>(y,x);

							pixcel[0] = src_px4[0];
							pixcel[1] = src_px4[1];
							pixcel[2] = src_px4[2];
							pixcel[3] = 255;
							save_img.at<cv::Vec4b>(y,x) = pixcel;
						}
						else //if(ch == 1)
						{
							unsigned char val = img2.at<unsigned char>(y,x);

							pixcel[0] = val;
							pixcel[1] = val;
							pixcel[2] = val;
							pixcel[3] = 255;
							save_img.at<cv::Vec4b>(y,x) = pixcel;
						}
					}
				}
			}

			cv::imwrite("output.png",save_img);
			printf(" Result saved as image \n");
		}
		else if(k == 'r') // reset everything
		{
			printf("resetting \n");
			rect = cv::Rect(0,0,1,1);
			drawing      = false;
			rectangle    = false;
			rect_or_mask = 100;
			rect_over    = false;
			value        = DRAW_FG;
			img          = img2.clone();
			mask         = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1); // mask initialized to PR_BG
			output       = cv::Mat::zeros(img.size(),CV_8UC1);                  // output image to be shown
		}
		else if(k == 'n') // segment the image
		{
			printf(""" For finer touchups, mark foreground and background after pressing keys 0-3 and again press 'n' \n""");
			if (rect_or_mask == 0)         // grabcut with rect
			{
				bgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
				fgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
				cv::grabCut(img2,mask,rect,bgdmodel,fgdmodel,1,cv::GC_INIT_WITH_RECT);
				rect_or_mask = 1;
			}
			else if(rect_or_mask == 1) // grabcut with mask
			{
				bgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
				fgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
				cv::grabCut(img2,mask,rect,bgdmodel,fgdmodel,1,cv::GC_INIT_WITH_MASK);
			}
		}
		//�O�i�����𔒂ɂ����}�X�N���쐬
		mask2 = cv::Mat::zeros(mask.size(),CV_8UC1);
		setNewValFromVal(mask,mask2,255,1);
		setNewValFromVal(mask,mask2,255,3);

		//���摜�Ƀ}�X�N��K�p
		output = 0;
		img2.copyTo(output,mask2);
	}

	return true;
}
//-------------------------------------------------
//�����I��
//-------------------------------------------------
bool TBGEraser::end()
{
	//�S�Ă�OpenCV�E�B���h�E�����
	cv::destroyAllWindows();

	return true;
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
//mat1,mat2�̓����l�̏���new_val���̑���0�ɂ���
//-------------------------------------------------
bool TBGEraser::setNewValFromSamePixcel(const cv::Mat& mat1,const cv::Mat& mat2,cv::Mat& dst,int new_val)
{
	for(int row=0;row < mat1.rows;row++)
	{
		const unsigned char *p1   = mat1.ptr<unsigned char>(row);
		const unsigned char *p2   = mat2.ptr<unsigned char>(row);
		unsigned char       *pdst = dst .ptr<unsigned char>(row);

		for(int col = 0;col < mat1.cols;col++)
		{
			if(p1[col] == p2[col])
			{
				//���ɂ���
				pdst[col] = new_val;
			}
		}
	}
	return true;
}
//-------------------------------------------------
//�}�E�X�C�x���g
//-------------------------------------------------
void TBGEraser::onmouse(int event,int x,int y,int flags,void *param)
{
	// Draw Rectangle
	if(event == cv::EVENT_RBUTTONDOWN)
	{
		pBGEraser->rectangle = true;
		pBGEraser->ix = x;
		pBGEraser->iy = y;
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(pBGEraser->rectangle == true)
		{
			pBGEraser->img = pBGEraser->img2.clone();
			cv::rectangle(pBGEraser->img,cv::Point(pBGEraser->ix,pBGEraser->iy),cv::Point(x,y),pBGEraser->BLUE,2);
			pBGEraser->rect = cv::Rect(std::min(pBGEraser->ix,x),std::min(pBGEraser->iy,y),abs(pBGEraser->ix-x),abs(pBGEraser->iy-y));
			pBGEraser->rect_or_mask = 0;
		}
	}
	else if(event == cv::EVENT_RBUTTONUP)
	{
		pBGEraser->rectangle = false;
		pBGEraser->rect_over = true;
		cv::rectangle(pBGEraser->img,cv::Point(pBGEraser->ix,pBGEraser->iy),cv::Point(x,y),pBGEraser->BLUE,2);
		pBGEraser->rect = cv::Rect(std::min(pBGEraser->ix,x),std::min(pBGEraser->iy,y),abs(pBGEraser->ix-x),abs(pBGEraser->iy-y));
		pBGEraser->rect_or_mask = 0;
		printf(" Now press the key 'n' a few times until no further change \n");
	}
	//draw touchup curves
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		if(pBGEraser->rect_over == false)
		{
			printf("first draw rectangle \n");
		}
		else
		{
			pBGEraser->drawing = true;
			cv::circle(pBGEraser->img ,cv::Point(x,y),pBGEraser->thickness,pBGEraser->value.color,-1);
			cv::circle(pBGEraser->mask,cv::Point(x,y),pBGEraser->thickness,pBGEraser->value.val,-1);
		}
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(pBGEraser->drawing == true)
		{
			cv::circle(pBGEraser->img ,cv::Point(x,y),pBGEraser->thickness,pBGEraser->value.color,-1);
			cv::circle(pBGEraser->mask,cv::Point(x,y),pBGEraser->thickness,pBGEraser->value.val,-1);
		}
	}
	else if(event == cv::EVENT_LBUTTONUP)
	{
		if(pBGEraser->drawing == true)
		{
			pBGEraser->drawing = false;
			cv::circle(pBGEraser->img,cv::Point(x,y) ,pBGEraser->thickness,pBGEraser->value.color,-1);
			cv::circle(pBGEraser->mask,cv::Point(x,y),pBGEraser->thickness,pBGEraser->value.val,-1);
		}
	}
}