//---------------------------------------------------------------------------
#ifndef TBGEraserH
#define TBGEraserH
#include <string>
#include <stack>
#include <opencv2/opencv.hpp>
//---------------------------------------------------------------------------
//�}�X�N�Ɋւ�����̌^
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

//���샂�[�h(�����}�X�N�쐬���[�h�A�}�X�N�X�V���[�h)
enum typBGEMode {tmNone=0,tmRect,tmMask};

//Undo�̂��߂ɒ~������̌^
class TUndotiness
{
private:
	cv::Mat     original_mat;
	cv::Mat     original_mask_mat;
	cv::Rect    rect;
	typBGEMode  mode;
private:
	void _copy(const TUndotiness& him)
	{
		original_mat      = him.original_mat.clone();
		original_mask_mat = him.original_mask_mat.clone();
		rect              = him.rect;
		mode              = him.mode;
	}
public:
	//�R���X�g���N�^
	TUndotiness()
	{
		mode = tmNone;
	}
	//�R�s�[�R���X�g���N�^
	TUndotiness(const TUndotiness& him)
	{
		_copy(him);
	}
	//�l�Z�b�g�R���X�g���N�^
	TUndotiness(const cv::Mat& disp,const cv::Mat& msk,const cv::Rect& r,typBGEMode md)
	{
		set(disp,msk,r,md);
	}
	//�f�X�g���N�^
	virtual ~TUndotiness()
	{
		original_mat.release();
		original_mask_mat.release();
	}
public:
	//=���Z�q
	TUndotiness& operator = (const TUndotiness& him)
	{
		_copy(him);

		return *this;
	}
public:
	//�l�̃Z�b�g
	bool set(const cv::Mat& disp,const cv::Mat& msk,const cv::Rect& r,typBGEMode md)
	{
		original_mat      = disp.clone();
		original_mask_mat = msk.clone();
		rect              = r;
		mode              = md;

		return true;
	}
	//�l�̎擾
	bool get(cv::Mat& disp,cv::Mat& msk,cv::Rect& r,typBGEMode& md)
	{
		disp = original_mat.clone();
		msk  = original_mask_mat.clone();
		r    = rect;
		md   = mode;

		return true;
	}

};

//�w�i�����N���X
class TBGEraser
{
public:
	//�O�i��`�����[�h�̒l
	static const TmaskInf DRAW_BACKGROUND;
	//�w�i�����[�h�̒l
	static const TmaskInf DRAW_FOREGROUND;
	//�ϊ��͈͂̋�`�̐F
	static const TmaskInf DRAW_RECTANGLE;
private:
	int        thickness;
	bool       drawing;
	bool       rectangle;
	bool       rect_over;
	cv::Mat    mask;
	cv::Mat    img_org;
	cv::Mat    output;
	cv::Rect   rect;
	typBGEMode BGEMode;
	TmaskInf   maskInf;
	//���ɖ߂����������邽�߂̃X�^�b�N
	std::stack<TUndotiness> histStack;
public:

private:
	//src�̓���̒l(v)�̃s�N�Z����new_val�A���̑��͕ύX���Ȃ�
	bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);
public:
	//�R���X�g���N�^
	TBGEraser();
	//�f�X�g���N�^
	virtual ~TBGEraser();
public:
	//�����l�ݒ�
	bool init();
	//�摜�̓Ǎ�
	bool readImage(const std::string& file_name);
	//�w�i�폜��i�߂�
	bool segmentImage();
	//�w�i�����摜��png�t�@�C���ɕۑ�����
	bool saveBGErasedImage(const std::string& file_name);
	//�w�i�w�胂�[�h�ɂ���
	bool setSpecifyBackgroundMode();
	//�w�i�w�胂�[�h�ɂ���
	bool setSpecifyForegroundMode();
	//�o��Mat�𓾂�
	bool getOutputMat(cv::Mat& output_mat);
	//�o��Mat���Z�b�g
	bool setOutputMat(const cv::Mat& output_mat);
	//�͈͂��擾
	cv::Rect getSelectRect();
	//�͈͂��Z�b�g
	bool setSelectRect(const cv::Rect& r);
	//�o�̓}�X�N�𓾂�
	bool getOutputMasktMat(cv::Mat& mask_mat);
	//�o�̓}�X�N���Z�b�g
	bool setOutputMasktMat(cv::Mat& mask_mat);
	//���摜Mat�𓾂�
	bool getOriginalMat(cv::Mat& original_mat);
	//���}�X�N�𓾂�
	bool getOriginalMaskMat(cv::Mat& original_mask_mat);
	//Undo����Push����
	bool pushUndoInf();
	//Undo����pop����(undo�̎��s�̓L�����Z��
	bool popUndoInf();
	//Undo�����s����
	bool undo();
	//BGE���[�h�𓾂�
	typBGEMode getBGEMode();
	//BGE���[�h���Z�b�g
	bool setBGEMode(typBGEMode mde);
	//�}�X�N�Ɋւ�����𓾂�
	const TmaskInf& getMaskInf();
public:
	//�}�X�N���X�V���ďo�͉摜���쐬����
	bool updateMaskAndOutputImage();
public:
	//�u���V�̑������擾
	int getThickness();
	//�u���V�̑������Z�b�g
	bool setThickness(int tn);
	//�}�X�N�`�惂�[�h�̗L�����擾
	bool getDrawing();
	//�}�X�N�`�惂�[�h�̗L�����Z�b�g
	void setDrawing(bool is_draw);
};



#endif