#pragma hdrstop
#pragma argsused

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>

//srcの特定の値(v)のピクセルをnew_val、その他は変更しない
bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);

int main(int argc, char* argv[])
{
	cv::Mat img     = cv::imread("messi5.png");

	cv::Mat  bgdModel;
	cv::Mat  fgdModel;
	cv::Rect rect(1,1,img.cols-2,img.rows-2);

	cv::Mat mask = cv::Mat(img.size(),CV_8UC1);
	mask.setTo(cv::Scalar::all(cv::GC_PR_FGD));
	//セグメンテーションの初期化
	cv::grabCut(img,mask,rect,bgdModel,fgdModel,1,cv::GC_INIT_WITH_RECT);

	//srcの特定の値のピクセルをnew_val、その他を0にする
	cv::Mat dst = cv::Mat::zeros(mask.size(),CV_8UC1);
	setNewValFromVal(mask,dst,255,cv::GC_FGD);
	setNewValFromVal(mask,dst,255,cv::GC_PR_FGD);
	cv::imshow("dst",dst);
	cv::waitKey(30);

	//追加のマスク読み込み
	cv::Mat newmask = cv::imread("newmask.png",0);
	//dstと追加のマスクを合成
	dst |= newmask;
	//dstの白の部分をGC_FGD(1:明らかな前景(物体)ピクセル)にする
	mask = 0;
	setNewValFromVal(dst,mask,cv::GC_FGD,255);
	//GrabCutアルゴリズムを実行します
	cv::grabCut(img,mask,rect,bgdModel,fgdModel,1,cv::GC_EVAL);

	//GrabCutを適用して得られたmaskで、明らかな前景と背景かもしれないピクセルを白
	//その他を黒にします
	dst = 0;
	setNewValFromVal(mask,dst,255,cv::GC_FGD);
	setNewValFromVal(mask,dst,255,cv::GC_PR_FGD);

cv::imshow("dst",dst);
cv::waitKey(30);
	//背景のマスク読み込み
	cv::Mat bgmask = cv::imread("logomask.png",0);

cv::imshow("bgmask",bgmask);
cv::waitKey(30);
	//bgmaskの白の部分をGC_BGD(1:明らかに背景ピクセル)にする
setNewValFromVal(bgmask,dst,0,255);
cv::imshow("dst",dst);
cv::waitKey(30);


	setNewValFromVal(dst,mask,cv::GC_FGD,255);
	setNewValFromVal(bgmask,mask,cv::GC_BGD,255);

cv::imshow("bg_dst",dst);
cv::waitKey(30);
	//GrabCutアルゴリズムを実行します
	cv::grabCut(img,mask,rect,bgdModel,fgdModel,5,cv::GC_EVAL);
	//背景を除去した画像を、元画像にmask2をマスクにして作成する
	cv::Mat remove_bg_img;
	img.copyTo(remove_bg_img,dst);
	//背景を除去した画像を表示する
	cv::imshow("remove_bg_img",remove_bg_img);
	cv::waitKey(30000);

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
