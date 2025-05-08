// SphereDialog.cpp: 实现文件
//

#include "pch.h"
#include "CG2022112453游坤坤.h"
#include "afxdialogex.h"
#include "SphereDialog.h"


// SphereDialog 对话框

IMPLEMENT_DYNAMIC(SphereDialog, CDialogEx)

SphereDialog::SphereDialog(CWnd* pParent)
	: CDialogEx(IDD_DIALOG_Sphere, pParent),
	type(type)
	, radius(0.5)
	, slice(40)
	, mstack(20)
	, xpos(0)
	, ypos(0)
	, zpos(0)
	,len(0.5)
	, height(0.5)
	, width(0.5)
{

}

SphereDialog::~SphereDialog()
{
}

void SphereDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_RADIUS, radius);
	DDX_Text(pDX, IDC_EDIT_SLICE, slice);
	DDX_Text(pDX, IDC_EDIT_STACKE, mstack);
	DDX_Text(pDX, IDC_EDIT_X, xpos);
	DDX_Text(pDX, IDC_EDIT_Y, ypos);
	DDX_Text(pDX, IDC_EDIT_Z, zpos);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, height);
	DDX_Text(pDX, IDC_EDIT_LEN, len);
	DDX_Text(pDX, IDC_EDIT_WIDTH, width);
}


BEGIN_MESSAGE_MAP(SphereDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &SphereDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// SphereDialog 消息处理程序

void SphereDialog::drawSphere()
{
	CWnd* pEditLen = GetDlgItem(IDC_EDIT_LEN);
	CWnd* pStaticLen = GetDlgItem(IDC_STATIC_LEN);
	CWnd* pEditWidth = GetDlgItem(IDC_EDIT_WIDTH);
	CWnd* pStaticWidth = GetDlgItem(IDC_STATIC_WIDTH);
	CWnd* pEditHeight = GetDlgItem(IDC_EDIT_HEIGHT);
	CWnd* pStaticHeight = GetDlgItem(IDC_STATIC_HEIGHT);

	if (pEditLen)     pEditLen->ShowWindow(SW_HIDE);
	if (pStaticLen)   pStaticLen->ShowWindow(SW_HIDE);
	if (pEditWidth)   pEditWidth->ShowWindow(SW_HIDE);
	if (pStaticWidth) pStaticWidth->ShowWindow(SW_HIDE);
	if (pEditHeight)  pEditHeight->ShowWindow(SW_HIDE);
	if (pStaticHeight)pStaticHeight->ShowWindow(SW_HIDE);

	// 可选：刷新对话框以确保控件立即隐藏
	Invalidate();
	UpdateWindow();
}

void SphereDialog::drawCube()
{
	// 方法一：直接使用 GetDlgItem (不需要 DDX_Control)
	CWnd* pEdit = GetDlgItem(IDC_EDIT_RADIUS);
	CWnd* pStatic = GetDlgItem(IDC_STATIC_R);

	if (pEdit) pEdit->ShowWindow(SW_HIDE);
	if (pStatic) pStatic->ShowWindow(SW_HIDE);

	// 刷新窗口
	this->Invalidate();
	this->UpdateWindow();
}

void SphereDialog::OnBnClickedOk()
{
	CDialogEx::OnOK();
}



BOOL SphereDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (type == DrawType::SPHERE)
	{
		this->drawSphere();
	}
	else if (type == DrawType::CUBE)
	{
		drawCube();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
