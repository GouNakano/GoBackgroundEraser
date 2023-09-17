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
	//前景を描くモードの値
	static const TmaskInf DRAW_BACKGROUND;
	//背景くモードの値
	static const TmaskInf DRAW_FOREGROUND;
	//変換範囲の矩形の色
	static const TmaskInf DRAW_RECTANGLE;
public:
	//動作モード(初期マスク作成モード、マスク更新モード)
	enum typMode {tmNone=0,tmRect,tmMask};
private:
	cv::Mat    mask2;
	int        thickness;
	bool       drawing;

	bool rectangle;
	bool rect_over;
public:
	cv::Mat    mask;
	cv::Mat    img;
	cv::Mat    img_org;
	cv::Mat    output;
	cv::Rect   rect;
	typMode    rect_or_mask;
	TmaskInf   value;

private:
	//srcの特定の値(v)のピクセルをnew_val、その他は変更しない
	bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);
public:
	//コンストラクタ
	TBGEraser();
	//デストラクタ
	virtual ~TBGEraser();
public:
	//初期値設定
	bool init();
	//画像の読込
	bool readImage(const std::string& file_name);
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
	//出力Matを得る
	bool getOutputMat(cv::Mat& output_mat);
	//出力Matをセット
	bool setOutputMat(cv::Mat& output_mat);
	//出力マスクを得る
	bool getOutputMasktMat(cv::Mat& mask_mat);
	//出力マスクをセット
	bool setOutputMasktMat(cv::Mat& mask_mat);
	//元画像Matを得る
	bool getOriginalMat(cv::Mat& original_mat);
	//元マスクを得る
	bool getOriginalMaskMat(cv::Mat& original_mask_mat);
public:
	//マスクを更新して出力画像を作成する
	bool updateMaskAndOutputImage();
public:
	//描画幅を取得
	int getThickness();
	//マスク描画モードの有無を取得
	bool getDrawing();
	//マスク描画モードの有無をセット
	void setDrawing(bool is_draw);
};

#endif
