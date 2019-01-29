// NewDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Mainproject.h"
#include "NewDialog.h"
#include "afxdialogex.h"


// NewDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(NewDialog, CDialogEx)

NewDialog::NewDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

NewDialog::~NewDialog()
{
}

void NewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewDialog, CDialogEx)
END_MESSAGE_MAP()


// NewDialog 메시지 처리기입니다.
