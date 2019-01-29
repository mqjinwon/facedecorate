
// MainprojectDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#define pi 3.141592653589793238462643383279



// CMainprojectDlg 대화 상자
class CMainprojectDlg : public CDialogEx
{
// 생성입니다.
public:
	CMainprojectDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CStatic m_Frame;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	//버튼 골라주는 변수
	int pick_button = 0;

	//이모티콘 변수
	Mat emoticon;
	Mat emoticon_sec;
	Mat pre_emotiocn;

	//위치변수
	Point pos[10];

	//시간변수
	int count_time[10] = { 0, };
	int add_count_time2 = 2;

	//시간재는 변수
	system_clock::time_point start = system_clock::now();
	system_clock::time_point end = system_clock::now();
	duration<double> now_time;
	int time_flag = 0;

	//이메일 담는 변수
	CString email_string;

	//난수용 변수
	int rand1 = 0;
	int rand2 = 0;

	//gif들을 위한 변수
	VideoCapture gif[5];
	Mat dog, cat, heart_background, rabbit_background;
	int gif_count[5] = { 0, };
	int swit[3] = { 0, };
	

	//버튼이미지 변수
	CBitmap bit1;
	CBitmap bit2;

	//editbox 각종 설정
	CFont font;

	//비디오 캡처변수
	VideoCapture *cam;
	Mat frame;
	CImage cimage_mfc;
	CStatic m_picture;

	//버튼 변수
	CButton button1;
	CButton button2;
	CButton button3;
	CButton button4;
	CButton take_picture;


	//얼굴인식용
	cv::Ptr<cuda::CascadeClassifier> detect_face;

	//정의 함수들
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton7();

	//컨트롤들의 초기사이즈를 지정해준다.
	void initSize();

	std::string  currentDataTime();

	
	

	
	CEdit email_text;
};