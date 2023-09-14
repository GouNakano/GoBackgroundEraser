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
	cv::Scalar BLUE;    // �ϊ��͈͂̋�`�̐F
	cv::Scalar RED;     // �w�i�ɑ΂���F
	cv::Scalar GREEN;   // �O�i�ɑ΂���F
	cv::Scalar BLACK;   // �w�i��������Ȃ��ɑ΂���F
	cv::Scalar WHITE;   // �O�i��������Ȃ��ɑ΂���F

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
	TmaskInf   DRAW_PR_FG;
	TmaskInf   DRAW_PR_BG;
private:
	//src�̓���̒l(v)�̃s�N�Z����new_val�A���̑��͕ύX���Ȃ�
	bool setNewValFromVal(const cv::Mat& src,cv::Mat& dst,int new_val,int v);
	//mat1,mat2�̓����l�̏���new_val���̑���0�ɂ���
	bool setNewValFromSamePixcel(const cv::Mat& mat1,const cv::Mat& mat2,cv::Mat& dst,int new_val);
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
	//���͑҂����[�v�J�n
	bool run();
	//�����I��
	bool end();
};

#endif