//---------------------------------------------------------------------------
#ifndef OrgImgDispFrmH
#define OrgImgDispFrmH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <opencv2/opencv.hpp>
//---------------------------------------------------------------------------
class TOrgImgDispForm : public TForm
{
__published:	// IDE で管理されるコンポーネント
	TPanel *ImageBasePanel;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ImageBasePanelResize(TObject *Sender);
private:
	HWND      hWnd1;
	HWND      hWnd1_parent;
	//ウィンドウサイズ
	cv::Size win_sz;
	//画像のMat
	cv::Mat  imageMat;
	//表示Mat
	cv::Mat  displayMat;
private:
	//描画用Matで表示更新
	void updateDispFromDrawMat();
	//画像の表示の大きさに合わせた描画用画像を作成する
	void makeDrawMatFromOrignalMat();
public:
	__fastcall TOrgImgDispForm(TComponent* Owner);
public:
	//表示画像のMatを設定
	bool setDisplayMat(const cv::Mat& disp_mat);
};
//---------------------------------------------------------------------------
extern PACKAGE TOrgImgDispForm *OrgImgDispForm;
//---------------------------------------------------------------------------
#endif
