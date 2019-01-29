
// MainprojectDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

#define pi 3.141592653589793238462643383279



// CMainprojectDlg ��ȭ ����
class CMainprojectDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMainprojectDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CStatic m_Frame;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	//��ư ����ִ� ����
	int pick_button = 0;

	//�̸�Ƽ�� ����
	Mat emoticon;
	Mat emoticon_sec;
	Mat pre_emotiocn;

	//��ġ����
	Point pos[10];

	//�ð�����
	int count_time[10] = { 0, };
	int add_count_time2 = 2;

	//�ð���� ����
	system_clock::time_point start = system_clock::now();
	system_clock::time_point end = system_clock::now();
	duration<double> now_time;
	int time_flag = 0;

	//�̸��� ��� ����
	CString email_string;

	//������ ����
	int rand1 = 0;
	int rand2 = 0;

	//gif���� ���� ����
	VideoCapture gif[5];
	Mat dog, cat, heart_background, rabbit_background;
	int gif_count[5] = { 0, };
	int swit[3] = { 0, };
	

	//��ư�̹��� ����
	CBitmap bit1;
	CBitmap bit2;

	//editbox ���� ����
	CFont font;

	//���� ĸó����
	VideoCapture *cam;
	Mat frame;
	CImage cimage_mfc;
	CStatic m_picture;

	//��ư ����
	CButton button1;
	CButton button2;
	CButton button3;
	CButton button4;
	CButton take_picture;


	//���νĿ�
	cv::Ptr<cuda::CascadeClassifier> detect_face;

	//���� �Լ���
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();

	//��Ʈ�ѵ��� �ʱ����� �������ش�.
	void initSize();

	std::string  currentDataTime();

	
	

	
	CEdit email_text;
};