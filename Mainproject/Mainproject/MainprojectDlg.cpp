
// MainprojectDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Mainproject.h"
#include "MainprojectDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



/*
src : ������ ����
over : ���� ����
pos : ���� ������ ��ġ(���δ� �ִ� 640, ���δ� 480)
white_era : �������� ����� ���� ��( 0 ~ 255)
*/
void overlayWhiteImage(Mat& src, const Mat& over, const Point& pos, int white_era)
{

	Mat over_gray;
	cv::cvtColor(over, over_gray, COLOR_RGB2GRAY);

	int sx = std::max(pos.x, 0);
	int sy = std::max(pos.y, 0);

	int ex = std::min(pos.x + over.cols, src.cols); // col :�� row : ��
	int ey = std::min(pos.y + over.rows, src.rows);

	Mat imageRoI(src, cv::Rect(sx, sy, ex - sx , ey - sy));

	//����ȭ �ȼ��� 255�� ���� �ʵ��� �Ѵ�.
	if (white_era <= 255)
	{
		Mat mask(white_era - over_gray);
		over.copyTo(imageRoI, mask);
	}

	////������ �����ȿ����� �̸�Ƽ�� ����
	//if ( (pos.x > 0) && (pos.x + over.cols < CAM_WIDTH) &&
	//	(pos.y > 0) && (pos.y + over.rows < CAM_HEIGHT))
	//{
	//	Mat imageRoI(src, cv::Rect(pos.x, pos.y, over.cols, over.rows));

	//	//����ȭ �ȼ��� 255�� ���� �ʵ��� �Ѵ�.
	//	if (white_era < 255)
	//	{
	//		Mat mask(white_era - over_gray);
	//		over.copyTo(imageRoI, mask);
	//	}

	//}

	/*
	int sx = std::max(pos.x, 0);
	int sy = std::max(pos.y, 0);


	//�� �����߿� ª�� ������ �����ٰ� ����.
	int ex = std::min(pos.x + over.cols, src.cols); // col :�� row : ��
	int ey = std::min(pos.y + over.rows, src.rows);

	for (int y = sy; y < ey; y++) {
		int y2 = y - pos.y; // y coordinate in overlay image

		//������ ��ҿ� ������ �� �ִ� ������ ����
		Vec3b* pSrc = src.ptr<Vec3b>(y);
		const Vec3b* pOvr = over.ptr<Vec3b>(y2);

		for (int x = sx; x < ex; x++)
		{
			int x2 = x - pos.x; // x coordinate in overlay image

			float white = (float)(pOvr[x2][0] + pOvr[x2][1] + pOvr[x2][1]) ; //����ä���� ���� 0���� �����

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
src : ������ ����
over : ���� ����
pos : ���� ������ ��ġ
*/
void overlayPngImage(Mat& src, const Mat& over, const Point& pos)
{
	//�������� Ÿ���� �׳� ������, pngŸ������ Ȯ���ϴ� ���� 
	CV_Assert(src.type() == CV_8UC3);
	CV_Assert(over.type() == CV_8UC4);

	int sx = std::max(pos.x, 0);
	int sy = std::max(pos.y, 0);

	//�� �����߿� ª�� ������ �����ٰ� ����.
	int ex = std::min(pos.x + over.cols, src.cols	); // col :�� row : ��
	int ey = std::min(pos.y + over.rows, src.rows);

	for (int y = sy; y < ey; y++) {
	int y2 = y - pos.y; // y coordinate in overlay image

	//������ ��ҿ� ������ �� �ִ� ������ ����
	Vec3b* pSrc = src.ptr<Vec3b>(y);
	const Vec4b* pOvr = over.ptr<Vec4b>(y2);

		for (int x = sx; x < ex; x++)
		{
			int x2 = x - pos.x; // x coordinate in overlay image

			float alpha = (float)pOvr[x2][3] / 255.f; //����ä���� ���� 0���� �����

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
src : ������ ����
over : ���� ����
erase : ����� ����� ���� ��( 0 ~ 255)
mode : 0(���), 1(������)
*/
void overlayBackgroundImage(Mat& src, const Mat& over, int erase, int mode = 0)
{

	Mat over_gray;
	cv::cvtColor(over, over_gray, COLOR_RGB2GRAY);

	Mat tmp(Size(CAM_WIDTH, CAM_HEIGHT), CV_8UC4);

	//����ȭ �ȼ��� 255�� ���� �ʵ��� �Ѵ�.
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

			float alpha = (float)pOvr[x][3] / 255.f; //����ä���� ���� 0���� �����

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

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMainprojectDlg ��ȭ ����
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

// CMainprojectDlg �޽��� ó����

BOOL CMainprojectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	srand((unsigned int)time(NULL)); //���� ��� ����

	//�ʱ� ������ �� ��ġ ����
	initSize();

	//�̸��� ���� edit box ����
	font.CreatePointFont(150, TEXT("�������"));
	GetDlgItem(IDC_EDIT1)->SetFont(&font);

	detect_face = cuda::CascadeClassifier::create("haarcascade_frontalface_default.xml"); // ���ν�

	//��ư�̹��� �ʱ�ȭ
	bit1.LoadBitmapW(IDB_BITMAP1);
	button1.SetBitmap(bit1);

	//bit2.LoadBitmapW(IDB_BITMAP2);
	//take_picture.SetBitmap(bit2);

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cam = new VideoCapture(1);

	if (!cam->isOpened()) { printf("--(!)Error opening video cam\n"); return-1; }

	cam->set(CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
	cam->set(CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

	SetTimer(1000, 30, NULL);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMainprojectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainprojectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CMainprojectDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.////////////////////////////////////////
	
	cam->read(frame); //frame�� ������ ����ִ´�
	GaussianBlur(frame, frame, Size(3, 3), 1.5);

	if (frame.empty())
	{
		MessageBox(_T("ķ�� ���� �����ϴ�. \n"));
	}

	Mat img; // ȸ���̹����� ���� ����
	std::vector<Rect> faces; // ���ν��� ���� ��� �迭
	Mat result; //���� ����� ��� ����


	//� �̸�Ƽ���� ������ ���� ����ġ��
	switch (pick_button)
	{
	case 1:
	{
		emoticon = imread("1.png", -1);

		//gif �޴� ��

		//������
		if (gif_count[0] % 16 == 0) // 16�� �� ������ �ٽ� ������ �޾Ƶ��δ�.
		{
			gif[0].release();
			gif[0].open("dog.gif");

		}

		gif[0] >> dog;
		dog.convertTo(dog, CV_8UC3);
		cv::resize(dog, dog, Size(), 0.15, 0.15);
		gif_count[0]++;

		//�����
		if (gif_count[1] % 8 == 0) // 16�� �� ������ �ٽ� ������ �޾Ƶ��δ�.
		{
			gif[1].release();
			gif[1].open("cat.gif");

		}

		gif[1] >> cat;
		cat.convertTo(cat, CV_8UC3);
		cv::resize(cat, cat, Size(), 0.12, 0.12);
		gif_count[1]++;

		//��Ʈ���
		if (gif_count[2] % 1000 == 0) // 1000�� �� ������ �ٽ� ������ �޾Ƶ��δ�.
		{
			gif[2].release();
			gif[2].open("heart_background.mp4");

				
		}

		for(int i=0; i<2; i++)
			gif[2] >> heart_background;

		cv::cvtColor(heart_background, heart_background, COLOR_BGR2BGRA);
		cv::resize(heart_background, heart_background, Size(CAM_WIDTH, CAM_HEIGHT));

		//����ä�� �����ϴ� ��
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

		if (gif_count[0] % 28 == 0) // 5�� �� ������ �ٽ� ������ �޾Ƶ��δ�.
		{
			
			gif[0].release();
			gif[0].open("rabbit_background.gif");

			
			////���� �߻���Ű��
			rand1 = rand() % 500 + 50;// �¿�� ��Ѹ��� ��
			rand2 = rand() % 400 + 30;
			
			swit[0]++;
		}

		//���� ������ ��� �����ϴ� ���(�ӵ� ���߱� ���ؼ�)
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
			
	cv::cvtColor(frame, img, COLOR_BGR2GRAY); //ķ�� ������ ȸ������ �ٲپ img�� ����

	cv::equalizeHist(img, img); // ��Ȱȭ
	GpuMat frame_gpu(img); // gpumat�� gray �̹����� ����

	GpuMat objbuf; //�ν��� �󱼵��� ��� �뵵
	detect_face->detectMultiScale(frame_gpu, objbuf);//���� �ν�

	detect_face->convert(objbuf, faces); // ��ü���� ǥ�������� ���ͷ� ��ȯ�Ѵ�.

	//�簢���� �� ������ �۾��� ��������.
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
			//������, ����� �̸�Ƽ��
			pos[3] = Point(count_time[0], 390);
			overlayWhiteImage(frame, dog, pos[3], 230);

			cv::rotate(dog, dog, ROTATE_180);

			pos[4] = Point(500 - count_time[0], 0);
			overlayWhiteImage(frame, dog, pos[4], 230);

			//����� �̸�Ƽ��
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
			//������, ����� �̸�Ƽ��

			cv::rotate(dog, dog, ROTATE_90_CLOCKWISE);

			pos[3] = Point(0, count_time[1]);
			overlayWhiteImage(frame, dog, pos[3], 230);

			cv::rotate(dog, dog, ROTATE_180);

			pos[4] = Point(550, 340 - count_time[1]);
			overlayWhiteImage(frame, dog, pos[4], 230);

			//����� �̸�Ƽ��
			pos[5] = Point(count_time[0], 415);
			overlayWhiteImage(frame, cat, pos[5], 200);

			cv::rotate(cat, cat, ROTATE_180);
			pos[6] = Point(555 - count_time[0],0);
			overlayWhiteImage(frame, cat, pos[6], 230);
		}

		// gif �̵��Լ�
		count_time[0] += 6; // ������ ������
		count_time[1] += 4; // ����� ������

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
			Mat tmp; // ��
			Mat tmp2; // ��
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

		//��� ������ֱ�
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				//���� �߻���Ű��
				rand1 = rand() % 15 + 1;// �¿�� ��Ѹ��� ��
				rand2 = rand() % 15 + 1;

				Mat tmp;
				int x = 30 + i * 150 + count_time[1] + 10 * j + rand1; //�ʱ���ġ + �⺻ ���� + �¿� ���� + ���� ������ ���� ���̰Ÿ� + ��Ѹ����
				int y = (j * 150 + count_time[0] + rand1) % 720; //

				cv::resize(emoticon, tmp, Size(), 0.3, 0.3);


				pos[0] = Point(x, y);

				Mat tmp2 = getRotationMatrix2D(Point(tmp.cols / 2, tmp.rows / 2), count_time[9] * (5  *i + j) , 1);
				cv::warpAffine(tmp, tmp, tmp2, tmp.size(), 2, 1, Scalar());

				overlayPngImage(frame, tmp, pos[0]);
			}

		}
		//���� ȸ����Ű�� ���� ���� ī����
		count_time[9]++;

		//���� �Ʒ��� �������� �ϴ� ȿ��
		if (count_time[0] > 720)
			count_time[0] = 0;
		//���� �¿�� �𳯸��� �ϴ� ȿ��
		if (count_time[1] > 15 || count_time[1] < -15)
			add_count_time2 *= -1;

		count_time[0] ++;
		count_time[1] += add_count_time2;

		//����Ű�� �Ӹ���
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
	
	//���� ���� �ҷ�����
	cv::flip(frame, frame, 1);
	//���� ���� �̹����� ����!
	//blur(frame, frame, Size(2, 2));
	//medianBlur(frame, frame, 3);
	//GaussianBlur(frame, frame, Size(3, 3), 1.5);
	//Mat bilateral;
	//cv::bilateralFilter(frame, bilateral, 2, 15, 15);
	result = frame.clone();


//��ư Ÿ�̸� ����
if(time_flag == 1)
	end = system_clock::now();

now_time = duration_cast<duration<double>>(end - start);
if (now_time.count() > 3)
{
	take_picture.SetWindowTextW(_T("ġ��"));

	if (now_time.count() > 3.5)
	{
		//�̾ȿ��� ������ ��� �̸��Ϸ� ������
		imwrite("capture_image.jpg", frame);

		take_picture.SetWindowTextW(_T("���� �Կ�"));

		//NewDialog dig;
		//dig.DoModal();

		//email_text.GetWindowTextW(email_string); // �̸��� �ּ�!
		//wchar_t *email_wchar = email_string.GetBuffer();

		//// ������ ���Ͽ� ���� ������ ���� ����ü
		//MapiMessageW tips_msg;
		//// �����ڿ� �����ڿ� ���� ������ ���� ����ü
		//MapiRecipDescW from_user, to_user;

		//// MAPI�� ����ϱ� ���Ͽ� MAPI32.DLL�� �����Ѵ�.
		//HINSTANCE h_send_mail = ::LoadLibrary(L"MAPI32.DLL");
		//if (NULL != h_send_mail) {
		//	// MAPI32.DLL�� ���ԵǾ� �ִ� MAPISendMailW �Լ��� �ּҸ� ��´�.
		//	LPMAPISENDMAILW fp_send_mail = (LPMAPISENDMAILW)GetProcAddress(h_send_mail,
		//		"MAPISendMailW");
		//	if (fp_send_mail != NULL) {
		//		// ���� ���ۿ� ����� ����ü���� ��� �ʱ�ȭ
		//		memset(&tips_msg, 0, sizeof(MapiMessageW));
		//		memset(&from_user, 0, sizeof(MapiRecipDescW));
		//		memset(&to_user, 0, sizeof(MapiRecipDescW));

		//		// ������ ������ ����� ������ �����Ѵ�. ( From. User )
		//		from_user.ulRecipClass = MAPI_ORIG;
		//		from_user.lpszAddress = from_user.lpszName = L"mqjinwon@gmail.com";

		//		// ������ ������ ����� ������ �����Ѵ�. ( To. User )
		//		to_user.ulRecipClass = MAPI_TO;
		//		to_user.lpszName = email_wchar;
		//		// ���� �ּ� �տ� "SMTP:"�� �ٿ����� ����� ���۵�
		//		to_user.lpszAddress = L"SMTP:";

		//		// tips_msg ����ü�� ������ ������ �ּҸ� �����Ѵ�.
		//		tips_msg.lpOriginator = &from_user;
		//		// �����ڰ� 1������ ����Ѵ�.
		//		tips_msg.nRecipCount = 1;
		//		// tips_msg ����ü�� ������ ������ �ּҸ� �����Ѵ�.
		//		tips_msg.lpRecips = &to_user;

		//		// ���� ������ �����Ѵ�.
		//		tips_msg.lpszSubject = L"����쿡�� ���� �����帳�ϴ�.";
		//		// ���� ������ ���´�.
		//		tips_msg.lpszNoteText = L"���α׷� ������ּż� �����մϴ�!!";

		//		// tips_msg�� ������ ���� ������ 
		//		// �ü���� ��ġ�� �⺻ ���� �ý����� ����Ͽ� �����Ѵ�.
		//		(*fp_send_mail)(0, (ULONG)m_hWnd, &tips_msg, MAPI_NEW_SESSION |
		//			MAPI_LOGON_UI, 0);
		//	}

		//	::FreeLibrary(h_send_mail); // MAPI32.DLL�� ������ ����
		//}
		//�ٽ� �ʱ�ȭ
		start = system_clock::now();
		end = system_clock::now();
		time_flag = 0;
	}

}
else if (now_time.count() > 2)
take_picture.SetWindowTextW(_T("1"));
else if (now_time.count() > 1)
take_picture.SetWindowTextW(_T("2"));

	///////////////////mfc�� ���� �ҷ�����//////////////////////
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

void CMainprojectDlg::OnBnClickedButton1()// ��ư Ŭ������ ��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pick_button = 1;

	//�迭�� 0���� �ʱ�ȭ
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}
void CMainprojectDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pick_button = 2;

	//�迭�� 0���� �ʱ�ȭ
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}
void CMainprojectDlg::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pick_button = 3;

	//�迭�� 0���� �ʱ�ȭ
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}
void CMainprojectDlg::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	pick_button = 4;

	//�迭�� 0���� �ʱ�ȭ
	std::fill_n(count_time, 10, 0);
	std::fill_n(gif_count, 5, 0);
	std::fill_n(swit, 3, 0);
}

//�����Կ���ư
void CMainprojectDlg::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	time_flag = 1;
	start = system_clock::now();
	take_picture.SetWindowTextW(_T("3"));
}

void CMainprojectDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//������ �ִ������
	lpMMI->ptMaxTrackSize.x = 10000; //2560;
	lpMMI->ptMaxTrackSize.y = 10000; //1440;
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

//�ʱ� ũ�� �������ִ� �Լ�
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







