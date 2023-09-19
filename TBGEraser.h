//---------------------------------------------------------------------------
#ifndef TBGEraserH
#define TBGEraserH
#include <string>
#include <stack>
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

//動作モード(初期マスク作成モード、マスク更新モード)
enum typBGEMode {tmNone=0,tmRect,tmMask};

//Undoのために蓄える情報の型
class TUndotiness
{
private:
	cv::Mat     original_mat;
	cv::Mat     original_mask_mat;
	typBGEMode  mode;
private:
	void _copy(const TUndotiness& him)
	{
		original_mat      = him.original_mat.clone();
		original_mask_mat = him.original_mask_mat.clone();
		mode              = him.mode;
	}
public:
	//コンストラクタ
	TUndotiness()
	{
		mode = tmNone;
	}
	//コピーコンストラクタ
	TUndotiness(const TUndotiness& him)
	{
		_copy(him);
	}
	//値セットコンストラクタ
	TUndotiness(const cv::Mat& disp,const cv::Mat& msk,typBGEMode md)
	{
		set(disp,msk,md);
	}
	//デストラクタ
	virtual ~TUndotiness()
	{
		original_mat.release();
		original_mask_mat.release();
	}
public:
	//=演算子
	TUndotiness& operator = (const TUndotiness& him)
	{
		_copy(him);

		return *this;
	}
public:
	//値のセット
	bool set(const cv::Mat& disp,const cv::Mat& msk,typBGEMode md)
	{
		original_mat      = disp.clone();
		original_mask_mat = msk.clone();
		mode              = md;

		return true;
	}
	//値の取得
	bool get(cv::Mat& disp,cv::Mat& msk,typBGEMode& md)
	{
		disp = original_mat.clone();
		msk  = original_mask_mat.clone();
		mode = md;

		return true;
	}

};

//背景除去クラス
class TBGEraser
{
public:
	//前景を描くモードの値
	static const TmaskInf DRAW_BACKGROUND;
	//背景くモードの値
	static const TmaskInf DRAW_FOREGROUND;
	//変換範囲の矩形の色
	static const TmaskInf DRAW_RECTANGLE;
private:
	cv::Mat    mask2;
	int        thickness;
	bool       drawing;

	bool rectangle;
	bool rect_over;
	//元に戻すを実現するためのスタック
	std::stack<TUndotiness> histStack;
public:
	cv::Mat    mask;
	cv::Mat    img;
	cv::Mat    img_org;
	cv::Mat    output;
	cv::Rect   rect;
	typBGEMode rect_or_mask;
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
	//Undo情報をPushする
	bool pushUndoInf();
	//Undoを実行する
	bool undo();
public:
	//マスクを更新して出力画像を作成する
	bool updateMaskAndOutputImage();
public:
	//ブラシの太さを取得
	int getThickness();
	//ブラシの太さをセット
	bool setThickness(int tn);
	//マスク描画モードの有無を取得
	bool getDrawing();
	//マスク描画モードの有無をセット
	void setDrawing(bool is_draw);
};



#endif
