// SphereDialog.cpp: ʵ���ļ�
//

#include "pch.h"
#include "CG2022112453������.h"
#include "afxdialogex.h"
#include "SphereDialog.h"


// SphereDialog �Ի���

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


// SphereDialog ��Ϣ�������

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

	// ��ѡ��ˢ�¶Ի�����ȷ���ؼ���������
	Invalidate();
	UpdateWindow();
}

void SphereDialog::drawCube()
{
	// ����һ��ֱ��ʹ�� GetDlgItem (����Ҫ DDX_Control)
	CWnd* pEdit = GetDlgItem(IDC_EDIT_RADIUS);
	CWnd* pStatic = GetDlgItem(IDC_STATIC_R);

	if (pEdit) pEdit->ShowWindow(SW_HIDE);
	if (pStatic) pStatic->ShowWindow(SW_HIDE);

	// ˢ�´���
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
	// �쳣: OCX ����ҳӦ���� FALSE
}
