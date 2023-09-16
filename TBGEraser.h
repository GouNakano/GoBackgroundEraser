//---------------------------------------------------------------------------
#ifndef TBGEraserH
#define TBGEraserH
#include <string>
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
	cv::Mat    img;
	cv::Mat    img2;
	cv::Mat    mask;
	cv::Mat    mask2;
	cv::Mat    output;
	cv::Mat    bgdmodel;
	cv::Mat    fgdmodel;
	cv::Mat    disp_mat;
	bool       drawing;
	TmaskInf   value;
	bool       rectangle;
	cv::Rect   rect;
	int        rect_or_mask;
	int        ix;
	int        iy;
	bool       rect_over;
	int        thickness;

private:
	//src�̓���̒l(v)�̃s�N�Z����new_val�A���̑��͕ύX���Ȃ�
	bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);
	//mat1,mat2�̓����l�̏���new_val���̑���0�ɂ���
	bool setNewValFromSamePixcel(const cv::Mat& mat1,const cv::Mat& mat2,cv::Mat& dst,int new_val);
	//�}�X�N���X�V���ďo�͉摜���쐬����
	bool updateMaskAndOutputImage();
public:
	//�}�E�X�C�x���g
	static void onmouse(int event,int x,int y,int flags,void *param);
public:
	//�R���X�g���N�^
	TBGEraser();
	//�f�X�g���N�^
	virtual ~TBGEraser();
public:
	//�����l�ݒ�
	bool init(const std::string& file_name);
	//�`��X�V
	bool updateDisplayWindow(int millisecond=1);
	//�����I��
	bool end();
	//�w�i�폜��i�߂�
	bool segmentImage();
	//�w�i�����摜��png�t�@�C���ɕۑ�����
	bool saveBGErasedImage(const std::string& file_name);
	//���Z�b�g���čŏ��ɖ߂�
	bool resetState();
	//�w�i�w�胂�[�h�ɂ���
	bool setSpecifyBackgroundMode();
	//�w�i�w�胂�[�h�ɂ���
	bool setSpecifyForegroundMode();
	//�o��Mat�𓾂�
	bool getOutputMat(cv::Mat& output_mat);
};

#endif
