// LightDialog.cpp: 实现文件
//

#include "pch.h"
#include "CG2022112453游坤坤.h"
#include "afxdialogex.h"
#include "LightDialog.h"


// LightDialog 对话框

IMPLEMENT_DYNAMIC(LightDialog, CDialogEx)

LightDialog::LightDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LIGHT, pParent)
{

}

LightDialog::~LightDialog()
{
}

void LightDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LightDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &LightDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// LightDialog 消息处理程序

void LightDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

BOOL LightDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

