//---------------------------------------------------------------------------
#pragma hdrstop

#include <opencv2/opencv.hpp>
#include <windows.h>
#include <stdio.h>
#include "TBGEraser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//-------------------------------------------------
//固定値
//-------------------------------------------------
const TmaskInf TBGEraser::DRAW_BACKGROUND(cv::Scalar(  0,  0,  0), 0);
const TmaskInf TBGEraser::DRAW_FOREGROUND(cv::Scalar(255,255,255), 1);
const TmaskInf TBGEraser::DRAW_RECTANGLE (cv::Scalar(255,  0,  0),-1);

//-------------------------------------------------
//コンストラクタ
//-------------------------------------------------
TBGEraser::TBGEraser()
{
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
	drawing      = false;           // 曲線描画のフラグ
	rectangle    = false;           // 描画範囲矩形のフラグ
	rect_over    = false;           // 四角形が描画されたかどうかを確認するフラグ
	rect_or_mask = 100;             // レククトモードまたはマスクモードを選択するためのフラグ
	value        = DRAW_FOREGROUND; // 図面が前景に初期化されました
	thickness    = 3;               // ブラシの太さ

	img     = cv::imread(file_name);
	img_org = img.clone();                                         // 元の画像のコピー
	mask    = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1); // マスクは背景かもしれないに初期化されました
	output  = cv::Mat::zeros(img.size(),CV_8UC1);                  // 表示される出力画像
	//入出力ウィンドウ
	cv::namedWindow("output");
//	cv::namedWindow("input");
//	cv::setMouseCallback("input",TBGEraser::onmouse,this);
	printf("説明: \n");
	printf("マウスの右ボタンを使用してオブジェクトの周囲に長方形を描きます。\n");

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
	img_org.copyTo(output,mask2);

	return true;
}
//-------------------------------------------------
//背景削除を進める
//-------------------------------------------------
bool TBGEraser::segmentImage()
{
	if (rect_or_mask == 0)
	{
		//矩形領域内の情報を基に初期値を決める
		bgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		fgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		cv::grabCut(img_org,mask,rect,bgdmodel,fgdmodel,1,cv::GC_INIT_WITH_RECT);
		rect_or_mask = 1;
	}
	else if(rect_or_mask == 1)
	{
		//前景/背景を指定する線を基に初期値を決める
		bgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		fgdmodel = cv::Mat::zeros(cv::Size(65,1),CV_64FC1);
		cv::grabCut(img_org,mask,rect,bgdmodel,fgdmodel,1,cv::GC_INIT_WITH_MASK);
	}
	//マスクを更新して出力画像を作成する
	updateMaskAndOutputImage();
	//描画更新
	updateDisplayWindow();

	return true;
}
//-------------------------------------------------
//背景除去画像をpngファイルに保存する
//-------------------------------------------------
bool TBGEraser::saveBGErasedImage(const std::string& file_name)
{
	//最後の . の位置を得る
	std::string::size_type pos = file_name.find_last_of(".");
	//見つかったか
	if(pos == std::string::npos)
	{
		return false;
	}
	//拡張子の切り出し
	std::string extname = file_name.substr(pos,file_name.size()-pos);
	//拡張子を大文字にする
	std::transform(extname.begin(),extname.end(),extname.begin(),std::toupper);
	//拡張子が.PNGかチェック
	if(extname != ".PNG")
	{
		return false;
	}
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
	//画像の保存
	if(cv::imwrite(file_name,save_img) == false)
	{
		return false;
	}
	return true;
}
//-------------------------------------------------
//リセットして最初に戻す
//-------------------------------------------------
bool TBGEraser::resetState()
{
	rect         = cv::Rect(0,0,1,1);
	drawing      = false;
	rectangle    = false;
	rect_or_mask = 100;
	rect_over    = false;
	value        = DRAW_FOREGROUND;
	img          = img_org.clone();
	mask         = cv::Mat::zeros(cv::Size(img.cols,img.rows),CV_8UC1);
	output       = cv::Mat::zeros(img.size(),CV_8UC1);
	//描画更新
	updateDisplayWindow();

	return true;
}
//-------------------------------------------------
//背景指定モードにする
//-------------------------------------------------
bool TBGEraser::setSpecifyBackgroundMode()
{
	//背景指定モード
	value = DRAW_BACKGROUND;

	return true;
}
//-------------------------------------------------
//前景指定モードにする
//-------------------------------------------------
bool TBGEraser::setSpecifyForegroundMode()
{
	//前景指定モード
	value = DRAW_FOREGROUND;

	return true;
}
//-------------------------------------------------
//出力Matを得る
//-------------------------------------------------
bool TBGEraser::getOutputMat(cv::Mat& output_mat)
{
	//内容の有無チェック
	if(output.rows == 0 || output.cols == 0)
	{
		return false;
	}
	//出力Matのコピーをセット
	output_mat = output.clone();

	return true;
}
//-------------------------------------------------
//出力マスクを得る
//-------------------------------------------------
bool TBGEraser::getOutputMasktMat(cv::Mat& mask_mat)
{
	//内容の有無チェック
	if(mask.rows == 0 || mask.cols == 0)
	{
		return false;
	}
	//出力Matのコピーをセット
	mask_mat = mask.clone();

	return true;
}
//-------------------------------------------------
//元画像Matを得る
//-------------------------------------------------
bool TBGEraser::getOriginalMat(cv::Mat& original_mat)
{
	//内容の有無チェック
	if(img_org.rows == 0 || img_org.cols == 0)
	{
		return false;
	}
	//元画像Matのコピーをセット
	original_mat = img_org.clone();

	return true;
}
//-------------------------------------------------
//元マスクを得る
//-------------------------------------------------
bool TBGEraser::getOriginalMaskMat(cv::Mat& original_mask_mat)
{
	//内容の有無チェック
	if(mask.rows == 0 || mask.cols == 0)
	{
		mask = cv::Mat::zeros(img_org.size(),CV_8UC1);
	}
	//元マスクMatのコピーをセット
	original_mask_mat = mask.clone();

	return true;
}
//-------------------------------------------------
//マスクを更新して出力画像を作成する
//-------------------------------------------------
bool TBGEraser::updateMaskAndOutputImage()
{
	//maskが有効であるかチェック
	if(mask.rows > 0 && mask.cols > 0)
	{
		//前景部分を白にしたマスクを作成
		mask2 = cv::Mat::zeros(mask.size(),CV_8UC1);
		setNewValFromVal(mask,mask2,255,1);
		setNewValFromVal(mask,mask2,255,3);
		//元画像にマスクを適用
		output = 0;
		img_org.copyTo(output,mask2);
	}
	return true;
}
//-------------------------------------------------
//描画更新
//-------------------------------------------------
bool TBGEraser::updateDisplayWindow(int millisecond)
{
//	cv::imshow("output",output);
//	cv::imshow("input" ,img);
	//与えれた時間で表示更新
	cv::waitKey(millisecond);

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
			pMe->img = pMe->img_org.clone();
			cv::rectangle(pMe->img,cv::Point(pMe->ix,pMe->iy),cv::Point(x,y),pMe->DRAW_RECTANGLE.color,2);
			pMe->rect = cv::Rect(std::min(pMe->ix,x),std::min(pMe->iy,y),abs(pMe->ix-x),abs(pMe->iy-y));
			pMe->rect_or_mask = 0;
			pMe->updateMaskAndOutputImage();
			pMe->updateDisplayWindow();
		}
	}
	else if(event == cv::EVENT_RBUTTONUP)
	{
		pMe->rectangle = false;
		pMe->rect_over = true;
		cv::rectangle(pMe->img,cv::Point(pMe->ix,pMe->iy),cv::Point(x,y),pMe->DRAW_RECTANGLE.color,2);
		pMe->rect = cv::Rect(std::min(pMe->ix,x),std::min(pMe->iy,y),abs(pMe->ix-x),abs(pMe->iy-y));
		pMe->rect_or_mask = 0;
		pMe->updateMaskAndOutputImage();
		pMe->updateDisplayWindow();
	}
	//タッチアップカーブを描く
	if(event == cv::EVENT_LBUTTONDOWN)
	{
		if(pMe->rect_over == false)
		{
			printf("最初に長方形を描画します\n");
		}
		else
		{
			pMe->drawing = true;
			cv::circle(pMe->img ,cv::Point(x,y),pMe->thickness,pMe->value.color,-1);
			cv::circle(pMe->mask,cv::Point(x,y),pMe->thickness,pMe->value.val,-1);
			pMe->updateMaskAndOutputImage();
			pMe->updateDisplayWindow();
		}
	}
	else if(event == cv::EVENT_MOUSEMOVE)
	{
		if(pMe->drawing == true)
		{
			cv::circle(pMe->img ,cv::Point(x,y),pMe->thickness,pMe->value.color,-1);
			cv::circle(pMe->mask,cv::Point(x,y),pMe->thickness,pMe->value.val,-1);
			pMe->updateMaskAndOutputImage();
			pMe->updateDisplayWindow();
		}
	}
	else if(event == cv::EVENT_LBUTTONUP)
	{
		if(pMe->drawing == true)
		{
			pMe->drawing = false;
			cv::circle(pMe->img,cv::Point(x,y) ,pMe->thickness,pMe->value.color,-1);
			cv::circle(pMe->mask,cv::Point(x,y),pMe->thickness,pMe->value.val,-1);
			pMe->updateMaskAndOutputImage();
			pMe->updateDisplayWindow();
		}
	}
}
