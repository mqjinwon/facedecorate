// NewDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Mainproject.h"
#include "NewDialog.h"
#include "afxdialogex.h"


// NewDialog ��ȭ �����Դϴ�.

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


// NewDialog �޽��� ó�����Դϴ�.
