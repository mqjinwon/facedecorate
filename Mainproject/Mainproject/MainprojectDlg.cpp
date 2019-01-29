
// MainprojectDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Mainproject.h"
#include "MainprojectDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/*
src : 덮어질 사진
over : 덮을 사진
pos : 덮을 사진의 위치(가로는 최대 640, 세로는 480)
white_era : 흰색배경을 지우기 위한 값( 0 ~ 255)
*/
void overlayWhiteImage(Mat& src, const Mat& over, const Point& pos, int white_era)
{

	Mat over_gray;
	cv::cvtColor(over, over_gray, COLOR_RGB2GRAY);

	int sx = std::max(pos.x, 0);
	int sy = std::max(pos.y, 0);

	int ex = std::min(pos.x + over.cols, src.cols); // col :열 row : 행
	int ey = std::min(pos.y + over.rows, src.rows);

	Mat imageRoI(src, cv::Rect(sx, sy, ex - sx , ey - sy));

	//이진화 픽셀이 255를 넘지 않도록 한다.
	if (white_era <= 255)
	{
		Mat mask(white_era - over_gray);
		over.copyTo(imageRoI, mask);
	}

	////사진의 범위안에서만 이모티콘 생성
	//if ( (pos.x > 0) && (pos.x + over.cols < CAM_WIDTH) &&
	//	(pos.y > 0) && (pos.y + over.rows < CAM_HEIGHT))
	//{
	//	Mat imageRoI(src, cv::Rect(pos.x, pos.y, over.cols, over.rows));

	//	//이진화 픽셀이 255를 넘지 않도록 한다.
	//	if (white_era < 255)
	//	{
	//		Mat mask(white_era - over_gray);
	//		over.copyTo(imageRoI, mask);
	//	}

	//}

	/*
	int sx = std::max(pos.x, 0);
	int sy = std::max(pos.y, 0);


	//두 사진중에 짧은 사진을 가져다가 쓴다.
	int ex = std::min(pos.x + over.cols, src.cols); // col :열 row : 행
	int ey = std::min(pos.y + over.rows, src.rows);

	for (int y = sy; y < ey; y++) {
		int y2 = y - pos.y; // y coordinate in overlay image

		//각각의 요소에 접근할 수 있는 포인터 생성
		Vec3b* pSrc = src.ptr<Vec3b>(y);
		const Vec3b* pOvr = over.ptr<Vec3b>(y2);

		for (int x = sx; x < ex; x++)
		{
			int x2 = x - pos.x; // x coordinate in overlay image

			float white = (float)(pOvr[x2][0] + pOvr[x2][1] + pOvr[x2][1]) ; //알파채널을 거의 0으로 만든다

			if (white < white_era)
			{
				pSrc[x][0] = saturate_cast<uchar>(pSrc[x][0] * 0
					+ pOvr[x2][0]);
				pSrc[x][1] = saturate_cast<uchar>(pSrc[x][1] * 0
					+ pOvr[x2][1]);
				pSrc[x][2] = saturate_cast<uchar>(pSrc[x][2] * 0
					+ pOvr[x2][2]);
			}
		}
	}
	*/
}

/*
src : 덮어질 사진
over : 덮을 사진
pos : 덮을 사진의 위치
*/
void overlayPngImage(Mat& src, const Mat& over, const Point& pos)
{
	//이파일의 타입이 그냥 사진과, png타입인지 확인하는 과정 
	CV_Assert(src.type() == CV_8UC3);
	CV_Assert(over.type() == CV_8UC4);

	int sx = std::max(pos.x, 0);
	int sy = std::max(pos.y, 0);

	//두 사진중에 짧은 사진을 가져다가 쓴다.
	int ex = std::min(pos.x + over.cols, src.cols	); // col :열 row : 행
	int ey = std::min(pos.y + over.rows, src.rows);

	for (int y = sy; y < ey; y++) {
	int y2 = y - pos.y; // y coordinate in overlay image

	//각각의 요소에 접근할 수 있는 포인터 생성
	Vec3b* pSrc = src.ptr<Vec3b>(y);
	const Vec4b* pOvr = over.ptr<Vec4b>(y2);

		for (int x = sx; x < ex; x++)
		{
			int x2 = x - pos.x; // x coordinate in overlay image

			float alpha = (float)pOvr[x2][3] / 255.f; //알파채널을 거의 0으로 만든다

			if (alpha > 0.f)
			{
			pSrc[x][0] = saturate_cast<uchar>(pSrc[x][0] * (1.f - alpha)
			+ pOvr[x2][0] * alpha);
			pSrc[x][1] = saturate_cast<uchar>(pSrc[x][1] * (1.f - alpha)
			+ pOvr[x2][1] * alpha);
			pSrc[x][2] = saturate_cast<uchar>(pSrc[x][2] * (1.f - alpha)
			+ pOvr[x2][2] * alpha);
			}
		}
	}
	
	
}

/*
src : 덮어질 사진
over : 덮을 사진
erase : 배경을 지우기 위한 값( 0 ~ 255)
mode : 0(흰색), 1(검정색)
*/
void overlayBackgroundImage(Mat& src, const Mat& over, int erase, int mode = 0)
{

	Mat over_gray;
	cv::cvtColor(over, over_gray, COLOR_RGB2GRAY);

	Mat tmp(Size(CAM_WIDTH, CAM_HEIGHT), CV_8UC4);

	//이진화 픽셀이 255를 넘지 않도록 한다.
	switch (mode)
	{
	case 0 :
	{
		if (erase < 255)
		{
			Mat mask(erase - over_gray);
			over.copyTo(tmp, mask);
		}

	break;
	}
	case 1 : 
	{
		if (erase < 255)
		{
			Mat mask(over_gray - erase);
			over.copyTo(tmp, mask);
		}
	}
	break;
	}

	
	for (int y = 0; y < CAM_HEIGHT; y++) {


		Vec3b* pSrc = src.ptr<Vec3b>(y);
		const Vec4b* pOvr = tmp.ptr<Vec4b>(y);

		for (int x = 0; x < CAM_WIDTH; x++)
		{

			float alpha = (float)pOvr[x][3] / 255.f; //알파채널을 거의 0으로 만든다

			if (alpha > 0.f)
			{
				pSrc[x][0] = saturate_cast<uchar>(pSrc[x][0] * (1.f - alpha)
					+ pOvr[x][0] * alpha);
				pSrc[x][1] = saturate_cast<uchar>(pSrc[x][1] * (1.f - alpha)
					+ pOvr[x][1] * alpha);
				pSrc[x][2] = saturate_cast<uchar>(pSrc[x][2] * (1.f - alpha)
					+ pOvr[x][2] * alpha);
			}


		}
	}
	

}

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainprojectDlg 대화 상자
CMainprojectDlg::CMainprojectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAINPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainprojectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_PICTURE, m_Frame);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_BUTTON1, button1);
	DDX_Control(pDX, IDC_BUTTON2, button2);
	DDX_Control(pDX, IDC_BUTTON3, button3);
	DDX_Control(pDX, IDC_BUTTON4, button4);
	DDX_Control(pDX, IDC_BUTTON7, take_picture);
	DDX_Control(pDX, IDC_EDIT1, email_text);
}

BEGIN_MESSAGE_MAP(CMainprojectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CMainprojectDlg::OnBnClickedButton1)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BUTTON2, &CMainprojectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMainprojectDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMainprojectDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CMainprojectDlg::OnBnClickedButton7)
END_MESSAGE_MAP()

// CMainprojectDlg 메시지 처리기

BOOL CMainprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	srand((unsigned int)time(NULL)); //랜덤 계수 설정

	//초기 사이즈 및 위치 선정
	initSize();

	//이메일 전송 edit box 설정
	font.CreatePointFont(150, TEXT("나눔고딕"));
	GetDlgItem(IDC_EDIT1)->SetFont(&font);

	detect_face = cuda::CascadeClassifier::create("haarcascade_frontalface_default.xml"); // 얼굴인식

	//버튼이미지 초기화
	bit1.LoadBitmapW(IDB_BITMAP1);
	button1.SetBitmap(bit1);

	//bit2.LoadBitmapW(IDB_BITMAP2);
	//take_picture.SetBitmap(bit2);

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cam = new VideoCapture(1);

	if (!cam->isOpened()) { printf("--(!)Error opening video cam\n"); return-1; }

	cam->set(CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	cam->set(CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

	SetTimer(1000, 30, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMainprojectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMainprojectDlg::OnPaint()
{
	if (IsIconic())
	{

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMainprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainprojectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CMainprojectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.////////////////////////////////////////
	
	cam->read(frame); //frame에 영상을 집어넣는다
	GaussianBlur(frame, frame, Size(3, 3), 1.5);

	if (frame.empty())
	{
		MessageBox(_T("캠을 열수 없습니다. \n"));
	}

	Mat img; // 회색이미지를 담을 변수
	std::vector<Rect> faces; // 얼굴인식한 것을 담는 배열
	Mat result; //최종 결과를 담는 변수


	//어떤 이모티콘을 받을지 고르는 스위치문
	switch (pick_button)
	{
	case 1:
	{
		emoticon = imread("1.png", -1);

		//gif 받는 법

		//강아지
		if (gif_count[0] % 16 == 0) // 16번 다 돌고나면 다시 비디오를 받아들인다.
		{
			gif[0].release();
			gif[0].open("dog.gif");

		}

		gif[0] >> dog;
		dog.convertTo(dog, CV_8UC3);
		cv::resize(dog, dog, Size(), 0.15, 0.15);
		gif_count[0]++;

		//고양이
		if (gif_count[1] % 8 == 0) // 16번 다 돌고나면 다시 비디오를 받아들인다.
		{
			gif[1].release();
			gif[1].open("cat.gif");

		}

		gif[1] >> cat;
		cat.convertTo(cat, CV_8UC3);
		cv::resize(cat, cat, Size(), 0.12, 0.12);
		gif_count[1]++;

		//하트배경
		if (gif_count[2] % 1000 == 0) // 1000번 다 돌고나면 다시 비디오를 받아들인다.
		{
			gif[2].release();
			gif[2].open("heart_background.mp4");

				
		}

		for(int i=0; i<2; i++)
			gif[2] >> heart_background;

		cv::cvtColor(heart_background, heart_background, COLOR_BGR2BGRA);
		cv::resize(heart_background, heart_background, Size(CAM_WIDTH, CAM_HEIGHT));

		//알파채널 설정하는 법
		cv::MatIterator_< cv::Vec3b> itd = heart_background.begin< cv::Vec3b>(), itd_end = heart_background.end< cv::Vec3b>();
		for (int i = 0; itd != itd_end; ++itd, ++i)
		{
			cv::Vec3b bgr = (*itd);

			(*itd)[3] = 180;
		}

		gif_count[2]++;
		break;
	}

	case 2:
	{

		emoticon = imread("2.png", -1);
		emoticon_sec = imread("2_sec.png", -1);

		if (gif_count[0] % 28 == 0) // 5번 다 돌고나면 다시 비디오를 받아들인다.
		{
			
			gif[0].release();
			gif[0].open("rabbit_background.gif");

			
			////난수 발생시키기
			rand1 = rand() % 500 + 50;// 좌우로 흩뿌리기 용
			rand2 = rand() % 400 + 30;
			
			swit[0]++;
		}

		//같은 프레임 계속 돌게하는 방법(속도 늦추기 위해서)
		if (swit[1] % 4 == 0)
			gif[0] >> rabbit_background;
		else
			rabbit_background = pre_emotiocn.clone();

		rabbit_background.convertTo(rabbit_background, CV_8UC3);

		gif_count[0]++;
		swit[1]++;

		break;
	}
	case 3:
	{
		emoticon = imread("3.png", -1);
		emoticon_sec = imread("3_sec.png", -1);
		break;
	}
	case 4:
	{
		break;
	}
	case 5:
	{
		break;
	}
	}
			
	cv::cvtColor(frame, img, COLOR_BGR2GRAY); //캠의 사진을 회색으로 바꾸어서 img에 저장

	cv::equalizeHist(img, img); // 평활화
	GpuMat frame_gpu(img); // gpumat에 gray 이미지를 저장

	GpuMat objbuf; //인식한 얼굴들을 담는 용도
	detect_face->detectMultiScale(frame_gpu, objbuf);//다중 인식

	detect_face->convert(objbuf, faces); // 물체들을 표준형태의 벡터로 변환한다.

	//사각형을 다 가지고 작업을 수행하자.
	switch (pick_button)
	{
	case 1:
	{
		overlayBackgroundImage(frame, heart_background, 50, 1);

		for (Rect face : faces)
		{
			Mat tmp;			

			float fx = float(face.width) / emoticon.cols;

			cv::resize(emoticon, tmp, Size(), fx * 0.15, fx * 0.15);

			pos[1] = Point(face.x + (face.width*0.2), face.y + face.height * 0.6);
			pos[2] = Point(face.x + (face.width*0.7), face.y + face.height * 0.6);

			overlayPngImage(frame, tmp, pos[1]);
			overlayPngImage(frame, tmp, pos[2]);

		}

		if (swit[0] % 2 ==  0)
		{
			//강아지, 고양이 이모티콘
			pos[3] = Point(count_time[0], 390);
			overlayWhiteImage(frame, dog, pos[3], 230);

			cv::rotate(dog, dog, ROTATE_180);

			pos[4] = Point(500 - count_time[0], 0);
			overlayWhiteImage(frame, dog, pos[4], 230);

			//고양이 이모티콘
			//cv::flip(cat, cat, 1);
			cv::rotate(cat, cat, ROTATE_90_CLOCKWISE);
			pos[5] = Point(0, count_time[1]);
			overlayWhiteImage(frame, cat, pos[5], 200);

			cv::rotate(cat, cat, ROTATE_180);
			pos[6] = Point(578, 340 - count_time[1]);
			overlayWhiteImage(frame, cat, pos[6], 230);
		}
		else 
		{
			//강아지, 고양이 이모티콘

			cv::rotate(dog, dog, ROTATE_90_CLOCKWISE);

			pos[3] = Point(0, count_time[1]);
			overlayWhiteImage(frame, dog, pos[3], 230);

			cv::rotate(dog, dog, ROTATE_180);

			pos[4] = Point(550, 340 - count_time[1]);
			overlayWhiteImage(frame, dog, pos[4], 230);

			//고양이 이모티콘
			pos[5] = Point(count_time[0], 415);
			overlayWhiteImage(frame, cat, pos[5], 200);

			cv::rotate(cat, cat, ROTATE_180);
			pos[6] = Point(555 - count_time[0],0);
			overlayWhiteImage(frame, cat, pos[6], 230);
		}

		// gif 이동함수
		count_time[0] += 6; // 강아지 움직임
		count_time[1] += 4; // 고양이 움직임

		if (count_time[0] > 510)
		{
			count_time[0] = 0;
			count_time[1] = 0;
			swit[0]++;
		}

		break;
	}
	case 2:

		for (Rect face : faces)
		{
			Mat tmp; // 귀
			Mat tmp2; // 코
			float fx = float(face.width) / emoticon.cols;

			cv::resize(emoticon, tmp, Size(), fx , fx);
			cv::resize(emoticon_sec, tmp2, Size(), fx*0.5, fx*0.5);

			pos[0] = Point(face.x , face.y - face.height * 0.5);
			pos[1] = Point(face.x + face.width * 0.27, face.y + face.height * 0.35);

			overlayPngImage(frame, tmp, pos[0]);
			overlayPngImage(frame, tmp2, pos[1]);
		}


		if(!rabbit_background.empty())
		{
			pos[2] = Point(rand1, rand2);
			pre_emotiocn = rabbit_background.clone();
			cv::resize(rabbit_background, rabbit_background, Size(), 0.2, 0.2);
			cv::flip(rabbit_background, rabbit_background, 1);
			overlayWhiteImage(frame, rabbit_background, pos[2], 255);
		}

		

		break;
	case 3:
		srand((unsigned int)time(NULL));

		//배경 눈깔아주기
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				//난수 발생시키기
				rand1 = rand() % 15 + 1;// 좌우로 흩뿌리기 용
				rand2 = rand() % 15 + 1;

				Mat tmp;
				int x = 30 + i * 150 + count_time[1] + 10 * j + rand1; //초기위치 + 기본 간격 + 좌우 떨림 + 다음 라인의 눈과 차이거리 + 흩뿌리기용
				int y = (j * 150 + count_time[0] + rand1) % 720; //

				cv::resize(emoticon, tmp, Size(), 0.3, 0.3);


				pos[0] = Point(x, y);

				Mat tmp2 = getRotationMatrix2D(Point(tmp.cols / 2, tmp.rows / 2), count_time[9] * (5  *i + j) , 1);
				cv::warpAffine(tmp, tmp, tmp2, tmp.size(), 2, 1, Scalar());

				overlayPngImage(frame, tmp, pos[0]);
			}

		}
		//눈을 회전시키기 위한 각도 카운터
		count_time[9]++;

		//눈이 아래로 떨어지게 하는 효과
		if (count_time[0] > 720)
			count_time[0] = 0;
		//눈이 좌우로 흩날리게 하는 효과
		if (count_time[1] > 15 || count_time[1] < -15)
			add_count_time2 *= -1;

		count_time[0] ++;
		count_time[1] += add_count_time2;

		//에스키모 머리띠
		for (Rect face : faces) {
			Mat tmp;
			float fx = float(face.width) / emoticon_sec.cols;

			cv::resize(emoticon_sec, tmp, Size(), fx*0.9, fx*0.9);

			pos[0] = Point(face.x , face.y - face.height * 0.35);
			overlayPngImage(frame, tmp, pos[0]);
		}

		break;

	case 4:
		
		break;
	}
	
	//최종 사진 불러오기
	cv::flip(frame, frame, 1);
	//블러는 원본 이미지에 적기!
	//blur(frame, frame, Size(2, 2));
	//medianBlur(frame, frame, 3);
	//GaussianBlur(frame, frame, Size(3, 3), 1.5);
	//Mat bilateral;
	//cv::bilateralFilter(frame, bilateral, 2, 15, 15);
	result = frame.clone();


//버튼 타이머 설정
if(time_flag == 1)
	end = system_clock::now();

now_time = duration_cast<duration<double>>(end - start);
if (now_time.count() > 3)
{
	take_picture.SetWindowTextW(_T("치즈"));

	if (now_time.count() > 3.5)
	{
		//이안에서 사진을 찍고 이메일로 보내기
		imwrite("capture_image.jpg", frame);

		take_picture.SetWindowTextW(_T("사진 촬영"));

		//NewDialog dig;
		//dig.DoModal();

		//email_text.GetWindowTextW(email_string); // 이메일 주소!
		//wchar_t *email_wchar = email_string.GetBuffer();

		//// 전송할 메일에 대한 정보를 담을 구조체
		//MapiMessageW tips_msg;
		//// 전송자와 수신자에 대한 정보를 담을 구조체
		//MapiRecipDescW from_user, to_user;

		//// MAPI를 사용하기 위하여 MAPI32.DLL을 연결한다.
		//HINSTANCE h_send_mail = ::LoadLibrary(L"MAPI32.DLL");
		//if (NULL != h_send_mail) {
		//	// MAPI32.DLL에 포함되어 있는 MAPISendMailW 함수의 주소를 얻는다.
		//	LPMAPISENDMAILW fp_send_mail = (LPMAPISENDMAILW)GetProcAddress(h_send_mail,
		//		"MAPISendMailW");
		//	if (fp_send_mail != NULL) {
		//		// 메일 전송에 사용할 구조체들을 모두 초기화
		//		memset(&tips_msg, 0, sizeof(MapiMessageW));
		//		memset(&from_user, 0, sizeof(MapiRecipDescW));
		//		memset(&to_user, 0, sizeof(MapiRecipDescW));

		//		// 메일을 전송할 사용자 정보를 구성한다. ( From. User )
		//		from_user.ulRecipClass = MAPI_ORIG;
		//		from_user.lpszAddress = from_user.lpszName = L"mqjinwon@gmail.com";

		//		// 메일을 수신할 사용자 정보를 구성한다. ( To. User )
		//		to_user.ulRecipClass = MAPI_TO;
		//		to_user.lpszName = email_wchar;
		//		// 메일 주소 앞에 "SMTP:"를 붙여야지 제대로 전송됨
		//		to_user.lpszAddress = L"SMTP:";

		//		// tips_msg 구조체에 전송자 정보의 주소를 저장한다.
		//		tips_msg.lpOriginator = &from_user;
		//		// 수신자가 1명임을 명시한다.
		//		tips_msg.nRecipCount = 1;
		//		// tips_msg 구조체에 수신자 정보의 주소를 저장한다.
		//		tips_msg.lpRecips = &to_user;

		//		// 메일 제목을 저장한다.
		//		tips_msg.lpszSubject = L"지노우에서 사진 보내드립니다.";
		//		// 메일 내용을 적는다.
		//		tips_msg.lpszNoteText = L"프로그램 사용해주셔서 감사합니다!!";

		//		// tips_msg에 구성된 메일 정보를 
		//		// 운영체제에 설치된 기본 메일 시스템을 사용하여 전송한다.
		//		(*fp_send_mail)(0, (ULONG)m_hWnd, &tips_msg, MAPI_NEW_SESSION |
		//			MAPI_LOGON_UI, 0);
		//	}

		//	::FreeLibrary(h_send_mail); // MAPI32.DLL과 연결을 해제
		//}
		//다시 초기화
		start = system_clock::now();
		end = system_clock::now();
		time_flag = 0;
	}

}
else if (now_time.count() > 2)
take_picture.SetWindowTextW(_T("1"));
else if (now_time.count() > 1)
take_picture.SetWindowTextW(_T("2"));

	///////////////////mfc에 사진 불러오기//////////////////////
	int bpp = 8 * result.elemSize();
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
		padding = 4 - (result.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	//32 bit image is always DWORD aligned because each pixel requires 4 bytes
	if (bpp < 32)
	{
		border = 4 - (result.cols % 4);
	}

	Mat mat_temp;
	if (border > 0 || result.isContinuous() == false)
	{
		// Adding needed columns on the right (max 3 px)
		cv::copyMakeBorder(result, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = result;
	}

	RECT r;
	m_picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	cimage_mfc.Create(winSize.width, winSize.height, 24);

	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = bpp;
	bitInfo.bmiHeader.biWidth = mat_temp.cols;
	bitInfo.bmiHeader.biHeight = -mat_temp.rows;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;

	// Image is bigger or smaller than into destination rectangle
	// we use stretch in full rect

	if (mat_temp.cols == winSize.width  && mat_temp.rows == winSize.height)
	{
		// source and destination have same size
		// transfer memory block
		// NOTE: the padding border will be shown here. Anyway it will be max 3px width

		SetDIBitsToDevice(cimage_mfc.GetDC(),
			//destination rectangle
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, &bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		// destination rectangle
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		// rectangle defined on source bitmap
		// using imgWidth instead of mat_temp.cols will ignore the padding border
		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(cimage_mfc.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	HDC dc = ::GetDC(m_picture.m_hWnd);
	cimage_mfc.BitBlt(dc, 0, 0);

	::ReleaseDC(m_picture.m_hWnd, dc);

	cimage_mfc.ReleaseDC();
	cimage_mfc.Destroy();

	CDialogEx::OnTimer(nIDEvent);
}

void CMainprojectDlg::OnBnClickedButton1()// 버튼 클릭했을 때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pick_button = 1;

	//배열들 0으로 초기화
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}
void CMainprojectDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pick_button = 2;

	//배열들 0으로 초기화
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}
void CMainprojectDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pick_button = 3;

	//배열들 0으로 초기화
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}
void CMainprojectDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	pick_button = 4;

	//배열들 0으로 초기화
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}

//사진촬영버튼
void CMainprojectDlg::OnBnClickedButton7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	time_flag = 1;
	start = system_clock::now();
	take_picture.SetWindowTextW(_T("3"));
}

void CMainprojectDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//윈도우 최대사이즈
	lpMMI->ptMaxTrackSize.x = 10000; //2560;
	lpMMI->ptMaxTrackSize.y = 10000; //1440;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

//초기 크기 설정해주는 함수
void CMainprojectDlg::initSize()
{
	button1.MoveWindow(30, 770, 100, 50);
	button2.MoveWindow(180, 770, 100, 50);
	button3.MoveWindow(330, 770, 100, 50);
	button4.MoveWindow(480, 770, 100, 50);
	email_text.MoveWindow(825, 770, 300, 50);
	take_picture.MoveWindow(1170, 770, 100, 50);
	m_picture.MoveWindow(20, 15, 1280, 720);
}







