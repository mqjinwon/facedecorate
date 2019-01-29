
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.

//////////////////////내가 정의한 include파일들//////////////////////
#include <iostream>
#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <vector>
#include <tbb\tbb.h>

//랜덤함수를 위해서
#include <cstdlib>
#include <ctime>

//시간을 측정하기 위해
#include <chrono>

//메일 전송하기 위한 라이브러리
#include <MAPI.h>

//실시간
#include <cstdio> 
#include <ctime>

//#include "NewDialog.h"

/************라이브러리 불러오기 용************/
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

//병렬프로그래밍
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
/************라이브러리 불러오기 용************/

using namespace std;
using namespace cv;
using namespace cv::cuda;
using namespace chrono;

#define CAM_WIDTH 640
#define CAM_HEIGHT 480

//이모티콘 변수들
// add the second parameter "-1" as flag, to make sure the transparancy channel is read!


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


