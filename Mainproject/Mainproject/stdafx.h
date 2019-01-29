
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.

//////////////////////���� ������ include���ϵ�//////////////////////
#include <iostream>
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <vector>
#include <tbb\tbb.h>

//�����Լ��� ���ؼ�
#include <cstdlib>
#include <ctime>

//�ð��� �����ϱ� ����
#include <chrono>

//���� �����ϱ� ���� ���̺귯��
#include <MAPI.h>

//�ǽð�
#include <cstdio> 
#include <ctime>

//#include "NewDialog.h"

/************���̺귯�� �ҷ����� ��************/
#ifdef _DEBUG               
//opencv & cuda
#pragma comment(lib, "opencv_core400d.lib")       
#pragma comment(lib, "opencv_highgui400d.lib")    
#pragma comment(lib, "opencv_imgcodecs400d.lib")  
#pragma comment(lib, "opencv_objdetect400d.lib")  
#pragma comment(lib, "opencv_imgproc400d.lib")  
#pragma comment(lib,"opencv_video400d.lib")
#pragma comment(lib, "opencv_videoio400d.lib")    
#pragma comment(lib, "opencv_cudaobjdetect400d.lib")  
#pragma comment(lib, "opencv_cudawarping400d.lib")
#pragma comment(lib, "opencv_cudaimgproc400d.lib")
#pragma comment(lib, "opencv_cudabgsegm400d.lib")  
#pragma comment(lib, "opencv_cudaoptflow400d.lib") 

//�������α׷���
#pragma comment(lib, "tbb.lib") 

#else       
#pragma comment(lib, "opencv_core400.lib")       
#pragma comment(lib, "opencv_highgui400.lib")    
#pragma comment(lib, "opencv_imgcodecs400.lib")    
#pragma comment(lib, "opencv_objdetect400.lib")  
#pragma comment(lib, "opencv_imgproc400.lib")  
#pragma comment(lib,"opencv_video400.lib")
#pragma comment(lib, "opencv_videoio400.lib")    
#pragma comment(lib, "opencv_cudaobjdetect400.lib")
#pragma comment(lib, "opencv_cudawarping400.lib")
#pragma comment(lib, "opencv_cudaimgproc400.lib")
#pragma comment(lib, "opencv_cudabgsegm400.lib")  
#pragma comment(lib, "opencv_cudaoptflow400.lib") 
#endif        
/************���̺귯�� �ҷ����� ��************/

using namespace std;
using namespace cv;
using namespace cv::cuda;
using namespace chrono;

#define CAM_WIDTH 640
#define CAM_HEIGHT 480

//�̸�Ƽ�� ������
// add the second parameter "-1" as flag, to make sure the transparancy channel is read!


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


