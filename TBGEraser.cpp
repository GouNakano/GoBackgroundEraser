//---------------------------------------------------------------------------
#pragma hdrstop

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include "TBGEraser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------
TBGEraser::TBGEraser()
{
	// 変換範囲の矩形の色
	BLUE = cv::Scalar(255,0,0);
	// 背景に対する色
	RED  = cv::Scalar(0,0,255);
	// 前景に対する色
	GREEN = cv::Scalar(0,255,0);
	// 背景かもしれないに対する色
	BLACK = cv::Scalar(0,0,0);
	// 前景かもしれないに対する色
	WHITE = cv::Scalar(255,255,255);
}
//-------------------------------------------------
//デストラクタ
//-------------------------------------------------
TBGEraser::~TBGEraser()
{
}
//-------------------------------------------------
//初期値設定
//-------------------------------------------------
bool TBGEraser::init(const std::string& file_name)
{
	//フラグの設定
	rect         = cv::Rect(0,0,1,1);
	drawing      = false;    // 曲線描画のフラグ
	rectangle    = false;    // 描画範囲矩形のフラグ
	rect_over    = false;    // 四角形が描画されたかどうかを確認するフラグ
	rect_or_mask = 100;      // レククトモードまたはマスクモードを選択するためのフラグ
	value        = DRAW_FG;  // 図面が前景に初期化されました
	thickness    = 3;        // ブラシの太さ

	DRAW_BG   .set(BLACK,0);
	DRAW_FG   .set(WHITE,1);
	DRAW_PR_FG.set(GREEN,3);
	DRAW_PR_BG.set(RED  ,2);

	img    = cv::imread(file_name);
	img2   = img.clone();                                         // 元の画像のコピー
	mask   = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1); // マスクは背景かもしれないに初期化されました
	output = cv::Mat::zeros(img.size(),CV_8UC1);                  // 表示される出力画像
	//入出力ウィンドウ
	cv::namedWindow("output");
	cv::namedWindow("input");
	cv::setMouseCallback("input",TBGEraser::onmouse,this);
	cv::moveWindow("input",img.cols+10,90);
	printf(" 説明: \n");
	printf(" マウスの右ボタンを使用してオブジェクトの周囲に長方形を描きます。\n");

	return true;
}
//-------------------------------------------------
//入力待ち(返却値がfalseの時は終了予定)
//-------------------------------------------------
bool TBGEraser::run(int PressKey)
{
	cv::imshow("output",output);
	cv::imshow("input" ,img);

	int k;
	//押下したキーをセット
	if(PressKey > 0)
	{
		//MainFormで押下されたキーをセット
		k = PressKey;
		//描画
		cv::waitKey(1);
	}
	else
	{
		//OpenCVで押下されたキーをセット
		k = 0xFF & cv::waitKey(1);
		k = std::toupper(k);
	}
	// キーによる処理分け
	if(k == VK_ESCAPE)
	{
		//ESCキー押下で終了
		return false;
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
	else if(k == 'S') // save image
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
	else if(k == 'R') // reset everything
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
	//前景部分を白にしたマスクを作成
	mask2 = cv::Mat::zeros(mask.size(),CV_8UC1);
	setNewValFromVal(mask,mask2,255,1);
	setNewValFromVal(mask,mask2,255,3);

	//元画像にマスクを適用
	output = 0;
	img2.copyTo(output,mask2);

	return true;
}
//-------------------------------------------------
//処理終了
//-------------------------------------------------
bool TBGEraser::end()
{
	//全てのOpenCVウィンドウを閉じる
	cv::destroyAllWindows();

	//前景部分を白にしたマスクを作成
	mask2 = cv::Mat::zeros(mask.size(),CV_8UC1);
	setNewValFromVal(mask,mask2,255,1);
	setNewValFromVal(mask,mask2,255,3);

	//元画像にマスクを適用
	output = 0;
	img2.copyTo(output,mask2);

	return true;
}
//-------------------------------------------------
//背景削除を進める
//-------------------------------------------------
bool TBGEraser::segmentImage()
{
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
	//マスクを更新して出力画像を作成する
	updateMaskAndOutputImage();
	//描画更新
	updateDisplayWindow();

	return true;
}
//-------------------------------------------------
//マスクを更新して出力画像を作成する
//-------------------------------------------------
bool TBGEraser::updateMaskAndOutputImage()
{
	//前景部分を白にしたマスクを作成
	mask2 = cv::Mat::zeros(mask.size(),CV_8UC1);
	setNewValFromVal(mask,mask2,255,1);
	setNewValFromVal(mask,mask2,255,3);
	//元画像にマスクを適用
	output = 0;
	img2.copyTo(output,mask2);

	return true;
}
//-------------------------------------------------
//描画更新
//-------------------------------------------------
bool TBGEraser::updateDisplayWindow()
{
	cv::imshow("output",output);
	cv::imshow("input" ,img);
	cv::waitKey(30);

	return true;
}
//-------------------------------------------------
//srcの特定の値(v)のピクセルをnew_val、その他は変更しない
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
				//白にする
				pdst[col] = new_val;
			}
		}
	}
	return true;
}
//-------------------------------------------------
//mat1,mat2の同じ値の所をnew_valその他を0にする
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
				//白にする
				pdst[col] = new_val;
			}
		}
	}
	return true;
}
//-------------------------------------------------
//マウスイベント
//-------------------------------------------------
void TBGEraser::onmouse(int event,int x,int y,int flags,void *param)
{
	//自身を得る
	TBGEraser *pMe = static_cast<TBGEraser *>(param);

	// Draw Rectangle
	if(event == cv::EVENT_RBUTTONDOWN)
	{
		pMe->rectangle = true;
		pMe->ix = x;
		pMe->iy = y;
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(pMe->rectangle == true)
		{
			pMe->img = pMe->img2.clone();
			cv::rectangle(pMe->img,cv::Point(pMe->ix,pMe->iy),cv::Point(x,y),pMe->BLUE,2);
			pMe->rect = cv::Rect(std::min(pMe->ix,x),std::min(pMe->iy,y),abs(pMe->ix-x),abs(pMe->iy-y));
			pMe->rect_or_mask = 0;
		}
	}
	else if(event == cv::EVENT_RBUTTONUP)
	{
		pMe->rectangle = false;
		pMe->rect_over = true;
		cv::rectangle(pMe->img,cv::Point(pMe->ix,pMe->iy),cv::Point(x,y),pMe->BLUE,2);
		pMe->rect = cv::Rect(std::min(pMe->ix,x),std::min(pMe->iy,y),abs(pMe->ix-x),abs(pMe->iy-y));
		pMe->rect_or_mask = 0;
		printf(" Now press the key 'n' a few times until no further change \n");
	}
	//draw touchup curves
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		if(pMe->rect_over == false)
		{
			printf("first draw rectangle \n");
		}
		else
		{
			pMe->drawing = true;
			cv::circle(pMe->img ,cv::Point(x,y),pMe->thickness,pMe->value.color,-1);
			cv::circle(pMe->mask,cv::Point(x,y),pMe->thickness,pMe->value.val,-1);
		}
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(pMe->drawing == true)
		{
			cv::circle(pMe->img ,cv::Point(x,y),pMe->thickness,pMe->value.color,-1);
			cv::circle(pMe->mask,cv::Point(x,y),pMe->thickness,pMe->value.val,-1);
		}
	}
	else if(event == cv::EVENT_LBUTTONUP)
	{
		if(pMe->drawing == true)
		{
			pMe->drawing = false;
			cv::circle(pMe->img,cv::Point(x,y) ,pMe->thickness,pMe->value.color,-1);
			cv::circle(pMe->mask,cv::Point(x,y),pMe->thickness,pMe->value.val,-1);
		}
	}
}
