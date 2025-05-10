// MyDialog.cpp: 实现文件
//

#include "pch.h"
#include "CG2022112453游坤坤.h"
#include "afxdialogex.h"
#include "MyDialog.h"


// MyDialog 对话框

IMPLEMENT_DYNAMIC(MyDialog, CDialogEx)

MyDialog::MyDialog(CWnd* pParent)
	: CDialogEx(IDD_DIALOG_Sphere, pParent),
	type(type)
	, radius(0.5)
	, slice(40)
	, mstack(20)
	, xpos(0)
	, ypos(0)
	, zpos(0)
	, len(0.5)
	, height(0.5)
	, width(0.5)
{

}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &MyDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// MyDialog 消息处理程序

void MyDialog::drawSphere()
{
	int ids[] = { IDC_EDIT_LEN ,IDC_EDIT_WIDTH ,IDC_EDIT_HEIGHT,
	IDC_STATIC_LEN ,IDC_STATIC_WIDTH ,IDC_STATIC_HEIGHT };

	hideItems(ids, 6);
	// 刷新对话框以确保控件立即隐藏
	Invalidate();
	UpdateWindow();
}

void MyDialog::drawCube()
{
	int ids[] = { IDC_EDIT_RADIUS ,IDC_EDIT_SLICE,IDC_EDIT_STACKE,
		IDC_STATIC_R , IDC_STATIC_SLICE, IDC_STATIC_STACK };

	hideItems(ids, 6);
	// 刷新窗口
	this->Invalidate();
	this->UpdateWindow();
}

void MyDialog::hideItem(int nId)
{
	CWnd* item = GetDlgItem(nId);
	if (item)
		item->ShowWindow(SW_HIDE);
}

void MyDialog::hideItems(int nIds[], int len)
{
	for (int i = 0; i < len; i++)
	{
		hideItem(nIds[i]);
	}
}

void MyDialog::OnBnClickedOk()
{
	CDialogEx::OnOK();
}



BOOL MyDialog::OnInitDialog()
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
