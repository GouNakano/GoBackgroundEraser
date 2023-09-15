//---------------------------------------------------------------------------
#ifndef TBGEraserH
#define TBGEraserH
#include <string>
#include <opencv2/opencv.hpp>
//---------------------------------------------------------------------------
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
public:
	bool set(cv::Scalar c,int v)
	{
		color = c;
		val   = v;

		return true;
	}
};


class TBGEraser
{
public:
	cv::Scalar BLUE;    // 変換範囲の矩形の色
	cv::Scalar RED;     // 背景に対する色
	cv::Scalar GREEN;   // 前景に対する色
	cv::Scalar BLACK;   // 背景かもしれないに対する色
	cv::Scalar WHITE;   // 前景かもしれないに対する色

	cv::Mat    img;
	cv::Mat    img2;
	cv::Mat    mask;
	cv::Mat    mask2;
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

	TmaskInf   DRAW_BG;
	TmaskInf   DRAW_FG;
private:
	//srcの特定の値(v)のピクセルをnew_val、その他は変更しない
	bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);
	//mat1,mat2の同じ値の所をnew_valその他を0にする
	bool setNewValFromSamePixcel(const cv::Mat& mat1,const cv::Mat& mat2,cv::Mat& dst,int new_val);
	//マスクを更新して出力画像を作成する
	bool updateMaskAndOutputImage();
public:
	//マウスイベント
	static void onmouse(int event,int x,int y,int flags,void *param);
public:
	//コンストラクタ
	TBGEraser();
	//デストラクタ
	virtual ~TBGEraser();
public:
	//初期値設定
	bool init(const std::string& file_name);
	//描画更新
	bool updateDisplayWindow(int millisecond=1);
	//処理終了
	bool end();
	//背景削除を進める
	bool segmentImage();
	//背景除去画像をpngファイルに保存する
	bool saveBGErasedImage(const std::string& file_name);
	//リセットして最初に戻す
	bool resetState();
	//背景指定モードにする
	bool setSpecifyBackgroundMode();
	//背景指定モードにする
	bool setSpecifyForegroundMode();
};

#endif
