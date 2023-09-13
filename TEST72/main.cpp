//---------------------------------------------------------------------------
#pragma hdrstop
#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma argsused

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>

//マスクに関する情報の型
struct TmaskInf
{
public:
	cv::Scalar color;
	int        val;
public:
	TmaskInf()
	{
		color = cv::Scalar(0);
		val   = 0;
	}
	TmaskInf(cv::Scalar c,int v)
	{
		color = c;
		val   = v;
	}
	TmaskInf(const TmaskInf& him)
	{
		color = him.color;
		val   = him.val;
	}
public:
	TmaskInf& operator = (const TmaskInf& him)
	{
		color = him.color;
		val   = him.val;

		return *this;
	}
};
typedef std::tuple<std::string,cv::Scalar,std::string,int> TmaskTuple;
//srcの特定の値(v)のピクセルをnew_val、その他は変更しない
bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);

//===============================================================================
// Interactive Image Segmentation using GrabCut algorithm.
// This sample shows interactive image segmentation using grabcut algorithm.
// USAGE:
//  python grabcut.py <filename>
// README FIRST:
//	Two windows will show up, one for input and one for output.
//	At first, in input window, draw a rectangle around the object using
// mouse right button. Then press 'n' to segment the object (once or a few times)
// For any finer touch-ups, you can press any of the keys below and draw lines on
// the areas you want. Then again press 'n' for updating the output.
// Key '0' - To select areas of sure background
// Key '1' - To select areas of sure foreground
// Key '2' - To select areas of probable background
// Key '3' - To select areas of probable foreground
// Key 'n' - To update the segmentation
// Key 'r' - To reset the setup
// Key 's' - To save the results
//===============================================================================

cv::Mat    img;
cv::Mat    img2;
cv::Mat    mask;
cv::Mat    mask2;
cv::Mat    mask3;
cv::Mat    output;
cv::Mat    bgdmodel;
cv::Mat    fgdmodel;
bool       drawing;
TmaskInf   value;
bool       rectangle;
cv::Rect   rect;
int        rect_or_mask;
int        ix;
int        iy;
bool       rect_over;
int        thickness;
cv::Scalar BLUE(255,0,0);        // 変換範囲の矩形の色
cv::Scalar RED(0,0,255);         // 背景に対する色
cv::Scalar GREEN(0,255,0);       // 前景に対する色
cv::Scalar BLACK(0,0,0);         // 背景かもしれないに対する色
cv::Scalar WHITE(255,255,255);   // 前景かもしれないに対する色

TmaskInf DRAW_BG   (BLACK,0);
TmaskInf DRAW_FG   (WHITE,1);
TmaskInf DRAW_PR_FG(GREEN,3);
TmaskInf DRAW_PR_BG(RED  ,2);


//-------------------------------------------------
//マウスイベント
//-------------------------------------------------
static void onmouse(int event,int x,int y,int flags,void *param)
{
	// Draw Rectangle
	if(event == cv::EVENT_RBUTTONDOWN)
	{
		rectangle = true;
		ix = x;
		iy = y;
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(rectangle == true)
		{
			img = img2.clone();
			cv::rectangle(img,cv::Point(ix,iy),cv::Point(x,y),BLUE,2);
			rect = cv::Rect(std::min(ix,x),std::min(iy,y),abs(ix-x),abs(iy-y));
			rect_or_mask = 0;
		}
	}
	else if(event == cv::EVENT_RBUTTONUP)
	{
		rectangle = false;
		rect_over = true;
		cv::rectangle(img,cv::Point(ix,iy),cv::Point(x,y),BLUE,2);
		rect = cv::Rect(std::min(ix,x),std::min(iy,y),abs(ix-x),abs(iy-y));
		rect_or_mask = 0;
		printf(" Now press the key 'n' a few times until no further change \n");
	}
	//draw touchup curves
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		if(rect_over == false)
		{
			printf("first draw rectangle \n");
		}
		else
		{
			drawing = true;
			cv::circle(img ,cv::Point(x,y),thickness,value.color,-1);
			cv::circle(mask,cv::Point(x,y),thickness,value.val,-1);
		}
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(drawing == true)
		{
			cv::circle(img ,cv::Point(x,y),thickness,value.color,-1);
			cv::circle(mask,cv::Point(x,y),thickness,value.val,-1);
		}
	}
	else if(event == cv::EVENT_LBUTTONUP)
	{
		if(drawing == true)
		{
			drawing = false;
			cv::circle(img,cv::Point(x,y) ,thickness,value.color,-1);
			cv::circle(mask,cv::Point(x,y),thickness,value.val,-1);
		}
	}
}
//-------------------------------------------------
//mat1,mat2の同じ値の所をnew_valその他を0にする
//-------------------------------------------------
bool setNewValFromSamePixcel(const cv::Mat& mat1,const cv::Mat& mat2,cv::Mat& dst,int new_val)
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
				//白にする
				pdst[col] = new_val;
			}
		}
	}
	return true;
}

//-------------------------------------------------
//メイン関数
//-------------------------------------------------
int main(int argc, char* argv[])
{
	std::string filename;

	//フラグの設定
	rect = cv::Rect(0,0,1,1);
	drawing      = false;    // flag for drawing curves
	rectangle    = false;    // flag for drawing rect
	rect_over    = false;    // flag to check if rect drawn
	rect_or_mask = 100;      // flag for selecting rect or mask mode
	value        = DRAW_FG;  // drawing initialized to FG
	thickness    = 3;        // brush thickness

	if(argc == 2)
	{
		filename = argv[1]; // for drawing purposes
	}
	else
	{
		printf("No input image given, so loading default image, ../data/lena.jpg \n");
		printf("Correct Usage: python grabcut.py <filename> \n");
		filename = "messi5.png";
	}
	img    = cv::imread(filename);
	img2   = img.clone();                                         // a copy of original image
	mask   = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1); // mask initialized to PR_BG
	output = cv::Mat::zeros(img.size(),CV_8UC1);                  // output image to be shown
	// input and output windows
	cv::namedWindow("output");
	cv::namedWindow("input");
	cv::setMouseCallback("input",onmouse);
	cv::moveWindow("input",img.cols+10,90);
	printf(" Instructions: \n");
	printf(" Draw a rectangle around the object using right mouse button \n");

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
			//保存用Mat
			cv::Mat save_img = cv::Mat::zeros(img.size(),CV_8UC4);
			//透明ピクセル
			cv::Vec4b alpha0(0,0,0,0);
			//ピクセル
			cv::Vec4b pixcel;
			//元ピクセル
			cv::Vec3b src_px3;
			cv::Vec4b src_px4;

			//チャンネル数
			int ch = img.channels();

			//アルファチャンネル付きピクセルの設定
			for(int y = 0;y < save_img.rows;y++)
			{
				for(int x = 0;x < save_img.cols;x++)
				{
					//マスクをチェック
					if(mask2.at<unsigned char>(y,x) == 0)
					{
						//マスクが黒なので透明にする
						save_img.at<cv::Vec4b>(y,x) = alpha0;
					}
					else
					{
						//マスクが白なので元画像のピクセル色を設定
						if(ch == 3)
						{
							src_px3 = img.at<cv::Vec3b>(y,x);

							pixcel[0] = src_px3[0];
							pixcel[1] = src_px3[1];
							pixcel[2] = src_px3[2];
							pixcel[3] = 255;
							save_img.at<cv::Vec4b>(y,x) = pixcel;
						}
						else if(ch == 4)
						{
							src_px4 = img.at<cv::Vec4b>(y,x);

							pixcel[0] = src_px4[0];
							pixcel[1] = src_px4[1];
							pixcel[2] = src_px4[2];
							pixcel[3] = 255;
							save_img.at<cv::Vec4b>(y,x) = pixcel;
						}
						else //if(ch == 1)
						{
							unsigned char val = img.at<unsigned char>(y,x);

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
		//前景部分を白にしたマスクを作成
		mask2 = cv::Mat::zeros(mask.size(),CV_8UC1);
		setNewValFromVal(mask,mask2,255,1);
		setNewValFromVal(mask,mask2,255,3);

		//元画像にマスクを適用
		output = 0;
		img2.copyTo(output,mask2);
	}

	cv::destroyAllWindows();

	return 0;
}

//-------------------------------------------------
//srcの特定の値(v)のピクセルをnew_val、その他は変更しない
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
				//白にする
				pdst[col] = new_val;
			}
		}
	}
	return true;
}

